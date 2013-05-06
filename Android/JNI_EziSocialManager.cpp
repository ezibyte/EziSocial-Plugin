//
//  JNI_EziSocialManager.cpp
//  EziSocial Plugin
//
//  Created by Paras Mendiratta on 11/04/13.
//
//
/***
 
 This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source distribution.
 
 */

#include "EziSocialDefinition.h"
#include "cocos2d.h"
#include "EziSocialObject.h"
#include <string.h>
#include <jni.h>

#include JNI_HELPER_PATH
#include CCCOMMON_PATH

#pragma mark - Facebook Login/Logout/Session Check

// User Login
void EziSocialWrapperNS::loginWithFacebook(EziSocialWrapperNS::FBSessionCallback callback)
{
    //cocos2d::CCMessageBox("Menu Action: Login Via Facebook pressed", "Login - Facebook (JNI)");
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "loginWithFacebook",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

bool EziSocialWrapperNS::isFacebookSessionActive()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "isFacebookSessionActive",
                                                "(J)Z"))
    {
        jlong arg = (long)(void*)0;
        jboolean result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
        
        return (result == JNI_TRUE);
    }
    else
    {
        return false;
    }
    
}

// User logout
void EziSocialWrapperNS::logoutFromFacebook(EziSocialWrapperNS::FBSessionCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "logoutFromFacebook",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#pragma mark - Facebook Post Message / Score

// Post message on User Wall
void EziSocialWrapperNS::postMessage(EziSocialWrapperNS::FBMessageCallback callback,
                                     const char* heading,
                                     const char* caption,
                                     const char* description,
                                     const char* badgeIconURL,
                                     const char* deepLinkURL)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "postMessageOnWall",
                                                "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jlong arg = (long)(void*)callback;
        jstring headingArg = t.env->NewStringUTF(heading);
        jstring captionArg = t.env->NewStringUTF(caption);
        jstring descArg = t.env->NewStringUTF(description);
        jstring badgeArg = t.env->NewStringUTF(badgeIconURL);
        jstring deepArg = t.env->NewStringUTF(deepLinkURL);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, headingArg, captionArg, descArg, badgeArg, deepArg);
        
        t.env->DeleteLocalRef(headingArg);
        t.env->DeleteLocalRef(captionArg);
        t.env->DeleteLocalRef(descArg);
        t.env->DeleteLocalRef(badgeArg);
        t.env->DeleteLocalRef(deepArg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void EziSocialWrapperNS::autoPostMessageOnWall(EziSocialWrapperNS::FBMessageCallback callback,
                                               const char* heading,
                                               const char* caption,
                                               const char* description,
                                               const char* badgeIconURL,
                                               const char* deepLinkURL)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "autoPostMessageOnWall",
                                                "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jlong arg = (long)(void*)callback;
        jstring headingArg = t.env->NewStringUTF(heading);
        jstring captionArg = t.env->NewStringUTF(caption);
        jstring descArg = t.env->NewStringUTF(description);
        jstring badgeArg = t.env->NewStringUTF(badgeIconURL);
        jstring deepArg = t.env->NewStringUTF(deepLinkURL);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, headingArg, captionArg, descArg, badgeArg, deepArg);
        
        t.env->DeleteLocalRef(headingArg);
        t.env->DeleteLocalRef(captionArg);
        t.env->DeleteLocalRef(descArg);
        t.env->DeleteLocalRef(badgeArg);
        t.env->DeleteLocalRef(deepArg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void EziSocialWrapperNS::postScore(EziSocialWrapperNS::FBMessageCallback callback,
                                   unsigned long long score)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "postScore",
                                                "(JD)V"))
    {
        jlong arg = (long)(void*)callback;
        jdouble arg2 = score;
        //jstring scoreArg = t.env->NewStringUTF(score);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2);
        
        //t.env->DeleteLocalRef(scoreArg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#pragma mark - Facebook Page Methods

void EziSocialWrapperNS::openFacebookPage(const char* pageID, bool checkPageLike, EziSocialWrapperNS::FBPageLikeCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "openFacebookPage",
                                                "(JLjava/lang/String;Z)V"))
    {
        jlong arg = (long)(void*)callback;
        jstring arg2 = t.env->NewStringUTF(pageID);
        jboolean arg3 = checkPageLike;
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2, arg3);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

