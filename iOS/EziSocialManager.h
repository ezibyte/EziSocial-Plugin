//
//  EziSocialManager.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 11/04/13.
//
//

#include "EziSocialDefinition.h"
#import  <MessageUI/MessageUI.h>

@interface EziSocialManager : NSObject <MFMailComposeViewControllerDelegate>
{
    NSMutableDictionary* mAutoPostDictionary;
}
@property (assign) EziSocialWrapperNS::FBSessionCallback mSessionCallback;
@property (assign) EziSocialWrapperNS::FBMessageCallback mMessageCallback;
@property (assign) EziSocialWrapperNS::FBPageLikeCallback mPageLikeCallback;
@property (assign) EziSocialWrapperNS::FBFriendsCallback mFriendsCallback;
@property (assign) EziSocialWrapperNS::FBUserDetailCallback mUserDetailCallback;
@property (assign) EziSocialWrapperNS::FBHighScoresCallback mHighScoreCallback;
@property (assign) EziSocialWrapperNS::MailCallback mMailCallback;

+(EziSocialManager*) sharedManager;

-(BOOL) handleURL:(NSURL *)url;
-(void) handleApplicationDidBecomeActive;
-(void) handleApplicationLaunched;

@property (strong, nonatomic) NSURL *mOpenedURL;
@property (strong, nonatomic) NSMutableDictionary *mUserDictionary;


@end
