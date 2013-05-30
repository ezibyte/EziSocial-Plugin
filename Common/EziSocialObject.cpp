//
//  EziSocialObject.cpp
//  EziSocial
//
//  Created by Paras Mendiratta on 11/04/13.
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

#include "EziSocialObject.h"
#include "EziSocialDefinition.h"
#include "EziSocialDelegate.h"
#include "cocos-ext.h"
#include "EziFacebookUser.h"
#include "EziFBIncomingRequestManager.h"
#include "EziFacebookFriend.h"

USING_NS_CC;
USING_NS_CC_EXT;

static EziSocialObject* sharedEziSocialObject;

// -------------------------------------------------------------
#pragma mark - Private Methods - Helper Functions (C & C++)
// -------------------------------------------------------------

bool EziSocialObject::isNeedsPublishPermission()
{
    return mNeedsPublishPermission;
}

std::vector<std::string> EziSocialObject::tokenizeStr( const std::string &s, const std::string &delim )
{
    std::vector< std::string > ret;
    int idx = 0;
    while ( idx < s.length() )
    {
        int fPos = s.find(delim, idx);
        if ( fPos != std::string::npos )
        {
            if ( fPos - idx > 0 )
            {
                ret.push_back( s.substr( idx, fPos - idx ) );
            }
            else
            {
                if ( fPos - idx == 0 ) ret.push_back("");
            }
            
            idx = fPos + delim.length();
        }
        else
        {
            ret.push_back( s.substr( idx ) );
            idx = s.length();
        }
    }
    return ret;
}
cocos2d::CCArray* getArrayFromString(const char* commaSeperatedData)
{
    cocos2d::CCArray *resultArray = cocos2d::CCArray::create();
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( commaSeperatedData, ",");
    for (int i = 0; i < strings.size(); ++i)
    {
        resultArray->addObject(cocos2d::CCString::createWithFormat("%s", strings[i].c_str(), NULL));
    }
    return resultArray;
}

cocos2d::CCArray* buildFriendsArray(std::string data)
{
    cocos2d::CCArray *resultArray = cocos2d::CCArray::create();
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( data, ";");
    EziFacebookFriend* fbFriend = NULL;//EziFacebookFriend::create();
    
    for (int i = 1; i < strings.size(); i += 2)
    {
        if ( i > 1 && strings[i-1] == strings[0] )
        {
            if (fbFriend) resultArray->addObject(fbFriend);
            fbFriend = NULL;
        }
        
        if ( fbFriend == NULL ) fbFriend = EziFacebookFriend::create();
        
        fbFriend->saveData(strings[i].c_str(), strings[i-1].c_str());
    }
    
    if (fbFriend)
    {
        resultArray->addObject(fbFriend);
    }
    
    return resultArray;
}

cocos2d::CCArray* getCustomizedArray(const char* data)
{
    cocos2d::CCArray *resultArray = cocos2d::CCArray::create();
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( data, ";");
    cocos2d::CCDictionary *tempDictionary = NULL;
    for (int i = 1; i < strings.size(); i += 2)
    {
        if ( i > 1 && strings[i-1] == strings[0] )
        {
            if (tempDictionary) resultArray->addObject(tempDictionary);
            tempDictionary = NULL;
        }
        
        if ( tempDictionary == NULL ) tempDictionary = cocos2d::CCDictionary::create();
        
        tempDictionary->setObject(cocos2d::CCString::createWithFormat("%s", strings[i].c_str(), NULL), strings[i-1].c_str());
    }
    
    if (tempDictionary) resultArray->addObject(tempDictionary);
    return resultArray;
}

cocos2d::CCDictionary* getCustomizedDictionary(const char* data)
{
    cocos2d::CCDictionary *resultDictionary = cocos2d::CCDictionary::create();
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( data, ";");
    for (int i = 1; i < strings.size(); i += 2)
    {
        resultDictionary->setObject( cocos2d::CCString::createWithFormat("%s", strings[i].c_str(), NULL), strings[i-1].c_str());
    }
    return resultDictionary;
}

// ---------------------------------------------------------
#pragma mark - (C) Callback Methods
// ---------------------------------------------------------

