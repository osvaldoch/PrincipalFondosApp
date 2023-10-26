//
//  DASAuthenticatorFactory.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/8/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

@protocol DASAuthenticator;
@protocol DASMultiAuthenticatorContext;
@protocol DASStorageProvider;

/*!
 @brief Provides a number of class factory methods for determining supported authenticator types, and creating instances of them.
 */
@interface DASAuthenticatorFactory : NSObject

/*!
 @functiongroup Authenticator Availability
 */

/*!
 @brief Provides an NSArray of all currently supported authenticator types.
 @result An NSArray containing NSNumber objects which hold a @link DASAuthenticatorFactor @/link type.
 */
+ (NSArray*) getSupportedAuthenticators;

/*!
 @brief Provides an NSArray of all currently supported authenticator types.
 @param extensions An NSDictionary mapping extension keys to values (Both NSString) that may have impact on the availability of certain authenticators. E.g "com.daon.sdk.embedded.face".
 @result An NSArray containing NSNumber objects which hold a @link DASAuthenticatorFactor @/link type.
 */
+ (NSArray*) getSupportedAuthenticatorsWithExtensions:(NSDictionary*)extensions;


/*!
 @functiongroup Authenticator instantiation
 */

/*!
 @brief Instantiates a new @link DASAuthenticator @/link object which supports a specific type of registration / authentication.
 @param factor The requested factor (@link DASAuthenticatorFactor @/link) type.
 @result A new @link DASAuthenticator @/link object supporting the specified factor type.
 */
+ (id<DASAuthenticator>) getAuthenticator:(DASAuthenticatorFactor)factor;

/*!
 @brief Instantiates a new @link DASAuthenticator @/link object which supports a specific type of registration / authentication and signing algorithm.
 @param factor The requested factor (@link DASAuthenticatorFactor @/link) type.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type to use when creating / accessing keys.
 @result A new @link DASAuthenticator @/link object supporting the specified factor type.
 */
+ (id<DASAuthenticator>) getAuthenticator:(DASAuthenticatorFactor)factor usingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;


/*!
 @functiongroup Multi-Authenticator instantiation
 */

/*!
 @brief Instantiates a new @link DASMultiAuthenticator @/link object which supports registration / authentication of a group or groups of authenticators.
 @param policyType The requested policy (@link DASAuthenticatorPolicyType @/link) type.
 @result A new @link DASMultiAuthenticator @/link object supporting the specified policy type.
 */
+ (id<DASMultiAuthenticator>) getMultiAuthenticatorForPolicyType:(DASAuthenticatorPolicyType)policyType;

/*!
 @brief Instantiates a new @link DASMultiAuthenticator @/link object which supports registration / authentication of a group or groups of authenticators with a specific signing algorithm.
 @param policyType The requested policy (@link DASAuthenticatorPolicyType @/link) type.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type to use when creating / accessing keys.
 @result A new @link DASMultiAuthenticator @/link object supporting the specified policy type.
 */
+ (id<DASMultiAuthenticator>) getMultiAuthenticatorForPolicyType:(DASAuthenticatorPolicyType)policyType usingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;


/*!
 @functiongroup Context instantiation
 */

/*!
 @brief Instantiates a new @link DASAuthenticatorContext @/link object which provides a central hub for all information and services required for registration / authentication of an individual authenticator.
 @param authenticator The authenticator (@link DASAuthenticator @/link) with which to create the context for.
 @param isRegistration Whether or not we are registering or authenticating.
 @param isADoS Whether or not to send data to a server for registration / authentication.
 @param requestExtensions An NSDictionary mapping extension name to extension value (Both NSString).
 @param requestKeys An NSArray containing the key names to use during registration or authentication.
 @param dismissUIOnCompletion Whether or not to dismiss the authenticators view controller automatically once registration / authentication is complete.
 @param handler A @link DASCompletionHandlerWithData @/link object that will be called on success or failure of the registration / authentication.
 @result A new @link DASAuthenticatorContext @/link object configured to support the selected authenticator.
 */
