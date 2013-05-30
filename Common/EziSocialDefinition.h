//
//  EziSocialDefinition.h
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


#ifndef FacebookGameDemo_EziSocialDefinition_h
#define FacebookGameDemo_EziSocialDefinition_h

#define JNI_HELPER_PATH            "../../cocos2dx/platform/android/jni/JniHelper.h"
#define CCCOMMON_PATH              "../../cocos2dx/platform/CCCommon.h"
#define FACEBOOK_PAGE_ID           "377572839023945"

#define APPCONTROLLER_HEADER       "AppController.h"
#define APPCONTROLLER_CLASS_NAME   AppController

// For CCUserDefault.
#define KEY_EZI_CURRENT_FB_USER_ID  "EZI_FB_CURRENT_USER_ID"

#define ENABLE_MAIL_FUNCTIONALITY
#define ENABLE_TWITTER_FUNCTIONALITY

#define KEY_FB_USER_ERROR               "error"
#define KEY_FB_USER_NAME                "username"
#define KEY_FB_USER_EMAIL               "email"
#define KEY_FB_USER_GENDER              "gender"
#define KEY_FB_USER_HOMETOWN            "hometown"
#define KEY_FB_USER_PRESENT_LOCATION    "location"
#define KEY_FB_USER_PROFILE_ID          "id"
#define KEY_FB_USER_FIRST_NAME          "first_name"
#define KEY_FB_USER_LAST_NAME           "last_name"
#define KEY_FB_USER_ACCESS_TOKEN        "token"

// This value defines the number of records can be hold by Completed Requests List.
#define MAX_COMPLETED_REQUEST_ID_TO_HOLD 20

// This clears the top 10 records from the completed request list. Change the value if don't want to clear it.
#define NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS 10

#include <iostream>

namespace EziSocialWrapperNS
{
    
    struct FB_REQUEST
    {
        enum TYPE
        {
            REQUEST_GIFT       = 0,
            REQUEST_CHALLENGE  = 1,
            REQUEST_INVITE     = 2
        };
    };
    
    struct FB_FRIEND_SEARCH
    {
        enum TYPE
        {
            ALL_FRIENDS         = 0,
            ONLY_INSTALLED      = 1,
            ONLY_NOT_INSTALLED  = 2
        };
    };
    
    typedef void (*FBSessionCallback)(int, const char*, const char*);
    typedef void (*FBMessageCallback)(int, const char*);
    typedef void (*FBPageLikeCallback) (int, const char*);
    typedef void (*FBFriendsCallback)(int, const char*, const char*);
    typedef void (*FBScoresCallback)(int, const char*, const char*);
    typedef void (*FBUserDetailCallback)(int, const char*, const char*);
    typedef void (*FBPhotoPostCallback)(int, const char*);
    typedef void (*MailCallback)(int);
    
    //typedef void (*FBPUserPhotoCallback)(const char*);
    