void internalFBSessionCallback(int responseCode, const char* responseMessage, const char* userID)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_FIRST_NEEDS_READ_PERMISSION)
    {
        // Boss, this is iOS 6 issue. We fist needs the read permission.
        EziSocialObject::sharedObject()->performLoginUsingFacebook(false);
        return;
    }
    
    if (responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_SUCCESSFUL)
    {
        if (strcmp(userID, "") != 0)
        {
            std::string storedUserID = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
            if (storedUserID.compare(userID) != 0)
            {
                // This is some new ID. Let's build the list.
                CCUserDefault::sharedUserDefault()->setStringForKey(KEY_EZI_CURRENT_FB_USER_ID, userID);
                CCUserDefault::sharedUserDefault()->flush();
                
                CCLog("Rebuilding Manager...");
                EziFBIncomingRequestManager::rebuildManager();
            }
        }
    }
    
    if (responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_LOGIN_MISSING_IOS_6_ACCOUNT)
    {
        // Developer needs to recall the Login method after sometimes.
    }
    if (tempFBDelegate)
    {
        tempFBDelegate->fbSessionCallback(responseCode, responseMessage);
    }
}

void internalFBMessageCallback(int responseCode, const char* responseMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbMessageCallback(responseCode, responseMessage);
    }
}

void internalFBPageLikeCallback(int responseCode, const char* responseMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbPageLikeCallback(responseCode, responseMessage);
    }
}

void internalFriendsCallback(int responseCode, const char* responseMessage, const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbFriendsCallback(responseCode, responseMessage, buildFriendsArray(data));
    }
    
}

void internalPostPhotoCallback(int responseCode, const char* responeMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbPostPhotoCallback(responseCode, responeMessage);
    }
}

void internalFBUserDetailCallBack(int responseCode, const char* responseMessage, const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    EziFacebookUser *fbUser = NULL;
    
    if (responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_USER_DETAIL_SUCCESS)
    {
        std::vector< std::string > strings = EziSocialObject::tokenizeStr(data, ";");
        fbUser = new EziFacebookUser();
        
        for (int i = 1; i < strings.size(); i += 2)
        {
            fbUser->saveData(strings[i-1].c_str(), strings[i]);
        }
    }
    
    if (tempFBDelegate)
    {
        //tempFBDelegate->fbUserDetailCallback(getCustomizedDictionary((const char*)specialValue.c_str()));
        tempFBDelegate->fbUserDetailCallback(responseCode, responseMessage, fbUser);
    }
    
}



void internalFBHighScoreCallBack(int responseCode, const char* responseMessage, const char* data)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbHighScoresCallback(responseCode, responseMessage, buildFriendsArray(data));
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

void internalRequestSendCallback(int responseCode, const char* responseMessage, const char* friendsGotRequestIDs)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbSendRequestCallback(responseCode, responseMessage, getArrayFromString(friendsGotRequestIDs));
    }
}

void internalRequestRecieveCallback(int responseCode,
                                    const char* requestID,
                                    const char* message,
                                    const char* senderID,
                                    const char* senderName,
                                    const char* receiverID,
                                    const char* data,
                                    const char* errorMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLENGE_RECEIVE ||
        responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_RECEIVE ||
        responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_RECEIVE)
    {
        // We can mark this request ID as complete in the List.
        //EziFBIncomingRequestManager::sharedManager()->requestComepleted(requestID);
        EziFBIncomingRequest* incomingRequest = EziFBIncomingRequestManager::sharedManager()->getIncomingRequest(requestID);
        
        switch (responseCode)
        {
            case EziSocialWrapperNS::RESPONSE_CODE::FB_CHALLENGE_RECEIVE:
                incomingRequest->setRequestType(EziSocialWrapperNS::FB_REQUEST::REQUEST_CHALLENGE);
                break;
                
            case EziSocialWrapperNS::RESPONSE_CODE::FB_INVITE_RECEIVE:
                incomingRequest->setRequestType(EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE);
                break;
                
            case EziSocialWrapperNS::RESPONSE_CODE::FB_GIFT_RECEIVE:
                incomingRequest->setRequestType(EziSocialWrapperNS::FB_REQUEST::REQUEST_GIFT);
                break;
                
            default:
                break;
        }
        
        incomingRequest->setMessage(message);
        incomingRequest->setSender(senderID, senderName);
        incomingRequest->setReceiverID(receiverID);
        incomingRequest->setDataDictionary(getCustomizedDictionary(data));
        incomingRequest->setDataFetchedFromFacebook(true);
        incomingRequest->saveToUserDefaults();
        
        EziFBIncomingRequestManager::sharedManager()->processNextRequest();
    }
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbRecieveRequestCallback(responseCode,
                                                 message,
                                                 senderName,
                                                 getCustomizedDictionary(data));
    }
}

