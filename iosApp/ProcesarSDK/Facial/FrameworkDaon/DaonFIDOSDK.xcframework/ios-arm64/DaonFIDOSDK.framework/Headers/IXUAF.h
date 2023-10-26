/*!
 @header IXUAF
 Simplified FIDO interface.
 @copyright Daon. All rights reserved.
 @updated 2019-01-10
 */

#import <Foundation/Foundation.h>
#import "DaonFIDO.h"
#import "IXUAFServiceDelegate.h"

static NSString * _Nonnull const kIXUAFServiceParameterUsername      = @"username";
static NSString * _Nonnull const kIXUAFServiceParameterApplication   = @"application";
static NSString * _Nonnull const kIXUAFServiceParameterDescription   = @"description";
static NSString * _Nonnull const kIXUAFServiceParameterIdentifier    = @"id";
static NSString * _Nonnull const kIXUAFServiceParameterProvider      = @"provider";
static NSString * _Nonnull const kIXUAFServiceParameterServer        = @"device.gateway.url";
static NSString * _Nonnull const kIXUAFServiceParameterType          = @"push.type";
static NSString * _Nonnull const kIXUAFServiceParameterRequest       = @"request";

static NSString * _Nonnull const kIXUAFServiceParameterPolicyRegistration = @"param.policy.reg";
static NSString * _Nonnull const kIXUAFServiceParameterPolicyAuthentication = @"param.policy.auth";

static NSString * _Nonnull const kIXUAFServiceParameterAccountNameFirst = @"param.account.name.first";
static NSString * _Nonnull const kIXUAFServiceParameterAccountNameLast = @"param.account.name.last";
static NSString * _Nonnull const kIXUAFServiceParameterAccountPassword = @"param.account.password";
static NSString * _Nonnull const kIXUAFServiceParameterAccountRegistrationRequest = @"param.account.registration";

static NSString * _Nonnull const kIXUAFServiceParameterEnableTransactionConfirmation = @"param.transaction.confirmation";
static NSString * _Nonnull const kIXUAFServiceParameterSingleShot = @"param.singleshot";

static NSString * _Nonnull const kIXUAFApplicationSchemeDefault = @"default";  // iOS bundle id
static NSString * _Nonnull const kIXUAFApplicationSchemeUser    = @"user";     // User set
static NSString * _Nonnull const kIXUAFApplicationSchemeURL     = @"url";      // E.g. Published Locally


@interface IXUAF : NSObject <IXUAFDelegate>

/*!
@brief The configuration delegate.
*/
@property(nonatomic, weak) id<IXUAFDelegate> _Nullable delegate;

/*!
@brief True if the SDK is initialized.
*/
@property (nonatomic, readonly) BOOL initialized;

/*!
@brief The FIDO application id.
*/
@property (nonatomic, strong)   NSString *_Nullable application;

/*!
@brief Enable or disable logging. Default is disabled.
*/
@property (nonatomic, assign)   BOOL logging;

/*!
 @brief Set token received when registering for push notifications
 @param token The Apple Push Notifications token.
 */
+ (void) setPushNotificationServiceToken:(NSData*_Nonnull)token NS_SWIFT_NAME(setPushNotificationService(token:));

- (instancetype _Nonnull) initWithService:(id<IXUAFServiceDelegate>_Nullable)service;

/*!
 @brief Initialise the SDK. This must be called before the SDK is used.
 @param parameters The SDK exensions and other parameters.
 @param completion The completion handler.
 */
- (void) initializeWithParameters:(NSDictionary *_Nullable)parameters
                       completion:(void (^_Nonnull)(IXUAFErrorCode code, NSArray<NSNumber*> *_Nonnull warnings))completion NS_SWIFT_NAME(initialize(parameters:completion:));


- (void) requestServiceAccessWithUsername:(NSString*_Nonnull)username
                               parameters:(NSDictionary *_Nullable)parameters
                               completion:(void (^_Nonnull)(NSString*_Nullable, NSError *_Nullable))completion NS_SWIFT_NAME(requestServiceAccess(username:parameters:completion:));

- (void) revokeServiceAccessWithParameters:(NSDictionary *_Nullable)parameters
                                completion:(void (^_Nonnull)(NSError *_Nullable))completion NS_SWIFT_NAME(revokeServiceAccess(parameters:completion:));

