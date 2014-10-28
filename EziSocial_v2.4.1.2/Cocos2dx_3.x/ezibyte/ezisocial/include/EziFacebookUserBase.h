//
//  EziFacebookUserBase.h
//  EziSocialDemo
//
//  Created by Paras Mendiratta on 18/04/14.
//
//

#ifndef EziSocialDemo_EziFacebookUserBase_h
#define EziSocialDemo_EziFacebookUserBase_h

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"

using namespace cocos2d;
using namespace cocos2d::network;

#include "EziSocialDefinition.h"

typedef std::function<void(cocos2d::Ref*, cocos2d::Sprite*)> EziCallback;

class EziFacebookUserBase: public cocos2d::Ref
{

public:
    
    const std::string &getProfileID() const;
    const std::string &getPicURL() const;
    
    cocos2d::Sprite* getPhoto();
    cocos2d::Sprite* getPhoto(const EziCallback& callback);
    cocos2d::Sprite* getPhoto(const EziCallback& callback, bool forceDownload);
    cocos2d::Sprite* getPhoto(const EziCallback& callback, bool forceDownload, EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType);
    cocos2d::Sprite* getPhoto(const EziCallback& callback, bool forceDownload, int width, int height);
    
protected:
    
    std::string _profileID;
    std::string _picURL;
    cocos2d::Sprite* _photo;
    
private:
    EziCallback _callback;
    
    cocos2d::Sprite* downloadPhoto(const EziCallback& callback, const char* fbURL, const char* filename, bool forceDownloadFromServer);
    void onRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
    
    void generateSprite(const char* userPhoto);
    
    std::string _photoKey;
    
};

#endif
