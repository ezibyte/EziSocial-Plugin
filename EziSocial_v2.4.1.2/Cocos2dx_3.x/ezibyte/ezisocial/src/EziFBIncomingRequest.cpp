//
//  EziFBIncomingRequest.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#include "EziFBIncomingRequest.h"
#include "EziSocialObject.h"

#define DATA_DICTIONARY_            "DATA_DICTIONARY_"
#define FB_INCOMING_REQUEST_DATA_   "FB_INCOMING_REQUEST_DATA_"

// Constructor
EziFBIncomingRequest::EziFBIncomingRequest()
:_requestType(EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE)
,_sender(nullptr)
,_consumed(false)
,_dataFetchedFromFacebook(false)
{
}

// Destructor
EziFBIncomingRequest::~EziFBIncomingRequest()
{
    CC_SAFE_RELEASE(_sender);
}

EziFBIncomingRequest* EziFBIncomingRequest::create()
{
    EziFBIncomingRequest* fbRequest = new EziFBIncomingRequest();
    if (fbRequest)
    {
        fbRequest->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(fbRequest);
        return NULL;
    }
    
    return fbRequest;
}


EziFBIncomingRequest* EziFBIncomingRequest::createForRequestID(std::string requestID)
{
    EziFBIncomingRequest* fbRequest = EziFBIncomingRequest::create();
    
    if (fbRequest)
    {
        fbRequest->setRequestID(requestID);
        
        // Build the items from CCUserDefaults
        std::string key = FB_INCOMING_REQUEST_DATA_;
        key.append(requestID);
        
        std::string dataKey = DATA_DICTIONARY_;
        dataKey.append(requestID);
        
        std::string statusKey = REQUEST_CONSUMED_STATUS_;
        statusKey.append(requestID);
        
        std::string requestData = cocos2d::UserDefault::getInstance()->getStringForKey(key.c_str());
        std::string dictionaryString = cocos2d::UserDefault::getInstance()->getStringForKey(dataKey.c_str());
        bool toConsumed = cocos2d::UserDefault::getInstance()->getBoolForKey(statusKey.c_str());
        
        // Mark it as consumed or not.
        fbRequest->setConsumed(toConsumed);
        
        // We need to break Request Data String and Data Dictionary String
        
        std::vector< std::string > requestDataVector    = EziSocialObject::tokenizeStr(requestData.c_str(), ";");
        std::vector< std::string > dataDictionaryVector = EziSocialObject::tokenizeStr(dictionaryString.c_str(), ";");
        
        if (requestData.size()==0)
        {
            // Data is not fetched from the Facebook.
            fbRequest->setDataFetchedFromFacebook(false);
        }
        else
        {
            fbRequest->setDataFetchedFromFacebook(true);
        }
        
        // Save the Request Data
        for (int i=0; i<requestDataVector.size(); i += 2)
        {
            fbRequest->setData(requestDataVector[i], requestDataVector[i+1]);
        }
        
        // Build the Data Dictionary
        if (dataDictionaryVector.size()%2 == 0 && dataDictionaryVector.size() > 0) // It should be of even size.
        {
            for (int j=0; j<dataDictionaryVector.size(); j += 2)
            {
                fbRequest->_dataDictionary[dataDictionaryVector[j]] = dataDictionaryVector[j+1];
            }
        }
    }
    
    return fbRequest;
}

// Setter
void EziFBIncomingRequest::setMessage(const std::string &message)
{
    _message = message;
}
void EziFBIncomingRequest::setSender(const std::string &fbID, const std::string &username)
{
    _sender = EziFacebookFriend::create(fbID,username);
    _sender->retain();
}

void EziFBIncomingRequest::setSender(EziFacebookFriend* sender)
{
    CC_SAFE_RETAIN(sender);
    CC_SAFE_RELEASE(_sender);
    _sender = sender;
}

void EziFBIncomingRequest::setRequestType(EziSocialWrapperNS::FB_REQUEST::TYPE requestType)
{
    _requestType = requestType;
}

void EziFBIncomingRequest::setRequestID(const std::string &requestID)
{
    _requestID = requestID;
}

void EziFBIncomingRequest::setDataDictionary(const std::unordered_map<std::string,std::string> &dataDictionary)
{
    _dataDictionary = dataDictionary;
}


void EziFBIncomingRequest::setConsumed(bool consumed)
{
    _consumed = consumed;
}

void EziFBIncomingRequest::setReceiverID(const std::string &receiverID)
{
    _receiverID = receiverID;
}


void EziFBIncomingRequest::setDataFetchedFromFacebook(bool dataFetched)
{
    this->_dataFetchedFromFacebook = dataFetched;
}

// Getter
const std::string& EziFBIncomingRequest::getRequestID() const
{
    return _requestID;
}

const std::string& EziFBIncomingRequest::getMessage() const
{
    return _message;
}

bool EziFBIncomingRequest::isConsumed() const
{
    return _consumed;
}

bool EziFBIncomingRequest::isDataFetchedFromServer() const
{
    return _dataFetchedFromFacebook;
}

const std::unordered_map<std::string,std::string> &EziFBIncomingRequest::getDataDictionary() const
{
    return _dataDictionary;
}

EziFacebookFriend* EziFBIncomingRequest::getSender() const
{
    return _sender;
}

