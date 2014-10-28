//
//  EziFacebookUser.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 17/05/13.
//
//

#ifndef __FacebookGameDemo__EziFacebookUser__
#define __FacebookGameDemo__EziFacebookUser__

#include <iostream>
#include "cocos2d.h"
#include "EziSocialDefinition.h"

USING_NS_CC;

class EziFacebookUser: public CCObject
{
    
    std::string username;
    std::string firstName;
    std::string lastName;
    std::string fullname;
    std::string profileID;
    std::string hometown;
    std::string presentLocation;
    std::string accessToken;
    std::string emailID;
    std::string gender;
    bool        installed;
    std::string userPhotoPath;
    std::string _photoURL;
    std::string _birthday;
    
    CCSprite* _profilePic;

    
public:
    
    EziFacebookUser();
    virtual ~EziFacebookUser();
    
    void setPhotoURL(const char* newPhotoURL);
    
    
    void saveData(const char* key, std::string dataValue);
    
    const char*  getUserName();
    const char*  getFirstName();
    const char*  getLastName();
    const char*  getProfileID();
    const char*  getHomeTown();
    const char*  getPresentLocation();
    const char*  getAccessToken();
    const char*  getEmailID();
    const char*  getGender();
    const char*  getFullName();
    const char*  getPhotoURL();
    const char*  getBirthday();
    
    bool isGameInstalled();
    
    void saveUserPhotoPath(std::string photoPath);

    const char* getPhotoPath();
    
    CCSprite* getProfilePic(cocos2d::CCLayer *sender, bool forceDownload, EziPhotoCallback callback);
    
private:
    
    EziPhotoCallback _selector;
    CCLayer* _target;
    void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    //EziFacebookDelegate::EziPhotoCallback _selector;
    
    
};

#endif /* defined(__FacebookGameDemo__EziFacebookUser__) */
