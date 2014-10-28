//
//  EziFacebookUser.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 17/05/13.
//
//

#include "EziFacebookUser.h"
#include "EziSocialObject.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
    _photoURL = "";
    _selector = NULL;
    _target = NULL;
    _birthday   = "";
}

EziFacebookUser:: ~EziFacebookUser()
{
    
}

void EziFacebookUser::setPhotoURL(const char *newPhotoURL)
{
    std::string str(newPhotoURL);
    _photoURL = str;
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
    else if (strcmp(key, "picURL") == 0)
    {
        this->setPhotoURL(dataValue.c_str());
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
    else if (strcmp(key, "birthday"))
    {
        this->_birthday = dataValue;
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

const char* EziFacebookUser::getPhotoURL()
{
    return _photoURL.c_str();
}

const char* EziFacebookUser::getBirthday()
{
    return _birthday.c_str();
}

CCSprite* EziFacebookUser::getProfilePic(cocos2d::CCLayer *sender, bool forceDownload, EziPhotoCallback callback)
{
    _selector = callback;
    _target = sender;
    
    //CCLOG("Force Download = %d", forceDownload);
    
    if (_profilePic != NULL && !forceDownload)
    {
        //CCLOG("Inside IF....");
        return _profilePic;
    }
    else
    {
        //CCLOG("Inside Elese....");
        
        const char* photoKey = "";
        int width = 100;
        int height = 100;
        
        CCString* fileName = CCString::createWithFormat("%s_%d_%d.jpg", profileID.c_str(), width, height);
        
        photoKey = fileName->getCString();
        
        std::string file = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().append(photoKey);
        bool fileExist = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(file);
        
        if (!forceDownload && fileExist)
        {
            _profilePic = EziSocialObject::sharedObject()->generateCCSprite(photoKey);
            
            if (_profilePic == NULL)
            {
                forceDownload = true;
            }
            else
            {
                return _profilePic;
            }
        }
        
        // If we have reached here then it means we need to forcefully download the photo.
        
        const char* downloadURL = "";
        
        //CCLOG("Photo URL = %s", this->getPhotoURL());
        
        if (std::strcmp(_photoURL.c_str(), "") != 0)
        {
            downloadURL = _photoURL.c_str();
            //CCLOG("downloadURL = %s", downloadURL);
        }
        else
        {
            //CCLOG("Creating new type of Download URL");
            
            CCString* tempURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?width=%d&height=%d", profileID.c_str(), 100, 100);
            
            downloadURL = tempURL->getCString();
        }
        
        
        
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl(downloadURL);
        request->setRequestType(CCHttpRequest::kHttpGet);
        
        request->setResponseCallback(this, httpresponse_selector(EziFacebookUser::onHttpRequestCompleted));
        
        request->setTag("ABC");
        
        CCHttpClient::getInstance()->send(request);
        request->release();
        
    }
    
    return NULL;
}

void EziFacebookUser::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    
    CCHttpResponse* response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLOG("[EziSocial Error]: No Response");
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        //CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    if (!response->isSucceed())
    {
        CCLog("[EziSocial Error]: response failed");
        CCLog("[EziSocial Error]: error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    
    // Create the CCSprite from data dump...
    
    CCImage * img=new CCImage();
    img->initWithImageData(&(buffer->front()), buffer->size());
    
    // Save file for resue.
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    //writablePath.append(response->getHttpRequest()->getTag());
    
    std::string fileName = "";
    fileName = fileName.append(profileID);
    fileName = fileName.append(".jpg");
    writablePath.append(fileName);
    
    //CCLOG("File Name = %s", fileName.c_str());
    
    //CCLOG("File Path = %s", writablePath.c_str());
    
    cocos2d::CCTexture2D* texture = new cocos2d::CCTexture2D();
    texture->initWithImage(img);
    
    if(texture)
    {
        _profilePic = cocos2d::CCSprite::createWithTexture(texture);
    }
    else
    {
        CCLOGERROR("[EziSocial Error]: Cannot create user profile pic from texture.");
    }
    
    img->saveToFile(writablePath.c_str());
    delete img;
    
    if (_target && _selector)
    {
        (_target->*_selector)(_profilePic, profileID.c_str());
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

