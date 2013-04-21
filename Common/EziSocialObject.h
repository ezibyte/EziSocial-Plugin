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

class EziSocialObject
{
    EziSocialObject();
    EziFacebookDelegate *mFacebookDelegate;
    EziTwitterDelegate *mTwitterDelegate;
    EziEmailDelegate *mEmailDelegate;
    
public:
    
    ~EziSocialObject();

    static EziSocialObject* sharedObject();
    
    void setFacebookDelegate(EziFacebookDelegate *facebookDelegate);
    void setTwitterDelegate(EziTwitterDelegate *twitterDelegate);
    void setEmailDelegate(EziEmailDelegate *emailDelegate);
    
    EziFacebookDelegate* getFacebookDelegate();
    EziTwitterDelegate* getTwitterDelegate();
    EziEmailDelegate* getEmailDelegate();
    
    void performLoginUsingFacebook();
    void perfromLogoutFromFacebook();
    
    void fetchFBUserDetails();
    
    // Post Message On Wall
    void postMessageOnWall(const char* heading,
                           const char* caption,
                           const char* description,
                           const char* badgeIconURL,
                           const char* deepLinkURL);

    void autoPostMessageOnWall(const char* heading,
                           const char* caption,
                           const char* description,
                           const char* badgeIconURL,
                           const char* deepLinkURL);

    void postScore(unsigned long long score);
    void hasUserLikedMyFBPage(const char* pageID);
    void getListOfFriendsUsingFBApp();
    void getHighScores();
    void openFacebookPage(const char* pageID, bool checkPageLikeOnApplicationBecomesActive);
    
    // Twitter
    void tweet(const char* message, const char* imageURL);
    
    // Email
    void sendEmail(const char* subject, const char* htmlMessageBody, const char* semicolonSeperatedRecipents);
    
    // Network Status
    bool checkNetworkStatusForHost(const char* hostURL);
    
};

#endif /* defined(__FacebookGameDemo__EziSocialObject__) */
