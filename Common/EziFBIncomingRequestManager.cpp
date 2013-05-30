//
//  EziFBIncomingRequestManager.cpp
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
    std::string incomingRequestIDs = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_FB_INCOMING_REQUEST_IDS, "");
    std::vector< std::string > incomingRequestIDsVector = EziSocialObject::tokenizeStr(incomingRequestIDs.c_str(), ",");
    
    _completedRequestDictionary = CCDictionary::create();
    _pendingRequestDictionary   = CCDictionary::create();
    
    std::string currentUser = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
    
    // Create the Pending & Completed Request Array
    for (int i=0; i<incomingRequestIDsVector.size(); i++)
    {
        EziFBIncomingRequest *fbRequest = EziFBIncomingRequest::createForRequestID(incomingRequestIDsVector[i]);

        // If this request belongs to current user then only add to the list.
        if (currentUser.compare(fbRequest->getReceiverID())==0)
        {
            if (fbRequest->isConsumed())
            {
                _completedRequestDictionary->setObject(fbRequest, incomingRequestIDsVector[i].c_str());
            }
            else
            {
                _pendingRequestDictionary->setObject(fbRequest, incomingRequestIDsVector[i].c_str());
            }   
        }
    }
    
    // Let's not lost these Dictionaries.
    _pendingRequestDictionary->retain();
    _completedRequestDictionary->retain();

    // Check if any of the request is actually not reterived from Facebook, then fetch the data.
}

// Destructor
EziFBIncomingRequestManager::~EziFBIncomingRequestManager()
{
    _completedRequestDictionary->release();
    _pendingRequestDictionary->release();
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
        std::string currentUser = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_EZI_CURRENT_FB_USER_ID, "");
        
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

CCDictionary* EziFBIncomingRequestManager::getPendingRequests()
{
    return _pendingRequestDictionary;
}