void internalIncomingRequestCallback(int responseCode, const char* requestIDs, const char* errorMessage)
{
    if (strcmp(requestIDs, "") != 0 && responseCode == EziSocialWrapperNS::RESPONSE_CODE::FB_INCOMING_REQUEST_NEW)
    {
        EziFBIncomingRequestManager::sharedManager()->addNewIncomingRequestIDs(requestIDs);
        int totalPendingRequest = EziFBIncomingRequestManager::sharedManager()->getPendingRequestCount();
        
        EziFacebookDelegate* tempFBDelegate;
        tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
        tempFBDelegate->fbIncomingRequestCallback(responseCode, errorMessage, totalPendingRequest);
        
        EziFBIncomingRequestManager::sharedManager()->processNextRequest();
    }
    else
    {
        EziFacebookDelegate* tempFBDelegate;
        tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
        tempFBDelegate->fbIncomingRequestCallback(responseCode, errorMessage, 0);
    }
}

bool EziSocialObject::isFacebookSessionActive()
{
    return EziSocialWrapperNS::isFacebookSessionActive();
}


void internalTwitterCallback(int responseCode)
{
    EziTwitterDelegate* tempTwitDelegate;
    tempTwitDelegate = EziSocialObject::sharedObject()->getTwitterDelegate();
    
    if (tempTwitDelegate)
    {
        tempTwitDelegate->twitterCallback(responseCode);
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
    mEmailDelegate       = NULL;
    mTwitterDelegate     = NULL;
    mFacebookDelegate    = NULL;
    mAllowIOS_5_Fallback = true;
    mNeedsPublishPermission = true;
    
    EziSocialWrapperNS::setIncomingRequestCallback(internalIncomingRequestCallback, internalRequestRecieveCallback);
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

void EziSocialObject::performLoginUsingFacebook(bool needsPublishPermission)
{
    mNeedsPublishPermission = needsPublishPermission;
    EziSocialWrapperNS::loginWithFacebook(internalFBSessionCallback, mNeedsPublishPermission);
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
                                        const char *message,
                                        const char *description,
                                        const char *badgeIconURL,
                                        const char *deepLinkURL)
{
    if (heading == NULL)
    {
        heading = "";
    }
    if (caption == NULL)
    {
        caption = "";
    }
    if (message == NULL)
    {
        message = "";
    }
    if (description == NULL)
    {
        description = "";
    }
    if (badgeIconURL == NULL)
    {
        badgeIconURL = "";
    }
    if (deepLinkURL == NULL)
    {
        deepLinkURL = "";
    }
    
    EziSocialWrapperNS::postMessage(internalFBMessageCallback,
                                    heading,
                                    caption,
                                    message,
                                    description,
                                    badgeIconURL,
                                    deepLinkURL);
}

void EziSocialObject::autoPostMessageOnWall(const char* heading,
                                            const char* caption,
                                            const char* message,
                                            const char* description,
                                            const char* badgeIconURL,
                                            const char* deepLinkURL)
{
    if (heading == NULL)
    {
        heading = "";
    }
    if (caption == NULL)
    {
        caption = "";
    }
    if (message == NULL)
    {
        message = "";
    }
    if (description == NULL)
    {
        description = "";
    }
    if (badgeIconURL == NULL)
    {
        badgeIconURL = "";
    }
    if (deepLinkURL == NULL)
    {
        deepLinkURL = "";
    }
    
    EziSocialWrapperNS::autoPostMessageOnWall(internalFBMessageCallback,
                                              heading,
                                              caption,
                                              message,
                                              description,
                                              badgeIconURL,
                                              deepLinkURL);
}

void EziSocialObject::postScore(unsigned long long score)
{
    EziSocialWrapperNS::postScore(internalFBMessageCallback, score);
}

void EziSocialObject::deleteScore()
{
    EziSocialWrapperNS::deleteScore(internalFBMessageCallback);
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

void EziSocialObject::checkIncomingRequest()
{
    EziSocialWrapperNS::checkIncomingRequests();
}

void EziSocialObject::processIncomingRequest(std::string requestID)
{
    EziSocialWrapperNS::processRequestID(internalRequestRecieveCallback, requestID.c_str());
}


void EziSocialObject::postPhoto(const char *imageFileName, const char *message)
{
    if (imageFileName == NULL)
    {
        CCLOG("Cannot post photo on Facebook with a imageFile");
        return;
    }
    
    if (message == NULL)
    {
        message = "";
    }
    
    EziSocialWrapperNS::postPhoto(imageFileName, message, internalPostPhotoCallback);
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
    
    EziSocialWrapperNS::tweet(internalTwitterCallback, message, imageURL);
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
    //"http://graph.facebook.com/1507014347/picture?width=200&height=200"
    
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
    //"http://graph.facebook.com/1507014347/picture?width=200&height=200"
    
    CCString* downloadURL = CCString::createWithFormat("http://graph.facebook.com/%s/picture?width=%d&height=%d",
                                                       userFacebookID, width, height);
    
    CCString* fileName = CCString::createWithFormat("%s_%d_%d.jpg", userFacebookID, width, height);
    
    this->downloadPhoto(downloadURL->getCString(), fileName->getCString(), forceDownload);
}

/*
 void EziSocialObject::getProfilePicForID(const char* userFacebookID)
 {
 return EziSocialWrapperNS::getUserPhoto(internalUserPhotoCallback, EziSocialWrapperNS::FBUSER::PIC_SQUARE, 0, 0, userFacebookID);
 }
 
 void EziSocialObject::getUserPhoto()
 {
 //return EziSocialWrapperNS::getUserPhoto(internalUserPhotoCallback, EziSocialWrapperNS::FBUSER::PIC_SQUARE, 0, 0);
 this->downloadPhoto("http://graph.facebook.com/1507014347/picture?width=200&height=200", "1507014347_w_200_h_200.png", false);
 }
 
 void EziSocialObject::getUserPhoto(EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType)
 {
 return EziSocialWrapperNS::getUserPhoto(internalUserPhotoCallback, picType, 0, 0);
 }
 
 void EziSocialObject::getUserCustomPhoto(int width, int height)
 {
 return EziSocialWrapperNS::getUserPhoto(internalUserPhotoCallback, EziSocialWrapperNS::FBUSER::PIC_SQUARE, width, height);
 }
 */

void EziSocialObject::downloadPhoto(const char *fbID, const char* filename, bool forceDownloadFromServer)
{
    
    if (forceDownloadFromServer == false) // Check if local copy exist
    {
        std::string file = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().append(filename);
        bool fileExist = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(file);
        
        if (fileExist)
        {
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
    CCHttpResponse* response = (CCHttpResponse*)data;
    
    if (!response)
    {
        CCLOG("No Response");
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    
    // Create the CCSprite from data dump...
    
    CCImage * img=new CCImage();
    img->initWithImageData(&(buffer->front()), buffer->size());
    
    // Save file for resue.
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    writablePath.append(response->getHttpRequest()->getTag());
    img->saveToFile(writablePath.c_str());
    
    internalUserPhotoCallback(writablePath.c_str());
}

cocos2d::CCSprite* EziSocialObject::generateCCSprite(const char* userPhoto)
{
    // Now prepare the CCSprite from the provided photo path.
    cocos2d::CCSprite* userPhotoSprite = NULL;
    
    bool fileFound = cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(userPhoto);
    
    if (fileFound)
    {
        unsigned long filesize = 0;
        unsigned char* fileData = NULL;
        
        fileData = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(userPhoto, "rb", &filesize);
        
        if (fileData)
        {
            cocos2d::CCImage image;
            image.initWithImageData((void*)fileData, filesize, (cocos2d::CCImage::EImageFormat)0);
            cocos2d::CCTexture2D* texture = new cocos2d::CCTexture2D();
            texture->initWithImage(&image);
            
            if(texture)
            {
                userPhotoSprite = cocos2d::CCSprite::createWithTexture(texture);
            }
            else
            {
                CCLOGERROR("Cannot create user profile pic from texture.");
            }
        }
        else
        {
            CCLOGERROR("Cannot load data for user profile picture.");
        }
    }
    else
    {
        CCLOGERROR("File not found");
    }
    
    return userPhotoSprite;
}

