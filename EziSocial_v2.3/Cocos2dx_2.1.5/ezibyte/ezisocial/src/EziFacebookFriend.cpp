//
//  EziFacebookFriend.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#include "EziFacebookFriend.h"

EziFacebookFriend::EziFacebookFriend()
{
    _name = "";
    _fbID = "";
    _installed = false;
    _facebookScore = 0;
    _photoPath = "";
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
    
    //pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}