CCDictionary* EziFBIncomingRequestManager::getCompletedRequest()
{
    return _completedRequestDictionary;
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
        
        if (_pendingRequestDictionary->objectForKey(incomingRequestID) != NULL)
        {
            needToAdd = false;
            continue;
        }
        else if (_completedRequestDictionary->objectForKey(incomingRequestID) != NULL)
        {
            needToAdd = false;
            continue;
        }
        
        if (needToAdd) // This mean request ID is not added to pending list or completed list. It's time to add it in pending list.
        {
            EziFBIncomingRequest* fbRequest = EziFBIncomingRequest::createForRequestID(incomingRequestID);
            _pendingRequestDictionary->setObject(fbRequest, incomingRequestID);
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
    EziFBIncomingRequest* fbRequest = NULL;
    
    if (_pendingRequestDictionary->objectForKey(requestID.c_str()) != NULL)
    {
        fbRequest = (EziFBIncomingRequest*)_pendingRequestDictionary->objectForKey(requestID.c_str());
    }
    else
    {
        fbRequest = (EziFBIncomingRequest*)_completedRequestDictionary->objectForKey(requestID.c_str());
    }
    
    return fbRequest;
}

int EziFBIncomingRequestManager::getPendingRequestCount()
{
    return _pendingRequestDictionary->count();
}

/**
 *   This method checks for the pending request IDs if the data is not fetched then it will fetch the data for the 
 *   very first request ID whose data is not yet fetched from the Facebook.
 */
void EziFBIncomingRequestManager::processNextRequest()
{
    bool found = false;
    CCArray* pendingKeys = _pendingRequestDictionary->allKeys();
    for (int i=0; i<pendingKeys->count(); i++)
    {
        CCString* key = (CCString*)pendingKeys->objectAtIndex(i);
        EziFBIncomingRequest* pendingRequest = (EziFBIncomingRequest*)_pendingRequestDictionary->objectForKey(key->getCString());
        if (pendingRequest->isDataFetchedFromServer() == false)
        {
            CCLOG("Got the ID to process - %s", pendingRequest->getRequestID());
            EziSocialObject::sharedObject()->processIncomingRequest(pendingRequest->getRequestID());
            found = true;
            break;
        }
    }
    
    if (found == false)
    {
        CCLOG("All requests are fetched from the facebook.");
    }
    
}


void EziFBIncomingRequestManager:: saveUpdatedRequestList()
{
    std::string requestIDsToSave    = "";
    
    CCArray* pendingRequestKeys     = _pendingRequestDictionary->allKeys();
    CCArray* completedRequestKeys   = _completedRequestDictionary->allKeys();
    
    if (pendingRequestKeys)
    {
        for (int i=0; i<pendingRequestKeys->count(); i++)
        {
            CCString* key = (CCString*)pendingRequestKeys->objectAtIndex(i);
            requestIDsToSave.append(key->getCString()).append(",");
        }
    }
    
    if (completedRequestKeys)
    {
        for (int i=0; i<completedRequestKeys->count(); i++)
        {
            CCString* key = (CCString*)completedRequestKeys->objectAtIndex(i);
            requestIDsToSave.append(key->getCString()).append(",");
        }
    }
    
    CCUserDefault::sharedUserDefault()->setStringForKey(KEY_FB_INCOMING_REQUEST_IDS, requestIDsToSave.c_str());
    CCUserDefault::sharedUserDefault()->flush();
    
}

bool EziFBIncomingRequestManager::autoPurgeCompletedRequestStorage()
{
    bool didPurge = false;
    
    // Purge the NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS completed records if the limit is crossed to MAX_COMPLETED_REQUEST_ID_TO_HOLD.
    if (_completedRequestDictionary->count() > MAX_COMPLETED_REQUEST_ID_TO_HOLD)
    {
        // Purge total completed request ID as mentioned in NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS in EziSocialDefiniation.h
        CCArray* itemsToRemove = CCArray::createWithCapacity(NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS);
        
        CCArray* keys = _completedRequestDictionary->allKeys();
        
        for (int i=0; i<keys->count(); i++)
        {
            if (i >= NUMBER_OF_AUTO_PURGE_TOP_COMPLETED_IDS)
            {
                break;
            }
            
            CCString* completedRequestID = (CCString*) keys->objectAtIndex(i);
            itemsToRemove->addObject(completedRequestID);
            
            EziFBIncomingRequest* fbRequest = (EziFBIncomingRequest*)(_completedRequestDictionary->
                                                                      objectForKey(completedRequestID->getCString()));
            fbRequest->purgeFromUserDefault();
            
        }
        
        if (itemsToRemove && itemsToRemove->count() > 0)
        {
            _completedRequestDictionary->removeObjectsForKeys(itemsToRemove);
            this->saveUpdatedRequestList();
            didPurge = true;
        }
    }
    
    return didPurge;
}

void EziFBIncomingRequestManager::consumeItem(EziFBIncomingRequest* fbRequest)
{
    if(fbRequest->isConsumed() == false)
    {
        fbRequest->setConsumed(true);
        fbRequest->saveToUserDefaults();
        
        _pendingRequestDictionary->removeObjectForKey(fbRequest->getRequestID());
        _completedRequestDictionary->setObject(fbRequest, fbRequest->getRequestID());
        saveUpdatedRequestList();
    }
}


void EziFBIncomingRequestManager::clearCompletedRequestList()
{
    // Remove all the objects from the completed Array List.
    
    CCArray* keys = _completedRequestDictionary->allKeys();
    
    if (keys)
    {
        for (int i=0; i<keys->count(); i++)
        {
            CCString* key = (CCString*)keys->objectAtIndex(i);
            EziFBIncomingRequest* fbRequest = (EziFBIncomingRequest*)(_completedRequestDictionary->objectForKey(key->getCString()));
            fbRequest->purgeFromUserDefault();
        }
    }
    
    _completedRequestDictionary->removeAllObjects();
    
    this->saveUpdatedRequestList();
}
