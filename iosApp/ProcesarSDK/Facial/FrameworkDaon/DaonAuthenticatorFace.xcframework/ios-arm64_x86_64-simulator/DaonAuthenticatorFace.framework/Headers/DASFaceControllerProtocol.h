//
//  DASFaceControllerProtocol.h
//  DaonAuthenticatorFace
//
//  Copyright © 2018-21 Daon. All rights reserved.
//

#ifndef DASFaceControllerProtocol_h
#define DASFaceControllerProtocol_h

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>

/*!
 @brief A protocol for classes that wish to provide face collection, registration and authentication functionality.
 */
@protocol DASFaceControllerProtocol <DASControllerProtocol>

/*!
 @brief Starts registration or authentication by configuring the camera and checking frames for quality. Optionally begins looking for liveness events if configured.
 @discussion Which liveness events are required and which have been detected can be determined using the @link expectedLivenessEvents @/link and @link detectedLivenessEvents @/link methods.
 */
- (void) start;

/*!
 @brief Requests that frame processing resumes.
 */
- (void) resume;

/*!
 @brief Requests that the next video frame be captured as a potential registration image.
 @return  A quality image for registration.
 */
- (UIImage*_Nullable) captureImage;

/*!
 @brief Register an image
 @param image The image to register.
 */
- (void) registerWithImage:(UIImage*_Nonnull)image NS_SWIFT_NAME(register(image:));

/*!
 @brief Match image against registered image
 @param image The image to match.
 */
- (void) authenticateWithImage:(UIImage*_Nullable)image NS_SWIFT_NAME(authenticate(image:));

/*!
 @brief Returns whether the authenticators extensions are requesting that liveness is performed at registration and enrollment.
 @discussion Which liveness events are required and which have been detected can be determined using the @link expectedLivenessEvents @/link and @link detectedLivenessEvents @/link methods.
 @return YES if liveness checks are required.
 */
- (BOOL) livenessAtEnrollment;

/*!
 @brief Provides the set of liveness events that are expected to be seen before authentication can continue.
 @return The set of expected liveness events. Each element is an NSNumber containing a @link DASFaceLivenessEvent @/link NSInteger.
 */
- (NSSet*_Nonnull)expectedLivenessEvents;

/*!
 @brief Provides the set of liveness events that have been detected during the current authentication session.
 @return The set of detected liveness events. Each element is an NSNumber containing a @link DASFaceLivenessEvent @/link NSInteger.
 */
- (NSSet*_Nonnull)detectedLivenessEvents;


/*!
 @brief Provides a video frame to the face controller for processing.
 @param frame The video frame to process.
 */
- (void) processFrame:(CVImageBufferRef _Nullable )frame NS_SWIFT_NAME(process(frame:));

/*!
 @brief Notifies the @link DASFaceControllerProtocol @/link that you wish it to take account of a change in device orientation.
 */
- (void) handleOrientationChange;


@end

#endif /* DASFaceControllerProtocol_h */
