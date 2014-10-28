//
//  EziFacebookFriend.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#ifndef __FacebookGameDemo__EziFacebookFriend__
#define __FacebookGameDemo__EziFacebookFriend__

#include <iostream>
#include "cocos2d.h"
#include "EziSocialDefinition.h"

USING_NS_CC;

class EziFacebookFriend : public CCObject
{
    std::string _name;
    std::string _fbID;
    std::string _photoPath;
    std::string _photoURL;
    
    bool _installed;
    long _facebookScore;
    
    CCSprite* _profilePic;

    EziFacebookFriend();
    
public:
    
    static EziFacebookFriend* create();

    ~EziFacebookFriend();
    
    void setName(const char* newName);
    void setID(const char* newFBID);
    void setScore(long newScore);
    void setInstalled(bool newInstalled);
    void setPhotoPath(const char* newPhotoPath);
    void setPhotoURL(const char* newPhotoURL);
    
    const char* getName();
    const char* getFBID();
    long getScore();
    bool isInstalled();
    const char* getPhotoPath();
    const char* getPhotoURL();
    
    void saveData(const char* data, const char* key);
    
    CCSprite* getProfilePic(cocos2d::CCLayer *sender, bool forceDownload, EziPhotoCallback callback);
    
    virtual CCObject* copyWithZone(CCZone *pZone);
    
    
    
private:
    
    CCLayer* _target;
    void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    EziPhotoCallback _selector;
    //SEL_MenuHandler    m_pfnSelector;

};

#endif /* defined(__FacebookGameDemo__EziFacebookFriend__) */
