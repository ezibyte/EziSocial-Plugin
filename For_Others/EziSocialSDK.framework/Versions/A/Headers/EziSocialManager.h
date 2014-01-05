//
//  EziSocialManager.h
//  EziSocialPlugin
//
//  Created by Paras Mendiratta on 11/04/13.
//
//  Modified on 1 Nov 2013

#include "Reachability.h"
#include "EziSocialDefinition.h"
#include <FacebookSDK/FacebookSDK.h>
#import  <MessageUI/MessageUI.h>


@interface EziSocialManager : NSObject  <MFMailComposeViewControllerDelegate, UIAlertViewDelegate>

{
    NSMutableDictionary* mAutoPostDictionary;
    NSMutableDictionary* mOpenGraphDictionaryForProfile;
    NSMutableDictionary* mOpenGraphDictionary;
}

@property (nonatomic) BOOL debug;
@property (assign) EziSocialWrapperNS::FBSessionCallback         mSessionCallback;
@property (assign) EziSocialWrapperNS::FBMessageCallback         mMessageCallback;
@property (assign) EziSocialWrapperNS::FBPageLikeCallback        mPageLikeCallback;
@property (assign) EziSocialWrapperNS::FBFriendsCallback         mFriendsCallback;
@property (assign) EziSocialWrapperNS::FBUserDetailCallback      mUserDetailCallback;
@property (assign) EziSocialWrapperNS::FBScoresCallback          mScoreCallback;
@property (assign) EziSocialWrapperNS::FBPhotoPostCallback       mPhotoPostCallback;
@property (assign) EziSocialWrapperNS::FBIncomingRequestCallback mIncomingCallback;
@property (assign) EziSocialWrapperNS::FBShareDialogCallback     mShareDialogCallback;
@property (assign) EziSocialWrapperNS::FBOpenGraphCallback       mOpenGraphCallback;
@property (assign) EziSocialWrapperNS::FBAchievementCallback     mAchievementCallback;

// Mail
@property (assign) EziSocialWrapperNS::MailCallback mMailCallback;


@property (assign) EziSocialWrapperNS::FBSendRequestCallback mSendRequestCallback;
@property (assign) EziSocialWrapperNS::FBRecieveRequestCallback mRecieveRequestCallback;

@property (assign) EziSocialWrapperNS::TwitterCallback mTwitterCallback;

//@property (strong, nonatomic) Reachability* reachability;

+(EziSocialManager*) sharedManager;

-(BOOL) handleURL:(NSURL *)url;
-(void) handleApplicationDidBecomeActive;
-(void) handleApplicationLaunched;
//-(BOOL) isFacebookSessionActive;

@property (assign) BOOL autoCheckIncomingOnAppActiveOrLoginSuccess;

@property (strong, nonatomic) NSURL *mOpenedURL;
@property (strong, nonatomic) NSMutableDictionary *mUserDictionary;

@end
