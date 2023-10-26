//
//  DASAuthenticator.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/8/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#ifndef DASAuthenticator_h
#define DASAuthenticator_h

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

// Enums

/*!
 @typedef DASAuthenticatorSigningAlgorithm
 @brief Categorizes the different signing algorithms available.
 @constant DASAuthenticatorSigningAlgorithmRSA                  RSA.
 @constant DASAuthenticatorSigningAlgorithmEC                   EC. Default.
 @constant DASAuthenticatorSigningAlgorithmECWithAccessibility  EC without requiring a device passcode to be set.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorSigningAlgorithm)
{
    DASAuthenticatorSigningAlgorithmRSA = 0,
    DASAuthenticatorSigningAlgorithmEC  = 1,
    DASAuthenticatorSigningAlgorithmECWithAccessibility  = 2
};

/*!
 @typedef DASAuthenticatorFactor
 @brief Categorizes the different types of authenticator.
 @constant DASAuthenticatorFactorFace                   Face collection via device camera. Face data is registered & authenticated on the device.
 @constant DASAuthenticatorFactorFaceADoS               Face collection via device camera. Face data is registered & authenticated on the server.
 @constant DASAuthenticatorFactorVoice                  Voice collection via device microphone. Voice data is registered & authenticated on the device.
 @constant DASAuthenticatorFactorVoiceADoS              Voice collection via device microphone. Voice data is registered & authenticated on the server.
 @constant DASAuthenticatorFactorPassword               Passcode collection. Passcode data is registered & authenticated on the device.
 @constant DASAuthenticatorFactorPasswordADoS           Passcode collection. Passcode data is registered & authenticated on the server.
 @constant DASAuthenticatorFactorFingerprint            Touch ID registration & authentication.
 @constant DASAuthenticatorFactorPattern                Not supported at this time.
 @constant DASAuthenticatorFactorSilent                 Device possession.
 @constant DASAuthenticatorFactorSilentAccessibility    Device possession using DASAuthenticatorSigningAlgorithmECWithAccessibility algorithm.
 @constant DASAuthenticatorFactorEye                    Discontinued.
 @constant DASAuthenticatorFactorPalm                   Palm collection via device camera. Palm data is registered & authenticated on the device.
 @constant DASAuthenticatorFactorOfflineOTP             Offline OTP.
 @constant DASAuthenticatorFactorUnsupported            Default if no type is set.
 @constant DASAuthenticatorFactorUnknown                No / unknown type.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorFactor)
{
    DASAuthenticatorFactorFace                  = 0,
    DASAuthenticatorFactorFaceADoS              = 1,
    DASAuthenticatorFactorVoice                 = 2,
    DASAuthenticatorFactorVoiceADoS             = 3,
    DASAuthenticatorFactorPassword              = 4,
    DASAuthenticatorFactorPasswordADoS          = 5,
    DASAuthenticatorFactorFingerprint           = 6,
    DASAuthenticatorFactorPattern               = 7,    // Not supported.
    DASAuthenticatorFactorSilent                = 8,
    DASAuthenticatorFactorSilentAccessibility   = 9,
    DASAuthenticatorFactorEye                   = 10,   // Discontinued.
    DASAuthenticatorFactorPalm                  = 11,
    DASAuthenticatorFactorOfflineOTP            = 12,
    DASAuthenticatorFactorFaceIDFix             = 13,
    DASAuthenticatorFactorUnsupported           = 14,
    DASAuthenticatorFactorUnknown               = 15
};

/*!
 @typedef DASAuthenticatorProtection
 @brief Categorizes the different types of authenticator protection mechanisms.
 @constant DASAuthenticatorProtectionHardware Hardware protection.
 @constant DASAuthenticatorProtectionSoftware Software protection.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorProtection)
{
    DASAuthenticatorProtectionHardware  = 0,
    DASAuthenticatorProtectionSoftware  = 1,
    DASAuthenticatorProtectionUnknown   = 2
};

/*!
 @typedef DASAuthenticatorLockState
 @brief Categorizes the different types of authenticator authenticator lock state.
 @constant DASAuthenticatorLockStateUnlocked    Not Locked.
 @constant DASAuthenticatorLockStateTemporary   Temporary Lock.
 @constant DASAuthenticatorLockStatePermanent   Permanent Lock.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorLockState)
{
    DASAuthenticatorLockStateUnlocked   = 0,
    DASAuthenticatorLockStateTemporary  = 1,
    DASAuthenticatorLockStatePermanent  = 2,
};

/*!
 @typedef DASAuthenticatorDataStore
 @brief Categorizes the type of data store in which the enrolled data was stored.
 @constant DASAuthenticatorDataStoreOS          The data store used is managed by the OS.
 @constant DASAuthenticatorDataStoreSoftware    N/A for iOS.
 @constant DASAuthenticatorDataStoreNone        No data is stored.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorDataStore)
{
    DASAuthenticatorDataStoreOS         = 0,
    DASAuthenticatorDataStoreSoftware   = 1,
    DASAuthenticatorDataStoreNone       = 2,
};

// Forward Declarations
@protocol DASAuthenticatorDelegate;

/*!
 @brief A protocol for classes that wish to implement Authenticator (Registration / Authentication) behaviour.
 */
