//
//  EziSocialObject.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//

#include "EziSocialObject.h"
#include "EziSocialDefinition.h"
#include "EziSocialDelegate.h"

static EziSocialObject* sharedEziSocialObject;

// ---------------------------------------------------------
    #pragma mark - Private Methods - Helper Functions (C)
// ---------------------------------------------------------

cocos2d::CCArray* getCustomizedArray(const char* data)
{
    cocos2d::CCArray *resultArray = cocos2d::CCArray::create();
    
    std::vector<std::string> strings;
    std::istringstream f(data);
    std::string s;
    bool odd = true;
    bool firstKeyFound = false;
    std::string lastID   = "";
    std::string firstKey = "";
    
    cocos2d::CCDictionary *tempDictionary = NULL;
    
    while (std::getline(f, s, ';'))
    {
        if (firstKeyFound == false)
        {
            firstKey = s;
            firstKeyFound = true;
        }
        
        if (firstKey.compare(s) == 0)
        {
            if (tempDictionary)
            {
                resultArray->addObject(tempDictionary);
            }
            tempDictionary = cocos2d::CCDictionary::create();
        }
        
        if (odd)
        {
            lastID = s;
            odd = !odd;
            continue;
        }
        else
        {
            odd = !odd;
            tempDictionary->setObject(cocos2d::CCString::createWithFormat("%s", s.c_str(), NULL), lastID.c_str());
        }
    }
    
    if (tempDictionary)
    {
        resultArray->addObject(tempDictionary);
    }
    
    return resultArray;
}

cocos2d::CCDictionary* getCustomizedDictionary(const char* data)
{
    cocos2d::CCDictionary *resultDictionary = cocos2d::CCDictionary::create();
    
    std::vector<std::string> strings;
    std::istringstream f(data);
    std::string s;
    bool odd = true;
    std::string lastID = "";
    
    while (std::getline(f, s, ';'))
    {
        if (odd)
        {
            lastID = s;
            odd = !odd;
            continue;
        }
        else
        {
            odd = !odd;
            resultDictionary->setObject(cocos2d::CCString::createWithFormat("%s", s.c_str(), NULL), lastID.c_str());
        }
    }
    
    return resultDictionary;
}


// ---------------------------------------------------------
    #pragma mark - (C) Callback Methods
// ---------------------------------------------------------

void internalFBSessionCallback(int responseCode)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbSessionCallback(responseCode);
    }
}

void internalFBMessageCallback(int responseCode)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbMessageCallback(responseCode);
    }
}

void internalFBPageLikeCallback(int responseCode)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbPageLikeCallback(responseCode);
    }
}

void internalFriendsCallback(const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    CCLOG("Friend Callback = %s", data);
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbFriendsCallback(getCustomizedArray(data));
        //tempFBDelegate->fbFriendsCallback(friends);
    }

}

void internalFBUserDetailCallBack(const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    //CCLOG("User Details = %s", data);
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbUserDetailCallback(getCustomizedDictionary(data));
    }

}

void internalFBHighScoreCallBack(const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    CCLOG("HighScore = %s", data);
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbHighScoresCallback(getCustomizedArray(data));
    }
}

void internalMailCallBack(int responseCode)
{
    EziEmailDelegate* tempEmailDelegate;
    tempEmailDelegate = EziSocialObject::sharedObject()->getEmailDelegate();
    
    if (tempEmailDelegate != NULL)
    {
        tempEmailDelegate->mailCallback(responseCode);
    }
}

// ---------------------------------------------------------
    #pragma mark - Destructor
// ---------------------------------------------------------

EziSocialObject::~EziSocialObject()
{
    
}

// ---------------------------------------------------------
    #pragma mark - Public Methods
// ---------------------------------------------------------

void EziSocialObject::setFacebookDelegate(EziFacebookDelegate *facebookDelegate)
{
    mFacebookDelegate = facebookDelegate;
}

void EziSocialObject::setTwitterDelegate(EziTwitterDelegate *twitterDelegate)
{
    mTwitterDelegate = twitterDelegate;
}

void EziSocialObject::setEmailDelegate(EziEmailDelegate *emailDelegate)
{
    mEmailDelegate = emailDelegate;
}

EziFacebookDelegate* EziSocialObject::getFacebookDelegate()
{
    return mFacebookDelegate;
}

EziTwitterDelegate* EziSocialObject::getTwitterDelegate()
{
    return mTwitterDelegate;
}

