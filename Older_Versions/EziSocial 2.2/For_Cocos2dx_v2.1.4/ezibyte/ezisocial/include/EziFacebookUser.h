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

class EziFacebookUser: public cocos2d::CCObject
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
    
public:
    
    EziFacebookUser();
    virtual ~EziFacebookUser();
    
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
    
    bool isGameInstalled();
    
    void saveUserPhotoPath(std::string photoPath);

    const char* getPhotoPath();
};

#endif /* defined(__FacebookGameDemo__EziFacebookUser__) */