@protocol DASAuthenticator <NSObject>

/*!
 @functiongroup Information
 */

/*!
 @brief A static internal id used only within the Daon Authenticator SDK.
 @return An NSString containing the authenticators ID.
 */
- (NSString*) getID;

/*!
 @brief A short name for the authenticator.
 @return An NSString containing the authenticators name.
 */
- (NSString*) getName;

/*!
 @brief A longer description of the authenticator.
 @return An NSString containing the authenticators description.
 */
- (NSString*) getDescription;

/*!
 @brief The version of the authenticator.
 @return An NSInteger containing the authenticators version.
 */
- (NSInteger) getVersionCode;

/*!
 @brief The version of the authenticator as a string.
 @return An NSString containing the authenticators version.
 */
- (NSString*) getVersionName;

/*!
 @brief The default icon for the authenticator.
 @return An UIImage containing the authenticators icon.
 */
- (UIImage*) getIcon;

/*!
 @brief The @link DASAuthenticatorFactor @/link type supported by the authenticator.
 @return The @link DASAuthenticatorFactor @/link type.
 */
- (DASAuthenticatorFactor) getFactorType;

/*!
 @brief The @link DASAuthenticatorProtection @/link type supported by the authenticator.
 @return The @link DASAuthenticatorProtection @/link type.
 */
- (DASAuthenticatorProtection) getMatcherProtection;

/*!
 @brief The current set of extensions for the authenticator, this includes all request extensions plus any response extensions that have been added.
 @return An NSDictionary mapping extension keys to values (Both NSString).
 */
- (NSDictionary*) getExtensions;

/*!
 @brief Updates the current set of extensions for the authenticator.
 @param extensions An NSDictionary mapping extension keys to values (Both NSString).
 */
- (void) setExtensions:(NSDictionary*)extensions;

/*!
 @brief The @link DASAuthenticatorDataStore @/link type supported by the authenticator.
 @return The @link DASAuthenticatorDataStore @/link type.
 */
- (DASAuthenticatorDataStore) getDataStoreType;

/*!
 @brief The @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator events.
 @return The @link DASAuthenticatorDelegate @/link derived object.
 */
- (id<DASAuthenticatorDelegate>) getClientDelegate;

/*!
 @brief Sets the @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator events.
 @param delegate The @link DASAuthenticatorDelegate @/link derived object.
 */
- (void) setClientDelegate:(id<DASAuthenticatorDelegate>)delegate;

/*!
 @brief The @link DASAuthenticatorSigningAlgorithm @/link type supported by the authenticator.
 @return The @link DASAuthenticatorSigningAlgorithm @/link type.
 */
- (DASAuthenticatorSigningAlgorithm) getSigningAlgorithm;

/*!
 @brief Sets the @link DASAuthenticatorSigningAlgorithm @/link type supported by the authenticator.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type.
 */
- (void) setSigningAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/*!
 @brief Whether or not the authenticator type has a user interface.
 @return YES if the authenticator type has a user interface.
 */
- (BOOL) hasUICollection;



/*!
 @functiongroup State
 */

/*!
 @brief Whether or not the authenticator is supported for the current device.
 @return YES if the authenticator type is supported.
 */
- (BOOL) isSupported;

/*!
 @brief Determines whether or not the authenticator has a given key registered.
 @param keyName The key to check.
 @return YES if key is registered.
 */
- (BOOL) isRegistered:(NSString*)keyName;

/*!
 @brief The @link DASAuthenticatorLockState @/link type currently set for the authenticator.
 @return The @link DASAuthenticatorLockState @/link type.
 */
- (DASAuthenticatorLockState) lockState;

/*!
 @brief The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970).
 @return Time in milliseconds or -1 if lockState is not @link DASAuthenticatorLockStateTemporary @/link.
 */
