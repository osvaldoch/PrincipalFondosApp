/*!
 @header IXUAFDiscoveryData
 FIDO authenticator discovery data
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>
#import "IXUAFVersion.h"
#import "IXUAFAuthenticator.h"

@interface IXUAFDiscoveryData : NSObject

@property (nonatomic, strong) NSArray<IXUAFVersion *> *supportedUafVersions;
@property (nonatomic, strong) NSString *clientVendor;
@property (nonatomic, strong) IXUAFVersion *clientVersion;
@property (nonatomic, strong) NSArray<IXUAFAuthenticator*> *availableAuthenticators;

- (id)initWithSupportedUafVersions:(NSArray<IXUAFVersion *> *)supportedUafVersions
                      clientVendor:(NSString *)clientVendor
                    clientVersions:(IXUAFVersion *)clientVersion
                    authenticators:(NSArray<IXUAFAuthenticator*> *)availableAuthenticators;
@end
