/*!
 @header IXUAFMessageReader
 Utility class for decoding FIDO messages.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>
#import "IXUAFTransaction.h"
#import "IXUAFVersion.h"

@interface IXUAFMessageReader : NSObject

/*!
 @brief Get Reader with message
 */
+ (IXUAFMessageReader*) readerWithMessage:(NSString*)message;

/*!
@brief Get Reader with message
@param validate If true, check if the message is a valid FIDO message.
*/
+ (IXUAFMessageReader*) readerWithMessage:(NSString*)message validate:(BOOL)validate;

/*!
 @brief Get Reader with dictionary
 */
+ (IXUAFMessageReader*) readerWithDictionary:(NSDictionary*)message;

/*!
 @brief Create Reader with message
 @param validate If true, check if the message is a valid FIDO message.
 */
- (id) initWithMessage:(NSString*)message validate:(BOOL)validate;

/*!
 @brief Create Reader with dictionary
 */
- (id) initWithDictionary:(NSDictionary*)message;

/*!
 @brief Returns true if the message requires transaction confirmation
 */
- (BOOL) requiresTransactionConfirmation;

/*!
 @brief Get transaction confirmation object
 */
- (IXUAFTransaction*) transaction;

/*!
 @brief true if this is a registration message
 */
- (BOOL) isRegistration;

/*!
 @brief true if this is an authentication message
 */
- (BOOL) isAuthentication;

/*!
 @brief true if this is a de-registration message
 */
- (BOOL) isDeregistration;

/*!
 @brief Get Application ID if available
 */
- (NSString*) application;

/*!
 @brief Get version
 */
- (IXUAFVersion*) version;

/*!
 @brief Get header extensions
 */
- (NSDictionary*) extensions;

/*!
 @brief Get final challenge, eg. fcparam
 */
- (NSDictionary<NSString*,id>*) fcParams;

- (NSArray<NSArray<NSString*>*> *) accepted;

/*!
 @brief Get assertion extensions. A dictionary mapping AAIDs to extensions.
 */
- (NSDictionary*) assertionExtensions;

/*!
 @brief Get OTP (if enabled on the policy)
 */
- (NSString*) otp;

/*!
 @brief Get assertions
 @discussion Parse registration and authentication assertions.
 Array of NSNumber -> NSData (see FIDO spec for tag ids)
 */
- (NSArray*) assertions;

/*!
 @brief Check trusted facets.
 @discussion This method will potentially make a network call.
 */
- (void) checkTrustedFacetsWithCompletion:(void (^)(BOOL trusted))completionHandler;

@end
