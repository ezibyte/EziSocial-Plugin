//
//  EziSocialDelegate.h
//  EziSocial
//
//  Created by Paras Mendiratta on 15/04/13.
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


#ifndef FacebookGameDemo_EziSocialDelegate_h
#define FacebookGameDemo_EziSocialDelegate_h

#include "cocos2d.h"
#include "EziFacebookUser.h"

class EziFacebookDelegate
{
public:
    virtual void fbSessionCallback(int responseCode, const char* responseMessage) {}
    virtual void fbUserDetailCallback(int responseCode, const char* responseMessage, EziFacebookUser* fbUser) {}
    virtual void fbMessageCallback(int responseCode, const char* responseMessage) {}
    
    virtual void fbSendRequestCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friendsGotRequests) {}
    virtual void fbRecieveRequestCallback(int responseCode,
                                          const char* message,
                                          const char* senderName, cocos2d::CCDictionary* dataDictionary) {}
    
    virtual void fbPageLikeCallback(int responseCode, const char* responseMessage) {}
    virtual void fbFriendsCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* friends) {}
    virtual void fbHighScoresCallback(int responseCode, const char* responseMessage, cocos2d::CCArray* highScores) {}
    
    virtual void fbUserPhotoCallback(const char *userPhotoPath) {}
    
    virtual void fbPostPhotoCallback(int responseCode, const char* responseMessage) {}
    virtual void fbIncomingRequestCallback(int responseCode, const char* responseMessage, int totalIncomingRequests) {}
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