// Check if user has liked my page
void EziSocialWrapperNS::hasUserLikePage(EziSocialWrapperNS::FBPageLikeCallback callback,
                                         const char*pageID)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "checkIfUserLikeFacebookPage",
                                                "(JLjava/lang/String;)V"))
    {
        jlong arg = (long)(void*)callback;
        jstring arg2 = t.env->NewStringUTF(pageID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2);
        //t.env->DeleteLocalRef(arg);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

#pragma mark - Facebook Friends

void EziSocialWrapperNS::getHighScores(EziSocialWrapperNS::FBHighScoresCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "getHighScores",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
    }
}

#pragma mark - Facebook Requests

void EziSocialWrapperNS::sendRequest(EziSocialWrapperNS::FBSendRequestCallback callback,
                                     EziSocialWrapperNS::FB_REQUEST::TYPE requestType,
                                     const char* message,
                                     const char* dataDictionary,
                                     const char* preselectedFriends)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "sendRequestToFriends",
                                                "(JLjava/lang/String;ILjava/lang/String;Ljava/lang/String;)V"))
    {
        jlong arg = (long)(void*)callback;
        jint  requestInt = (int)requestType;
        jstring messageString = t.env->NewStringUTF(message);
        jstring dataString = t.env->NewStringUTF(dataDictionary);
        jstring friendsString = t.env->NewStringUTF(preselectedFriends);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, friendsString, requestInt, messageString, dataString);
        
        t.env->DeleteLocalRef(friendsString);
        t.env->DeleteLocalRef(messageString);
        t.env->DeleteLocalRef(dataString);
        t.env->DeleteLocalRef(t.classID);
    }
}

void EziSocialWrapperNS::setRequestRecievedCallback(EziSocialWrapperNS::FBRecieveRequestCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "setRequestReceiveCallbackAddress",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#pragma mark - Facebook User details

// User details
void EziSocialWrapperNS::fetchUserDetails(EziSocialWrapperNS::FBUserDetailCallback callback, bool getEmailIDAlso)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "getUserDetails",
                                                "(JZ)V"))
    {
        jlong arg = (long)(void*)callback;
        jboolean arg2 = getEmailIDAlso;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

// Get the list of friends who are using this app.
void EziSocialWrapperNS::getFriends(EziSocialWrapperNS::FBFriendsCallback callback,
                                    EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType,
                                    int startIndex, int limit)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "getFriends",
                                                "(JIII)V"))
    {
        jlong arg           = (long)(void*)callback;
        jint  searchTypeArg = (int) searchType;
        jint  startIndexArg = (int) startIndex;
        jint  limitArg      = (int) limit;
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, searchTypeArg, startIndexArg, limitArg);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#pragma mark - Twitter - Tweet

void EziSocialWrapperNS::tweet(const char* message, const char* imageURL)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "tweet",
                                                "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring arg  = t.env->NewStringUTF(message);
        jstring arg2 = t.env->NewStringUTF(imageURL);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2);
        t.env->DeleteLocalRef(arg);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#pragma mark - Send Email

void EziSocialWrapperNS::sendEmail(const char* subject,
                                   const char* messageBody,
                                   const char* recipents,
                                   EziSocialWrapperNS::MailCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "sendEmail",
                                                "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jlong arg = (long)(void*)callback;
        jstring arg2 = t.env->NewStringUTF(subject);
        jstring arg3 = t.env->NewStringUTF(messageBody);
        jstring arg4 = t.env->NewStringUTF(recipents);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg, arg2, arg3, arg4);
        
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(arg3);
        t.env->DeleteLocalRef(arg4);
        t.env->DeleteLocalRef(t.classID);
    }
}

#pragma mark - Check Network Status
bool EziSocialWrapperNS::networkAvailableForHost(const char* hostURL)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "androidNetworkStatus",
                                                "(JLjava/lang/String;)Z"))
    {
        jlong arg = (long)(void*)0;
        jstring arg2 = t.env->NewStringUTF(hostURL);
        jboolean result = t.env->CallStaticBooleanMethod(t.classID, t.methodID, arg, arg2);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(t.classID);
        
        return (result == JNI_TRUE);
    }
    else
    {
        return false;
    }
    
}




