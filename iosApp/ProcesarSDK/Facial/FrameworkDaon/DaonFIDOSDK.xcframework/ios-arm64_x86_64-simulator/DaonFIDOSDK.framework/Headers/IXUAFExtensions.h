//
//  IXUAFExtensions
//  DaonFIDOSDK
//
//  Created by Neil Johnston on 11/28/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IXUAFCaptureDataEncryptor.h"

// Name spaces
static NSString * const kAuthenticatorExtensionPrefix   = @"com.daon";

static NSString * const kSDKExtensionPrefix             = @"com.daon.sdk";
static NSString * const kSDKExtensionPrefix2            = @"com.daon.sdk.";
static NSString * const kSDKADOSExtensionPrefix         = @"com.daon.sdk.ados";
static NSString * const kResponseExtensionPrefix        = @"com.daon.sdk.response";
static NSString * const kStatusExtensionPrefix          = @"com.daon.status";

static NSString * const kPasscodeExtensionNamespace     = @"passcode";
static NSString * const kPatternExtensionNamespace      = @"pattern";
static NSString * const kFaceExtensionNamespace         = @"face";
static NSString * const kFingerprintExtensionNamespace  = @"finger";
static NSString * const kVoiceExtensionNamespace        = @"voice";
static NSString * const kSilentExtensionNamespace       = @"silent";
static NSString * const kHandprintExtensionNamespace    = @"hand";
static NSString * const kOTPExtensionNamespace          = @"otp";
static NSString * const kResponseExtensionNamespace     = @"response";


static NSString * const kAuthenticatorExtensionFormat   = @"^com\\.daon\\.%@\\..*";
static NSString * const kSDKExtensionFormat             = @"^com\\.daon\\.sdk\\..*";


// Extensions
static NSString * const kDeleteEnrollmentDataExtension  = @"com.daon.sdk.deleteEnrollmentData";
static NSString * const kExtensionHashExtension         = @"com.daon.sdk.extensionsHash";
static NSString * const kNoDaonExtensionsExtension      = @"com.daon.sdk.noDaonExts";
static NSString * const kHardwareKeystoreOnlyExtension  = @"com.daon.sdk.keystore.hardware.only";

static NSString * const kDeviceInfoExtension            = @"com.daon.sdk.deviceInfo";
static NSString * const kExtendedDeviceInfoExtension    = @"com.daon.sdk.deviceInfo.ext";
static NSString * const kLocationExtension              = @"com.daon.sdk.location";
static NSString * const kJailbreakDetectionExtension    = @"com.daon.sdk.healthCheck";
static NSString * const kEnvDetectionExtension          = @"com.daon.sdk.envCheck";
static NSString * const kMetadataExtension              = @"com.daon.sdk.authenticatorMetadata";
static NSString * const kLicenseExtension               = @"com.daon.sdk.license";
static NSString * const kSDKVersionExtension            = @"com.daon.sdk.version";
static NSString * const kSilentExtension                = @"com.daon.sdk.silent";
static NSString * const kCurrentEnrollmentOnly          = @"com.daon.sdk.enrollment.current.only";
static NSString * const kKeyAccessControlBiometry       = @"com.daon.sdk.keys.access.biometry";
static NSString * const kKeyMigrate                     = @"com.daon.sdk.keys.migrate";
static NSString * const kKeyMigrateDeregister           = @"com.daon.sdk.keys.migrate.deregister";
static NSString * const kFriendlyNameExtension          = @"com.daon.sdk.friendlyName";

static NSString * const kExpiryWarnings                 = @"expiryWarnings";
static NSString * const kOTP                            = @"otp";

// ADOS Request extensions
static NSString * const kADOSEnabled                    = @"com.daon.sdk.ados.enabled";
static NSString * const kADOSCertificateChainExtension  = @"com.daon.sdk.ados.decChain";
static NSString * const kADOSKeyID                      = @"com.daon.sdk.ados.dekId";

static NSString * const kADOSRootCertificate            = @"com.daon.sdk.ados.rootCert";
static NSString * const kADOSSubjectAlternativeName     = @"com.daon.sdk.ados.decId";

// ADOS Capture data
static NSString * const kADOSCaptureDataSchemeID        = @"capture.schemeId";
static NSString * const kADOSCaptureDataIV              = @"capture.iv";
static NSString * const kADOSCaptureData                = @"capture.data";
static NSString * const kADOSCaptureDataVerify          = @"capture.data.verify";
static NSString * const kADOSCaptureDataEncryptionKey   = @"capture.cdek";
static NSString * const kADOSStatusCode                 = @"authStatusCode";

