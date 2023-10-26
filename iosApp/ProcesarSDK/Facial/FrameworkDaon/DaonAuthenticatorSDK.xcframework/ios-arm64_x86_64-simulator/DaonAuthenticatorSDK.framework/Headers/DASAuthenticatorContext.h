//
//  DASAuthenticatorContext.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 3/9/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

#ifndef DASAuthenticatorContext_h
#define DASAuthenticatorContext_h

// Forward Declarations
@class DASAuthenticatorInfo;
@protocol DASMetadataControllerDelegate;
@protocol DASMetadataControllerProtocol;

// Blocks

/*!
 @typedef DASTimeoutHandler
 @brief Block that is used to notify a calling object that an operation has timed out.
 */
typedef void (^DASTimeoutHandler) (void);

/*!
 @typedef DASCompletionHandler
 @brief Block that is used to notify a calling object that an operation has completed.
 @param error The error that occurred. A nil error should be treated as success.
 */
typedef void (^DASCompletionHandler) (NSError *error);

/*!
 @typedef DASCompletionHandlerWithData
 @brief Block that is used to notify a calling object that an operation has completed and data collected from the user.
 @param error The error that occurred. A nil error should be treated as success.
 @param data The collected data.
 */
typedef void (^DASCompletionHandlerWithData) (NSError *error, NSData *data);



/*!
 @brief A protocol for classes that wish to provide controller functionality.
 */
@protocol DASControllerProtocol <NSObject>

/*!
 @brief Terminates all current work where possible.
 */
- (void) cancel;
@end



/*!
 @brief A protocol for classes that wish to ADoS data delivery functionality.
 */
@protocol DASADoSControllerProtocol <DASControllerProtocol>

/*!
 @brief YES if reenrollment data is required along with authentication data.
 */
@property (nonatomic, readonly) BOOL isReenrollRequired;

/*!
 @brief Converts an UIImage object into a UT8 encoded JSON object for delivery to the server.
 @param image The UIImage to convert.
 @return The converted data.
 */
- (NSData*) dataForImage:(UIImage*)image;

/*!
 @brief Converts an UIImage object into a UT8 encoded JSON object for delivery to the server.
 @param image The UIImage to convert.
 @param quality The jpg quality
 @param format Either jpeg or png
 @return The converted data.
 */
- (NSData*) dataForImage:(UIImage*)image quality:(CGFloat)quality format:(NSString*)format;

/*!
 @brief Converts a Liveness template object into a UT8 encoded JSON object for delivery to the server.
 @param data The template data to convert.
 @return The converted data.
 */
- (NSData*) dataForTemplate:(NSData*)data;

/*!
 @brief Converts a set of PCM audio samples into a UT8 encoded JSON object for delivery to the server.
 @param samples The samples to convert.
 @return The converted data.
 */
- (NSData*) dataForVoiceSamples:(NSArray<NSData*>*)samples;

/*!
 @brief Converts a set of SRP attributes into a UT8 encoded JSON object for delivery to the server.
 @param v Password verifier
 @param m1 Challenge
 @param a Ephemeral value A
 @return The converted data.
 */
- (NSData*) dataForPasswordV:(NSData*)v M1:(NSData*)m1 A:(NSData*)a;

/*!
 @brief Converts an NSArray of NSData objects into a UT8 encoded JSON object for delivery to the server.
 @param dataArray The NSArray of NSData objects
 @return The converted data.
 */
- (NSData*) dataForDataArray:(NSArray<NSData*>*)dataArray;

/*!
 @brief Attempts to deliver the data to the server.
 @param data The data to be delivered to the server
 @param handler A @link DASCompletionHandler @/link object that will be called on success or failure of the delivery.
 */
- (void) deliverData:(NSData*)data completionHandler:(DASCompletionHandler)handler;

@end



/*!
 @brief A protocol for classes that wish to provide local authentication functionality.
 */
@protocol DASAppleBiometricsControllerProtocol <DASControllerProtocol>

/*!
 @brief Initiates a Local Authentication on the device using Touch ID or Face ID
 @param reason The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
 @param handler A @link DASCompletionHandler @/link object that will be called on success or failure.
 */
- (void) performAuthenticationWithReason:(NSString*)reason completionHandler:(DASCompletionHandler)handler;

/*!
 @brief Initiates a Local Authentication on the device using Touch ID or Face ID
 @param reason The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
 @param handler A @link DASCompletionHandler @/link object that will be called on success or failure.
 @param fallbackTitle Allows fallback button title customization. If set to empty string, the button will be hidden. A default title "Enter Password" is used when this property is left nil.
 */
