//
//  EziSocialManager.h
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
