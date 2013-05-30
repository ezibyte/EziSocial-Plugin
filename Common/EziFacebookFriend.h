//
//  EziFacebookFriend.h
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

#ifndef __FacebookGameDemo__EziFacebookFriend__
#define __FacebookGameDemo__EziFacebookFriend__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class EziFacebookFriend : public CCObject
{
    std::string _name;
    std::string _fbID;
    std::string _photoPath;
    
    bool _installed;
    long _facebookScore;
    

    EziFacebookFriend();
    
public:
    
    static EziFacebookFriend* create();

    ~EziFacebookFriend();
    
    void setName(const char* newName);
    void setID(const char* newFBID);
    void setScore(long newScore);
    void setInstalled(bool newInstalled);
    void setPhotoPath(const char* newPhotoPath);
    
    const char* getName();
    const char* getFBID();
    long getScore();
    bool isInstalled();
    const char* getPhotoPath();
    
    void saveData(const char* data, const char* key);
    
    virtual CCObject* copyWithZone(CCZone *pZone);

};

#endif /* defined(__FacebookGameDemo__EziFacebookFriend__) */