- (void) performAuthenticationWithReason:(NSString*)reason completionHandler:(DASCompletionHandler)handler fallback:(NSString*)fallbackTitle;

/*!
 @brief Initiates a Local Authentication on the device using Touch ID or Face ID
 @param reason The reason for the authentication. This will be shown in the Touch ID dialog. This is not supported for Face ID.
 @param handler A @link DASCompletionHandler @/link object that will be called on success or failure.
 @param fallbackTitle Allows fallback button title customization. If set to empty string, the button will be hidden. A default title "Enter Password" is used when this property is left nil.
 @param terminateOnFallback If YES, the context will be automatically completed with a DASAuthenticatorErrorFallback error if fallback is selected and no error will be returned via the completionHandler (this is the default behaviour for the other overloads). If NO, the error will be returned via the completionHandler for the developer to handle.
 */
- (void) performAuthenticationWithReason:(NSString*)reason completionHandler:(DASCompletionHandler)handler fallback:(NSString*)fallbackTitle terminateOnFallback:(BOOL)terminateOnFallback;

@end

/*!
 @brief A protocol for classes that wish to provide Touch ID functionality.
 */
@protocol DASFingerprintControllerProtocol <DASAppleBiometricsControllerProtocol>
@end



/*!
 @brief A protocol for classes that wish to provide Face ID functionality.
 */
@protocol DASFaceIdControllerProtocol <DASAppleBiometricsControllerProtocol>
@end



/*!
 @brief A protocol for classes that wish to implement their own concrete authenticator context.
 @discussion The authenticator context is the central hub for all information and services which data collection view controllers may need to perform their tasks.
 */
@protocol DASAuthenticatorContext <NSObject>
    
/*!
 @group Properties
 */

/*!
 @brief The location of a folder where view controllers can save temporary data.
 @discussion
 The folder is generated at the following location: [NSTemporaryDirectory() stringByAppendingPathComponent:@"Authenticators"]
 The folder is deleted at the beginning and end of capture.
 */
@property (nonatomic, readonly) NSString *tempDataDirectory;

/*!
 @brief YES if the context was instantiated in registration mode, NO for authentication mode.
 */
@property (nonatomic, readonly) BOOL isRegistration;

/*!
 @brief YES if the context requires ADoS for registration and authentication.
 */
@property (nonatomic, readonly) BOOL isADoSRequired;

/*!
 @brief YES if the context is in a success, failure, or cancellation state.
 @discussion If isCaptureComplete is true, then any calls to complete or cancel methods will be ignored. To reset this flag, call @link reset /@link.
 */
@property (nonatomic, readonly) BOOL isCaptureComplete;

/*!
 @brief The current view controller being used for collection.
 */
@property (nonatomic, weak) UIViewController *activeViewController;

/*!
 @brief The current authenticator information.
 */
@property (nonatomic, readonly) DASAuthenticatorInfo *authenticatorInfo;

/*!
 @brief YES if the activeViewController should be automatically dismissed on capture completion.
 */
@property (nonatomic) BOOL dismissViewControllerOnCompletion;

/*!
 @functiongroup Collection
 */

/*!
 @brief Dismisses the UI (if the client is not responsible) and terminates the capture process with the @link DASAuthenticatorErrorCancelled @/link error.
 */
- (void) cancelCapture;

/*!
 @brief Dismisses the UI (if the client is not responsible) and completes the capture process with success.
 */
- (void) completeCapture;

/*!
 @brief Dismisses the UI (if the client is not responsible) and completes the capture process with success and some additional data.
 @param data The additional data. Currently only used to provide the users input when performing Offline OTP.
 */
- (void) completeCaptureWithTemporaryData:(NSData*)data;

/*!
 @brief Dismisses the UI (if the client is not responsible) and completes the capture process with an @link DASAuthenticatorError @/link error.
 @param error The @link DASAuthenticatorError @/link type that caused capture to fail.
 */
- (void) completeCaptureWithError:(DASAuthenticatorError)error NS_SWIFT_NAME(completeCapture(error:));

/*!
@brief Resets a completed (isCaptureComplete == true) context so that it can be used again.
@discussion This is typically only used when going backwards in a navigation stack to previously completed authenticators.
*/
- (void) reset;


/*!
 @functiongroup Failed Attempts
 */

