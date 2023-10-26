//
//  DASCaptureDataEncryptor.h
//  DaonAuthenticatorSDK
//
//  Created by Jonny Mortensen on 3/2/17.
//  Copyright © 2017-18 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString * const IXUAF_SESSION_ENCRYPTION_DATA = @"data";
static NSString * const IXUAF_SESSION_ENCRYPTION_IV   = @"iv";
static NSString * const IXUAF_SESSION_ENCRYPTION_KEY  = @"key";

@interface IXUAFCaptureDataEncryptor : NSObject
{
    NSUInteger  _sequence;
    NSData *    _IV;
    NSData *    _sessionKey;
    SecKeyRef   _encryptionKey;
    
    NSString *  _certificate;
    NSString *  _root;
    NSString *  _san;
}

- (id) initWithCertificate:(NSString*)certificate root:(NSString*)root san:(NSString*)san;
- (id) initWithEncryptionKey:(SecKeyRef)encryptionKey;

- (void) free;

- (NSDictionary*) encryptCaptureData:(NSArray<NSData*>*)data;

- (NSString*) encryptString:(NSString*)value;
- (NSString*) decryptString:(NSString*)base64;

- (NSString*) base64EncodedIV;
- (NSString*) base64EncodedWrappedSessionKey;
@end
