EziSocial-Plugin
-----

[EziSocial plugin] uses common development code for both Android and iOS Cocos2D-x project. So, there is no duplicity of code and you need not to worry about portability issue at all.

There are some basic features of [EziSocial Plugin], we will cover them one by one in detail. In case, if you want to explore it first then you can just download the sample code, compile it and run it our your devices or emulators. Here is the [download link] for the demo application.

### Facebook

1. Login via Facebook
2. Logout from Facebook
3. Get user details
4. Open Facebook Page
5. Auto check Facebook likt to your page, when user come back to your game from your page.
6. Check Facebook like to your page anytime during the time app is running.
7. Get the list of friends with filters - user playing game, start index and limit.
8. Post message on the user’s timeline.
9. Auto post message or achievement on user’s timeline without notifying him.
10. Post Score – uses advance feature of Facebook Score Graph API. All scores are stored online at Facebook.com as per Facebook.
11. Get high scores – fetch the scores of the friends of the user playing same game in unsorted order. You can sort it at your end.
12. Send three types of request - Invite, Challenge and Gift
13. Receive three types of request - Invite, Challenge and Gift.
14. Get email ID of the application user.
15. Get user profile picture
16. Get user's friends' profile pictures.
17. Create a TableView from the user's profile picture

### Twitter

1. Tweet - Uses native twitter client of the device to tweet message on the user’s timeline.

### Internet Status

1. Internet Connection - allows you to check the internet connection anytime in the game. 
2. It also gives option to you to check that if a particular website is reachable or not.

### Email

Email - Allows you to preconfigure the mail and allows user to send the mail to you or their friends.

### How to use this plugin

To know about how to use this plugin, please visit site: http://www.ezibyte.com

=========================================
Version 2.1.1 - Pushed on 22 Jan 2013
———————————————————————-

Fixed twitter app not found issue


=========================================
Version 1.0.1 - Pushed on 30th April 2013
-----

Added one new method and modified one method. Details as follows:-

 	bool isUserAlreadyLoginedToFacebook_Or_IsSessionActive = EziSocialObject::sharedObject()->isFacebookSessionActive();

While app is running, anytime if you like to know if user is actually logined to Facebook or not. Or whether session is expired or not. Just simply called above method.
There is no callback method of this and result will immediately return.

	EziSocialObject::sharedObject()->fetchFBUserDetails(true);

Definition of fetchUserDetails has been changed. Now you can actually fetch user email ID also. To get the user email ID, pass the value as true otherwise false.

_**NOTE**: If ask for user email ID, then first time it will ask extra permission from the app user to allow your app to see user email ID._

### HOW TO CHECK IF USER ALLOWED TO SEE HIS EMAIL ID OR NOT


In case user decide not to send you the email ID then in callback method, within Data Dictionary an Error message will return.

Use can check the error message as follows:-
	
    
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



### Android Changes


To make this code working on Android side, you need to change onActivityResult(...) within Cocos2dxActivity as follows:-

	  		
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		super.onActivityResult(requestCode, resultCode, data);
		EziSocialManager.onActivityResult(requestCode, resultCode, data);
	}
	


### Debugging On Android


In version 1.0.1, you can enable Android debugging by calling following method in Any Java Class (prefer your MainActivity class):

	EziSocialManager.setEnableDebugLogs(false); // To disable logs. By Default, disable

	EziSocialManager.setEnableDebugLogs(true); // To enable logs. By Default, disable
	


#
Version 1.1 - Logs
--

### New Features

1. Get user profile picture
2. Get user's friends profile picture _(square, small, normal, large, custom size)_
3. Build TableView of friends list - see [EziSocialDemo] for example code
4. Send three types of request to user's friends: Invite, Gift and Challenge
5. Receive three types of request from user's friends: Invite, Gift and Challenge
6. Add custom data set for each type of request
7. Added new function - **getFriends** with filters like: User using app, User not using app and All friends
8. **getFriends** also supports _startIndex_ and _limit_ on the result set.
9. iOS Plugin code is updated to Facebook SDK v3.5.1 (latest)

## Major changes on code signatures

### Common to iOS and Android (CPP Code)

- Three new callbacks added in **EziSocialDelegate.h** class.


```ruby

    /* This method will be called whenever a request will come to app via Facebook. */
    virtual void fbRecieveRequestCallback(int responseCode,
                                          const char* message,
                                          const char* senderName, cocos2d::CCDictionary* dataDictionary) = 0;
    
    /* This methid will be called when app user send Facebook request: Invite, Challenge and Gift to his friends.
    It will return with response code nad list of the friends to whom request is sent. */
    virtual void fbSendRequestCallback(int responseCode, cocos2d::CCArray* friendsGotRequests) = 0;
    
    /* This method will be called whenever user profile pic is available for display. */
    virtual void fbUserPhotoCallback(const char *userPhotoPath) = 0;
```

