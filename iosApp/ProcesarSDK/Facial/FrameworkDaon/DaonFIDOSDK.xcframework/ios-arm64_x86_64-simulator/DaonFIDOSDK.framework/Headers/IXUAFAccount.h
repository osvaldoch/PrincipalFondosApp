/*!
 @header IXUAFAccount
 FIDO Account object
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

@interface IXUAFAccount : NSObject

@property (nonatomic, strong) NSString * userName;

- (id)initWithName:(NSString *)userName;


@end