const std::string& EziFBIncomingRequest::getReceiverID() const
{
    return _receiverID;
}
void EziFBIncomingRequest::setData(const std::string &key, const std::string &data)
{
    
    if (key.compare("REQUEST_TYPE")==0)
    {
        int requestType = atoi(data.c_str());
        switch (requestType)
        {
            case EziSocialWrapperNS::FB_REQUEST::REQUEST_CHALLENGE:
                _requestType = EziSocialWrapperNS::FB_REQUEST::REQUEST_CHALLENGE;
                break;
                
            case EziSocialWrapperNS::FB_REQUEST::REQUEST_GIFT:
                _requestType = EziSocialWrapperNS::FB_REQUEST::REQUEST_GIFT;
                break;
                
            case EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE:
                _requestType = EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE;
                break;
                
            case EziSocialWrapperNS::FB_REQUEST::REQUEST_CUSTOM:
                _requestType = EziSocialWrapperNS::FB_REQUEST::REQUEST_CUSTOM;
                break;

                
            default:
                break;
        }
        
    }
    else if (key.compare("REQUEST_ID")==0)
    {
        this->setRequestID(data);
    }
    else if (key.compare("MESSAGE")==0)
    {
        this->setMessage(data);
    }
    else if (key.compare("SENDER_ID")==0)
    {
        if (this->_sender == NULL)
        {
            _sender = EziFacebookFriend::create("");
            _sender->retain();
        }
        _sender->_profileID = data;
    }
    else if (key.compare("SENDER_NAME")==0)
    {
        if (this->_sender == NULL)
        {
            _sender = EziFacebookFriend::create("");
            _sender->retain();
        }
        _sender->_name = data;
    }
    else if (key.compare("TO")==0)
    {
        this->setReceiverID(data);
    }
    else
    {
        CCLOGERROR("Unrecognized Key in EziFBIncomingRequest = %s", key.c_str());
    }
}

// Save to persistant storage
void EziFBIncomingRequest::saveToUserDefaults()
{
    std::string dataToSave = "";
    std::string key = FB_INCOMING_REQUEST_DATA_;
    key.append(_requestID);
    
    char requestType[20] = {};
    snprintf(requestType, 20, "%d", _requestType);
    
    // Add the request type
    dataToSave.append("REQUEST_TYPE;").append(requestType).append(";");
    
    // Add reciever ID
    dataToSave.append("TO;").append(_receiverID).append(";");
    
    // Add request ID
    dataToSave.append("REQUEST_ID;").append(_requestID).append(";");
    
    // Add Message
    dataToSave.append("MESSAGE;").append(_message).append(";");
    
    // Add Sender ID
    dataToSave.append("SENDER_ID;").append(_sender->getProfileID()).append(";");
    
    // Add Sender Name
    dataToSave.append("SENDER_NAME;").append(_sender->getName()).append(";");
    
    // Build Dictionary Data
    std::string dictionaryToSave = "";
    
    if (!_dataDictionary.empty())
    {
        for(auto &it : _dataDictionary)
        {
            dictionaryToSave.append(it.first).append(";");
            dictionaryToSave.append(it.second).append(";");
        }
    }
    
    std::string dictionaryKey = DATA_DICTIONARY_;
    dictionaryKey.append(_requestID);
    
    std::string statusKey = REQUEST_CONSUMED_STATUS_;
    statusKey.append(_requestID);
    
    cocos2d::UserDefault::getInstance()->setStringForKey(key.c_str(), dataToSave);
    cocos2d::UserDefault::getInstance()->setStringForKey(dictionaryKey.c_str(), dictionaryToSave);
    cocos2d::UserDefault::getInstance()->setBoolForKey(statusKey.c_str(), _consumed);
    
    cocos2d::UserDefault::getInstance()->flush();
    
}

void EziFBIncomingRequest::purgeFromUserDefault()
{
    std::string dataKey = FB_INCOMING_REQUEST_DATA_;
    dataKey.append(_requestID);
    
    std::string dictionaryKey = DATA_DICTIONARY_;
    dictionaryKey.append(_requestID);
    
    std::string statusKey = REQUEST_CONSUMED_STATUS_;
    statusKey.append(_requestID);
    
    cocos2d::UserDefault::getInstance()->setStringForKey(dataKey.c_str(), "");
    cocos2d::UserDefault::getInstance()->setStringForKey(dictionaryKey.c_str(), "");
    cocos2d::UserDefault::getInstance()->setBoolForKey(statusKey.c_str(), true);
    cocos2d::UserDefault::getInstance()->flush();
}

EziSocialWrapperNS::FB_REQUEST::TYPE EziFBIncomingRequest::getRequestType() const
{
    return _requestType;
}

// Useful to when you want to save the EziFBIncomingRequest Object in CCArray or CCDictionary.
EziFBIncomingRequest* EziFBIncomingRequest::clone() const
{
    EziFBIncomingRequest* pCopy = EziFBIncomingRequest::create();
    
    pCopy->setReceiverID(getReceiverID());
    pCopy->setSender(getSender());
    pCopy->setRequestID(getRequestID());
    pCopy->setMessage(getMessage());
    pCopy->setConsumed(isConsumed());
    pCopy->setDataDictionary(getDataDictionary());
    
    return pCopy;
}


