//
//  IXAFactor.h
//
//  Created by Jonny Mortensen on 2/18/15.
//  Copyright (c) 2015-21 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DaonCryptoSDK/IXASecureKeys.h>

typedef NS_OPTIONS (NSUInteger, IXAAuthenticationOption) {
    AuthenticationOptionDefault                         = 0,
    AuthenticationOptionDoNotCreateKeys                 = 2,
    AuthenticationOptionJailbreakDetection              = 4,
    AuthenticationOptionTouchIDCurrentSet               = 8,     // Invalidate keys if enrollment changes
    AuthenticationOptionBiometricsCurrentSet            = 8,
    AuthenticationOptionAlgorithmECDSA                  = 16,
    AuthenticationOptionBackgroundApplication           = 32
};

// TODO Fix error code mapping

#define kIXAErrorMissingPrivateKey               114    // DASAuthenticatorErrorFailedToSign
#define kIXAErrorMissingChallenge                114
#define kIXAErrorMissingKeys                     114
#define kIXAErrorDeviceCompromised              0xAA    // IXUAFErrorCodeDeviceCompromised
#define kIXAErrorDeviceBiometricsInvalidated     122    // DASAuthenticatorErrorLocalAuthenticationEnrollmentHasChanged
#define kIXAErrorDeviceBiometricsTokenMismatch   106    // DASAuthenticatorErrorAuthenticatorAuthTokenMismatch
#define kIXAErrorDeviceBiometricsRetryLimit     1000    // DASAuthenticatorErrorLocalAuthRetryLimitExceeeded
#define kIXAErrorDeviceBiometricsLockedOut      1001    // DASAuthenticatorErrorLocalAuthBiometryLockedOut
#define kIXAErrorDeviceBiometricsCancelled      1005    // DASAuthenticatorErrorLocalAuthCancelled
#define kIXAErrorDeviceBiometricsFailedToVerify  800    // DASAuthenticatorErrorFingerprintFailedToVerify

static NSString * const IXAFactorParameterReason    = @"reason";
static NSString * const IXAFactorParameterToken     = @"token";
static NSString * const IXAFactorParameterTimeout   = @"timeout";
static NSString * const IXAFactorParameterSilent    = @"silent";

/*!
 * @header IXAFactor
 */


@interface IXAFactor : NSObject 
{
    IXASecureKeys  *_sk;
}

+ (IXAFactor*) factorWithKeyname:(NSString*)name __deprecated;
+ (IXAFactor*) factorWithKeyname:(NSString*)name options:(NSUInteger)options __deprecated;
+ (BOOL) hasKeyWithName:(NSString*)name __deprecated;
- (BOOL) removeKeys __deprecated;

+ (IXAFactor*) factorWithKey:(NSString*)key;
+ (IXAFactor*) factorWithKey:(NSString*)key options:(NSUInteger)options;

+ (BOOL) isSupported;
+ (BOOL) hasKey:(NSString*)key;

- (id) initWithKey:(NSString*)key options:(NSUInteger)options;

- (NSString*) key;

- (BOOL) isNew;
- (BOOL) remove;
- (BOOL) rename:(NSString*)newname;

/*!
 * @abstract Get the encoded public key
 * @returns encoded public key as an NSData object.
 */
- (NSData*) encodedPublicKey;
- (NSData*) publicKey;

- (SecKeyRef) publicKeyRef;
- (SecKeyRef) privateKeyRef;

- (void) authenticateWithChallenge:(NSData*)challenge
                        parameters:(NSDictionary*)params
                           handler:(void (^)(NSData* signature, NSError *error))handler;

- (NSData*) authenticateWithChallenge:(NSData*)challenge
                           parameters:(NSDictionary*)params
                                error:(NSError **)error;
    
- (NSUInteger) options;

- (BOOL) createKeys;
- (BOOL) convert;

- (BOOL) hasAccessControl;
- (BOOL) isStoredInSecureEnclave;
- (BOOL) isSecureEnclaveSupported;
- (BOOL) hasEnrollmentChanged;

- (NSData*) encryptData:(NSData*)content;
- (NSData*) decryptData:(NSData*)content;

- (BOOL) updateKeyAttributes:(CFDictionaryRef)attributes;

@end
