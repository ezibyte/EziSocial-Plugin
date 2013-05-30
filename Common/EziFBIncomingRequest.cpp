//
//  EziFBIncomingRequest.cpp
//  EziSocial
//
//  Created by Paras Mendiratta on 20/05/13.
//  Copyright @EziByte 2013 (http://www.ezibyte.com)
//
//  Version 1.2 (Dt: 30-May-2013)
//
/***
 
 This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source distribution.
 
 */
#include "EziFBIncomingRequest.h"
#include "EziSocialObject.h"

#define DATA_DICTIONARY_            "DATA_DICTIONARY_"
#define FB_INCOMING_REQUEST_DATA_   "FB_INCOMING_REQUEST_DATA_"

// Constructor
EziFBIncomingRequest::EziFBIncomingRequest()
{
    _requestType    = EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE;
    _dataDictionary = NULL;
    _sender         = NULL;
    _message        = "";
    _requestID      = "";
    _receiverID     = "";
    _consumed       = false;
    _dataFetchedFromFacebook = false;
    
}

// Destructor
EziFBIncomingRequest::~EziFBIncomingRequest()
{
    if (_dataDictionary != NULL)
    {
        _dataDictionary->release();
    }
    
    if (_sender != NULL)
    {
        _sender->release();
    }
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
        
        std::string requestData = CCUserDefault::sharedUserDefault()->getStringForKey(key.c_str());
        std::string dictionaryString = CCUserDefault::sharedUserDefault()->getStringForKey(dataKey.c_str());
        bool toConsumed = CCUserDefault::sharedUserDefault()->getBoolForKey(statusKey.c_str());
        
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
            CCDictionary *dataDictionary = CCDictionary::create();
            
            for (int j=0; j<dataDictionaryVector.size(); j += 2)
            {
                dataDictionary->setObject(CCString::create(dataDictionaryVector[j+1]), dataDictionaryVector[j]);
            }
            
            fbRequest->setDataDictionary(dataDictionary);
        }
    }
    
    return fbRequest;
}

// Setter
void EziFBIncomingRequest::setMessage(std::string message)
{
    this->_message = message;
}
void EziFBIncomingRequest::setSender(std::string fbID, std::string username)
{
    this->_sender = EziFacebookFriend::create();
    this->_sender->setID(fbID.c_str());
    this->_sender->setName(username.c_str());
    this->_sender->retain();
}

void EziFBIncomingRequest::setSender(EziFacebookFriend* sender)
{
    this->_sender = sender;
}

void EziFBIncomingRequest::setRequestType(EziSocialWrapperNS::FB_REQUEST::TYPE requestType)
{
    _requestType = requestType;
}

void EziFBIncomingRequest::setRequestID(std::string requestID)
{
    this->_requestID = requestID;
}

void EziFBIncomingRequest::setDataDictionary(cocos2d::CCDictionary *dataDictionary)
{
    this->_dataDictionary = dataDictionary;
    this->_dataDictionary->retain();
}


void EziFBIncomingRequest::setConsumed(bool consumed)
{
    this->_consumed = consumed;
}

void EziFBIncomingRequest::setReceiverID(std::string receiverID)
{
    this->_receiverID = receiverID;
}

 
void EziFBIncomingRequest::setDataFetchedFromFacebook(bool dataFetched)
{
    this->_dataFetchedFromFacebook = dataFetched;
}

// Getter
const char* EziFBIncomingRequest::getRequestID()
{
    return _requestID.c_str();
}

const char* EziFBIncomingRequest::getMessage()
{
    return _message.c_str();
}

bool EziFBIncomingRequest::isConsumed()
{
    return _consumed;
}

bool EziFBIncomingRequest::isDataFetchedFromServer()
{
    return _dataFetchedFromFacebook;
}

CCDictionary* EziFBIncomingRequest::getDataDictionary()
{
    return _dataDictionary;
}

EziFacebookFriend* EziFBIncomingRequest::getSender()
{
    return _sender;
}