EziEmailDelegate* EziSocialObject::getEmailDelegate()
{
    return mEmailDelegate;
}

// ---------------------------------------------------------
    #pragma mark - Singleton Object
// ---------------------------------------------------------

EziSocialObject::EziSocialObject()
{
    mEmailDelegate    = NULL;
    mTwitterDelegate  = NULL;
    mFacebookDelegate = NULL;
}

EziSocialObject*  EziSocialObject::sharedObject()
{
    if (sharedEziSocialObject == NULL)
    {
        sharedEziSocialObject = new EziSocialObject();
    }
    return sharedEziSocialObject;
}



// ---------------------------------------------------------
    #pragma mark - Facebook Methods
// ---------------------------------------------------------

void EziSocialObject::performLoginUsingFacebook()
{
    EziSocialWrapperNS::loginWithFacebook(internalFBSessionCallback);
}


void EziSocialObject::perfromLogoutFromFacebook()
{
    EziSocialWrapperNS::logoutFromFacebook(internalFBSessionCallback);
}

void EziSocialObject::fetchFBUserDetails()
{
    EziSocialWrapperNS::fetchUserDetails(internalFBUserDetailCallBack);
}

void EziSocialObject::getListOfFriendsUsingFBApp()
{
    EziSocialWrapperNS::getListOfFriendsUsingThisApp(internalFriendsCallback);
}

void EziSocialObject::hasUserLikedMyFBPage(const char *pageID)
{
    EziSocialWrapperNS::hasUserLikePage(internalFBPageLikeCallback, pageID);
}

void EziSocialObject::postMessageOnWall(const char *heading,
                                        const char *caption,
                                        const char *description,
                                        const char *badgeIconURL,
                                        const char *deepLinkURL)
{
    EziSocialWrapperNS::postMessage(internalFBMessageCallback,
                                    heading,
                                    caption,
                                    description,
                                    badgeIconURL,
                                    deepLinkURL);
}

void EziSocialObject::autoPostMessageOnWall(const char* heading,
                                            const char* caption,
                                            const char* description,
                                            const char* badgeIconURL,
                                            const char* deepLinkURL)
{
    EziSocialWrapperNS::autoPostMessageOnWall(internalFBMessageCallback,
                                              heading,
                                              caption,
                                              description,
                                              badgeIconURL,
                                              deepLinkURL);
}

void EziSocialObject::postScore(unsigned long long score)
{
    EziSocialWrapperNS::postScore(internalFBMessageCallback, score);
}

void EziSocialObject::getHighScores()
{
    EziSocialWrapperNS::getHighScores(internalFBHighScoreCallBack);
}

void EziSocialObject::openFacebookPage(const char* pageID, bool checkPageLikeOnApplicationBecomesActive)
{
    if (checkNetworkStatusForHost(""))
    {
        if (checkPageLikeOnApplicationBecomesActive)
        {
            EziSocialWrapperNS::openFacebookPage(pageID, checkPageLikeOnApplicationBecomesActive, internalFBPageLikeCallback);
        }
        else
        {
            EziSocialWrapperNS::openFacebookPage(pageID, checkPageLikeOnApplicationBecomesActive, 0);
        }
    }
}

// ---------------------------------------------------------
    #pragma mark - Twitter Methods
// ---------------------------------------------------------

void EziSocialObject::tweet(const char* message, const char* imageURL)
{
    if (message == NULL)
    {
        message = "";
    }
    
    if (imageURL == NULL)
    {
        imageURL = "";
    }
    
    EziSocialWrapperNS::tweet(message, imageURL);
}

// ---------------------------------------------------------
    #pragma mark - Email Methods
// ---------------------------------------------------------

void EziSocialObject::sendEmail(const char* subject, const char* htmlMessageBody, const char* semicolonSeperatedRecipents)
{
    if (subject == NULL)
    {
        subject = "";
    }
    if (htmlMessageBody == NULL)
    {
        htmlMessageBody = "";
    }
    if (semicolonSeperatedRecipents == NULL)
    {
        semicolonSeperatedRecipents = "";
    }
    
    EziSocialWrapperNS::sendEmail(subject, htmlMessageBody, semicolonSeperatedRecipents, internalMailCallBack);
}

bool EziSocialObject::checkNetworkStatusForHost(const char *hostURL)
{
    if (hostURL == NULL)
    {
        hostURL = "";
    }
    return EziSocialWrapperNS::networkAvailableForHost(hostURL);
}