- (void) deleteUser:(NSString*_Nonnull)username
         parameters:(NSDictionary *_Nullable)parameters
         completion:(void (^_Nonnull)(NSError *_Nullable))completion NS_SWIFT_NAME(delete(username:parameters:completion:));

/*!
@brief Set parameter/extension
@param param The SDK exensions and other parameters.
@param value The value.
*/
- (IXUAFErrorCode) setParameter:(NSString*_Nonnull)param value:(NSString*_Nonnull)value;

/*!
@brief Get application scheme
*/
- (NSString*_Nonnull) applicationScheme;

/*!
 @brief Discover available UAF authenticators.
 @param handler The handler returns the list of authenticators or an error.
 */
- (void) discoverWithCompletionHandler:(void (^_Nonnull)(IXUAFDiscoveryData *_Nullable response, NSError *_Nullable error))handler;

/*!
 @brief Perform UAF register operation.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler __deprecated_msg("This method has been deprecated, please use register(username:handler:)");

/*!
 @brief Perform UAF register operation.
 @param parameters Additional parameters passed during registration.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithParameters:(NSDictionary*_Nullable)parameters
                        handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(parameters:handler:)) __deprecated_msg("This method has been deprecated, please use register(username:parameters:handler:)");

/*!
 @brief Perform UAF register operation.
 @param username The username.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithUsername:(NSString*_Nullable)username
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(username:handler:));

/*!
 @brief Perform UAF register operation.
 @param username The username.
 @param parameters Additional parameters passed during registration.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithUsername:(NSString*_Nullable)username
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(username:parameters:handler:));

/*!
 @brief Perform UAF authenticate operation.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithCompletionHandler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler;

/*!
 @brief Perform UAF authenticate operation.
 @param parameters Additional parameters passed during authentication
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithParameters:(NSDictionary*_Nullable)parameters
                            handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(parameters:handler:));

/*!
 @brief Perform UAF step-up authenticate operation.
 @param username The username.
 @param description A short description
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithUsername:(NSString*_Nullable)username
                      description:(NSString*_Nullable)description
                          handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(username:description:handler:));

/*!
 @brief Perform UAF step-up authenticate operation.
 @param username The username.
 @param description A short description
 @param parameters Additional parameters passed during authentication.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithUsername:(NSString*_Nullable)username
                      description:(NSString*_Nullable)description
                       parameters:(NSDictionary*_Nullable)parameters
                          handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(username:description:parameters:handler:));

/*!
 @brief Perform UAF authenticate operation in response to a push notification.
 @param notification The push notification dictionary.
 @param username The username.
 @param parameters Additional parameters passed during authentication.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithNotification:(NSDictionary*_Nonnull)notification
                             username:(NSString*_Nullable)username
                           parameters:(NSDictionary*_Nullable)parameters
                              handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(notification:username:parameters:handler:));

/*!
 @brief Perform UAF deregister operation.
 @param aaid The AAID.
 @param username The username if available
 @param parameters Additional parameters passed during deregistration.
 @param handler The handler returns nil if the operation was a success.
 */
- (void) deregisterWithAaid:(NSString*_Nonnull)aaid
                   username:(NSString*_Nullable)username
                 parameters:(NSDictionary*_Nullable)parameters
                    handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(aaid:username:parameters:handler:));

/*!
 @brief Perform UAF deregister operation.
 @param aaid The AAID.
 @param username The username if available
 @param handler The handler returns nil if the operation was a success.
 */
- (void) deregisterWithAaid:(NSString*_Nonnull)aaid
                   username:(NSString*_Nullable)username
                    handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(aaid:username:handler:));

/*!
 @brief Perform UAF deregister operation.
 @param message The FIDO deregistration message.

 @param handler The handler returns nil if the operation was a success.
 */
- (void) deregisterWithMessage:(NSString*_Nonnull)message
                       handler:(void (^_Nonnull)(NSError *_Nullable))handler NS_SWIFT_NAME(deregister(message:handler:));

/*!
 @brief Perform UAF deregister operation.
 @discussion The handler is called for each deregistered authenticator with an AAID and/or error. The call is complete when the AAID is nil.
 @param parameters Additional parameters passed during deregistration.
 @param handler The handler is called with an AAID and/or error. The call is complete when the AAID is nil.
 */
