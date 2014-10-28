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
#include <string>
#include <map>
#include "cocos2d.h"
#include "EziSocialDefinition.h"
#include "EziFacebookFriend.h"

#define REQUEST_CONSUMED_STATUS_    "REQUEST_CONSUMED_STATUS_"


class EziFBIncomingRequest : public cocos2d::Ref
{
public:
    
    // Static create methods
    static EziFBIncomingRequest* create();
    static EziFBIncomingRequest* createForRequestID(std::string requestID);
    
    // Destructor
    virtual ~EziFBIncomingRequest();
    
    // Setter
    void setReceiverID(const std::string &receiverID);
    void setMessage(const std::string &message);
    void setSender(const std::string &fbID, const std::string &username);
    void setSender(EziFacebookFriend* sender);
    void setRequestID(const std::string &requestID);
    void setDataDictionary(const std::unordered_map<std::string,std::string> &dataDictionary);
    void setDataFetchedFromFacebook(bool dataFetched);
    void setConsumed(bool consumed);
    void setRequestType(EziSocialWrapperNS::FB_REQUEST::TYPE requestType);
    
    // Getter
    const std::string &getReceiverID() const;
    const std::string &getRequestID() const;
    const std::string &getMessage() const;
    bool isConsumed() const;
    bool isDataFetchedFromServer() const;
    const std::unordered_map<std::string,std::string> &getDataDictionary() const;
    EziFacebookFriend* getSender() const;
    EziSocialWrapperNS::FB_REQUEST::TYPE getRequestType() const;
    
    // Save to persistant storage
    void saveToUserDefaults();
    
    void purgeFromUserDefault();
    
    // Useful to when you want to save the EziFBIncomingRequest Object in CCArray or CCDictionary.
    EziFBIncomingRequest* clone() const;
    
private:
    EziFBIncomingRequest();
    EziSocialWrapperNS::FB_REQUEST::TYPE _requestType;
    
    // Receiver's Facebook ID. This is important because if user change facebook login on device then he should not see other Facebook
    // user's request.
    
    std::string _receiverID;
    
    // This is gift dictionary or any other item dictionary.
    std::unordered_map<std::string,std::string> _dataDictionary;
    
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
    
    void setData(const std::string &key, const std::string &data);
    
};

#endif /* defined(__FacebookGameDemo__EziFBIncomingRequest__) */
