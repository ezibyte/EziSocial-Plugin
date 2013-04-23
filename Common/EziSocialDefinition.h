//
//  EziSocialDefinition.h
//  EziSocial
//
//  Created by Paras Mendiratta on 11/04/13.
//  Copyright @EziByte 2013
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
#define APPCONTROLLER_HEADER       "AppController.h"
#define APPCONTROLLER_CLASS_NAME   AppController

#define FACEBOOK_PAGE_ID    "377572839023945"

#define ENABLE_MAIL_FUNCTIONALITY
#define ENABLE_TWITTER_FUNCTIONALITY

#define KEY_FB_USER_NAME                "username"
#define KEY_FB_USER_EMAIL               "email"
#define KEY_FB_USER_GENDER              "gender"
#define KEY_FB_USER_HOMETOWN            "hometown"
#define KEY_FB_USER_PRESENT_LOCATION    "location"
#define KEY_FB_USER_PROFILE_ID          "id"
#define KEY_FB_USER_FIRST_NAME          "first_name"
#define KEY_FB_USER_LAST_NAME           "last_name"
#define KEY_FB_USER_ACCESS_TOKEN        "token"

namespace EziSocialWrapperNS
{
    typedef void (*FBSessionCallback)(int);
    typedef void (*FBMessageCallback)(int);
    typedef void (*FBPageLikeCallback) (int);
    typedef void (*FBFriendsCallback)(const char*);
    typedef void (*FBHighScoresCallback)(const char*);
    typedef void (*FBUserDetailCallback)(const char*);
    typedef void (*MailCallback)(int);
    
    struct RESPONSE_CODE
    {
        enum
        {
            // Login response code
            FB_LOGIN_NO_TOKEN           = 0,
            FB_LOGIN_SUCCESSFUL         = 1,
            FB_LOGIN_FAILED             = 2,
            FB_LOGOUT_SUCCESSFUL        = 3,
            
            // Message for user wall
            FB_MESSAGE_PUBLISHING_ERROR = 4,
            FB_MESSAGE_CANCELLLED       = 5,
            FB_MESSAGE_PUBLISHED        = 6,
            
            // Gift Items
            FB_GIFT_SENDING_ERROR       = 7,
            FB_GIFT_SENDING_CANCELLED   = 8,
            FB_GIFT_SENT                = 9,
            
            // Challenges
            FB_CHALLENGE_SENDING_ERROR  = 10,
            FB_CHALLEGE_CANCELLED       = 11,
            FB_CHALLEGE_PUBLISHED       = 12,
            
            // Page Like
            FB_PAGELIKE_ERROR           = 13,
            FB_PAGELIKE_NEGATIVE        = 14,
            FB_PAGELIKE_POSITIVE        = 15,
            
            // Email Response Code
            MAIL_SEND_ERROR             = 16,
            MAIL_SEND_SUCCESS           = 17,
            MAIL_SEND_CANCLLED          = 18,
            MAIL_SEND_STORED            = 19,
            
        };
    };
    
    
    // Messages
    void postMessage(FBMessageCallback callback,
                     const char* heading,
                     const char* caption,
                     const char* description,
                     const char* badgeIconURL,
                     const char* deepLinkURL);
    
    void autoPostMessageOnWall(FBMessageCallback callback,
                               const char* heading,
                               const char* caption,
                               const char* description,
                               const char* badgeIconURL,
                               const char* deepLinkURL);
    
    
    void postScore(EziSocialWrapperNS::FBMessageCallback callback,
                   unsigned long long score);
    
    // User details
    void fetchUserDetails(FBUserDetailCallback callback);
    
    // User login / logout
    void loginWithFacebook(FBSessionCallback callback);
    void logoutFromFacebook(FBSessionCallback callback);
    
    // Check if user has liked my page
    void hasUserLikePage(FBPageLikeCallback callback, const char*pageID);
    
    // Get the list of friends who are using this app.
    void getListOfFriendsUsingThisApp(FBFriendsCallback callback);
    
    
    void getHighScores(FBHighScoresCallback callback);
    
    void openFacebookPage(const char* pageID, bool checkPageLike, FBPageLikeCallback callback);
    
    // Twitter Methods...
    void tweet(const char* message, const char* imageURL);
    
    // Email Methods
    void sendEmail(const char* subject, const char* messageBody, const char* recipents, MailCallback callback);
    
    bool networkAvailableForHost(const char* hostURL);
}

#endif
