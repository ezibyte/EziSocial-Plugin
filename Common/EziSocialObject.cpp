//
//  EziSocialObject.cpp
//  EziSocialDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//  EziByte (http://www.ezibyte.com)
//

/***
 
 This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source distribution.
 
*/


#include "EziSocialObject.h"
#include "EziSocialDefinition.h"
#include "EziSocialDelegate.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

static EziSocialObject* sharedEziSocialObject;

// ---------------------------------------------------------
#pragma mark - Private Methods - Helper Functions (C)
// ---------------------------------------------------------

cocos2d::CCArray* getArrayFromString(const char* commaSeperatedData)
{
    cocos2d::CCArray *resultArray = cocos2d::CCArray::create();
    
    std::vector<std::string> strings;
    std::istringstream f(commaSeperatedData);
    std::string s;
    std::string lastID   = "";
    std::string firstKey = "";
    
    
    while (std::getline(f, s, ','))
    {
        resultArray->addObject(cocos2d::CCString::createWithFormat("%s", s.c_str(), NULL));
    }
    
    return resultArray;
}

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
    
    //CCLOG("Friend Callback = %s", data);
    
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
    
    //CCLOG("HighScore = %s", data);
    
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


void internalUserPhotoCallback(const char* userPhoto)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbUserPhotoCallback(userPhoto);
    }
}

void internalRequestSendCallback(int responseCode, const char* friendsGotRequestIDs)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbSendRequestCallback(responseCode, getArrayFromString(friendsGotRequestIDs));
    }
}

void internalRequestRecieveCallback(int responseCode, const char* message, const char* senderName, const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbRecieveRequestCallback(responseCode, message, senderName, getCustomizedDictionary(data));
    }
}

bool EziSocialObject::isFacebookSessionActive()
{
    return EziSocialWrapperNS::isFacebookSessionActive();
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
    
    EziSocialWrapperNS::setRequestRecievedCallback(internalRequestRecieveCallback);
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


void EziSocialObject::fetchFBUserDetails(bool getEmailIDAlso)
{
    EziSocialWrapperNS::fetchUserDetails(internalFBUserDetailCallBack, getEmailIDAlso);
}

void EziSocialObject::getListOfFriendsUsingFBApp()
{
    this->getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::ONLY_INSTALLED, 0, 0);
}

void EziSocialObject::getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType)
{
    this->getFriends(searchType, 0, 0);
}

void EziSocialObject::getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType, int startIndex, int limit)
{
    EziSocialWrapperNS::getFriends(internalFriendsCallback, searchType, startIndex, limit);
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

void EziSocialObject::sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::TYPE requestType,
                                           const char* message,
                                           cocos2d::CCArray *selectedFriendIDs,
                                           cocos2d::CCDictionary *dataDictionary)
{
    
    std::string dataString      = "";
    std::string friendsString   = "";
    
    if (dataDictionary)
    {
        cocos2d::CCArray *keys = dataDictionary->allKeys();
        
        for (int i=0; i<keys->count(); i++)
        {
            cocos2d::CCString* key = (cocos2d::CCString*)keys->objectAtIndex(i);
            cocos2d::CCString* value = (cocos2d::CCString*)dataDictionary->objectForKey(key->getCString());
            
            if (i>0)
            {
                dataString.append(",");
            }
            
            dataString.append(key->getCString());
            dataString.append(",");
            dataString.append(value->getCString());
            
        }
        
    }
    
    
    if (selectedFriendIDs)
    {
        for (int i=0; i<selectedFriendIDs->count(); i++)
        {
            cocos2d::CCString* friendID = (cocos2d::CCString*)selectedFriendIDs->objectAtIndex(i);
            
            if (i>0)
            {
                friendsString.append(",");
            }
            
            friendsString.append(friendID->getCString());
            
        }
        
    }
    
    EziSocialWrapperNS::sendRequest(internalRequestSendCallback,
                                    requestType,
                                    message,
                                    dataString.c_str(),
                                    friendsString.c_str());
}

void EziSocialObject::getProfilePicForID(const char* userFacebookID, bool forceDownload)
{
    CCString* downloadURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?type=square",
                                                       userFacebookID);
    
    CCString* fileName = CCString::createWithFormat("%s_square.jpg", userFacebookID);
    
    this->downloadPhoto(downloadURL->getCString(), fileName->getCString(), forceDownload);
}


void EziSocialObject::getProfilePicForID(const char* userFacebookID,
                                         EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType,
                                         bool forceDownload)
{
    
    std::string downloadURL = "http://graph.facebook.com/";
    downloadURL.append(userFacebookID);
    downloadURL.append("/picture?type=");
    
    std::string fileName = "";
    fileName.append(userFacebookID);
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
    
    this->downloadPhoto(downloadURL.c_str(), fileName.c_str(), forceDownload);
    
}
void EziSocialObject::getProfilePicForID(const char* userFacebookID, int width, int height, bool forceDownload)
{
    
    CCString* downloadURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?width=%d&height=%d",
                                                       userFacebookID, width, height);
    
    CCString* fileName = CCString::createWithFormat("%s_%d_%d.jpg", userFacebookID, width, height);
    
    this->downloadPhoto(downloadURL->getCString(), fileName->getCString(), forceDownload);
}

void EziSocialObject::downloadPhoto(const char *fbID, const char* filename, bool forceDownloadFromServer)
{
    
    if (forceDownloadFromServer == false) // Check if local copy exist
    {
        std::string file = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().append(filename);
        bool fileExist = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(file);
        
        if (fileExist)
        {
            //CCLOG("%s file exist already.", filename);
            internalUserPhotoCallback(file.c_str());
            return;
        }
    }
    
    // If we have reached here; that means local copy does not exsist. Download a new one.
    
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(fbID);
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback((CCNode*)mFacebookDelegate, callfuncND_selector(EziSocialObject::onHttpRequestCompleted));
    request->setTag(filename);
    
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void EziSocialObject::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    //CCLOG("HTTP Request Completed...");
    
    CCHttpResponse* response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLOG("No Response");
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
        CCLog("Cannot fetch user image");
        CCLog("error buffer: %s", response->getErrorBuffer());
        internalUserPhotoCallback("");
        
        return;
    }
    
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    //printf("Http Test, dump data: ");
    
    // Create the CCSprite from data dump...
    
    CCImage * img=new CCImage();
    img->initWithImageData(&(buffer->front()), buffer->size());
    
    // Save file for resue.
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    writablePath.append(response->getHttpRequest()->getTag());
    img->saveToFile(writablePath.c_str());
    
    internalUserPhotoCallback(writablePath.c_str());
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

