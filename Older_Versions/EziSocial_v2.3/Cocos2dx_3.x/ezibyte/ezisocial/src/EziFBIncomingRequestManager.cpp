//
//  EziFBIncomingRequestManager.cpp
//  FacebookGameDemo
//
//  Created by Paras Mendiratta on 20/05/13.
//
//

#include "EziFBIncomingRequestManager.h"
#include "EziSocialObject.h"
#include "EziSocialDefinition.h"
#include "EziFBIncomingRequest.h"

USING_NS_CC;

#define KEY_FB_INCOMING_REQUEST_IDS "FB_INCOMING_REQUEST_IDS"

static EziFBIncomingRequestManager* sharedRequestManager;

// Constructor
EziFBIncomingRequestManager::EziFBIncomingRequestManager()
{
    std::string incomingRequestIDs = cocos2d::UserDefault::getInstance()->getStringForKey(KEY_FB_INCOMING_REQUEST_IDS, "");
    std::vector< std::string > incomingRequestIDsVector = EziSocialObject::tokenizeStr(incomingRequestIDs.c_str(), ",");
    
    std::string currentUser = cocos2d::UserDefault::getInstance()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
    
    // Create the Pending & Completed Request Array
    for (int i=0; i<incomingRequestIDsVector.size(); i++)
    {
        EziFBIncomingRequest *fbRequest = EziFBIncomingRequest::createForRequestID(incomingRequestIDsVector[i]);
        
        // If this request belongs to current user then only add to the list.
        if (currentUser.compare(fbRequest->getReceiverID())==0)
        {
            if (fbRequest->isConsumed())
            {
                _completedRequestDictionary.insert(incomingRequestIDsVector[i],fbRequest);
            }
            else
            {
                _pendingRequestDictionary.insert(incomingRequestIDsVector[i],fbRequest);
            }
        }
    }
    
    // Check if any of the request is actually not reterived from Facebook, then fetch the data.
}

// Destructor
EziFBIncomingRequestManager::~EziFBIncomingRequestManager()
{
}

void EziFBIncomingRequestManager::rebuildManager()
{
    if (sharedRequestManager != NULL)
    {
        sharedRequestManager->release();
        sharedRequestManager = NULL;
    }
    EziFBIncomingRequestManager::sharedManager();
}

EziFBIncomingRequestManager* EziFBIncomingRequestManager::sharedManager()
{
    if (sharedRequestManager == NULL)
    {
        // Create the new manager
        std::string currentUser = UserDefault::getInstance()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
        
        if (currentUser.compare("") == 0)
        {
            CCLOGERROR("Error! Cannot initialize EziFBIncomingRequestManager. First set the current Facebook User ID key CCUserDefaults using KEY = KEY_EZI_CURRENT_FB_USER_ID");
        }
        else
        {
            sharedRequestManager = new EziFBIncomingRequestManager();
        }
    }
    
    return sharedRequestManager;
    
}

const cocos2d::Map<std::string, EziFBIncomingRequest*> EziFBIncomingRequestManager::getPendingRequests() const
{
    return _pendingRequestDictionary;
}

const cocos2d::Map<std::string, EziFBIncomingRequest*> EziFBIncomingRequestManager::getCompletedRequest() const
{
    return _completedRequestDictionary;
}

std::vector<EziFBIncomingRequest*> EziFBIncomingRequestManager::getAllRequests() const
{
    std::vector<EziFBIncomingRequest*> allRequests;
    for(auto &it : _completedRequestDictionary)
        allRequests.push_back(it.second);
    
    for(auto &it : _pendingRequestDictionary)
        allRequests.push_back(it.second);
    
    return allRequests;
}

