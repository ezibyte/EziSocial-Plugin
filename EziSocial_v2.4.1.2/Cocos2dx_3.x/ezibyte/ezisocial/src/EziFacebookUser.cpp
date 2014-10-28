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
:_installed(false)
{
}

EziFacebookUser:: ~EziFacebookUser()
{
    
}

void EziFacebookUser::saveData(const std::string &key, const std::string &dataValue)
{
    if (key == KEY_FB_USER_NAME)
    {
        _username = dataValue;
    }
    else if (key == KEY_FB_USER_ACCESS_TOKEN)
    {
        _accessToken = dataValue;
    }
    else if (key == KEY_FB_USER_EMAIL)
    {
        _emailID = dataValue;
    }
    else if (key == KEY_FB_USER_FIRST_NAME)
    {
        _firstName = dataValue;
    }
    else if (key == KEY_FB_USER_GENDER)
    {
        _gender = dataValue;
    }
    else if (key == KEY_FB_USER_HOMETOWN)
    {
        _hometown = dataValue;
    }
    else if (key == KEY_FB_USER_LAST_NAME)
    {
        _lastName = dataValue;
    }
    else if (key == KEY_FB_USER_PROFILE_ID)
    {
        _profileID = dataValue;
    }
    else if (key ==  KEY_FB_USER_PRESENT_LOCATION)
    {
        _presentLocation = dataValue;
    }
    else if (key == KEY_FB_USER_BIRTHDAY)
    {
        _birthday = dataValue;
    }
    else
    {
        cocos2d::log("Unrecognized Key while saving the user data. KEY = %s", key.c_str());
    }
    
}

const std::string &EziFacebookUser::getUserName() const
{
    return _username;
}

const std::string &EziFacebookUser::getFirstName() const
{
    return _firstName;
}

const std::string &EziFacebookUser::getLastName() const
{
    return _lastName;
}

const std::string &EziFacebookUser::getHomeTown() const
{
    return _hometown;
}

const std::string &EziFacebookUser::getPresentLocation() const
{
    return _presentLocation;
}

const std::string &EziFacebookUser::getAccessToken() const
{
    return _accessToken;
}

const std::string &EziFacebookUser::getEmailID() const
{
    return _emailID;
}

const std::string &EziFacebookUser::getGender() const
{
    return _gender;
}

const std::string &EziFacebookUser::getBirthday() const
{
    return _birthday;
}


bool EziFacebookUser::isGameInstalled() const
{
    return _installed;
}



const std::string &EziFacebookUser::getFullName() const
{
    if (_fullname.empty())
    {
        // Full name is not available. So join first name and last name and return it.
        _fullname = _firstName;
        _fullname = _fullname.append(" ").append(_lastName);
    }
    
    return _fullname;
}

void EziFacebookUser::saveUserPhotoPath(const std::string &photoPath)
{
    _userPhotoPath = photoPath;
}

const std::string &EziFacebookUser::getPhotoPath() const
{
    return _userPhotoPath;
}





