//
//  EziFBIncomingRequest.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#ifndef __FacebookGameDemo__EziFBIncomingRequest__
#define __FacebookGameDemo__EziFBIncomingRequest__

#include <iostream>
#include "cocos2d.h"
#include "EziSocialDefinition.h"
#include "EziFacebookFriend.h"

#define REQUEST_CONSUMED_STATUS_    "REQUEST_CONSUMED_STATUS_"

USING_NS_CC;

class EziFBIncomingRequest : public cocos2d::CCObject
{
    EziFBIncomingRequest();
    EziSocialWrapperNS::FB_REQUEST::TYPE _requestType;
    
    // Receiver's Facebook ID. This is important because if user change facebook login on device then he should not see other Facebook
    // user's request.
    
    std::string _receiverID;
    
    // This is gift dictionary or any other item dictionary.
    CCDictionary* _dataDictionary;
    
    // Friend who has sent the request.
    EziFacebookFriend* _sender;
    
    // Message came along with the request.
    std::string _message;
    
    // Facebook Request ID.
    std::string _requestID;
    
    // Call this when you have actually used this request in game.
    bool _consumed;
    
    // This is called if the data is already fetched from the server.
    // In case data is not fetched then you need to fetch the data first.
    bool _dataFetchedFromFacebook;
    
    void setData(std::string key, std::string data);
    
public:
    
    // Static create methods
    static EziFBIncomingRequest* create();
    static EziFBIncomingRequest* createForRequestID(std::string requestID);
    
    // Destructor
    virtual ~EziFBIncomingRequest();

    // Setter
    void setReceiverID(std::string receiverID);
    void setMessage(std::string message);
    void setSender(std::string fbID, std::string username);
    void setSender(EziFacebookFriend* sender);
    void setRequestID(std::string requestID);
    void setDataDictionary(CCDictionary* dataDictionary);
    void setDataFetchedFromFacebook(bool dataFetched);
    void setConsumed(bool consumed);
    void setRequestType(EziSocialWrapperNS::FB_REQUEST::TYPE requestType);
    
    // Getter
    const char* getReceiverID();
    const char* getRequestID();
    const char* getMessage();
    bool isConsumed();
    bool isDataFetchedFromServer();
    CCDictionary* getDataDictionary();
    EziFacebookFriend* getSender();
    EziSocialWrapperNS::FB_REQUEST::TYPE getRequestType();

    // Save to persistant storage
    void saveToUserDefaults();
    
    void purgeFromUserDefault();
    
    // Useful to when you want to save the EziFBIncomingRequest Object in CCArray or CCDictionary.
    virtual CCObject* copyWithZone(CCZone *pZone);

};

#endif /* defined(__FacebookGameDemo__EziFBIncomingRequest__) */
