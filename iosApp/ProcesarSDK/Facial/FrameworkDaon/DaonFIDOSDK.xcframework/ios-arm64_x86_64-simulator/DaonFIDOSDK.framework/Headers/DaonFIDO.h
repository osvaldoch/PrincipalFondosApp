/*!
 @header DaonFIDO
 Daon FIDO UAF SDK interface. Provides an abstraction of FIDO UAF functionality. Exposes internal SDK authenticators.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

#import <DaonCryptoSDK/DaonCryptoSDK.h>

#import "IXUAFDelegate.h"
#import "IXUAFDiscoveryData.h"
#import "IXUAFTransaction.h"
#import "IXUAFVersion.h"
#import "IXUAFError.h"
#import "IXUAFLocator.h"
#import "IXUAFMessageReader.h"
#import "IXUAFAccount.h"

extern NSNumber * IXUAFWarningDeviceSecurityDisabled;
extern NSNumber * IXUAFWarningDeviceDebug;
extern NSNumber * IXUAFWarningDeviceCompromised;
extern NSNumber * IXUAFWarningDeviceNoHardwareKeystore;
extern NSNumber * IXUAFWarningKeyMigrationFailed;
extern NSNumber * IXUAFWarningPendingRegistrationsRemoved;
extern NSNumber * IXUAFWarningDeviceSimulator;

typedef NS_ENUM (NSInteger, IXUAFOfflineOTPMode)
{
    IXUAFOfflineOTPModeIdentify   = 0,  // User authenticates then the OTP is displayed.
    IXUAFOfflineOTPModeSign  = 1,       // User authenticates, enters transaction data / scans QR code, then the OTP is displayed.
};


@interface DaonFIDO : NSObject

@property(nonatomic, weak) id<IXUAFDelegate> delegate;

@property (nonatomic, readonly) BOOL initialized;

@property (nonatomic, strong, readonly) NSArray * warnings;

/*!
 @brief Initialize the SDK. This must be called before the SDK is used.
 */
- (IXUAFErrorCode) initialize;

/*!
 @brief Initialize the SDK. This must be called before the SDK is used.
 */
- (IXUAFErrorCode) initializeWithParameters:(NSDictionary*)parameters NS_SWIFT_NAME(initialize(parameters:));

/*!
 @brief Set token received when registering for push notifications
 */
+ (void) setPushNotificationServiceToken:(NSData*)token NS_SWIFT_NAME(setPushNotificationService(token:));

/*!
 @brief Perform UAF register operation
 @discussion If the registrationResponseMessageString in the completion response is nil,
 then there was an error with the format of the server response.
 */
- (void) register:(NSString*)uafMessage
       completion:(void (^)(NSString* response, NSError* error))completion NS_SWIFT_NAME(register(message:completion:));

/*!
 @brief Notify UAF client of the result of a UAF operation (registration or authentication)
 */
- (void) notifyResult:(NSString *)uafMessage responseCode:(NSInteger)responseCode NS_SWIFT_NAME(notifyResult(message:code:));

/*!
 @brief Notify UAF client of the result of a UAF operation (registration or authentication)
 @discussion The completion handler will return additional information about expired keys and if
 confirmation OTP is enabled, the OTP.
 */
- (void) notifyResult:(NSString *)uafMessage
         responseCode:(NSInteger)responseCode
           parameters:(NSDictionary*)parameters
           completion:(void (^)(NSDictionary* response, NSError* error))completion NS_SWIFT_NAME(notifyResult(message:code:params:completion:));

- (void) notifyResult:(NSString *)uafMessage
         responseCode:(NSInteger)responseCode
      responseMessage:(NSString*)responseMessage
           parameters:(NSDictionary*)parameters
           completion:(void (^)(NSDictionary* response, NSError* error))completion;

/*!
 @brief Perform UAF authenticate operation
 @discussion If the authenticationResponseMessage in the completion response is nil,
 then there was an error with the format of the server response.
 */
- (void) authenticate:(NSString *)uafMessage
           completion:(void (^)(NSString* response, NSError* error))completion NS_SWIFT_NAME(authenticate(message:completion:));

/*!
 @brief Generate a One Time Password (OTP).
 */
- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode
                        username:(NSString *)username
                           appId:(NSString *)appId
                      completion:(void (^)(NSDictionary<NSString*, NSString*>* response, NSError* error))completion;