- Six new methods added to **EziSocialObject.h** file to fullfill following request:-

#### To get the friends with a search filter. 

```ruby

    /* To get the list of Friends */
    /* It supports three kind of search filter.
    	- FB_FRIEND_SEARCH::ALL_FRIENDS
    	- FB_FRIEND_SEARCH::ONLY_INSTALLED
    	- FB_FRIEND_SEARCH::ONLY_INSTALLED
    */	
    	void getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType);

```
    
#### To apply range filter on the search filter on top of Search Filter.

```ruby
	/* A range filter can be applied on top of Search Filter.
	void getFriends(EziSocialWrapperNS::FB_FRIEND_SEARCH::TYPE searchType, int startIndex, int limit);
```

#### To get the user profile photo of default type: SQUARE

```ruby
	/* It will download the user profile picture with types: SQUARE
		- FBUSER::PIC_SQUARE
	*/
	void getProfilePicForID(const char* userFacebookID, bool forceDownload);
```

#### To get the user profile photo of facebook supported type

```ruby
	/* It will download the user profile picture with types: SQUARE, NORMAL, SMALL, LARGE
		- FBUSER::PIC_SQUARE
		- FBUSER::PIC_SMALL
		- FBUSER::PIC_NORMAL
		- FBUSER::PIC_LARGE
	
	if forcedownload = true, then it will download the photo from internet otherwise it will search
	first local storage.
	
	*/
	void getProfilePicForID(const char* userFacebookID, EziSocialWrapperNS::FBUSER::PROFILE_PIC_TYPE picType, bool forceDownload);
```

#### To get the user profile photo of custom height and width

```ruby
	/* It will download the user profile picture with custom width and height. 
	Facebook support MAX width and height is equal to 200x200.
	
	if forcedownload = true, then it will download the photo from internet otherwise it will search
	first local storage.
	
	*/
	
	void getProfilePicForID(const char* userFacebookID, int width, int height, bool forceDownload);
```

#### To send request to user friends.

```ruby
	/* You can specify whether a request is Invite, Challenge or Gift Type. 
		- FB_REQUEST::REQUEST_GIFT
		- FB_REQUEST::REQUEST_CHALLENGE
		- FB_REQUEST::REQUEST_INVITE
		
	If can pass an array of CCStrings (of friend's Facebook ID) if you want to send request to particular friends.
	This function supports frictionless supports by default. So if user chooses frictionless request for a friend then 
	request will automatically send without showing any dialog box.
	
	You can also pass data dictionary with each object type as CCString only. For example:
	Key = GOLD (const char*), Value = 500 (CCString)
	Key = LIFE (const char*), Value = 1   (CCString)
	
	Use data dictionary if you are sending gifts.
	
	*/
	
	void sendRequestToFriends(EziSocialWrapperNS::FB_REQUEST::TYPE requestType,
                              const char* message,
                              cocos2d::CCArray *selectedFriendIDs,
                              cocos2d::CCDictionary *dataDictionary);
    
```

- **JNI_EziSocialManager.cpp** file is also modified to supports these new functionality.

### Android / iOS

On Android and iOS platform there are no changes but the library files are modified to support these new functionalities.

#
Version 1.2 - Logs
--

### New Features / Updates

1. **Better error handling**         - with each callback developer will receive now response message. If there is an error, it will give complete description of the error.
2. **Delete / Reset user score**     - You can now delete the Facebook Score of the user. It will reset it to zero.
3. **Incoming Request Manager**      - Inbuild request manager fetches and manages all the incoming request.
4. **Storage of Incoming Request**   - Each Incoming Facebook Request is now stored on the CCUserDefault automatically and deleted if user consume the item. This part is open source and can be easily modified.
5. **Added User/Request Objects**    - Requests, Friends & User got their own objects. No more dirty handling of CCStrings.
6. **UTF-8 Character support**       - You can now post and receiver UTF-8 characters.
7. **Post Photo**                    - You can post either screenshot or any resouce image on the user wall (within your app album).
8. **Message parameter in AutoPost** - you can now add message within the post.
9. **Seperate Read and Publish Permission Request** - Developer can now simply ask Read Permission in the starting and later plugin automatically ask for publish permission if required.
10. Removed limit for score callback
11. Automatic handling of incoming request on app become active.
12. Manual handling of incoming request on the developer's wish. :)
13. Delegate Class is modified and now its not necessary to support all the methods. Use whatever delegate method you need it.
14. Minor other bug fixes.


Check the website for updated and new tutorials.

[EziSocialDemo]: https://github.com/ezibyte/EziSocialDemo/
[download link]: https://github.com/ezibyte/EziSocialDemo/
[EziSocial plugin]: http://www.ezibyte.com