+ (id<DASAuthenticatorContext>) getAuthenticatorContextForAuthenticator:(id<DASAuthenticator>)authenticator
                                                         isRegistration:(BOOL)isRegistration
                                                                 isADoS:(BOOL)isADoS
                                                      requestExtensions:(NSDictionary*)requestExtensions
                                                            requestKeys:(NSArray*)requestKeys
                                                  dismissUIOnCompletion:(BOOL)dismissUIOnCompletion
                                                      completionHandler:(DASCompletionHandlerWithData)handler;

/*!
 @brief Instantiates a new @link DASAuthenticatorContext @/link object specifically for accessing context functionality without a specific authenticator. isRegistration will default to true.
 @result A new @link DASAuthenticatorContext @/link object.
 */
+ (id<DASAuthenticatorContext>) getSimpleContext;

/*!
 @brief Instantiates a new @link DASMultiAuthenticatorContext @/link object which provides a central hub for all information and services required for registration / authentication of an set of authenticators.
 @param authenticators The selected authenticators in an NSDictionary with a mapping of NSNumber objects holding a @link DASAuthenticatorFactor @/link type to their associated @link DASAuthenticator @/link object.
 @param policyType The @link DASAuthenticatorPolicyType @/link type which will prescribe the way in which the authenticators are presented to the user for selection.
 @param factorsAndKeys An NSArray of authenticator groups, each group made up of an NSDictionary that maps @link DASAuthenticatorFactor @/link types (in a NSNumber object) to an NSArray of keys (NSString objects).
 @param factorsAndExtensions An NSDictionary that maps @link DASAuthenticatorFactor @/link types (in a NSNumber object) to an NSDictionary mapping extension name to extension value (Both NSString).
 @param uiCustomizationDelegate An @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator events specific to UI customization.
 @param isRegistration Whether or not we are registering or authenticating the set of authenticators.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing an authenticators key.
 @param filterNonUIAuthenticators Whether or not to filter out Non-ui authenticators when performing an DASAuthenticatorPolicyTypeOR policy. Default is YES.
 @param completionHandler A block object that will be called on success of the registration / authentication for a set of authenticators.
 @param failureHandler A block object that will be called on failure of the registration / authentication for a set of authenticators
 @result A new @link DASMultiAuthenticatorContext @/link object configured to support the selected select of authenticators.
 */
+ (id<DASMultiAuthenticatorContext>) getMultiAuthenticatorContextForAuthenticators:(NSDictionary*)authenticators
                                                                            policy:(DASAuthenticatorPolicyType)policyType
                                                                    factorsAndKeys:(NSArray<NSDictionary*>*)factorsAndKeys
                                                                 requestExtensions:(NSDictionary<NSNumber*, NSDictionary*>*)factorsAndExtensions
                                                           uiCustomizationDelegate:(id<DASAuthenticatorDelegate>)uiCustomizationDelegate
                                                                    isRegistration:(BOOL)isRegistration
                                                                  signingAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm
                                                         filterNonUIAuthenticators:(BOOL)filterNonUIAuthenticators
                                                                      onCompletion:(void (^) (NSDictionary* extensions, NSDictionary* keys))completionHandler
                                                                         onFailure:(void (^) (id<DASAuthenticator> authenticator, DASAuthenticatorError error))failureHandler;


/*!
 @functiongroup Controller instantiation
 */

/*!
 @brief Instantiates a new @link DASADoSControllerProtocol @/link derived object responsible for delivering ADoS data to a server.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param authenticator The @link DASAuthenticator @/link authenticator to be used.
 @param extensions The incoming request extensions.
 @param keys The incoming request keys.
 @param startTime The time at which the authenticator process started.
 @return A new object conforming to the @link DASADoSControllerProtocol @/link protocol.
 */
+ (id<DASADoSControllerProtocol>) getStandardADoSControllerWithContext:(id<DASAuthenticatorContext>)context
                                                         authenticator:(id<DASAuthenticator>)authenticator
                                                     requestExtensions:(NSDictionary*)extensions
                                                           requestKeys:(NSArray*)keys
                                                             startTime:(NSDate*)startTime;

