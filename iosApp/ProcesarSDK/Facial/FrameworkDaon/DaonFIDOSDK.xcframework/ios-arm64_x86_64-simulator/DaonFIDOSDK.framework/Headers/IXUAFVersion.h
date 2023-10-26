/*!
 @header IXUAFVersion
 FIDO UAF version object
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

@interface IXUAFVersion : NSObject

@property (nonatomic, assign) NSInteger major;
@property (nonatomic, assign) NSInteger minor;


- (id)initWithMajor:(NSInteger)major minor:(NSInteger)minor;

- (NSString*) stringValue;

- (NSDictionary*) dictionary;
@end
