//
//  DASFaceControllerDelegate.h
//  DaonAuthenticatorFace
//
//  Copyright © 2021 Daon. All rights reserved.
//

#ifndef DASFaceControllerDelegate_h
#define DASFaceControllerDelegate_h

#import <DaonAuthenticatorFace/DASFaceLivenessEvent.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

// Forward Declarations
@class DFSQualityResult;
@class DFSResult;
/*!
 @brief A protocol for classes that wish to be notified of face collection events from an object that implements the @link DASFaceControllerProtocol @/link protocol.
 */
@protocol DASFaceControllerDelegate <NSObject>


/*!
 @brief Used to notify a conforming object that an authentication or registration attempt has completed processing.
 */
- (void) controllerDidCompleteSuccessfully;

/*!
 @brief Used to notify a conforming object that an authentication or registration attempt has failed.
 @param error If present, an error that caused registration to fail, such as a timeout or image quality issue.
 @param score The score if available.
 */
- (void) controllerDidFailWithError:(NSError*_Nullable)error
                              score:(NSNumber*_Nullable)score NS_SWIFT_NAME(controllerDidFail(error:score:));

/*!
 @brief Used to notify a conforming object that a liveness event (passive, blink, etc) has been detected.
 @param event The @link DASFaceLivenessEvent @/link that was detected.
 @param image The image at the time the event was detected.
 @param allEventsDetected YES if all expected liveness events have been detected during this session.
 */
- (void) controllerDidDetectLiveness:(DASFaceLivenessEvent)event
                              result:(DFSResult*_Nonnull)result
                               image:(UIImage*_Nullable)image
                   allEventsDetected:(BOOL)allEventsDetected NS_SWIFT_NAME(controllerDidDetectLiveness(event:result:image:allEventsDetected:));


@optional

/*!
 @brief Used to notify a conforming object that a frame from the live video has completed processing.
 @param result The raw @link DFSResult @/link result object that provides access to all metrics.
 @param quality YES if the image frame passed our quality checks.
 @param issues If imageQualityPassed is NO, then this will provide a list of any quality issues (DASAuthenticatorError in NSNumber) detected.
 */
- (void) controllerDidAnalyzeWithResult:(DFSResult*_Nonnull)result
                                quality:(BOOL)quality
                                  issues:(NSArray<NSNumber*>*_Nullable)issues NS_SWIFT_NAME(controllerDidAnalyze(result:quality:issues:));


/*!
@brief Used to provide a custom image quality criteria.
@param result The raw @link DFSResult @/link result object that provides access to all image metrics.
*/
- (NSArray<NSNumber*>*_Nullable) controllerShouldUseQualityCriteriaWithResult:(DFSResult*_Nonnull)result NS_SWIFT_NAME(controllerShouldUseQualityCriteria(result:));


/*!
@brief Update Face SDK configuration. May be called more than once during a session.
@param configuration The the current configuration
@return New of additional configuration parameters
*/
- (NSDictionary*_Nullable) controllerShouldUseConfiguration:(NSDictionary*_Nonnull)configuration NS_SWIFT_NAME(controllerShouldUse(configuration:));

@end

#endif /* DASFaceControllerDelegate_h */