/*!
 @brief Instantiates a new @link DASADoSControllerProtocol @/link derived object responsible for delivering ADoS SRP data to a server.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param authenticator The @link DASAuthenticator @/link authenticator to be used.
 @param extensions The incoming request extensions.
 @param keys The incoming request keys.
 @param startTime The time at which the authenticator process started.
 @return A new object conforming to the @link DASADoSControllerProtocol @/link protocol.
 */
+ (id<DASADoSControllerProtocol>) getSrpADoSControllerWithContext:(id<DASAuthenticatorContext>)context
                                                    authenticator:(id<DASAuthenticator>)authenticator
                                                requestExtensions:(NSDictionary*)extensions
                                                      requestKeys:(NSArray*)keys
                                                        startTime:(NSDate*)startTime;

/*!
 @brief Instantiates a new @link DASFingerprintControllerProtocol @/link derived object responsible for providing access to Touch ID registration and authentication functionality.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @return A new object conforming to the @link DASFingerprintControllerProtocol @/link protocol.
 */
+ (id<DASFingerprintControllerProtocol>) getFingerprintControllerWithContext:(id<DASAuthenticatorContext>)context;

/*!
 @brief Instantiates a new @link DASFingerprintControllerProtocol @/link derived object responsible for providing access to Touch ID registration and authentication functionality. It provides a simpler path
 to creating a custom UI for Touch ID as it encapsulates the logic surrounding calls to @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link and the "sdk.locking" extension so that your code does not need to.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param sdkWillHandleLockEvents Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
 @link performAuthenticationWithReason:completionHandler: @/link.
 @return A new object conforming to the @link DASFingerprintControllerProtocol @/link protocol.
 */
+ (id<DASFingerprintControllerProtocol>) getFingerprintControllerWrapperWithContext:(id<DASAuthenticatorContext>)context
                                                              sdkHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/*!
 @brief Instantiates a new @link DASFaceIdControllerProtocol @/link derived object responsible for providing access to Face ID registration and authentication functionality.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @return A new object conforming to the @link DASFaceIdControllerProtocol @/link protocol.
 */
+ (id<DASFaceIdControllerProtocol>) getFaceIdControllerWithContext:(id<DASAuthenticatorContext>)context;

/*!
 @brief Instantiates a new @link DASFaceIdControllerProtocol @/link derived object responsible for providing access to Face ID registration and authentication functionality. It provides a simpler path
 to creating a custom UI for Face ID as it encapsulates the logic surrounding calls to @link incrementFailuresAndCheckForLockWithErrorCode:score: @/link and the "sdk.locking" extension so that your code does not need to.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param sdkWillHandleLockEvents Whether or not the SDK will automatically handle display of lock errors (and will subsequently dismiss the UI) when a lock occurs. If NO, the lock error will be returned to via the handler of
 @link performAuthenticationWithReason:completionHandler: @/link.
 @return A new object conforming to the @link DASFaceIdControllerProtocol @/link protocol.
 */
+ (id<DASFaceIdControllerProtocol>) getFaceIdControllerWrapperWithContext:(id<DASAuthenticatorContext>)context
                                                    sdkHandlingLockEvents:(BOOL)sdkWillHandleLockEvents;

/*!
 @brief Instantiates a new @link DASMetadataControllerProtocol @/link derived object responsible for providing access metadata scanning functionality.
 @param delegate An object implementing @link DASMetadataControllerDelegate @/link that wishes to be notified of metadata scanning events from an @link DASMetadataControllerProtocol @/link derived object.
 @param previewView The UIView upon which the video preview will be drawn.
 @param metadataTypes The list of metadata types that you wish to scan for.
 @return A new object conforming to the @link DASMetadataControllerProtocol @/link protocol.
 */
+ (id<DASMetadataControllerProtocol>) getMetadataControllerWithDelegate:(id<DASMetadataControllerDelegate>)delegate
                                                            previewView:(UIView*)previewView
                                                          metadataTypes:(NSArray<AVMetadataObjectType>*)metadataTypes;


/*!
 @functiongroup Key management and data storage
 */

/*!
 @brief Instantiates a new @link DASStorageProvider @/link derived object responsible for providing key management and storage capabilities.
 @return A new object conforming to the @link DASStorageProvider @/link protocol.
 */
+ (id<DASStorageProvider>) getStorageProvider;

@end