- (void) oneTimePasswordWithMode:(IXUAFOfflineOTPMode)mode
                           appId:(NSString *)appId
                      completion:(void (^)(NSDictionary<NSString*, NSString*>* response, NSError* error))completion;


/*!
 @brief The expiration time of a current OTP
 */
+ (NSInteger) oneTimePasswordExpiration;

/*!
 @brief Perform UAF deregister operation
 */
- (void) deregister:(NSString *)uafMessage
         completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(deregister(message:completion:));

/*!
 @brief Discover the available UAF authenticators
 */
- (void) discover:(void (^)(IXUAFDiscoveryData* response, NSError* error))completion NS_SWIFT_NAME(discover(completion:));

/*!
 @brief Check that a UAF request policy can be processed by at least one of the available UAF authenticators.
 */
- (void) checkPolicy:(NSString *)uafRequest
          completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(checkPolicy(message:completion:));

/*!
 @brief Check that a UAF request policy can be processed by at least one of the available UAF authenticators for a given user.
 */
- (void) checkPolicy:(NSString *)uafRequest
            username:(NSString *)username
          completion:(void (^)(NSError* error))completion NS_SWIFT_NAME(checkPolicy(message:username:completion:));

/*!
 @brief Check for registered authenticators
 @discussion Get a list of authenticators which match the given registration policy and lists those which
 are registered for the given user and app ID.
 */
- (void) checkRegistrations:(NSString *)registrationPolicy
                   username:(NSString *)username
                      appId:(NSString *)appId
                 completion:(void (^)(NSArray<IXUAFAuthenticator*>* authenticators, NSError* error))completion
NS_SWIFT_NAME(checkRegistrations(policy:username:appId:completion:));

- (void) checkGroupRegistrations:(NSString *)registrationPolicy
                        username:(NSString *)username
                           appId:(NSString *)appId
                      completion:(void (^)(NSArray<NSArray<IXUAFAuthenticator*>*> * authenticators, NSError* error))completion
NS_SWIFT_NAME(checkGroupRegistrations(policy:username:appId:completion:));

/*!
 @brief Test whether an authenticator with a given aaid is locked.
 */
- (BOOL) isLocked:(NSString *)aaid NS_SWIFT_NAME(isLocked(aaid:));

/*!
 @brief Enable or disable runtime logging.
 */
+ (void) setLoggingEnabled:(BOOL)enabled NS_SWIFT_NAME(setLogging(enabled:));

+ (void) setLoggingEnabled:(BOOL)enabled level:(IXALogLevel)level NS_SWIFT_NAME(setLogging(enabled:level:));

+ (void) setLoggingEnabled:(BOOL)enabled level:(IXALogLevel)level persist:(BOOL)persist NS_SWIFT_NAME(setLogging(enabled:level:persist:));

/*!
 @brief Remove all keys and enrolled data
 */
+ (void) reset;

/*!
 @brief Remove all keys, enrolled data and alls keys with a UUID name
 */
+ (void) resetAndRemoveUUIDKeys;

/*!
 @brief Get device status information, e.g. jailbroken, environment, etc.
 */
+ (NSDictionary<NSString*, NSString*>*) status __deprecated;

/*!
 @brief Get SDK version.
 */
+ (NSString*) version;

/*!
 @brief Get key information and validity
 */
+ (NSDictionary*) keys;

/*!
 @brief Check if there are any valid keys
 */
+ (BOOL) hasValidKeys;

/*!
 @brief Get authenticator with AAID
 */
+ (IXUAFAuthenticator*) authenticatorWithAaid:(NSString*)aaid;

/*!
 @brief Set the facet ID.
 @discussion Under normal SDK operation this method should never be called.
 @param facetId The facet ID to set
 */
+ (void) setFacetId:(NSString *)facetId NS_SWIFT_NAME(setFacet(withId:));

/*!
 @brief Get Facet ID
 */
+ (NSString*) facetId;

/*!
 @brief Get device ID
 */
+ (NSString*) deviceId;

/*!
 @brief Get list of available accounts
 */
+ (NSArray<NSString*>*) accounts;

/*!
 @brief Delete account from device
 @param account the account to delete
 */
+ (void) deleteAccount:(IXUAFAccount*)account;
@end
