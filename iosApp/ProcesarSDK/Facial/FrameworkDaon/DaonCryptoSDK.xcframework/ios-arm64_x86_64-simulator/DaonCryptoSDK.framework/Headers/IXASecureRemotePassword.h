//
//  IXASecureRemotePassword
//
//  Created by Jonny Mortensen on 1/18/18.
//  Copyright 2018 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>



@interface IXASecureRemotePassword : NSObject

- (instancetype)initWithN:(NSString*)N g:(NSString*)g I:(NSString*)user s:(NSData*)salt H:(NSString*)hashAlgorithm;

- (instancetype) initWithExtensionsN:(NSString*)N g:(NSString*)g I:(NSString*)user s:(NSString*)salt H:(NSString*)hashAlgorithm;

- (NSData*) generateVerifierWithPassword:(NSString*)password;
- (NSDictionary*) generateEvidenceWithPassword:(NSString*)password serverPublicValue:(NSString*)base64EncodedB;
- (BOOL)isValidEvidenceMessage:(NSString*)base64EncodedM2;

@end