- (long long) lockEndTime;

/*!
 @brief Unlocks the authenticator.
 @discussion The random string is stored with the authenticators state. When a subsequent unlock request is made, the new string will be compared against the previous string. If they do not match, then the unlock will proceed.
 @param randomId A random string that will be stored with the unlock request.
 @return YES if the authenticator was unlocked
 */
- (BOOL) unlock:(NSString*)randomId;

/*!
 @brief Prepares the authenticator for re-enrollment.
 @discussion The random string is stored with the authenticators state. When a subsequent re-enroll request is made, the new string will be compared against the previous string. If they do not match, then the re-enroll can proceed.
 @param randomId A random string that will be stored with the reenroll request.
 @return YES if the authenticator can re-enroll
 */
- (BOOL) reenroll:(NSString*)randomId;

/*!
 @brief Determines whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
 @return YES if the authenticator has been invalidated
 */
- (BOOL) isInvalidated;

/*!
 @brief Update the authenticators state to show that it has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
 */
- (void) invalidate;



/*!
 @functiongroup Keys
 */

/*!
 @brief Retrieve the public key that is being stored for a particular key name.
 @param keyName The key to retrieve the public key for.
 @return An NSData object containing the public key.
 */
- (NSData*) getPublicKey:(NSString*)keyName;

/*!
 @brief Determine the public key format that is current is used.
 @discussion
 The supported format is based on the current @link DASAuthenticatorSigningAlgorithm @/link type:
 1) @link DASAuthenticatorSigningAlgorithmRSA @/link: "X.509"
 2) @link DASAuthenticatorSigningAlgorithmEC @/link: "X9.62"
 3) @link DASAuthenticatorSigningAlgorithmECWithAccessibility @/link: X9.62
 @return An NSString object containing the public key format.
 */
- (NSString*) getPublicKeyFormat;

/*!
 @brief Determine the public key type that is current is used.
 @discussion
 The supported type is based on the current @link DASAuthenticatorSigningAlgorithm @/link type:
 1) @link DASAuthenticatorSigningAlgorithmRSA @/link: "RSA"
 2) @link DASAuthenticatorSigningAlgorithmEC @/link: "EC"
 3) @link DASAuthenticatorSigningAlgorithmECWithAccessibility @/link: "EC"
 @return An NSString object containing the public key type.
 */
- (NSString*) getPublicKeyType;

/*!
 @brief The @link DASAuthenticatorProtection @/link type supported by the authenticator.
 @return The @link DASAuthenticatorProtection @/link type.
 */
- (DASAuthenticatorProtection) getKeyProtection;

/*!
 @brief The signing algorithm currently used by the authenticator.
 @discussion
 The current algorithm is based on the current @link DASAuthenticatorSigningAlgorithm @/link type:
 1) @link DASAuthenticatorSigningAlgorithmRSA @/link: "SHA256withRSA"
 2) @link DASAuthenticatorSigningAlgorithmEC @/link: "SHA256withECDSA"
 3) @link DASAuthenticatorSigningAlgorithmECWithAccessibility @/link: "SHA256withECDSA"
 @return An NSString object containing the current signing algorithm.
 */
- (NSString*) getAlgorithm;



/*!
 @functiongroup Actions
 */

/*!
 @brief Initiates the process to register an authenticator.
 @param keyName The name of the signing key that will be completed once registration completes.
 @param extensions An NSDictionary mapping extension keys to values (Both NSString) that will be used during the registration process.
 @param delegate The @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator registration events.
 */
- (void) register:(NSString*)keyName extensions:(NSDictionary*)extensions delegate:(id<DASAuthenticatorDelegate>)delegate;

/*!
 @brief Initiates the process to deregister an authenticator.
 @param keyName The name of the signing key that was previously registered and should be removed.
 @param removeAllData Whether or not to remove the local encrypted data once the signing key has been removed.
 @return YES if the authenticator was deregistered.
 */
- (BOOL) deregister:(NSString*)keyName removeAllData:(BOOL)removeAllData;

/*!
 @brief Initiates the process to authenticate an authenticator.
 @param keys An NSArray containing all key names that have previously been registered..
 @param extensions An NSDictionary mapping extension keys to values (Both NSString) that will be used during the authentication process.
 @param delegate The @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator authentication events.
 */
- (void) authenticate:(NSArray*)keys extensions:(NSDictionary*)extensions delegate:(id<DASAuthenticatorDelegate>)delegate;


@end

#endif /* DASAuthenticator_h */