bool EziFBIncomingRequestManager::addNewIncomingRequestIDs(std::string requestIDs)
{
    //CCUserDefault::sharedUserDefault()->get
    
    // Get the user IDs into vector.
    std::vector< std::string > incomingRequestVector = EziSocialObject::tokenizeStr(requestIDs.c_str(), ",");
    int totalIncomingRequest = incomingRequestVector.size();
    
    bool gotAnyNewIncomingRequest = false;
    
    // Now check if any of these incoming request is already processed or already added to our pending request list.
    for (int i=0; i<totalIncomingRequest; i++)
    {
        std::string incomingRequestID = incomingRequestVector[i];
        bool needToAdd = true;
        
        if (_pendingRequestDictionary.find(incomingRequestID) != _pendingRequestDictionary.end())
        {
            needToAdd = false;
            continue;
        }
        else if (_completedRequestDictionary.find(incomingRequestID) != _completedRequestDictionary.end())
        {
            needToAdd = false;
            continue;
        }
        
        if (needToAdd) // This mean request ID is not added to pending list or completed list. It's time to add it in pending list.
        {
            EziFBIncomingRequest* fbRequest = EziFBIncomingRequest::createForRequestID(incomingRequestID);
            _pendingRequestDictionary.insert(incomingRequestID, fbRequest);
            gotAnyNewIncomingRequest = true;
        }
    }
    
    if (gotAnyNewIncomingRequest)
    {
        this->saveUpdatedRequestList();
    }
    
    return gotAnyNewIncomingRequest;
}


EziFBIncomingRequest* EziFBIncomingRequestManager::getIncomingRequest(std::string requestID)
{
    auto it = _pendingRequestDictionary.find(requestID);
    if (it != _pendingRequestDictionary.end())
        return it->second;
    
    it = _completedRequestDictionary.find(requestID);
    if (it != _completedRequestDictionary.end())
        return it->second;
    
    
    return nullptr;
}

int EziFBIncomingRequestManager::getPendingRequestCount()
{
    return _pendingRequestDictionary.size();
}

/**
 *   This method checks for the pending request IDs if the data is not fetched then it will fetch the data for the
 *   very first request ID whose data is not yet fetched from the Facebook.
 */
void EziFBIncomingRequestManager::processNextRequest()
{
    bool found = false;
    for (auto &it : _pendingRequestDictionary)
    {
        if(!it.second->isDataFetchedFromServer())
        {
            EziSocialObject::sharedObject()->processIncomingRequest(it.second->getRequestID());
            found = true;
            break;
        }
    }
    
    if (found == false)
    {
        //CCLOG("All requests are fetched from the facebook.");
    }
    
}


void EziFBIncomingRequestManager:: saveUpdatedRequestList()
{
    std::string requestIDsToSave    = "";
    
    for(auto &it : _pendingRequestDictionary)
    {
        requestIDsToSave.append(it.first);
    }
    
    for(auto &it : _completedRequestDictionary)
    {
        requestIDsToSave.append(it.first);
    }
    
    UserDefault::getInstance()->setStringForKey(KEY_FB_INCOMING_REQUEST_IDS, requestIDsToSave);
    UserDefault::getInstance()->flush();
    
}

bool EziFBIncomingRequestManager::autoPurgeCompletedRequestStorage()
{
    bool didPurge = false;
    
    // Purge the NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS completed records if the limit is crossed to MAX_COMPLETED_REQUEST_ID_TO_HOLD.
    if (_completedRequestDictionary.size() > MAX_COMPLETED_REQUEST_ID_TO_HOLD)
    {
        // Purge total completed request ID as mentioned in NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS in EziSocialDefiniation.h
        for (int i=0; i< NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS; ++i) {
            _completedRequestDictionary.begin()->second->purgeFromUserDefault();
            _completedRequestDictionary.erase(_completedRequestDictionary.begin());
            didPurge = true;
        }
        if(didPurge)
            this->saveUpdatedRequestList();
    }
    
    return didPurge;
}

void EziFBIncomingRequestManager::consumeItem(EziFBIncomingRequest* fbRequest)
{
    if(fbRequest->isConsumed() == false)
    {
        fbRequest->setConsumed(true);
        fbRequest->saveToUserDefaults();
        
        _pendingRequestDictionary.erase(fbRequest->getRequestID());
        _completedRequestDictionary.erase(fbRequest->getRequestID());
        saveUpdatedRequestList();
    }
}


void EziFBIncomingRequestManager::clearCompletedRequestList()
{
    // Remove all the objects from the completed Array List.
    
    for(auto it: _completedRequestDictionary)
        it.second->purgeFromUserDefault();
    
    _completedRequestDictionary.clear();
    
    this->saveUpdatedRequestList();
}