- (void) deregisterWithUsername:(NSString*_Nonnull)username
                     parameters:(NSDictionary*_Nullable)parameters
                        handler:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(deregister(username:parameters:handler:));

/*!
 @brief Perform UAF deregister operation.
 @discussion The handler is called for each deregistered authenticator with an AAID and/or error. The call is complete when the AAID is nil.

 @param handler The handler is called with an AAID and/or error. The call is complete when the AAID is nil.
 */
- (void) deregisterWithUsername:(NSString*_Nonnull)username
                        handler:(void (^_Nonnull)(NSString *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(deregister(username:handler:));

/*!
 @brief Check for registered authenticators.
 @discussion Get a list of authenticators which match the given registration policy and lists those which
 are registered for the given user and app ID.
 @param username The username.
 @param parameters Additional parameters
 @param handler The handler returns the list of authenticators or an error.
 */
- (void) checkRegistrationsWithUsername:(NSString*_Nonnull)username
                             parameters:(NSDictionary*_Nullable)parameters
                                handler:(void (^_Nonnull)(NSArray<IXUAFAuthenticator *> * _Nullable authenticators, NSError * _Nullable error)) handler NS_SWIFT_NAME(checkRegistrations(username:parameters:handler:)) __deprecated;

/*!
 @brief Check that a UAF message can be processed by at least one of the available UAF authenticators.
 @param message The FIDO message.
 @param handler The handler returns nil if the operation was a success.
 */
- (void) checkMessage:(NSString *_Nonnull)message handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/*!
 @brief Check that a UAF message can be processed by at least one of the available UAF authenticators.
 @param message The FIDO message.
 @param username The username
 @param handler The handler returns nil if the operation was a success.
 */
- (void) checkMessage:(NSString *_Nonnull)message username:(NSString*_Nullable)username handler:(void (^_Nonnull)(NSError *_Nullable error))handler;

/*!
 @brief Generate a One Time Password (OTP).
 @param mode The mode IXUAFOfflineOTPModeIdentify or IXUAFOfflineOTPModeSign.
 @param handler The handler returns the response or an error.
 */
- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode handler:(void (^_Nonnull)(NSDictionary<NSString*, NSString*> *_Nullable response, NSError *_Nullable error))handler;

/*!
 @brief Check if authenticator is registered
 @param aaid The aaid
 @param username The username
 */
- (BOOL) registeredWithAuthenticator:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;
    
// Single Shot

/*!
 @brief Register with FIDO message, e.g. can be used for single-shot registration.
 @param message The FIDO message.
 @param parameters Additional parameters passed during registration.
 @param handler The handler returns the response or an error.
 */
- (void) registerWithMessage:(NSString*_Nonnull)message
                  parameters:(NSDictionary*_Nullable)parameters
                     handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(message:parameters:handler:));

/*!
 @brief Authenticate with FIDO message, e.g. can be used for single-shot authentication.
 @param message The FIDO message.
 @param parameters Additional parameters passed during authentication.
 @param handler The handler returns the response or an error.
 */
- (void) authenticateWithMessage:(NSString*_Nonnull)message
                      parameters:(NSDictionary*_Nullable)parameters
                         handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(message:parameters:handler:));

// Headless

- (BOOL) isRegisteredAaid:(NSString*_Nonnull)aaid username:(NSString*_Nullable)username;

- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
                     data:(id _Nullable)data
               parameters:(NSDictionary*_Nullable)parameters
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(aaid:username:data:parameters:handler:));

- (void) registerWithAaid:(NSString*_Nonnull)aaid
                 username:(NSString*_Nullable)username
               parameters:(NSDictionary*_Nullable)parameters
                  handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(register(aaid:username:parameters:handler:));

- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                  description:(NSString*_Nullable)description
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(aaid:username:description:parameters:handler:));

- (void) authenticateWithAaid:(NSString*_Nonnull)aaid
                     username:(NSString*_Nullable)username
                         data:(id _Nullable)data
                  description:(NSString*_Nullable)description
                   parameters:(NSDictionary*_Nullable)parameters
                      handler:(void (^_Nonnull)(NSDictionary<NSString*, id> *_Nullable, NSError *_Nullable))handler NS_SWIFT_NAME(authenticate(aaid:username:data:description:parameters:handler:));
@end