/*!
 @brief Logs the error and locks the authenticator if there have been too many attempts.
 @discussion The following is the default behavior when using this method:
 On each call, an attempt counter is incremented. If the attempt counter reaches 5 (override with "lock.max.attempts" extension) then:
 1) The attempt counter is reset
 2) The suspension counter is incremented
 3) The authenticator is temporarily locked for suspension counter * suspension milliseconds (Default: 30000, Override: "lock.suspend.init").
 
 If a successful attempt is made once the temporary lock expires, the attempt and suspension counters will both reset to 0.
 
 if failures continue, and the suspension counter reaches 3 (override with "lock.max.unlocks" extension), the authenticator will be permanently locked.
 
 For each attempt, @link reportAttemptWithErrorCode:score: @/link will be called to log the error.
 
 If either a temporary or permanent lock occurs, the Daon Authenticator SDK will display an error, then dismiss the capture UI.
 @note NOTE
 This function should not be called for ADoS authenticators as the server will be in control of locking those authenticators.
 @param errorCode The error code that was reported.
 @param score An optional score for reporting back with the error to the server.
 @return YES if the authenticator is now locked, NO otherwise.
 */
- (BOOL) incrementFailuresAndCheckForLockWithErrorCode:(NSInteger)errorCode score:(NSNumber*)score;

/*!
 @brief Logs the error and locks the authenticator if there have been too many attempts. Caller will control the display of any lock error.
 @discussion As @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link except the caller will control the display of any lock error. Includes a call to reportAttemptWithErrorCode:score:, allows custom UIs to handle locking error presentation themselves.
 @param errorCode The error code that was reported.
 @param score An optional score for potential reporting back with the error to the server.
 @param responseHandler A @link DASCompletionHandler @/link object that will be called on completion of the lock checks. If passed nil, authenticator is not locked.
 */
- (void) incrementFailuresAndCheckForLockWithErrorCode:(NSInteger)errorCode
                                                 score:(NSNumber*)score
                                       responseHandler:(DASCompletionHandler)responseHandler NS_SWIFT_NAME(incrementFailures(error:score:completion:));

/*!
 @brief Logs the error and locks the authenticator if there have been too many attempts. Caller will control the display of any lock error.
 @discussion As @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link except the caller will control the display of any lock error.
 @param error The error that was reported.
 @param delegate A @link DASAuthenticatorDelegate @/link object.
 */
- (NSError*) incrementFailuresAndCheckForLockWithError:(NSError*)error
                                              delegate:(id<DASAuthenticatorDelegate>)delegate;

- (void) resetLock;

/*!
 @brief Determine if there have been enough failed attempts to display a warning to the user.
 @return YES if the number of attempts is currently 3, otherwise NO.
 */
- (BOOL) haveEnoughFailedAttemptsForWarning;

/*!
 @brief Uses the @link DASAuthenticatorDelegate @/link object to report back any errors for potential delivery to a server for logging.
 @param errorCode The error code that was reported.
 @param score An optional score for potential reporting back with the error to the server.
 @return YES if the current authenticator action should be aborted.
 */
- (BOOL) reportAttemptWithErrorCode:(NSInteger)errorCode score:(NSNumber*)score;

/*!
 @brief Displays a lock error and terminates capture once the user presses OK.
 @param lockError The error to display
 */
- (void) showLockError:(NSError*)lockError;

/*!
 @functiongroup Controllers
 */

/*!
 @brief Register a @link DASControllerProtocol @/link derived object with the context so that cleanup can be perform at the completion of capture.
 @param controller The controller to register.
 */
- (void) registerController:(id<DASControllerProtocol>)controller;

/*!
 @brief Determines whether a @link DASControllerProtocol @/link derived object has been registered with the context.
 @param controller The controller to check.
 @return YES if the controller is registered.
 */
- (BOOL) isControllerRegistered:(id<DASControllerProtocol>)controller;

/*!
 @brief Instantiates a new @link DASADoSControllerProtocol @/link derived object responsible for delivering ADoS data to a server.
 @return A new object conforming to the @link DASADoSControllerProtocol @/link protocol.
 */
- (id<DASADoSControllerProtocol>) createStandardADoSController;

/*!
 @brief Instantiates a new @link DASADoSControllerProtocol @/link derived object responsible for delivering ADoS SRP data to a server.
 @return A new object conforming to the @link DASADoSControllerProtocol @/link protocol.
 */
- (id<DASADoSControllerProtocol>) createSrpADoSController;

/*!
 @brief Instantiates a new @link DASFingerprintControllerProtocol @/link derived object responsible for providing access to Touch ID registration and authentication functionality.
 @return A new object conforming to the @link DASFingerprintControllerProtocol @/link protocol.
 */
- (id<DASFingerprintControllerProtocol>) createFingerprintController;

/*!
 @brief Instantiates a new @link DASFingerprintControllerProtocol @/link derived object responsible for providing access to Touch ID registration and authentication functionality. It provides a simpler path
 to creating a custom UI for Touch ID as it encapsulates the logic surrounding calls to @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link and the "sdk.locking" extension so that your code does not need to.
 @param sdkWillHandleLockEvents Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
 @link performAuthenticationWithReason:completionHandler: @/link.
 @return A new object conforming to the @link DASFingerprintControllerProtocol @/link protocol.
 */
