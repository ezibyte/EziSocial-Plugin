//
//  EziFBIncomingRequestManager.h
//  EziSocial
//
//  Created by Paras Mendiratta on 20/05/13.
//  Copyright @EziByte 2013 (http://www.ezibyte.com)
//
//  Version 1.2 (Dt: 30-May-2013)
//
/***
 
 This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source distribution.
 
*/


#ifndef __FacebookGameDemo__EziFBIncomingRequestManager__
#define __FacebookGameDemo__EziFBIncomingRequestManager__

#include <iostream>
#include "cocos2d.h"
#include "EziFBIncomingRequest.h"

USING_NS_CC;

class EziFBIncomingRequestManager: public CCObject
{
    CCDictionary* _pendingRequestDictionary;
    CCDictionary* _completedRequestDictionary;

    // Constructor
    EziFBIncomingRequestManager();
    
    void saveUpdatedRequestList();
    bool autoPurgeCompletedRequestStorage();
    
public:
    
    static EziFBIncomingRequestManager* sharedManager();
    static void rebuildManager();
    // Destructor.
    virtual ~EziFBIncomingRequestManager();
    
    CCDictionary* getPendingRequests();
    CCDictionary* getCompletedRequest();
    
    
    
    bool addNewIncomingRequestIDs(std::string requestIDs);
    int  getPendingRequestCount();
    
    EziFBIncomingRequest* getIncomingRequest(std::string requestID);
    void consumeItem(EziFBIncomingRequest* fbRequest);

    void processNextRequest();    
    void clearCompletedRequestList();

};

#endif /* defined(__FacebookGameDemo__EziFBIncomingRequestManager__) */
