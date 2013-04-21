//
//  JNI_EziSocialManager.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//

#include "EziSocialDefinition.h"
#include "cocos2d.h"
#include "EziSocialObject.h"
#include <string.h>
#include <jni.h>

#include JNI_HELPER_PATH
#include CCCOMMON_PATH

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
    
    /*
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getMethodInfo(t,
                                          "com/ezibyte/social/EziSocialManager",
                                          "checkNetworkStatusInJava",
                                          "()V"))
    {
        jstring  arg = t.env->NewStringUTF(hostURL);
        //jboolean ret = t.env->CallBooleanMethod(t.classID, t.methodID);
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(arg);
        t.env->DeleteLocalRef(t.classID);

        //return ret == JNI_TRUE;
        return JNI_TRUE;
    }
    else
    {
        return false;
    }
     */
}

// User details
void EziSocialWrapperNS::fetchUserDetails(EziSocialWrapperNS::FBUserDetailCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "getUserDetails",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
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

// Get the list of friends who are using this app.
void EziSocialWrapperNS::getListOfFriendsUsingThisApp(EziSocialWrapperNS::FBFriendsCallback callback)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "com/ezibyte/social/EziSocialManager",
                                                "getFriendsPlayingThisGame",
                                                "(J)V"))
    {
        jlong arg = (long)(void*)callback;
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg);
        t.env->DeleteLocalRef(t.classID);
    }

}

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
    
   
    
};



