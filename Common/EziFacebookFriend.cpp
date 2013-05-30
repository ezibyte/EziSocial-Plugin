//
//  EziFacebookFriend.cpp
//  EziSocial
//
//  Created by Paras Mendiratta on 20/05/13.
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