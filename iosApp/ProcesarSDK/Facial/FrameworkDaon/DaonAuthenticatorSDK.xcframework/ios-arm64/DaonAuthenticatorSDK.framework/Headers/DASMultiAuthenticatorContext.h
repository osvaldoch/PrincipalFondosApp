//
//  DASMultiAuthenticatorContext.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 4/28/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>

#ifndef DASMultiAuthenticatorContext_h
#define DASMultiAuthenticatorContext_h

// Forward Declarations
@class DASAuthenticatorInfo;

// Blocks

/*!
 @typedef DASMultiAuthenticatorContextCompletionHandler
 @brief Block that is used to notify a calling object that registration or authentication has completed successfully.
 @param factor The @link DASAuthenticatorFactor @/link type that was completed.
 */
typedef void (^DASMultiAuthenticatorContextCompletionHandler) (DASAuthenticatorFactor factor);

/*!
 @typedef DASMultiAuthenticatorContextFailureHandler
 @brief Block that is used to notify a calling object that registration or authentication has failed.
 @param factor The @link DASAuthenticatorFactor @/link type that failed.
 @param error The @link DASAuthenticatorError @/link type that caused registration or authentication to fail.
 */
typedef void (^DASMultiAuthenticatorContextFailureHandler) (DASAuthenticatorFactor factor, DASAuthenticatorError error);


/*!
 @brief A protocol for classes that wish to implement their own concrete Multi-Authenticator context.
 @discussion The Multi-Authenticator context is the central hub for all information and services relating to registration and authenticator of a group or groups of authenticators.
 */
@protocol DASMultiAuthenticatorContext <NSObject>

/*!
 @brief The current view controller being used for collection.
 */
@property (nonatomic) UIViewController *activeViewController;

/*!
 @brief The current factor (@link DASAuthenticatorFactor @/link) being collected.
 @discussion Typical this is called from the current Multi-Authenticator view controller to alert the context when the user has switched between different authenticators.
 */
@property (nonatomic) DASAuthenticatorFactor activeFactor;

/*!
 @brief The ordered priority of authenticators, as configured using the "com.daon.sdk.authenticator.precedence" extension. Each element being an NSNumber object containing a value from the @link DASAuthenticatorFactor @/link enum.
 */
@property (nonatomic, readonly) NSArray *authenticatorPrecedence;

/*!
 @brief YES if the context is in a success, failure, or cancellation state.
 */
@property (nonatomic, readonly) BOOL isCaptureComplete;


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
 @brief Dismisses the UI (if the client is not responsible) and completes the capture process with an @link DASAuthenticatorError @/link error.
 @param error The @link DASAuthenticatorError @/link type that caused capture to fail.
 */
- (void) completeCaptureWithError:(DASAuthenticatorError)error;


/*!
 @functiongroup Authenticators 
 */

/*!
 @brief Provides access to the set of authenticator groups that the context was instantiated with.
 @discussion For the @link DASAuthenticatorPolicyTypeAND @/link and @link DASAuthenticatorPolicyTypeOR @/link policy types, the top level of the NSArray should only contain one item. 
 For the @link DASAuthenticatorPolicyTypeMultipleChoice @/link policy type there will be multiple items (authenticator groups) as specified by your server policy.
 @return An NSArray where each element represents an authenticator group as an NSArray of @link DASAuthenticatorInfo @/link objects.
 */
- (NSArray<NSArray<DASAuthenticatorInfo*>*>*) requestedAuthenticatorGroups;

/*!
 @brief Instantiates a ready for presentation UIViewController for a specific factor. Completion and failure handlers provide event handling.
 @param factor The @link DASAuthenticatorFactor @/link type to instantiate a view controller for.
 @param completionHandler The block that will be executed once data completion for the authenticator completes successfully.
 @param failureHandler The block that will be executed once data completion for the authenticator completes with an error.
 @return A new UIViewController instance ready for presentation.
 */
- (UIViewController*) authenticatorViewControllerForFactor:(DASAuthenticatorFactor)factor
                                         completionHandler:(DASMultiAuthenticatorContextCompletionHandler)completionHandler
                                            failureHandler:(DASMultiAuthenticatorContextFailureHandler)failureHandler;

/*!
 @brief Instantiates a @link DASAuthenticatorContext @/link object for registration/authentication of a specific factor. Completion and failure handlers provide event handling.
 @param factor The @link DASAuthenticatorFactor @/link type to instantiate a @link DASAuthenticatorContext @/link object for.
 @param completionHandler The block that will be executed once data completion for the context completes successfully.
 @param failureHandler The block that will be executed once data completion for the context completes with an error.
 @return A new @link DASAuthenticatorContext @/link object instance ready for use.
 */
- (id<DASAuthenticatorContext>) authenticatorContextForFactor:(DASAuthenticatorFactor)factor
                                            completionHandler:(DASMultiAuthenticatorContextCompletionHandler)completionHandler
                                               failureHandler:(DASMultiAuthenticatorContextFailureHandler)failureHandler;


/*!
 @functiongroup Factors 
 */

/*!
 @brief Returns whether or not the Multi-Authenticator contains at least one Authenticator that has been invalidated (had its keys removed).
 @discussion Invalidation currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
 @return Whether or not the Multi-Authenticator contains at least one Authenticator that has been invalidated.
 */
- (BOOL) hasInvalidatedFactors;

/*!
@brief Resets a completed (isCaptureComplete == true) individual factors context so that it can be used again.
@discussion This is typically only used when going backwards in a navigation stack to previously completed authenticators.
*/
- (void) resetActiveFactorContext;


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
 @return The localised string.
 */
- (NSString*) localise:(NSString*)key;

@end

#endif /* DASMultiAuthenticatorContext_h */
