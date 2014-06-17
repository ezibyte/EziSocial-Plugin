//
//  EziFacebookUserBase.cpp
//  EziSocialDemo
//
//  Created by Paras Mendiratta on 18/04/14.
//
//

#include "EziFacebookUserBase.h"


const std::string &EziFacebookUserBase::getProfileID() const
{
    return _profileID;
}

const std::string &EziFacebookUserBase::getPicURL() const
{
    return _picURL;
}

cocos2d::Sprite* EziFacebookUserBase::getPhoto()
{
    return _photo;
}

cocos2d::Sprite* EziFacebookUserBase::getPhoto(const EziCallback& callback)
{
    return this->getPhoto(callback, false);
}

cocos2d::Sprite* EziFacebookUserBase::getPhoto(const EziCallback& callback, bool forceDownload)
{
    char downloadURL[1024] = {};
    snprintf(downloadURL, 1024, "http://graph.facebook.com/%s/picture?type=square", this->getProfileID().c_str());
    
    char fileName[1024] = {};
    snprintf(fileName, 1024, "%s_square.jpg", this->getProfileID().c_str());
    
    return this->downloadPhoto(callback, downloadURL, fileName, forceDownload);
    
}

cocos2d::Sprite* EziFacebookUserBase::getPhoto(const EziCallback& callback,
                                           bool forceDownload, EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType)
{
    std::string downloadURL = "http://graph.facebook.com/";
    downloadURL.append(this->getProfileID().c_str());
    downloadURL.append("/picture?type=");
    
    std::string fileName = "";
    fileName.append(this->getProfileID().c_str());
    fileName.append("_");
    
    switch (picType)
    {
        case EziSocialWrapperNS::FBUSER::PIC_SQUARE:
            downloadURL.append("square");
            fileName.append("square");
            break;
            
        case EziSocialWrapperNS::FBUSER::PIC_SMALL:
            downloadURL.append("small");
            fileName.append("small");
            break;
            
        case EziSocialWrapperNS::FBUSER::PIC_NORMAL:
            downloadURL.append("normal");
            fileName.append("normal");
            break;
            
        case EziSocialWrapperNS::FBUSER::PIC_LARGE:
            downloadURL.append("large");
            fileName.append("large");
            break;
            
        default:
            downloadURL.append("square");
            fileName.append("square");
            break;
    }
    
    fileName.append(".jpg");
    
    return this->downloadPhoto(callback, downloadURL.c_str(), fileName.c_str(), forceDownload);
}

cocos2d::Sprite* EziFacebookUserBase::getPhoto(const EziCallback& callback, bool forceDownload, int width, int height)
{
    char downloadURL[1024] = {};
    snprintf(downloadURL, 1024, "http://graph.facebook.com/%s/picture?width=%d&height=%d",this->getProfileID().c_str(), width, height);
    
    char fileName[1024] = {};
    snprintf(fileName, 1024, "%s_%d_%d.jpg", this->getProfileID().c_str(), width, height);
    
    return downloadPhoto(callback, downloadURL, fileName, forceDownload);
}

cocos2d::Sprite* EziFacebookUserBase::downloadPhoto(const EziCallback& callback,
                                                const char* fbURL,
                                                const char* filename,
                                                bool forceDownload)
{
    _callback = callback;
    cocos2d::Sprite* photo = nullptr;
    
    if (this->getPicURL().compare("")!=0)
    {
        fbURL = this->getPicURL().c_str();
    }
    
    //CCLOG("Photo Key = %s", _photoKey.c_str());
    //CCLOG("filename = %s", filename);
    
    
    
    if (forceDownload == false) // Check if local copy exist
    {
        if (_photoKey.compare(filename) == 0 && _photo != nullptr)
        {
            return _photo;
        }
        else
        {
            Data d = UserDefault::getInstance()->getDataForKey(filename);
            
            if (!d.isNull())
            {
                this->generateSprite(filename);
                return _photo;
            }
        }
        
    }
    
    
    
    
    
    //CCLOG("fbURL = %s", fbURL);
        
    //if (this->getPicURL())
    
    // If we have reached here; that means local copy does not exsist. Download a new one.
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(fbURL);
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    
    request->setResponseCallback(CC_CALLBACK_2(EziFacebookUserBase::onRequestCompleted, this));
    
    //request->setResponseCallback(this, httpresponse_selector(EziFacebookUserBase::onRequestCompleted));
    request->setTag(filename);
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    
    
    return photo;
}


void EziFacebookUserBase::onRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response)
{
    //return;
    
    if (!response)
    {
        CCLOG("[EziSocial Error]: No Response");
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        //CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    
    //if (!response->isSucceed())
    if (statusCode != 200)
    {
        cocos2d::log("[EziSocial Error]: response failed");
        cocos2d::log("[EziSocial Error]: error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    //char statusString[64] = {};
    //sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    
    
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    
    // Create the Sprite from data dump...
    
    cocos2d::Image * img=new cocos2d::Image();
    img->initWithImageData((unsigned char*)&(buffer->front()), buffer->size());
    
    std::string writablePath = "";
    writablePath.append(response->getHttpRequest()->getTag());
    
    Data *d = new Data();
    d->fastSet((unsigned char*)&(buffer->front()), buffer->size());
    
    //d.fastSet(img->getData(), buffer->size());
    UserDefault::getInstance()->setDataForKey(writablePath.c_str(), *d);
    
    delete img;
    
    if (_callback)
    {
        this->generateSprite(writablePath.c_str());
        _callback(this, _photo);
    }
}

void EziFacebookUserBase::generateSprite(const char* userPhoto)
{
    
    _photo = nullptr;
    
    // Fetch back the data from the storage.
    Data* tempData;
    Data d = UserDefault::getInstance()->getDataForKey(userPhoto);
    tempData = new Data();
    tempData->fastSet(d.getBytes(), d.getSize());
    
    if (!tempData->isNull())
    {
        cocos2d::Image * img2=new cocos2d::Image();
        //img2->initWithJpgData(tempData->getBytes(), tempData->getSize());
        img2->initWithImageData(tempData->getBytes(), tempData->getSize());
        Texture2D *tempTexture2 = new Texture2D();
        tempTexture2->initWithImage(img2);
        
        _photo = Sprite::createWithTexture(tempTexture2);
        
        
        // Correct the photo scale to make it of 100x100 pixels
        _photo->setScale(100/_photo->getTextureRect().getMaxX(), 100/_photo->getTextureRect().getMaxY());
        
        
    }
    
    
}