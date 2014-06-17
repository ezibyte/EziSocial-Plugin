//
//  EziSocialDelegate.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 15/04/13.
//
//

#ifndef FacebookGameDemo_EziSocialDelegate_h
#define FacebookGameDemo_EziSocialDelegate_h

#include "cocos2d.h"
#include "EziFacebookUser.h"
#include "EziFacebookFriend.h"
//#include "EziSocialDefinition.h"

class EziFacebookDelegate
{
public:
    virtual void fbSessionCallback(int responseCode, const char* responseMessage) {}
    virtual void fbUserDetailCallback(int responseCode,
                                      const char* responseMessage,
                                      EziFacebookUser* fbUser) {}
    
    virtual void fbMessageCallback(int responseCode, const char* responseMessage) {}
    
    virtual void fbSendRequestCallback(int responseCode,
                                       const char* responseMessage,
                                       const std::vector<std::string> &friendsGotRequests) {}
    
    virtual void fbRecieveRequestCallback(int responseCode,
                                          const char* message,
                                          const char* senderName, const std::unordered_map<std::string,std::string> &dataDictionary) {}
    
    virtual void fbPageLikeCallback(int responseCode, const char* responseMessage) {}
    virtual void fbFriendsCallback(int responseCode, const char* responseMessage, const std::vector<EziFacebookFriend*> friends) {}
    virtual void fbHighScoresCallback(int responseCode, const char* responseMessage, const std::vector<EziFacebookFriend*> &highScores) {}
        
    virtual void fbPostPhotoCallback(int responseCode, const char* responseMessage) {}
    virtual void fbIncomingRequestCallback(int responseCode, const char* responseMessage, int totalIncomingRequests) {}
    
    virtual void fbShareDialogCallback(int responseCode, const char* responseMessage) {}
    
    virtual void fbOpenGraphCallback(int responseCode, const char* responseMessage) {}
    virtual void fbAchievementCallback(int responseCode, const char* responseMessage) {}
};

class EziEmailDelegate
{
public:
    
    // This only works in iOS. Android doesn't provide any response.
    virtual void mailCallback(int responseCode) {}
};

class EziTwitterDelegate
{
    
public:
    // This only works in iOS. Android doesn't provide any response.
    virtual void twitterCallback(int responseCode) {}
};

#endif
