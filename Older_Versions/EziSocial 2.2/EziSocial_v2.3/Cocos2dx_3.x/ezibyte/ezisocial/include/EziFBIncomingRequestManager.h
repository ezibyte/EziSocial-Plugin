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


class EziFBIncomingRequestManager: public cocos2d::Ref
{
public:
    
    static EziFBIncomingRequestManager* sharedManager();
    static void rebuildManager();
    // Destructor.
    virtual ~EziFBIncomingRequestManager();
    
    std::vector<EziFBIncomingRequest*> getAllRequests() const;
    const cocos2d::Map<std::string, EziFBIncomingRequest*> getPendingRequests() const;
    const cocos2d::Map<std::string, EziFBIncomingRequest*> getCompletedRequest() const;
    
    
    
    bool addNewIncomingRequestIDs(std::string requestIDs);
    int  getPendingRequestCount();
    
    EziFBIncomingRequest* getIncomingRequest(std::string requestID);
    void consumeItem(EziFBIncomingRequest* fbRequest);
    
    void processNextRequest();
    void clearCompletedRequestList();
    
private:
    cocos2d::Map<std::string, EziFBIncomingRequest*> _pendingRequestDictionary;
    cocos2d::Map<std::string, EziFBIncomingRequest*> _completedRequestDictionary;
    
    // Constructor
    EziFBIncomingRequestManager();
    
    void saveUpdatedRequestList();
    bool autoPurgeCompletedRequestStorage();
    
};

#endif /* defined(__FacebookGameDemo__EziFBIncomingRequestManager__) */
