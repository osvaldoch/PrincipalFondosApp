//
//  DASFaceLivenessEvent.h
//  DaonAuthenticatorFace
//
//  Created by Neil Johnston on 2/5/18.
//  Copyright © 2018 Daon. All rights reserved.
//

#ifndef DASFaceLivenessEvent_h
#define DASFaceLivenessEvent_h

/*!
 @typedef DASFaceLivenessEvent
 @brief Categorizes the different liveness events that can occur whilst processing live video.
 @constant DASFaceLivenessEventNone                     Default value. No event detected.
 @constant DASFaceLivenessEventReset                    Lost track of face, so liveness analysis will restart.
 @constant DASFaceLivenessEventPassive                  Passive has been detected.
 @constant DASFaceLivenessEventBlink                    A blink has been detected.
 @constant DASFaceLivenessEventSpoof                    A spoof has been detected.
 @constant DASFaceLivenessEventInitializing             Face liveness is initializing. A valid face must be presented.
 @constant DASFaceLivenessEventStarted        Face liveness has started. User should be asked to hold the camera in place.
 @constant DASFaceLivenessEventTracking       Face liveness is tracking. User should be asked to move the camera towards their face.
 @constant DASFaceLivenessEventAnalyzing      Face liveness is analyzing and generating a liveness score.
 @constant DASFaceLivenessEventCompleted      Face liveness has completed analysis and the liveness score will be compared against the liveness threshold.
 */
typedef NS_ENUM(NSInteger, DASFaceLivenessEvent)
{
    DASFaceLivenessEventNone,
    DASFaceLivenessEventReset,
    DASFaceLivenessEventPassive,
    DASFaceLivenessEventBlink,
    DASFaceLivenessEventSpoof,
    DASFaceLivenessEventInitializing,
    DASFaceLivenessEventStarted,
    DASFaceLivenessEventTracking,
    DASFaceLivenessEventAnalyzing,
    DASFaceLivenessEventCompleted
};


#endif /* DASFaceLivenessEvent_h */
