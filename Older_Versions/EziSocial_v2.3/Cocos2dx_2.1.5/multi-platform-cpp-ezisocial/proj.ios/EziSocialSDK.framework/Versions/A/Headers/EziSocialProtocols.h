//
//  EziSocialProtocols.h
//  EziSocialPluginDevelopment
//
//  Created by Paras Mendiratta on 23/08/13.
//
//

#ifndef EziSocialPluginDevelopment_EziSocialProtocols_h
#define EziSocialPluginDevelopment_EziSocialProtocols_h

#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>

// Wraps an Open Graph object (of type "scrumps:meal") that has just two properties,
// an ID and a URL. The FBGraphObject allows us to create an FBGraphObject instance
// and treat it as an SCOGMeal with typed property accessors.
@protocol EziOpenGraphObject<FBGraphObject>

@property (retain, nonatomic) NSString        *id;
@property (retain, nonatomic) NSString        *url;

@end

// Wraps an Open Graph object (of type "scrumps:eat") with a relationship to a meal,
// as well as properties inherited from FBOpenGraphAction such as "place" and "tags".
@protocol EziOpenGraphAction<FBOpenGraphAction>

@property (retain, nonatomic) id<EziOpenGraphObject>    object;

@end

#endif
