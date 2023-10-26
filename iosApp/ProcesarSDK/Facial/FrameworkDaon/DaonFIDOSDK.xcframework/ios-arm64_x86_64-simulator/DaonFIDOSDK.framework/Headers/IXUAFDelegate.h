/*!
 @header IXUAFDelegate
 SDK delegate for controlling registration and authentication behaviour, including UI customization.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "IXUAFAuthenticator.h"
#import "IXUAFAccount.h"
#import "IXUAFTransaction.h"
#import "IXUAFOperation.h"
#import "IXUAFCaptureDataEncryptor.h"

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticatorContext.h>
#import <DaonAuthenticatorSDK/DASMultiAuthenticatorCollectorInfo.h>
#import <DaonAuthenticatorSDK/DASCaptureControllerProtocol.h>

@protocol IXUAFDelegate <NSObject>

@optional

/*!
 @brief Allowed authenticators
 @discussion Called before registration or authentication with a list of allowed authenticators for the current request.
 Return all or a subset of authenticators.
 @param operation The current operation.
 @param authenticators The list of allowed authenticators.
 */
- (NSArray<NSArray<IXUAFAuthenticator*>*> * _Nullable ) operation:(id<IXUAFOperation> _Nonnull)operation willAllowAuthenticators:(NSArray<NSArray<IXUAFAuthenticator*>*> * _Nonnull)authenticators;

/*!
 @brief Can use accounts
 @discussion Called after authentication with a list of available accounts.
 Use the operation object to choose an account for signing.
 @param operation The current operation.
 @param accounts The list of available accounts.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation canUseAccounts:(NSArray<IXUAFAccount*> * _Nonnull)accounts;

/*!
 @brief Did select account
 @discussion Called when an account was selected.
 @param operation The current operation.
 @param account The selected account.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation didSelectAccount:(IXUAFAccount* _Nonnull)account ;

/*!
 @brief Should display transaction confirmation
 @discussion Called after authentication if a transaction confirmation is required.
 @param operation The current operation.
 @param transaction The transaction object. See IXUAFTransaction.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation shouldDisplayTransaction:(IXUAFTransaction* _Nonnull)transaction ;

/*!
 @brief Should verify message
 @discussion Called during registration or authentication if an operation requires additional validation. Currently this is
 only used for ADoS to submit the data to the server.
 @param operation The current operation.
 @param message The FIDO message.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation shouldVerifyMessage:(NSString* _Nonnull)message;

/*!
 @brief Signed fido message
 @discussion Called during registration or authentication when response is ready for the server
 @param operation The current operation.
 @param message The FIDO message.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation didSignMessage:(NSString* _Nonnull)message encryptor:(IXUAFCaptureDataEncryptor*_Nullable)encryptor;

/*!
 @brief Authentication attempt failed (non ADOS only)
 @discussion Called when an authentication attempt fails.
 @param operation The current operation.
 @param info The attempt info.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation authenticationAttemptFailedWithInfo:(NSDictionary<NSString*, id>* _Nonnull)info;

/*!
 @brief Authentication attempt failed (all authenticators
 @discussion Called when an authentication attempt fails.
 @param operation The current operation.
 @param info The attempt info. Max attempts and remaining attempts before being locked.
 */
- (void) operation:(id<IXUAFOperation> _Nonnull)operation attemptFailedWithInfo:(NSDictionary<NSString*, id>* _Nonnull)info;

/*!
 @brief Allow multiple choice authentication
 @discussion Enable multiple choice authentication. This requires a specific set of policies.
 */
- (BOOL) shouldAllowMultipleChoiceAuthentication;


// UI Customization

/*!
 @brief Return a view controller for a User Verification type
 @discussion This method has been deprecated, please use operation:shouldUseCollectionViewControllerForUserVerification:context: which provides greater control over presentation.
 @param operation The current operation.
 @param method The FIDO User Verification method/type.
 @param context The authenticator context.
 */
// -- Deprecated
//- (UIViewController* _Nullable)  operation:(id<IXUAFOperation> _Nonnull)operation
//shouldUseViewControllerForUserVerification:(NSInteger)method
//                                   context:(_Nonnull id<DASAuthenticatorContext>)context __deprecated_msg("This method has been deprecated, please use operation:shouldUseCollectionViewControllerForUserVerification:context: which provides greater control over presentation.");

/*!
 @brief Return a view controller for a User Verification type
 @discussion Called when an authenticator for a given User Verification needs a view controller.
 @param operation The current operation.
 @param method The FIDO User Verification method/type.
 @param context The authenticator context.
 */
- (DASAuthenticatorCollectorInfo* _Nullable)  operation:(id<IXUAFOperation> _Nonnull)operation
   shouldUseCollectionViewControllerForUserVerification:(NSInteger)method
                                                context:(_Nonnull id<DASAuthenticatorContext>)context;

/*!
 @brief Return a view controller for an authenticator type
 @discussion Called when a containing AND/OR view controller is needed.
 @param operation The current operation.
 @param type The policy type, e.g. AND/OR.
 @param context The authenticator context.
 */
- (DASMultiAuthenticatorCollectorInfo* _Nullable) operation:(id<IXUAFOperation> _Nonnull)operation
                shouldUseViewControllerForAuthenticatorType:(DASAuthenticatorPolicyType)type
                                                    context:(_Nonnull id<DASMultiAuthenticatorContext>)context;

/*!
 @brief Return a capture controller for a User Verification type
 @discussion Called when an authenticator for a given User Verification needs a capture controller.
 @param operation The current operation.
 @param method The FIDO User Verification method/type.
 @param context The authenticator context.
 */
- (id<DASCaptureControllerProtocol> _Nullable)  operation:(id<IXUAFOperation> _Nonnull)operation
            shouldUseCaptureControllerForUserVerification:(NSInteger)method
                                                  context:(_Nonnull id<DASAuthenticatorContext>)context;

/*!
 @brief Return a capture controller for a policy type
 @discussion Called when a containing AND/OR capture controller is needed.
 @param operation The current operation.
 @param type The policy type, e.g. AND/OR.
 @param context The authenticator context.
 */
- (id<DASCaptureControllerProtocol> _Nullable) operation:(id<IXUAFOperation> _Nonnull)operation
                     shouldUseCaptureControllerForPolicy:(DASAuthenticatorPolicyType)type
                                                 context:(_Nonnull id<DASMultiAuthenticatorContext>)context;

@end
