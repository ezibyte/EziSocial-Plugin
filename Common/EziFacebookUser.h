//
//  EziFacebookUser.h
//  EziSocial
//
//  Created by Paras Mendiratta on 17/05/13.
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
#ifndef __FacebookGameDemo__EziFacebookUser__
#define __FacebookGameDemo__EziFacebookUser__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

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
    std::string userPhotoPath;
    
    EziFacebookUser();
    
public:
    
    virtual ~EziFacebookUser();
    
    static EziFacebookUser* create();
    
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
        
    void saveUserPhotoPath(std::string photoPath);

    const char* getPhotoPath();
    
    CCObject* copyWithZone(CCZone *pZone);
};

#endif /* defined(__FacebookGameDemo__EziFacebookUser__) */
