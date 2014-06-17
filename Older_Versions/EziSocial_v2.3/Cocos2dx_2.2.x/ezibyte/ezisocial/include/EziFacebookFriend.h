//
//  EziFacebookFriend.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

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
