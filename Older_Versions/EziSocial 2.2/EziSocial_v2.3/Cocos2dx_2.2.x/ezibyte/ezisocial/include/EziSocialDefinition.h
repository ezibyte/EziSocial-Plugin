//
//  EziSocialDefinition.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//

#ifndef FacebookGameDemo_EziSocialDefinition_h
#define FacebookGameDemo_EziSocialDefinition_h

#define JNI_HELPER_PATH            "../../cocos2dx/platform/android/jni/JniHelper.h"
#define CCCOMMON_PATH              "../../cocos2dx/platform/CCCommon.h"

#define APPCONTROLLER_HEADER       "AppController.h"
#define APPCONTROLLER_CLASS_NAME   AppController

#define FACEBOOK_NAMESPACE         ""
#define FACEBOOK_OG_SERVER         ""

// For CCUserDefault. 
#define KEY_EZI_CURRENT_FB_USER_ID  "EZI_FB_CURRENT_USER_ID"

#define ENABLE_MAIL_FUNCTIONALITY
#define ENABLE_TWITTER_FUNCTIONALITY

#define KEY_FB_USER_BIRTHDAY            "birthday"
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
            REQUEST_INVITE     = 2,
            REQUEST_CUSTOM     = 3
        };
    };
    
    struct FB_FRIEND_SEARCH
    {
        enum TYPE
        {
            ALL_FRIENDS         = 0,
            ONLY_INSTALLED      = 1,
            ONLY_NOT_INSTALLED  = 2,
            ONLY_MY_DEVICES     = 3
        };
    };
    
    typedef void (*FBSessionCallback)(int, const char*, const char*);
    typedef void (*FBMessageCallback)(int, const char*);
    typedef void (*FBPageLikeCallback) (int, const char*);
    typedef void (*FBFriendsCallback)(int, const char*, const char*);
    typedef void (*FBScoresCallback)(int, const char*, const char*);
    typedef void (*FBUserDetailCallback)(int, const char*, const char*);
    typedef void (*FBPhotoPostCallback)(int, const char*);
    typedef void (*FBShareDialogCallback)(int, const char*);
    typedef void (*FBOpenGraphCallback)(int, const char*);
    typedef void (*FBAchievementCallback)(int, const char*);
    
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
            ERROR_INTERNET_NOT_AVAILABLE            = 100,
            ERROR_READ_PERMISSION_ERROR             = 101,
            ERROR_PUBLISH_PERMISSION_ERROR          = 102,
            
            // This appears if user has not setup Facebook account in iOS device settings
            FB_LOGIN_MISSING_IOS_6_ACCOUNT          = 103,
            
            // This comes if user has revoked the permission in his Facebook account to use your app.
            FB_LOGIN_USER_PERMISSION_REVOKED        = 104,
           
            // This comes if in the device settings, user has denied the Faccebook to your game.
            FB_LOGIN_APP_NOT_ALLOWERD_TO_USE_FB     = 105,
            
            // We frist needs the read permission before we actually ask for the publish permsision - iOS 6 issue.
            FB_LOGIN_FIRST_NEEDS_READ_PERMISSION    = 106,
            
            
            // This comes if user don't allow to give permission to use his facebook account for any activity.
            FB_LOGIN_PERMISSION_DENIED              = 107,
            
            FB_LOGIN_SUCCESSFUL                     = 200,
            FB_LOGIN_FAILED                         = 201,
            FB_LOGOUT_SUCCESSFUL                    = 202,
            
            FB_USER_DETAIL_ERROR                    = 210,
            FB_USER_DETAIL_SUCCESS                  = 211,
            
            // Message for user wall
            FB_NORMAL_MESSAGE_ERROR                 = 300,
            FB_NORMAL_MESSAGE_CANCELLED             = 301,
            FB_NORMAL_MESSAGE_PUBLISHED             = 302,
            
            // Auto Post Message on User Wall
            FB_AUTO_MESSAGE_ERROR                   = 303,
            FB_AUTO_MESSAGE_PUBLISHED               = 304,

            // Submit Score to Facebook
            FB_SCORE_POSTING_ERROR                  = 400,
            FB_SCORE_POSTED                         = 401,
            FB_SCORE_DELETE_ERROR                   = 402,
            FB_SCORE_DELETED                        = 403,
            FB_HIGH_SCORE_GET_ERROR                 = 404,
            FB_HIGH_SCORE_SUCCESS                   = 405,
            
            // Facebook Request
            FB_REQUEST_SENDING_ERROR                = 500,
            FB_REQUEST_SENDING_CANCELLED            = 501,
            FB_REQUEST_SENT                         = 502,
            
            // Page Like
            FB_PAGELIKE_ERROR           = 600,
            FB_PAGELIKE_NEGATIVE        = 601,
            FB_PAGELIKE_POSITIVE        = 602,
            
            // Facebook Friends
            FB_FRIEND_GET_ERROR         = 650,
            FB_FRIEND_GET_SUCCESS       = 651,
            
            // Post Photo Callback
            FB_INVALID_IMAGE_FILE       = 652,
            FB_PHOTO_POST_ERROR         = 653,
            FB_PHOTO_POST_SUCCESS       = 654,
            
            // Requests Responses
            FB_REQUEST_RECEIVE_ALREADY_FETCHED_ERROR    = 700,
            FB_REQUEST_RECEIVE_SESSION_ERROR            = 701,
            
            FB_INCOMING_REQUEST_ERROR   = 702,
            FB_INCOMING_REQUEST_NEW     = 703,
            FB_NO_NEW_INCOMING_REQUEST  = 704,
            
            FB_CHALLENGE_RECEIVE  = 705,
            FB_GIFT_RECEIVE       = 706,
            FB_INVITE_RECEIVE     = 707,
            
            // Share Dialog
            FB_SHARE_DIALOG_ERROR       = 800,
            FB_SHARE_DIALOG_SUCCESS     = 801,
            FB_SHARE_DIALOG_CANCELLED   = 802,
            
            // Achievements
            FB_ACHIEVEMENT_ERROR        = 810,
            FB_ACHIEVEMENT_SUCCESS      = 811,
            
            // Open Graph
            FB_OPEN_GRAPH_ERROR         = 900,
            FB_OPEN_GRAPH_PUBLISHED     = 901,
            
            // Email Response Code
            MAIL_SEND_ERROR     = 1000,
            MAIL_SEND_SUCCESS   = 1001,
            MAIL_SEND_CANCLLED  = 1002,
            MAIL_SEND_STORED    = 1003,

            // Twitter Response Code
            TWIT_SEND   = 1100,
            TWIT_CANCEL = 1101
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
                     	const char* preselectedFriends, const char* customTitle);
    
        void processRequestID(FBRecieveRequestCallback callback, const char* requestID);
    
        void setIncomingRequestCallback(FBIncomingRequestCallback callback, FBRecieveRequestCallback requestCallback);
    
        void checkIncomingRequests();
        void setAutoCheckIncomingRequestsOnAppLaunch(bool toAllow);
    
        bool isFacebookSessionActive();
    
    
        // Achievements
        void publishAchievement(const char* achievementURL, FBAchievementCallback achievementCallback);
    
        // Publish Open Graph Action
        void publishOpenGraphAction(const char* serverAddress, const char* namespcae,
                                    const char* objectType, const char* actionType,
                                    const char* title, const char* imageAddress,
                                    const char* description, const char* body,
                                    FBOpenGraphCallback openGraphCallback);
    
        void publishOpenGraphActionForProfile(const char *friendProfileID,
                                                              const char *namespcae,
                                                              const char *actionType,
                                              FBOpenGraphCallback openGraphCallback);

    
        // Share Dialog
        void shareLink(const char* linkURL, FBShareDialogCallback shareDialogCallback);
        void shareOpenGraph(const char* serverAddress, const char* namespcae,
                        const char* objectType, const char* actionType,
                        const char* title, const char* imageAddress,
                        const char* description, FBShareDialogCallback callback);
    
        bool canUseShareDialogs();
    
        // LogEvents
        void logEvent(const char* eventName);
        void logEventWithValue(const char* eventName, double value);
        void logPurchase(double value, const char* currencyType);
        void setLoggingActiveness(bool toLogActiveness);
    
        // Twitter Methods...
        void tweet(TwitterCallback callback, const char* message, const char* imageURL);
    
        // Email Methods
        void sendEmail(const char* subject, const char* messageBody, const char* recipents, MailCallback callback);
    
        // Network Status
        bool networkAvailableForHost(const char* hostURL);
    

}

#endif
