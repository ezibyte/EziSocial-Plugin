
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
#include "extensions/cocos-ext.h"
#include "EziFacebookUser.h"
#include "EziFBIncomingRequestManager.h"
#include "EziFacebookFriend.h"
#include "network/HttpClient.h"

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
std::vector<std::string> getArrayFromString(const char* commaSeperatedData)
{
    return EziSocialObject::tokenizeStr( commaSeperatedData, ",");
}

std::vector<EziFacebookFriend*> buildFriendsArray(std::string data)
{
    std::vector<EziFacebookFriend*> resultArray;
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( data, ";");
    EziFacebookFriend* fbFriend = NULL;//EziFacebookFriend::create();
    
    for (int i = 1; i < strings.size(); i += 2)
    {
        if ( i > 1 && strings[i-1] == strings[0] )
        {
            if (fbFriend)
                resultArray.push_back(fbFriend);
            fbFriend = NULL;
        }
        
        if ( fbFriend == NULL )
            fbFriend = EziFacebookFriend::create("");
        
        fbFriend->saveData(strings[i].c_str(), strings[i-1].c_str());
        //tempDictionary->setObject(cocos2d::CCString::createWithFormat("%s", strings[i].c_str(), NULL), strings[i-1].c_str());
    
    }
    
    if (fbFriend)
    {
        resultArray.push_back(fbFriend);
    }
    
    return resultArray;
}

/*cocos2d::CCArray* getCustomizedArray(const char* data)
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
 }*/

std::unordered_map<std::string,std::string> getCustomizedDictionary(const char* data)
{
    std::unordered_map<std::string,std::string> resultDictionary;
    std::vector< std::string > strings = EziSocialObject::tokenizeStr( data, ";");
    for (int i = 1; i < strings.size(); i += 2)
    {
        resultDictionary.insert( std::make_pair(strings[i-1], strings[i]));
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
        CCLOG("Fetching user details...");
        EziSocialObject::sharedObject()->fetchFBUserDetails(false);
        
        if (strcmp(userID, "") != 0)
        {
            std::string storedUserID = UserDefault::getInstance()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
            if (storedUserID.compare(userID) != 0)
            {
                // This is some new ID. Let's build the list.
                UserDefault::getInstance()->setStringForKey(KEY_EZI_CURRENT_FB_USER_ID, userID);
                UserDefault::getInstance()->flush();
                
                log("Rebuilding Manager...");
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
        std::vector<EziFacebookFriend*> myFriends = buildFriendsArray(data);
        //std::vector<EziFacebookFriend*> myFriends;
        tempFBDelegate->fbFriendsCallback(responseCode, responseMessage, myFriends);
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
            //CCLOG("Key = %s = %s",  strings[i-1].c_str(), strings[i].c_str());
            fbUser->saveData(strings[i-1].c_str(), strings[i]);
        }
    }
    
    EziSocialObject::sharedObject()->setCurrentFacebookUser(fbUser);
    
    if (tempFBDelegate)
    {
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

void internalFBShareDialogCallback(int responseCode, const char* responseMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbShareDialogCallback(responseCode, responseMessage);
    }
}

void internalFBOpenGraphCallback(int responseCode, const char* responseMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbOpenGraphCallback(responseCode, responseMessage);
    }
}

void internalAchievementCallback(int responseCode, const char* responseMessage)
{
    EziFacebookDelegate* tempFBDelegate;
    tempFBDelegate = EziSocialObject::sharedObject()->getFacebookDelegate();
    
    if (tempFBDelegate)
    {
        tempFBDelegate->fbAchievementCallback(responseCode, responseMessage);
    }
}


// ---------------------------------------------------------
#pragma mark - Destructor
// ---------------------------------------------------------

EziSocialObject::~EziSocialObject()
{
    _currentUser = NULL;
}

// ---------------------------------------------------------
#pragma mark - Public Methods
// ---------------------------------------------------------

EziFacebookUser* EziSocialObject::getCurrentFacebookUser()
{
    if (_currentUser == NULL || isFacebookSessionActive() == false)
    {
        _currentUser = NULL;
        return NULL;
    }
    else
    {
        return _currentUser;
    }
}

void EziSocialObject::setCurrentFacebookUser(EziFacebookUser *fbUser)
{
    _currentUser = NULL;
    _currentUser = fbUser;
}

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
    _currentUser         = NULL;
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
    _currentUser = NULL;
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

void EziSocialObject::setAutoCheckIncomingRequestsOnAppLaunch(bool toAllow)
{
    EziSocialWrapperNS::setAutoCheckIncomingRequestsOnAppLaunch(toAllow);
}

void EziSocialObject::sendGiftsToFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const std::unordered_map<std::string,std::string> &dataDictionary)
{
    sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::REQUEST_GIFT, message, selectedFriendIDs, dataDictionary, "");
}