    // Request Callbacks
    typedef void (*FBSendRequestCallback)(int, const char*, const char*);
    typedef void (*FBIncomingRequestCallback)(int, const char*, const char*);
    typedef void (*FBRecieveRequestCallback)(int, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
    
    // Twitter Callback
    typedef void (*TwitterCallback)(int);
    
    
    struct FBUSER
    {
        enum PROFILE_PIC_TYPE
        {
            PIC_SQUARE      = 0,
            PIC_SMALL       = 1,
            PIC_NORMAL      = 2,
            PIC_LARGE       = 3
        };
    };
    
    struct RESPONSE_CODE
    {
        enum
        {
            // Internet connection error while making the request.
            ERROR_INTERNET_NOT_AVAILABLE            = 0,
            ERROR_READ_PERMISSION_ERROR             = ERROR_INTERNET_NOT_AVAILABLE + 1,
            ERROR_PUBLISH_PERMISSION_ERROR          = ERROR_READ_PERMISSION_ERROR + 1,
            
            // This appears if user has not setup Facebook account in iOS device settings
            FB_LOGIN_MISSING_IOS_6_ACCOUNT      = ERROR_PUBLISH_PERMISSION_ERROR + 1,
            
            // This comes if user has revoked the permission in his Facebook account to use your app.
            FB_LOGIN_USER_PERMISSION_REVOKED         = FB_LOGIN_MISSING_IOS_6_ACCOUNT + 1,
            
            // This comes if in the device settings, user has denied the Faccebook to your game.
            FB_LOGIN_APP_NOT_ALLOWERD_TO_USE_FB = FB_LOGIN_USER_PERMISSION_REVOKED + 1,
            
            // We frist needs the read permission before we actually ask for the publish permsision - iOS 6 issue.
            FB_LOGIN_FIRST_NEEDS_READ_PERMISSION = FB_LOGIN_APP_NOT_ALLOWERD_TO_USE_FB + 1,
            
            
            // This comes if user don't allow to give permission to use his facebook account for any activity.
            FB_LOGIN_PERMISSION_DENIED = FB_LOGIN_FIRST_NEEDS_READ_PERMISSION + 1,
            
            FB_LOGIN_SUCCESSFUL         = FB_LOGIN_PERMISSION_DENIED     + 1,
            FB_LOGIN_FAILED             = FB_LOGIN_SUCCESSFUL   + 1,
            FB_LOGOUT_SUCCESSFUL        = FB_LOGIN_FAILED       + 1,
            
            FB_USER_DETAIL_ERROR        = FB_LOGOUT_SUCCESSFUL + 1,
            FB_USER_DETAIL_SUCCESS      = FB_USER_DETAIL_ERROR + 1,
            
            // Message for user wall
            FB_NORMAL_MESSAGE_ERROR     = FB_USER_DETAIL_SUCCESS        + 1,
            FB_NORMAL_MESSAGE_CANCELLED = FB_NORMAL_MESSAGE_ERROR       + 1,
            FB_NORMAL_MESSAGE_PUBLISHED = FB_NORMAL_MESSAGE_CANCELLED   + 1,
            
            // Auto Post Message on User Wall
            FB_AUTO_MESSAGE_ERROR       = FB_NORMAL_MESSAGE_PUBLISHED   + 1,
            FB_AUTO_MESSAGE_PUBLISHED   = FB_AUTO_MESSAGE_ERROR         + 1,
            
            // Submit Score to Facebook
            FB_SCORE_POSTING_ERROR      = FB_AUTO_MESSAGE_PUBLISHED     + 1,
            FB_SCORE_POSTED             = FB_SCORE_POSTING_ERROR        + 1,
            FB_SCORE_DELETE_ERROR       = FB_SCORE_POSTED               + 1,
            FB_SCORE_DELETED            = FB_SCORE_DELETE_ERROR         + 1,
            FB_HIGH_SCORE_GET_ERROR     = FB_SCORE_DELETED              + 1,
            FB_HIGH_SCORE_SUCCESS       = FB_HIGH_SCORE_GET_ERROR       + 1,
            
            // Gift Items
            FB_GIFT_SENDING_ERROR       = FB_HIGH_SCORE_SUCCESS     + 1,
            FB_GIFT_SENDING_CANCELLED   = FB_GIFT_SENDING_ERROR     + 1,
            FB_GIFT_SENT                = FB_GIFT_SENDING_CANCELLED + 1,
            
            // Challenges
            FB_CHALLENGE_SENDING_ERROR  = FB_GIFT_SENT                  + 1,
            FB_CHALLEGE_CANCELLED       = FB_CHALLENGE_SENDING_ERROR    + 1,
            FB_CHALLEGE_SENT            = FB_CHALLEGE_CANCELLED         + 1,
            
            // Invite
            FB_INVITE_SENDING_ERROR     = FB_CHALLEGE_SENT          + 1,
            FB_INVITE_CANCELLED         = FB_INVITE_SENDING_ERROR   + 1,
            FB_INVITE_SENT              = FB_INVITE_CANCELLED       + 1,
            
            // Page Like
            FB_PAGELIKE_ERROR           = FB_INVITE_SENT        + 1,
            FB_PAGELIKE_NEGATIVE        = FB_PAGELIKE_ERROR     + 1,
            FB_PAGELIKE_POSITIVE        = FB_PAGELIKE_NEGATIVE  + 1,
            
            // Facebook Friends
            FB_FRIEND_GET_ERROR         = FB_PAGELIKE_POSITIVE    + 1,
            FB_FRIEND_GET_SUCCESS       = FB_FRIEND_GET_ERROR     + 1,
            
            // Email Response Code
            MAIL_SEND_ERROR             = FB_FRIEND_GET_SUCCESS + 1,
            MAIL_SEND_SUCCESS           = MAIL_SEND_ERROR       + 1,
            MAIL_SEND_CANCLLED          = MAIL_SEND_SUCCESS     + 1,
            MAIL_SEND_STORED            = MAIL_SEND_CANCLLED    + 1,
            
            // Recieve
            FB_REQUEST_RECEIVE_ALREADY_FETCHED_ERROR    = MAIL_SEND_STORED                          + 1,
            FB_REQUEST_RECEIVE_SESSION_ERROR            = FB_REQUEST_RECEIVE_ALREADY_FETCHED_ERROR  + 1,
            
            FB_INCOMING_REQUEST_ERROR   = FB_REQUEST_RECEIVE_SESSION_ERROR + 1,
            FB_INCOMING_REQUEST_NEW     = FB_INCOMING_REQUEST_ERROR        + 1,
            FB_NO_NEW_INCOMING_REQUEST  = FB_INCOMING_REQUEST_NEW          + 1,
            
            FB_CHALLENGE_RECEIVE  = FB_NO_NEW_INCOMING_REQUEST  + 1,
            FB_GIFT_RECEIVE       = FB_CHALLENGE_RECEIVE        + 1,
            FB_INVITE_RECEIVE     = FB_GIFT_RECEIVE             + 1,
            
            // Post Photo Callback
            FB_INVALID_IMAGE_FILE = FB_INVITE_RECEIVE       + 1,
            FB_PHOTO_POST_ERROR   = FB_INVALID_IMAGE_FILE   + 1,
            FB_PHOTO_POST_SUCCESS = FB_PHOTO_POST_ERROR     + 1,
            
            // Twitter Response Code
            TWIT_SEND   = FB_PHOTO_POST_SUCCESS + 1,
            TWIT_CANCEL = TWIT_SEND             + 1
        };
    };
    
    
    // Messages
    void postMessage(FBMessageCallback callback,
                     const char* heading,
                     const char* caption,
                     const char* message,
                     const char* description,
                     const char* badgeIconURL,
                     const char* deepLinkURL);
    
    void autoPostMessageOnWall(FBMessageCallback callback,
                               const char* heading,
                               const char* caption,
                               const char* message,
                               const char* description,
                               const char* badgeIconURL,
                               const char* deepLinkURL);
    
    
    void postScore(EziSocialWrapperNS::FBMessageCallback callback,
                   unsigned long long score);
    
    // Deletes the user score from the Facebook.
    void deleteScore(EziSocialWrapperNS::FBMessageCallback callback);
    
    // User details
    void fetchUserDetails(FBUserDetailCallback callback, bool getEmailIDAlso);
    
    // User login / logout
    void loginWithFacebook(FBSessionCallback callback, bool needsPublishPermission);
    void logoutFromFacebook(FBSessionCallback callback);
    
    // Check if user has liked my page
    void hasUserLikePage(FBPageLikeCallback callback, const char*pageID);
    
    // Get friends
    void getFriends(FBFriendsCallback callback, FB_FRIEND_SEARCH::TYPE searchType, int startIndex, int limit);
    
    // Get the high score of user and his friends.
    void getHighScores(FBScoresCallback callback);
    
    // Open Facebook Page and on returing back to application, check if user likes Facebook page.
    void openFacebookPage(const char* pageID, bool checkPageLike, FBPageLikeCallback callback);
    
    // Post the image on facebook user wall.
    void postPhoto(const char* imageFileName, const char* message, FBPhotoPostCallback callback);
    
    /*
     // Get the user photo.
     void getUserPhoto(FBPUserPhotoCallback callback, FBUSER::PROFILE_PIC_TYPE picType, int width, int height);
     void getUserPhoto(FBPUserPhotoCallback callback, FBUSER::PROFILE_PIC_TYPE picType, int width, int height, const char* fbuid);
     */
    
    void sendRequest(FBSendRequestCallback callback,
                     FB_REQUEST::TYPE requestType,
                     const char* message,
                     const char* dataDictionary,
                     const char* preselectedFriends);
    
    void processRequestID(FBRecieveRequestCallback callback, const char* requestID);
    
    void setIncomingRequestCallback(FBIncomingRequestCallback callback, FBRecieveRequestCallback requestCallback);
    
    void checkIncomingRequests();
    
    bool isFacebookSessionActive();
    
    // Twitter Methods...
    void tweet(TwitterCallback callback, const char* message, const char* imageURL);
    
    // Email Methods
    void sendEmail(const char* subject, const char* messageBody, const char* recipents, MailCallback callback);
    
    // Network Status
    bool networkAvailableForHost(const char* hostURL);
    
    
}

#endif