// ------------------------------------
#pragma mark - Callback Methods
// ------------------------------------

extern "C"
{
	void Java_com_ezibyte_social_EziSocialManager_nativeFBSessionRequestComplete(JNIEnv* env,
                                                                                 jobject thiz,
                                                                                 jlong callback_address,
                                                                                 jint responseCode)
	{
		if (callback_address)
        {
			(*reinterpret_cast<EziSocialWrapperNS::FBSessionCallback>(callback_address))(responseCode);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFBMessageRequestComplete(JNIEnv* env,
                                                                                 jobject thiz,
                                                                                 jlong callback_address,
                                                                                 jint responseCode)
	{
		if (callback_address)
        {
			(*reinterpret_cast<EziSocialWrapperNS::FBMessageCallback>(callback_address))(responseCode);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFBPageLikeRequestComplete(JNIEnv* env,
                                                                                  jobject thiz,
                                                                                  jlong callback_address,
                                                                                  jint responseCode)
	{
		if (callback_address)
        {
			(*reinterpret_cast<EziSocialWrapperNS::FBPageLikeCallback>(callback_address))(responseCode);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFBFriendsRequestComplete(JNIEnv* env,
                                                                                 jobject thiz,
                                                                                 jlong callback_address,
                                                                                 jstring resultString)
    {
        if (callback_address)
        {
            const char* resultData = env->GetStringUTFChars(resultString, 0);
            (*reinterpret_cast<EziSocialWrapperNS::FBFriendsCallback>(callback_address))(resultData);
        }
        
        //env->DeleteLocalRef(stringArray);
    }
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFBUserDetailsRequestComplete(JNIEnv* env,
                                                                                     jobject thiz,
                                                                                     jlong callback_address,
                                                                                     jstring response)
    {
        if (callback_address)
        {
            const char *rawString = env->GetStringUTFChars(response, 0);
            (*reinterpret_cast<EziSocialWrapperNS::FBUserDetailCallback>(callback_address))(rawString);
            
        }
    }
    
    void Java_com_ezibyte_social_EziSocialManager_nativeSendMailRequestComplete(JNIEnv* env,
                                                                                jobject thiz,
                                                                                jlong callback_address,
                                                                                jint responseCode)
	{
		if (callback_address)
        {
			(*reinterpret_cast<EziSocialWrapperNS::MailCallback>(callback_address))(responseCode);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFBHighScoreRequestComplete(JNIEnv* env,
                                                                                   jobject thiz,
                                                                                   jlong callback_address,
                                                                                   jstring response)
	{
		if (callback_address)
        {
            const char *rawString = env->GetStringUTFChars(response, 0);
			(*reinterpret_cast<EziSocialWrapperNS::FBHighScoresCallback>(callback_address))(rawString);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeRequestSentCallback(JNIEnv* env,
                                                                            jobject thiz,
                                                                            jlong callback_address,
                                                                            jint  responseCode,
                                                                            jstring responseData)
	{
		if (callback_address)
        {
            int responseCodeInt = (int)responseCode;
            const char *rawString = env->GetStringUTFChars(responseData, 0);
			(*reinterpret_cast<EziSocialWrapperNS::FBSendRequestCallback>(callback_address))(responseCodeInt, rawString);
        }
	}
    
    void Java_com_ezibyte_social_EziSocialManager_nativeFacebookRequestReceived(JNIEnv* env,
                                                                                jobject thiz,
                                                                                jlong callback_address,
                                                                                jint responseCode,
                                                                                jstring message,
                                                                                jstring senderName,
                                                                                jstring data)
	{
		if (callback_address)
        {
            const char *rawMessage    = env->GetStringUTFChars(message, 0);
            const char *rawSenderName = env->GetStringUTFChars(senderName, 0);
            const char *rawData       = env->GetStringUTFChars(data, 0);
            int responseType          = (int) responseCode;
            
			(*reinterpret_cast<EziSocialWrapperNS::FBRecieveRequestCallback>(callback_address))(responseType, rawMessage, rawSenderName, rawData);
        }
	}
    
};



