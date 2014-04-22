//
//  EziFBIncomingRequestManager.h
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

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
    
    CCArray* getAllRequests();
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
