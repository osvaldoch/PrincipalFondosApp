//
//  DASAuthenticatorDelegate.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/11/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#ifndef DASAuthenticatorDelegate_h
#define DASAuthenticatorDelegate_h

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

// Forward Declarations
@protocol DASAuthenticatorContext;
@protocol DASCaptureControllerProtocol;
@protocol DASMultiAuthenticatorContext;
@class DASAuthenticatorCollectorInfo;
@class DASMultiAuthenticatorCollectorInfo;

// Blocks

/*!
 @typedef ADoSCompletionHandler
 @brief Block that is used to notify a calling object that ADoS submission has completed.
 @param error An error that came back from the server, or from the transmission process. If a nil is returned then it should be treated as success.
 @param data Any additional data returned from the server, such as SRP parameters.
 */
typedef void (^ADoSCompletionHandler) (NSError * _Nullable error, NSDictionary * _Nullable data);


/*!
 @brief A protocol for classes that wish to be notified of DASAuthenticator events.
 */
@protocol DASAuthenticatorDelegate <NSObject>


/*!
 @functiongroup General
 */

/*!
 @brief Used to notify a conforming object that a register operation has completed successfully.
 @param authenticator The active @link DASAuthenticator @/link object when register completed
 @param extensions An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into register as well as any completion extensions.
 @param keys An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to an NSArray containing the names of all keys just registered.
 */
- (void) onRegisterComplete:(nonnull id<DASAuthenticator>)authenticator
                 extensions:(nonnull NSDictionary*)extensions
                       keys:(nonnull NSDictionary*)keys;

/*!
 @brief Used to notify a conforming object that an authenticate operation has completed successfully.
 @param extensions An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into authenticate as well as any completion extensions.
 @param keys An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to an NSArray containing the names of all keys just authenticated.
 */
- (void) onAuthenticateComplete:(nonnull NSDictionary*)extensions
                           keys:(nonnull NSDictionary*)keys;

/*!
 @brief Used to notify a conforming object that the current operation has failed and capture has been terminated.
 @param authenticator The active @link DASAuthenticator @/link object when the operation failed.
 @param code The error code that was raised.
 @param message The message associated with the error that was raised.
 */
- (void) onFailed:(nullable id<DASAuthenticator>)authenticator
             code:(NSInteger)code
          message:(nonnull NSString*)message;

/*!
 @brief Used to notify a conforming object that the current authentication operation has failed but the user will be allowed to retry.
 @param authenticator The active authenticator when the operation failed.
 @param info An NSDictionary containing additional information related to the failure (lockStatus, errorCode, attempt, attemptsRemaining).
 @return YES if the authenticator should abort due to too many errors.
 */
- (BOOL) onAttemptFailed:(nonnull id<DASAuthenticator>)authenticator
                    info:(nonnull NSDictionary*)info;


/*!
 @functiongroup ADoS Only
 */

/*!
 @brief Used to notify a conforming object that ADoS data has been collected and should be delivered to the server for processing.
 @param factor The @link DASAuthenticatorFactor @/link type for which data has been collected.
 @param data The collected data, encoded and compressed for transmission.
 @param extensions An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to a secondary NSDictionary mapping extension keys to values. This contains any extensions initially passed into the current operation as well as any completion extensions.
 @param keys An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to an NSArray containing the names of all keys just registered.
 @param handler A @link ADoSCompletionHandler @/link block object that will be called once ADoS processing is complete.
 */
- (void) onDataCollectionCompleteForFactor:(DASAuthenticatorFactor)factor
                             collectedData:(nullable NSArray<NSData*>*)data
                                extensions:(nonnull NSDictionary*)extensions
                                      keys:(nonnull NSDictionary*)keys
                         onAnalysisComplete:(nullable ADoSCompletionHandler )handler;


/*!
 @functiongroup Optional UI Customization
 */

@optional

/*!
 @brief Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own UI.
 @param factor The @link DASAuthenticatorFactor @/link type for which data will be collected.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @return A custom UIViewController, or nil if the default view controller provided by the SDK should be used.
 */
- (nullable UIViewController*) onViewControllerForFactor:(DASAuthenticatorFactor)factor context:(nonnull id<DASAuthenticatorContext>)context;

/*!
 @brief Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own UI.
 @param factor The @link DASAuthenticatorFactor @/link type for which data will be collected.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @return A @link DASAuthenticatorCollectorInfo @/link object containing a reference to the custom UIViewController and whether or not the caller will be responsible for presentation of it. If nil is returned, the default view controller provided by the SDK will be used.
 */
- (nullable DASAuthenticatorCollectorInfo*) onCollectionViewControllerForFactor:(DASAuthenticatorFactor)factor context:(nonnull id<DASAuthenticatorContext>)context;

/*!
 @brief Used to notify a conforming object that data collection is about to begin for a specific grouped policy type, and that if they wish they can provide their own UI.
 @param policyType The @link DASAuthenticatorPolicyType @/link type which will prescribe the way in which the authenticators are presented to the user for selection.
 @param context The @link DASMultiAuthenticatorContext @/link object with which a custom view controller can determine which authenticators to display and how to authenticate them.
 @return A @link DASMultiAuthenticatorCollectorInfo @/link object containing a reference to the custom UIViewController and whether or not the caller will be responsible for presentation of it. If nil is returned, the default view controller provided by the SDK will be used.
 */
- (nullable DASMultiAuthenticatorCollectorInfo*) onCollectionViewControllerForPolicyType:(DASAuthenticatorPolicyType)policyType context:(nonnull id<DASMultiAuthenticatorContext>)context;

/*!
 @brief Used to notify a conforming object that data collection is about to begin for a specific factor, and that if they wish they can provide their own capture controller.
 @param factor The @link DASAuthenticatorFactor @/link type for which data will be collected.
 @param context The @link DASAuthenticatorContext @/link object with which a capture controller can register or authenticate.
 @return A @link DASCaptureControllerProtocol @/link object whose execute method will be called to begin collection.
 */
- (nullable id<DASCaptureControllerProtocol>) onCaptureControllerForFactor:(DASAuthenticatorFactor)factor
                                                                   context:(nonnull id<DASAuthenticatorContext>)context;

/*!
 @brief Used to notify a conforming object that data collection is about to begin for a specific grouped policy type, and that if they wish they can provide their own capture controller.
 @param policy The @link DASAuthenticatorPolicyType @/link type which dictates how selection should occur.
 @param context The @link DASMultiAuthenticatorContext @/link object with which a capture controller can create single authenticator @link DASAuthenticatorContext @/link objects.
 @return A @link DASCaptureControllerProtocol @/link object whose execute method will be called to begin collection.
 */
- (nullable id<DASCaptureControllerProtocol>) onCaptureControllerForPolicy:(DASAuthenticatorPolicyType)policy
                                                                   context:(nonnull id<DASMultiAuthenticatorContext>)context;

@end

#endif /* DASAuthenticatorDelegate_h */