void EziSocialObject::inviteFriends(const char* message)
{
    inviteFriends(message, std::vector<std::string>());
}

void EziSocialObject::inviteFriends(const char* message, const std::vector<std::string> &selectedFriendIDs)
{
    inviteFriends(message, selectedFriendIDs, "");
}
void EziSocialObject::inviteFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const char* customTitle)
{
    sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::REQUEST_INVITE, message, selectedFriendIDs, std::unordered_map<std::string,std::string>(), customTitle);
}

void EziSocialObject::challengeFriends(const char* message)
{
    challengeFriends(message, std::vector<std::string>());
}
void EziSocialObject::challengeFriends(const char* message, const std::vector<std::string> &selectedFriendIDs)
{
    challengeFriends(message, selectedFriendIDs, "");
}
void EziSocialObject::challengeFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const char* customTitle)
{
    sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::REQUEST_CHALLENGE, message, selectedFriendIDs, std::unordered_map<std::string,std::string>(), customTitle);
}


void EziSocialObject::sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::TYPE requestType,
                                           const char* message,
                                           const std::vector<std::string> &selectedFriendIDs,
                                           const std::unordered_map<std::string,std::string> &dataDictionary, const char* customTitle)
{
    
    std::string dataString      = "";
    std::string friendsString   = "";
    
    for(auto it = dataDictionary.begin();it!=dataDictionary.end();++it)
    {
        if (it != dataDictionary.begin())
        {
            dataString.append(",");
        }
        dataString.append(it->first);
        dataString.append(",");
        dataString.append(it->second);
    }
    
    for(auto it = selectedFriendIDs.begin();it!=selectedFriendIDs.end();++it)
    {
        if (it != selectedFriendIDs.begin())
        {
            friendsString.append(",");
        }
        friendsString.append(*it);
    }
    
    EziSocialWrapperNS::sendRequest(internalRequestSendCallback,
                                    requestType,
                                    message,
                                    dataString.c_str(),
                                    friendsString.c_str(), customTitle);
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
        CCLOG("Cannot post NULL photo on Facebook with a imageFile");
        return;
    }
    
    if (message == NULL)
    {
        message = "";
    }
    
    EziSocialWrapperNS::postPhoto(imageFileName, message, internalPostPhotoCallback);
}

// ---------------------------------------------------------
#pragma mark - Facebook [Share Dialogs]
// ---------------------------------------------------------

void EziSocialObject::useShareDialogForLink (const char *linkURL)
{
    EziSocialWrapperNS::shareLink(linkURL, internalFBShareDialogCallback);
}

void EziSocialObject::useShareDialogForStatusForUpdate()
{
    EziSocialWrapperNS::shareLink(NULL, internalFBShareDialogCallback);
}

void EziSocialObject::useShareDialogForOpenGraph(const char *objectType, const char *actionType, const char *title, const char *imageAddress, const char *description)
{
    EziSocialWrapperNS::shareOpenGraph(FACEBOOK_OG_SERVER, FACEBOOK_NAMESPACE,
                                       objectType, actionType, title,
                                       imageAddress, description, internalFBShareDialogCallback);
}

