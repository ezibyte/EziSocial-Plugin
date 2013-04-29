EziSocial-Plugin
================

EziSocial plugin uses common development code for both Android and iOS Cocos2D-x project. So, there is no duplicity of code and you need not to worry about portability issue at all.

There are some basic features of EziSocial Plugin, we will cover them one by one in detail. In case, if you want to explore it first then you can just download the sample code, compile it and run it our your devices or emulators. Here is the download link for the demo application.

Facebook
--------
1. Login via Facebook
2. Logout from Facebook
3. Get user details
4. Open Facebook Page
5. Auto check Facebook likt to your page, when user come back to your game from your page.
6. Check Facebook like to your page anytime during the time app is running.
7. Get the list of friends of the user who are playing your game
8. Post message on the user’s timeline.
9. Auto post message or achievement on user’s timeline without notifying him.
10. Post Score – uses advance feature of Facebook Score Graph API. All scores are stored online at Facebook.com as per Facebook.
11. Get high scores – fetch the scores of the friends of the user playing same game in unsorted order. You can sort it at your end.

Twitter
-------
1. Tweet - Uses native twitter client of the device to tweet message on the user’s timeline.

Internet Status
---------------
1. Internet Connection - allows you to check the internet connection anytime in the game. 
2. It also gives option to you to check that if a particular website is reachable or not.

Email
-----
Email - Allows you to preconfigure the mail and allows user to send the mail to you or their friends.

How to use this plugin
----------------------
To know about how to use this plugin, please visit site: http://www.ezibyte.com


=========================================
Version 1.0.1 - Pushed on 30th April 2013
=========================================

Added two new methods:

1. bool isUserAlreadyLoginedToFacebook_Or_IsSessionActive = EziSocialObject::sharedObject()->isFacebookSessionActive();

While app is running, anytime if you like to know if user is actually logined to Facebook or not. Or whether session is expired or not. Just simply called above method.
There is no callback method of this and result will immediately return.

2. EziSocialObject::sharedObject()->fetchFBUserDetails(true);

Definition of fetchUserDetails has been changed. Now you can actually fetch user email ID also. To get the user email ID, pass the value as true otherwise false.

NOTE: If ask for user email ID, then first time it will ask extra permission from the app user to allow your app to see user email ID.

HOW TO CHECK IF USER ALLOWED TO SEE HIS EMAIL ID OR NOT
-------------------------------------------------------

In case user decide not to send you the email ID then in callback method, within Data Dictionary an Error message will return.

Use can check the error message as follows:-

-------- CODE START -----------

if (data)
    {
        if (data->objectForKey(KEY_FB_USER_ERROR))
        {
            CCMessageBox(((CCString*)(data->objectForKey(KEY_FB_USER_ERROR)))->getCString(), "Error");
            return;
        }
        
        mUsername->setString(((CCString*)(data->objectForKey(KEY_FB_USER_NAME)))->getCString());
        mGender->setString(((CCString*)(data->objectForKey(KEY_FB_USER_GENDER)))->getCString());
        mHometown->setString(((CCString*)(data->objectForKey(KEY_FB_USER_HOMETOWN)))->getCString());
        mPresentLocation->setString(((CCString*)(data->objectForKey(KEY_FB_USER_PRESENT_LOCATION)))->getCString());
        mProfileID->setString(((CCString*)(data->objectForKey(KEY_FB_USER_PROFILE_ID)))->getCString());
        mFirstName->setString(((CCString*)(data->objectForKey(KEY_FB_USER_FIRST_NAME)))->getCString());
        mLastName->setString(((CCString*)(data->objectForKey(KEY_FB_USER_LAST_NAME)))->getCString());
        mAccessToken->setString(((CCString*)(data->objectForKey(KEY_FB_USER_ACCESS_TOKEN)))->getCString());
        
        CCLOG("Access Token = %s", ((CCString*)(data->objectForKey(KEY_FB_USER_ACCESS_TOKEN)))->getCString());
        
        CCString* name = CCString::createWithFormat("%s %s", mFirstName->getString(), mLastName->getString(), NULL);
        mName->setString(name->getCString());
        
        /* Here is the email ID of the user */
        if (data->objectForKey(KEY_FB_USER_EMAIL))
        {
            CCLOG("User email ID = %s", ((CCString*)(data->objectForKey(KEY_FB_USER_EMAIL)))->getCString());
        }
        
        this->showUserDetailPage();
    }
    else
    {
        CCMessageBox("Sorry, user details not available", "fbUserDetailCallback");
    }

-------- CODE END -----------

Android Changes
---------------

To make this code working on Android side, you need to change onActivityResult(...) within Cocos2dxActivity as follows:-

-------- CODE START -----------

@Override
  public void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		EziSocialManager.onActivityResult(requestCode, resultCode, data);
		
	}

-------- CODE END -----------


Debugging On Android
--------------------

In version 1.0.1, you can enable Android debugging by calling following method in Any Java Class:

EziSocialManager.setEnableDebugLogs(false); // To disable logs. By Default, disable

EziSocialManager.setEnableDebugLogs(true); // To enable logs. By Default, disable

