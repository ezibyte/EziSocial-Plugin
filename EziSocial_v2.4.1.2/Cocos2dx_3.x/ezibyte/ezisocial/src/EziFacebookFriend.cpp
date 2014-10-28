//
//  EziFacebookFriend.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#include "EziFacebookFriend.h"

EziFacebookFriend::EziFacebookFriend()
:_installed(false)
,_score(0)
{
}

EziFacebookFriend::~EziFacebookFriend()
{
    
}

const std::string & EziFacebookFriend::getName() const
{
    return _name;
}

long EziFacebookFriend::getScore() const
{
    return _score;
}

bool EziFacebookFriend::isInstalled() const
{
    return _installed;
}

const std::string & EziFacebookFriend::getPhotoPath() const
{
    return _photoPath;
}

EziFacebookFriend* EziFacebookFriend::create(const std::string& fbID,const std::string& name, long score, const std::string& photoPath, bool installed, const std::string& picURL)
{
    EziFacebookFriend* fbFriend = new EziFacebookFriend();
    if (fbFriend)
    {
        fbFriend->_profileID = fbID;
        //fbFriend->_fbID = fbID;
        fbFriend->_name = name;
        fbFriend->_score = score;
        fbFriend->_photoPath = photoPath;
        fbFriend->_installed = installed;
        fbFriend->_picURL = picURL;
        fbFriend->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(fbFriend);
        return NULL;
    }
    
    return fbFriend;
}

void EziFacebookFriend::saveData(const std::string &data, const std::string &key)
{
    if (key == "id")
    {
        this->_profileID = data;
    }
    else if (key == "name")
    {
        _name = data;
    }
    else if (key == "score")
    {
        _score = atol(data.c_str());
    }
    else if (key == "installed")
    {
        _installed = (data == "1");
    }
    else if (key == "photo")
    {
        _photoPath = data;
    }
    else if (key == "picURL")
    {
        _picURL = data;
    }
    else
    {
        cocos2d::log("Invalid Key %s", key.c_str());
    }
}

EziFacebookFriend *EziFacebookFriend::clone() const
{
    EziFacebookFriend *ret = EziFacebookFriend::create(_profileID, _name, _score, _photoPath, _installed, _picURL);
    return ret;
}