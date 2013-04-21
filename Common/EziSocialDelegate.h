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

class EziFacebookDelegate
{
public:
    virtual void fbSessionCallback(int responseCode) = 0;
    virtual void fbUserDetailCallback(cocos2d::CCDictionary* data) = 0;
    virtual void fbMessageCallback(int responseCode) = 0;
    virtual void fbChallengeCallback(int responseCode) = 0;
    virtual void fbGiftCallback(int responseCode) = 0;
    virtual void fbPageLikeCallback(int responseCode) = 0;
    virtual void fbFriendsCallback(cocos2d::CCArray* friends) = 0;
    virtual void fbHighScoresCallback(cocos2d::CCArray* highScores) = 0;
};

class EziEmailDelegate
{
public:
    virtual void mailCallback(int responseCode) = 0;
};

class EziTwitterDelegate
{
    
public:
    virtual void twSessionCallback(int responseCode) = 0;
};

#endif
