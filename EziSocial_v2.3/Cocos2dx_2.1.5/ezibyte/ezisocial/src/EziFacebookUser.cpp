//
//  EziFacebookUser.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 17/05/13.
//
//

#include "EziSocialDefinition.h"
#include "EziFacebookUser.h"

EziFacebookUser::EziFacebookUser()
{
    fullname        = "";
    username        = "";
    firstName       = "";
    lastName        = "";
    profileID       = "";
    hometown        = "";
    presentLocation = "";
    accessToken     = "";
    emailID         = "";
    gender          = "";
    installed       = false;
    userPhotoPath   = "";
}

EziFacebookUser:: ~EziFacebookUser()
{
    
}

void EziFacebookUser::saveData(const char* key, std::string dataValue)
{
    if (strcmp(key, KEY_FB_USER_NAME) == 0)
    {
        this->username = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_ACCESS_TOKEN) == 0)
    {
        this->accessToken = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_EMAIL) == 0)
    {
        this->emailID = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_FIRST_NAME) == 0)
    {
        this->firstName = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_GENDER) == 0)
    {
        this->gender = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_HOMETOWN) == 0)
    {
        this->hometown = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_LAST_NAME) == 0)
    {
        this->lastName = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_PROFILE_ID) == 0)
    {
        this->profileID = dataValue;
    }
    else if (strcmp(key, KEY_FB_USER_PRESENT_LOCATION) == 0)
    {
        this->presentLocation = dataValue;
    }
    else
    {
        CCLOG("Unrecognized Key while saving the user data. KEY = %s", key);
    }
        
}

const char* EziFacebookUser::getUserName()
{
    return username.c_str();
}

const char* EziFacebookUser::getFirstName()
{
    return firstName.c_str();
}

const char* EziFacebookUser::getLastName()
{
    return lastName.c_str();
}

const char* EziFacebookUser::getProfileID()
{
    return profileID.c_str();
}

const char* EziFacebookUser::getHomeTown()
{
    return hometown.c_str();
}

const char* EziFacebookUser::getPresentLocation()
{
    return presentLocation.c_str();
}

const char* EziFacebookUser::getAccessToken()
{
    return accessToken.c_str();
}

const char* EziFacebookUser::getEmailID()
{
    return emailID.c_str();
}

const char* EziFacebookUser::getGender()
{
    return gender.c_str();
}

bool EziFacebookUser::isGameInstalled()
{
    return installed;
}

const char* EziFacebookUser::getFullName()
{
    if (fullname.compare("") == 0)
    {
        // Full name is not available. So join first name and last name and return it.
        fullname = firstName;
        fullname = fullname.append(" ").append(lastName);
    }
    
    return fullname.c_str();
}

void EziFacebookUser::saveUserPhotoPath(std::string photoPath)
{
    this->userPhotoPath = photoPath;
}

const char* EziFacebookUser::getPhotoPath()
{
    return userPhotoPath.c_str();
}

