/*!
 @header IXUAFOperation
 FIDO operation. The IXUAFOperation object is provided by the IXUAFDelegate methods.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

#import "IXUAFAuthenticator.h"
#import "IXUAFAccount.h"
#import "IXUAFVersion.h"


@protocol IXUAFOperation <NSObject>

/*!
 @brief Message type, e.g. "Reg", "Dereg", "Auth"
 */
- (NSString*) type;

/*!
 @brief Message version
 */
- (IXUAFVersion*) version;

/*!
 @brief Start verification with authenticator
 @param authenticator The authenticator or list of authenticators for AND
 */
- (void) verifyWithAuthenticator:(NSArray<IXUAFAuthenticator*> *) authenticator;

@optional
/*!
 @brief Sign message
 @param account The account.
 @discussion If more than one account is available, call this method when an account has been selected.
 */
- (void) signWithAccount:(IXUAFAccount*)account;

/*!
 @brief Notify the SDK with result
 @param result The result, either a fido message or error message.
 @param responseCode The response code.
 @discussion Call this method after getting a response back from the server, to make sure the SDK
 is in sync.
 */
- (void) notifyWithResult:(NSString*)result code:(NSInteger)responseCode;

@end


