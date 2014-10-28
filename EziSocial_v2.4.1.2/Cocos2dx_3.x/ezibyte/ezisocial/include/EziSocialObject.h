//
//  EziSocialObject.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//

#ifndef __FacebookGameDemo__EziSocialObject__
#define __FacebookGameDemo__EziSocialObject__

#include <iostream>
#include "EziSocialDelegate.h"
#include "EziSocialDefinition.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
//#include "network/HttpClient.h"

using namespace cocos2d;
using namespace cocos2d::network;


class EziSocialObject
{
public:
    
    ~EziSocialObject();
    
    static EziSocialObject* sharedObject();
    static std::vector<std::string> tokenizeStr( const std::string &s, const std::string &delim );
    
    EziFacebookUser* getCurrentFacebookUser();
    void setCurrentFacebookUser(EziFacebookUser* fbUser);
    
    bool isNeedsPublishPermission();
    
    void setFacebookDelegate(EziFacebookDelegate *facebookDelegate);
    void setTwitterDelegate(EziTwitterDelegate *twitterDelegate);
    void setEmailDelegate(EziEmailDelegate *emailDelegate);
    
    EziFacebookDelegate* getFacebookDelegate();
    EziTwitterDelegate* getTwitterDelegate();
    EziEmailDelegate* getEmailDelegate();
    
    void performLoginUsingFacebook(bool needsPublishPermission);
    void perfromLogoutFromFacebook();
    
    void fetchFBUserDetails(bool getEmailIDAlso);
    
    // Post Message On Wall
    void postMessageOnWall(const char* heading,
                           const char* caption,
                           const char* message,
                           const char* description,
                           const char* badgeIconURL,
                           const char* deepLinkURL);
    
    void autoPostMessageOnWall(const char* heading,
                               const char* caption,
                               const char* message,
                               const char* description,
                               const char* badgeIconURL,
                               const char* deepLinkURL);
    
    void postScore(unsigned long long score);
    void deleteScore();
    
    void hasUserLikedMyFBPage(const char* pageID);
    
    
    void getListOfFriendsUsingFBApp();
    void processIncomingRequest(std::string requestID);
    
    void getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType);
    void getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType, int startIndex, int limit);
    
    void getHighScores();
    void openFacebookPage(const char* pageID, bool checkPageLikeOnApplicationBecomesActive);
    
    /*
    void getProfilePicForID(cocos2d::Node* parentNode, const char* userFacebookID, bool forceDownload);
    void getProfilePicForID(cocos2d::Node* parentNode, const char* userFacebookID,
                            EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType, bool forceDownload);
    void getProfilePicForID(cocos2d::Node* parentNode, const char* userFacebookID, int width, int height, bool forceDownload);
    */

    void setAutoCheckIncomingRequestsOnAppLaunch(bool toAllow);
    
    void sendGiftsToFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const std::unordered_map<std::string,std::string> &dataDictionary);
    
    void inviteFriends(const char* message);
    void inviteFriends(const char* message, const std::vector<std::string> &selectedFriendIDs);
    void inviteFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const char* customTitle);
    
    void challengeFriends(const char* message);
    void challengeFriends(const char* message, const std::vector<std::string> &selectedFriendIDs);
    void challengeFriends(const char* message, const std::vector<std::string> &selectedFriendIDs, const char* customTitle);
    
    
    void sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::TYPE requestType,
                              const char* message,
                              const std::vector<std::string> &selectedFriendIDs,
                              const std::unordered_map<std::string,std::string> &dataDictionary, const char* customTitle);
    
    void checkIncomingRequest();
    
    void postPhoto(const char* imageFileName, const char* message);
    
    // Share Dialog
    void useShareDialogForLink(const char* linkURL);
    void useShareDialogForStatusForUpdate();
    void useShareDialogForOpenGraph(const char* objectType, const char* actionType,
                                    const char* title, const char* imageAddress,
                                    const char* description);
    bool canUseShareDialog();
    
    
    // Log Events...
    void logEvent(const char* eventName);
    void logEventWithValue(const char* eventName, double value);
    void logPurchase(double value, const char* currencyType);
    void setLogActiveness(bool toLogActiveness);
    
    // Open Graph actions...
    void publishOpenGraphAction(const char* objectType, const char* actionType, const char* title);
    void publishOpenGraphAction(const char* objectType, const char* actionType, const char* title, const char* imageAddress);
    void publishOpenGraphAction(const char* objectType, const char* actionType,
                                const char* title, const char* imageAddress,
                                const char* description, const char* body);
    
    void publishOpenGraphActionWithFriend(const char* friendID, const char* actionType);
    
    
    // Post Achievements
    void postAchievement(const char* achievementURL);
    
    // Twitter
    void tweet(const char* message, const char* imageURL);
    
    // Email
    void sendEmail(const char* subject, const char* htmlMessageBody, const char* semicolonSeperatedRecipents);
    
    // Network Status
    bool checkNetworkStatusForHost(const char* hostURL);
    
    bool isFacebookSessionActive();
    
    cocos2d::Sprite* generateSprite(const char* userPhoto);
    
    void setAllowIos5Fallback(bool allowed);
    
private:
    EziSocialObject();
    EziFacebookDelegate *mFacebookDelegate;
    EziTwitterDelegate *mTwitterDelegate;
    EziEmailDelegate *mEmailDelegate;
    
    EziFacebookUser* _currentUser;
    
    bool mAllowIOS_5_Fallback;
    bool mNeedsPublishPermission;
    
    /*
    void downloadPhoto(cocos2d::Node* parentNode, const char *fbID, const char* fbURL, const char* filename, bool forceDownloadFromServer);
    //void onHttpRequestCompleted(cocos2d::Node *sender, void *data);
    void onRequestCompleted(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
    */
};

#endif /* defined(__FacebookGameDemo__EziSocialObject__) */
