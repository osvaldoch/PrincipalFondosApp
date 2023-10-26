//
//  DFSLivenessResult.h
//  DaonFaceSDK
//
//  Created by Neil Johnston on 12/15/15.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

static NSString* const kLivenessResultShakeKey              = @"result.liveness.shake";
static NSString* const kLivenessResultNodKey                = @"result.liveness.nod";
static NSString* const kLivenessResultBlinkKey              = @"result.liveness.blink";
static NSString* const kLivenessResultSpoofKey              = @"result.liveness.spoof";
static NSString* const kLivenessResultPassiveKey            = @"result.liveness.passive";
static NSString* const kLivenessResultLightReflectionKey    = @"result.liveness.clr";

static NSString* const kLivenessResultAlertKey              = @"result.liveness.alert";

static NSString* const kLivenessResultLightReflectionColorKey = @"result.liveness.clr.color";

static NSString* const kLivenessResultScoreKey      = @"result.liveness.score";
static NSString* const kLivenessResultStateKey      = @"result.liveness.state";
static NSString* const kLivenessResultTemplateKey   = @"result.liveness.template";
static NSString* const kLivenessResultTarget        = @"result.liveness.target";
static NSString* const kLivenessResultImageKey      = @"result.liveness.image";

/*!
 @brief Categorizes the different types of tracker states supported.
 @constant LivenessTrackerStatusFinding     Tracker is trying to find the face.
 @constant LivenessTrackerStatusTracking    Tracker has found a face and is tracking it between images.
 @constant LivenessTrackerStatusRefinding   Tracker has lost the face and is trying to re-find the face.
 */
typedef NS_ENUM (NSUInteger, DFSLivenessTrackerStatus) {
    DFSLivenessTrackerStatusFinding     = 0,
    DFSLivenessTrackerStatusTracking    = 1,
    DFSLivenessTrackerStatusRefinding   = 2
};

typedef NS_ENUM (NSUInteger, DFSLivenessEvent) {    
    DFSLivenessEventBlink,
    DFSLivenessEventNod,
    DFSLivenessEventShake,
    DFSLivenessEventSpoof,
    DFSLivenessEventPassive
};

typedef NS_ENUM (NSUInteger, DFSLivenessState) {
    DFSLivenessStateNone,
    DFSLivenessStateInitializing,
    DFSLivenessStateStart,
    DFSLivenessStateTracking,
    DFSLivenessStateAnalyzing,
    DFSLivenessStateDone
};

typedef NS_ENUM (NSUInteger, DFSLivenessAlert) {
    DFSLivenessAlertNone               = 0,
    DFSLivenessAlertFaceNotDetected    = 1,
    DFSLivenessAlertFaceNotCentered    = 2,
    DFSLivenessAlertMotionTooFast      = 3,            // the user moves his/her head too fast (rotation speed)
    DFSLivenessAlertMotionSwingTooFast = 4,            // the user nods or shakes too fast (oscillation speed, number of nods/shakes per second)
    DFSLivenessAlertMotionTooFar       = 5,            // the user is turning his/her head too far, tracking hasn’t been lost yet
    DFSLivenessAlertFaceTooCloseToEdge = 6,            // the user’s head is too close to the vertical edges of the frame
    DFSLivenessAlertFaceTooNear        = 7,            // the user is too close to the device (head too large)
    DFSLivenessAlertFaceTooFar         = 8,            // the user is too far from the device (head too small)
    DFSLivenessAlertSpoofDetected      = 9,            // Passive liveness was not detected
    
    DFSLivenessAlertInsufficientFaceData   = 10,
    DFSLivenessAlertInsufficientFrameData  = 11,
    DFSLivenessAlertFrameMismatch          = 12,
    DFSLivenessAlertNoMovementDetected     = 13,
    DFSLivenessAlertFaceQuality            = 14,
    DFSLivenessAlertTimeout                = 15
};

/*!
 @brief Liveness result.
 */
@interface DFSLivenessResult : NSObject


/*!
 @brief Get the liveness alert message code.
 */
@property (nonatomic, readonly) DFSLivenessAlert alert;

/*!
 @brief Get the liveness state.
 */
@property (nonatomic, readonly) DFSLivenessState state;

/*!
 @brief A spoof attempt was detected.
 */
@property (nonatomic, readonly) BOOL spoof;

/*!
 @brief Get the status of the head movement face tracker.
 @description Status will be one of Finding, Tracking, Refinding.
 */
@property (nonatomic, readonly) DFSLivenessTrackerStatus trackerStatus;

/*!
 @brief Get the score for the detected liveness type.
 @description The score value will be between 0 and 1.
 */
@property (nonatomic, readonly) float score;

/*!
 @brief Check if a nod was detected.
 */
@property (nonatomic, readonly) BOOL isNod;

/*!
 @brief Check if a shake was detected.
 */
@property (nonatomic, readonly) BOOL isShake;

/*!
 @brief Check if a blink was detected.
 */
@property (nonatomic, readonly) BOOL isBlink;

/*!
 @brief Check if passive liveness detected.
 */
@property (nonatomic, readonly) BOOL isPassive;


@property (nonatomic, readonly) NSUInteger numberOfFrames;

/*!
 @brief Best image
 */
@property (nonatomic, readonly) UIImage * image;


- (BOOL) hasData;

/*!
 @brief Initialises a new instance and parses the raw results to populate the class properties.
 @param results The raw results.
 @result A new instance ready.
 */
- (id) initWithResults:(NSDictionary*)results;



@end
