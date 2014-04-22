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
#include "network/HttpClient.h"
#include "EziFacebookUserBase.h"

using namespace cocos2d;
using namespace cocos2d::network;

#include "EziSocialDefinition.h"

class EziFacebookUser: public EziFacebookUserBase
{
public:
    
    EziFacebookUser();
    virtual ~EziFacebookUser();
    
    void saveData(const std::string &key, const std::string &dataValue);
    
    const std::string &getUserName() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const std::string &getHomeTown() const;
    const std::string &getPresentLocation() const;
    const std::string &getAccessToken() const;
    const std::string &getEmailID() const;
    const std::string &getGender() const;
    const std::string &getFullName() const;
    const std::string &getBirthday() const;
    
    bool isGameInstalled() const;
    
    void saveUserPhotoPath(const std::string &photoPath);
    
    const std::string &getPhotoPath() const;
    
private:
    
    std::string _username;
    std::string _firstName;
    std::string _lastName;
    mutable std::string _fullname;
    
    std::string _hometown;
    std::string _presentLocation;
    std::string _birthday;
    std::string _accessToken;
    std::string _emailID;
    std::string _gender;
    bool        _installed;
    std::string _userPhotoPath;
    
};

#endif /* defined(__FacebookGameDemo__EziFacebookUser__) */
