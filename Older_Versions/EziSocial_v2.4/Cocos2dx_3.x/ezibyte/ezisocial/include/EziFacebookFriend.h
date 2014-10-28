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
#include "EziFacebookUserBase.h"

class EziFacebookFriend : public EziFacebookUserBase
{
public:
    
    static EziFacebookFriend* create(const std::string& fbID, const std::string& name = "", long score = 0, const std::string& photoPath = "", bool installed = false, const std::string& picURL = "");
    
    ~EziFacebookFriend();
    
    const std::string& getName() const;

    
    
    long getScore() const;
    bool isInstalled() const;
    const std::string& getPhotoPath() const;
    
    
    
    void saveData(const std::string& data, const std::string& key);
    
    EziFacebookFriend *clone() const;
    
private:
    
    friend class EziFBIncomingRequest;
    
    std::string _name;
    std::string _photoPath;

    
    bool _installed;
    long _score;
    
    
    EziFacebookFriend();
    
};

#endif /* defined(__FacebookGameDemo__EziFacebookFriend__) */