const char* EziFBIncomingRequest::getReceiverID()
{
    return _receiverID.c_str();
}
void EziFBIncomingRequest::setData(std::string key, std::string data)
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
            _sender = EziFacebookFriend::create();
            _sender->retain();
            
        }
        _sender->setID(data.c_str());
    }
    else if (key.compare("SENDER_NAME")==0)
    {
        if (this->_sender == NULL)
        {
            _sender = EziFacebookFriend::create();
            _sender->retain();
        }
        _sender->setName(data.c_str());
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
    
    CCString* requestType = CCString::createWithFormat("%d", _requestType);
    
    // Add the request type
    dataToSave.append("REQUEST_TYPE;").append(requestType->getCString()).append(";");
    
    // Add reciever ID
    dataToSave.append("TO;").append(_receiverID).append(";");
    
    // Add request ID
    dataToSave.append("REQUEST_ID;").append(_requestID).append(";");
    
    // Add Message
    dataToSave.append("MESSAGE;").append(_message).append(";");
    
    // Add Sender ID
    dataToSave.append("SENDER_ID;").append(_sender->getFBID()).append(";");
    
    // Add Sender Name
    dataToSave.append("SENDER_NAME;").append(_sender->getName()).append(";");
    
    // Build Dictionary Data
    std::string dictionaryToSave = "";
    
    if (_dataDictionary)
    {
        CCArray* dataKeys = _dataDictionary->allKeys();
        
        if (dataKeys)
        {
            for (int i=0; i<dataKeys->count(); i++)
            {
                CCString* currentKey = (CCString*) dataKeys->objectAtIndex(i);
                CCString* dataObject = (CCString*)(_dataDictionary->objectForKey(currentKey->getCString()));
                
                dictionaryToSave.append(currentKey->getCString()).append(";");
                dictionaryToSave.append(dataObject->getCString()).append(";");
            }
        }
        
    }
    
    std::string dictionaryKey = DATA_DICTIONARY_;
    dictionaryKey.append(_requestID);
    
    std::string statusKey = REQUEST_CONSUMED_STATUS_;
    statusKey.append(_requestID);
    
    CCUserDefault::sharedUserDefault()->setStringForKey(key.c_str(), dataToSave);
    CCUserDefault::sharedUserDefault()->setStringForKey(dictionaryKey.c_str(), dictionaryToSave);
    CCUserDefault::sharedUserDefault()->setBoolForKey(statusKey.c_str(), _consumed);
    
    CCUserDefault::sharedUserDefault()->flush();

}

void EziFBIncomingRequest::purgeFromUserDefault()
{
    std::string dataKey = FB_INCOMING_REQUEST_DATA_;
    dataKey.append(_requestID);
    
    std::string dictionaryKey = DATA_DICTIONARY_;
    dictionaryKey.append(_requestID);
    
    std::string statusKey = REQUEST_CONSUMED_STATUS_;
    statusKey.append(_requestID);
    
    CCUserDefault::sharedUserDefault()->setStringForKey(dataKey.c_str(), "");
    CCUserDefault::sharedUserDefault()->setStringForKey(dictionaryKey.c_str(), "");
    CCUserDefault::sharedUserDefault()->setBoolForKey(statusKey.c_str(), true);
    CCUserDefault::sharedUserDefault()->flush();
}

EziSocialWrapperNS::FB_REQUEST::TYPE EziFBIncomingRequest::getRequestType()
{
    return _requestType;
}

// Useful to when you want to save the EziFBIncomingRequest Object in CCArray or CCDictionary.
CCObject* EziFBIncomingRequest::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    EziFBIncomingRequest* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (EziFBIncomingRequest*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new EziFBIncomingRequest();
        pNewZone = new CCZone(pCopy);
    }
    
    pCopy->setReceiverID(getReceiverID());
    pCopy->setSender(getSender());
    pCopy->setRequestID(getRequestID());
    pCopy->setMessage(getMessage());
    pCopy->setConsumed(isConsumed());
    pCopy->setDataDictionary(getDataDictionary());
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}