// SRP
static NSString * const kSRPServerMessage               = @"M2";

// Extension encryption
static NSString * const kExtensionDataEncryptionKey     = @"com.daon.capture.edek";
static NSString * const kExtensionDataIV                = @"com.daon.capture.iv";
static NSString * const kExtensionDataScheme            = @"com.daon.capture.schemeId";

// OTP
static NSString * const kOTPEnabled                     = @"com.daon.sdk.otpEnabled";
static NSString * const kOTPEncryptionKey               = @"com.daon.sdk.otpEncryptionKey";         // RSA/ECB/PKCS1Padding
static NSString * const kOTPConfirmation                = @"com.daon.sdk.confirmationOTP";

// OTP Offline
static NSString * const kOOTPPolicy                     = @"com.daon.sdk.ootpPolicy";
static NSString * const kOOTPMode                       = @"com.daon.sdk.ootp.mode";
static NSString * const kOOTPUser                       = @"com.daon.sdk.ootp.user";

static NSString * const kOOTPKeyChain                   = @"com.daon.otp.ootpKeyChain";          // OTP Key cert chain
static NSString * const kOOTPAlgorithm                  = @"com.daon.otp.ootpAlgorithm";         // HMAC 256
static NSString * const kOOTPTimeStep                   = @"com.daon.otp.ootpTimeStep";          // In seconds, default 30
static NSString * const kOOTPLength                     = @"com.daon.otp.ootpLength";            // 6-8

// From authenticator
static NSString * const kOOTPTransactionData            = @"otp.data";
static NSString * const kOOTPToken                      = @"otp.token";
static NSString * const kOOTPTokenExpiration            = @"otp.ttl";
static NSString * const kOOTPDevicePublicKey            = @"otp.ecdhPubKey";
static NSString * const kOOTPDevicePublicKeyFormat      = @"otp.ecdhPubKeyFormat";

static NSString * const kDeviceBiometricRegistrationReason   = @"registration.reason";
static NSString * const kDeviceBiometricAuthenticationReason = @"authentication.reason";

// User attempts
static NSString * const kUserAttemptsRemaining          = @"com.daon.user.retriesRemaining";
static NSString * const kUserAttemptsMax                = @"com.daon.user.maxAttempts";

// Request attempts
static NSString * const kRequestMaxAttemptsExtension    = @"com.daon.authRequest.maxAttempts";
static NSString * const kRequestRetriesRemainingExtension = @"com.daon.authRequest.retriesRemaining";

// To authenticator
static NSString * const kDeviceBiometricSilentRegistration  = @"silent";
static NSString * const kDeviceBiometricReason              = @"embedded.ui.reason";
static NSString * const kDeviceBiometricRetry               = @"retry";

@class IXUAFAuthenticator;

@interface IXUAFExtensions : NSObject
{
@private
    NSMutableDictionary *requestExtensions;
    NSMutableDictionary *responseExtensions;
    NSMutableDictionary *assertionExtensions;    
}

- (id) initWithExtensions:(NSDictionary*)extensions;

- (void) initializeWithExtensions:(NSArray<NSDictionary*>*)extensions;

- (void) finalizeExtensionsWithApplication:(NSString*)appid username:(NSString*)username encryptor:(IXUAFCaptureDataEncryptor*)encryptor;
- (void) setAssertionExtensions:(NSDictionary*)extensions authenticator:(IXUAFAuthenticator*)authenticator;

- (NSArray<NSDictionary*>*) assertionExtensionsWithAaid:(NSString*)aaid;
- (NSArray<NSDictionary*>*) messageExtensions;

- (NSString*) valueForRequestExtension:(NSString*)extension;
- (NSString*) valueForRequestExtension:(NSString*)extension defaultValue:(NSString*)defaultValue;
- (NSString*) assertionExtension:(NSString*)extension aaid:(NSString*)aaid;

- (NSDictionary*) extensionsWithAaid:(NSString*)aaid;

- (NSData*) digestMessageWithAaid:(NSString*)aaid;

- (NSDictionary*) expiryWarnings;

- (void) processExtensionsWithKeys;

- (NSDictionary<NSNumber*, NSDictionary*>*) extensionsForGroup:(NSArray<IXUAFAuthenticator*>*)authenticators;

- (NSInteger) statusCodeWithExtensions:(NSDictionary*)extensions;

@end

