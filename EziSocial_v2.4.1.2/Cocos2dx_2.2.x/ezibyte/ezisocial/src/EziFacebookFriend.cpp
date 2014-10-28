//
//  EziFacebookFriend.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#include "EziFacebookFriend.h"
#include "cocos-ext.h"
#include "EziSocialObject.h"

USING_NS_CC;
USING_NS_CC_EXT;

EziFacebookFriend::EziFacebookFriend()
{
    _name = "";
    _fbID = "";
    _installed = false;
    _facebookScore = 0;
    _photoPath = "";
    _profilePic = NULL;
    _photoURL = "";
    _selector = NULL;
    _target = NULL;
}

EziFacebookFriend::~EziFacebookFriend()
{
    
}

void EziFacebookFriend::setName(const char* newName)
{
    std::string str(newName);
    _name = str;
}

void EziFacebookFriend::setID(const char* newFBID)
{
    std::string str(newFBID);
    _fbID = str;
    
}

void EziFacebookFriend::setScore(long newScore)
{
    _facebookScore = newScore;
}

void EziFacebookFriend::setInstalled(bool newInstalled)
{
    _installed = newInstalled;
}

void EziFacebookFriend::setPhotoPath(const char* newPhotoPath)
{
    std::string str(newPhotoPath);
    _photoPath = str;
}

const char* EziFacebookFriend::getName()
{
    return _name.c_str();
}

const char* EziFacebookFriend::getFBID()
{
    return _fbID.c_str();
}

long EziFacebookFriend::getScore()
{
    return _facebookScore;
}

bool EziFacebookFriend::isInstalled()
{
    return _installed;
}

void EziFacebookFriend::setPhotoURL(const char *newPhotoURL)
{
    std::string str(newPhotoURL);
    _photoURL = str;
}


const char* EziFacebookFriend::getPhotoPath()
{
    return _photoPath.c_str();
}

EziFacebookFriend* EziFacebookFriend::create()
{
    EziFacebookFriend* fbFriend = new EziFacebookFriend();
    if (fbFriend)
    {
        fbFriend->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(fbFriend);
        return NULL;
    }
    
    return fbFriend;
}

const char* EziFacebookFriend::getPhotoURL()
{
    return _photoURL.c_str();
}

void EziFacebookFriend::saveData(const char* data, const char* key)
{
    if (strcmp(key, "id") == 0)
    {
        this->setID(data);
    }
    else if (strcmp(key, "name") == 0)
    {
        this->setName(data);
    }
    else if (strcmp(key, "score") == 0)
    {
        CCString* scoreString = CCString::create(data);
        _facebookScore = scoreString->intValue();
        
        //_facebookScore = std::atol(data.c_str());
    }
    else if (strcmp(key, "picURL") == 0)
    {
        this->setPhotoURL(data);
    }
    else if (strcmp(key, "installed") == 0)
    {
        if (strcmp(data, "1") == 0)
        {
            _installed = true;
        }
        else
        {
            _installed = false;
        }
    }
    else
    {
        CCLOG("Invalid Key %s", key);
    }
}

CCSprite* EziFacebookFriend::getProfilePic(cocos2d::CCLayer *sender, bool forceDownload, EziPhotoCallback callback)
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
        
        CCString* fileName = CCString::createWithFormat("%s_%d_%d.jpg", _fbID.c_str(), width, height);
        
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
            
            CCString* tempURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?width=%d&height=%d", _fbID.c_str(), 100, 100);
            
            downloadURL = tempURL->getCString();
        }
        
        
        
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl(downloadURL);
        request->setRequestType(CCHttpRequest::kHttpGet);
        
        request->setResponseCallback(this, httpresponse_selector(EziFacebookFriend::onHttpRequestCompleted));
        //request->setResponseCallback(sender, httpresponse_selector(EziSocialObject::onHttpRequestCompleted));
        
        request->setTag("ABC");
        
        CCHttpClient::getInstance()->send(request);
        request->release();
        
    }
    
    return NULL;
}

void EziFacebookFriend::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
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
    fileName = fileName.append(_fbID);
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
        (_target->*_selector)(_profilePic, _fbID.c_str());
    }
}

CCObject* EziFacebookFriend::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    EziFacebookFriend* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (EziFacebookFriend*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new EziFacebookFriend();
        pNewZone = new CCZone(pCopy);
    }
    
    pCopy->setName(getName());
    pCopy->setID(getFBID());
    pCopy->setScore(getScore());
    pCopy->setPhotoPath(getPhotoPath());
    pCopy->setInstalled(isInstalled());
    pCopy->setPhotoURL(getPhotoURL());
    
    //pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}