bool EziSocialObject::canUseShareDialog()
{
    return EziSocialWrapperNS::canUseShareDialogs();
}

// ---------------------------------------------------------
#pragma mark - Achievement Publish
// ---------------------------------------------------------

void EziSocialObject::postAchievement(const char *achievementURL)
{
    if (achievementURL == NULL)
    {
        CCLOG("[EziSocial Error]: Cannot publish achievement with NULL URL.");
        return;
    }
    
    EziSocialWrapperNS::publishAchievement(achievementURL, internalAchievementCallback);
}

// ---------------------------------------------------------
#pragma mark - Facebook [Log Events] Methods
// ---------------------------------------------------------

void EziSocialObject::logEvent(const char* eventName)
{
    if (eventName == NULL)
    {
        CCLOG("[EziSocial Error]: Cannot log event with NULL or empty Value. Please specifiy a value");
        return;
    }
    
    EziSocialWrapperNS::logEvent(eventName);
    
}

void EziSocialObject::logEventWithValue(const char* eventName, double value)
{
    if (eventName == NULL)
    {
        CCLOG("[EziSocial Error]: Cannot log event with NULL or empty Value. Please specifiy a value");
        return;
    }
    
    EziSocialWrapperNS::logEventWithValue(eventName, value);
    
}

void EziSocialObject::logPurchase(double value, const char* currencyType)
{
    if (currencyType == NULL)
    {
        CCLOG("[EziSocial Error]: Cannot log purchase with NULL or empty currency type. Please specifiy a right currency code. You can see the valid code here: http://en.wikipedia.org/wiki/ISO_4217");
        return;
    }
    
    EziSocialWrapperNS::logPurchase(value, currencyType);
    
}

void EziSocialObject::setLogActiveness(bool toLogActiveness)
{
    EziSocialWrapperNS::setLoggingActiveness(toLogActiveness);
}

// ---------------------------------------------------------
#pragma mark - Publish Open Graph Actions
// ---------------------------------------------------------


void EziSocialObject::publishOpenGraphAction(const char* objectType, const char* actionType, const char* title)
{
    EziSocialObject::sharedObject()->publishOpenGraphAction(objectType, actionType, title, NULL, NULL, NULL);
}

void EziSocialObject::publishOpenGraphAction(const char* objectType, const char* actionType,
                                             const char* title, const char* imageAddress)
{
    EziSocialObject::sharedObject()->publishOpenGraphAction(objectType, actionType, title, imageAddress, NULL, NULL);
}


void EziSocialObject::publishOpenGraphAction(const char* objectType, const char* actionType,
                                             const char* title, const char* imageAddress,
                                             const char* description, const char* body)
{
    
    if (objectType == NULL || actionType == NULL || title == NULL)
    {
        CCLOG("[EziSocial Error]: For Open graph action, you need to mention object type, action type and title. Without this, open graph action cannot be published.");
        return;
    }
    
    
    
    
    EziSocialWrapperNS::publishOpenGraphAction(FACEBOOK_OG_SERVER, FACEBOOK_NAMESPACE,
                                               objectType, actionType, title,
                                               imageAddress, description, body,
                                               internalFBOpenGraphCallback);
    
    
}

void EziSocialObject::publishOpenGraphActionWithFriend(const char* friendID, const char* actionType)
{
    if (actionType == NULL || friendID == NULL)
    {
        CCLOG("[EziSocial Error]: For Open graph action, you need to mention object action type, friend ID. Without this, open graph action cannot be published.");
        return;
    }
    
    EziSocialWrapperNS::publishOpenGraphActionForProfile(friendID,
                                                         FACEBOOK_NAMESPACE,
                                                         actionType, internalFBOpenGraphCallback);
    
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