- (id<DASFingerprintControllerProtocol>) createFingerprintControllerWrapperWithSDKHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/*!
 @brief Instantiates a new @link DASFaceIdControllerProtocol @/link derived object responsible for providing access to Face ID registration and authentication functionality.
 @return A new object conforming to the @link DASFaceIdControllerProtocol @/link protocol.
 */
- (id<DASFaceIdControllerProtocol>) createFaceIdController;

/*!
 @brief Instantiates a new @link DASFaceIdControllerProtocol @/link derived object responsible for providing access to Face ID registration and authentication functionality. It provides a simpler path
 to creating a custom UI for Face ID as it encapsulates the logic surrounding calls to @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link and the "sdk.locking" extension so that your code does not need to.
 @param sdkWillHandleLockEvents Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
 @link performAuthenticationWithReason:completionHandler: @/link.
 @return A new object conforming to the @link DASFaceIdControllerProtocol @/link protocol.
 */
- (id<DASFaceIdControllerProtocol>) createFaceIdControllerWrapperWithSDKHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/*!
 @brief Instantiates a new @link DASMetadataControllerProtocol @/link derived object responsible for providing access metadata scanning functionality.
 @param delegate An object implementing @link DASMetadataControllerDelegate @/link that wishes to be notified of metadata scanning events from an @link DASMetadataControllerProtocol @/link derived object.
 @param previewView The UIView upon which the video preview will be drawn.
 @param metadataTypes The list of metadata types that you wish to scan for.
 @return A new object conforming to the @link DASMetadataControllerProtocol @/link protocol.
 */
- (id<DASMetadataControllerProtocol>) createMetadataControllerWithDelegate:(id<DASMetadataControllerDelegate>)delegate previewView:(UIView*)previewView metadataTypes:(NSArray<AVMetadataObjectType>*)metadataTypes;


/*!
 @functiongroup Extensions - Request
 */

/*!
 @brief Reads a value from the incoming extensions as a float.
 @param key The extensions key to read.
 @param defaultValue The default value to return if the key is not present in the extensions.
 @return A float value read from the incoming extensions, or defaultValue.
 */
- (float) extensionsFloatForKey:(NSString*)key defaultValue:(float)defaultValue;

/*!
 @brief Reads a value from the incoming extensions as an NSInteger.
 @param key The extensions key to read.
 @param defaultValue The default value to return if the key is not present in the extensions.
 @return A NSInteger value read from the incoming extensions, or defaultValue.
 */
- (NSInteger) extensionsIntForKey:(NSString*)key defaultValue:(NSInteger)defaultValue;

/*!
 @brief Reads a value from the incoming extensions as an NSString.
 @param key The extensions key to read.
 @return A NSString value read from the incoming extensions, or nil.
 */
- (NSString*) extensionsStringForKey:(NSString*)key;

/*!
 @brief Reads a value from the incoming extensions as a BOOL.
 @param key The extensions key to read.
 @param defaultValue The default value to return if the key is not present in the extensions.
 @return A BOOL value read from the incoming extensions, or defaultValue.
 */
- (BOOL) extensionsBoolForKey:(NSString*)key defaultValue:(BOOL)defaultValue;


/*!
 @functiongroup Extensions - Response
 */

/*!
 @brief Gets the current set of extensions that will be returned via the @link DASAuthenticatorDelegate @/link when registration or authentication completes.
 @return An NSDictionary mapping extension keys to values (both NSString).
 */
- (NSDictionary*)responseExtensions;

/*!
 @brief Sets the extensions that will be returned via the @link DASAuthenticatorDelegate @/link when registration or authentication completes.
 @param extensions An NSDictionary mapping extension keys to values (both NSString).
 */
- (void) setResponseExtensions:(NSDictionary*)extensions;


/*!
 @functiongroup Utilities
 */

/*!
 @brief Instantiates a new NSError object which encapsulates an @link DASAuthenticatorError @/link type.
 @param errorCode The @link DASAuthenticatorError @/link type that has occurred.
 @return A new NSError object for the @link DASAuthenticatorError @/link type.
 */
- (NSError*) errorForCode:(DASAuthenticatorError)errorCode;

/*!
 @brief Loads the localisation for a specific key.
 @param key The localisation key. See the DAS-Localizable.strings file for available keys and values.
 @return The localized string.
 */
- (NSString*) localise:(NSString*)key;
  
@end

#endif /* DASAuthenticatorContext_h */
