/*!
 @header IXUAFMessageWriter
 Utility class for creating FIDO messages. This can be used for Offline message creation or On-Shot authentication.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

static NSString * const kNoApplicationID  = @"";

@interface IXUAFMessageWriter : NSObject

/*!
 @brief Create a FIDO registration OR request
 @param aaids An array of aaid's.
 @param appid The application id. If null the facet id is used.
 @param username The username
 */
+ (NSString*) registrationRequestWithOrPolicy:(NSArray*)aaids application:(NSString*)appid username:(NSString*)username;

/*!
 @brief Create a FIDO registration AND request
 @param aaids An array of aaid's.
 @param appid The application id. If null the facet id is used.
 @param username The username
 */
+ (NSString*) registrationRequestWithAndPolicy:(NSArray*)aaids application:(NSString*)appid username:(NSString*)username;

/*!
 @brief Create a FIDO registration with an Open Policy
 @param appid The application id. If null the facet id is used.
 @param username The username
 */
+ (NSString*) registrationRequestWithApplication:(NSString*)appid username:(NSString*)username;

/*!
 @brief Create a FIDO authentication OR request
 @param aaids An array of aaid's.
 @param appid The application id. If null the facet id is used.
*/
+ (NSString*) authenticationRequestWithOrPolicy:(NSArray*)aaids application:(NSString*)appid;

/*!
 @brief Create a FIDO authentication AND request
 @param aaids An array of aaid's.
 @param appid The application id. If null the facet id is used.
 */
+ (NSString*) authenticationRequestWithAndPolicy:(NSArray*)aaids application:(NSString*)appid;

/*!
 @brief Create a FIDO authentication request with policy
 @discussion Create a FIDO authentication with a FIDO accepted policy object, e.g
 [[{"aaid":["53EC#C002"]}],[{"aaid":["D409#0301"]}],[{"aaid":["53EC#C002"]},{"aaid":["D409#0601"]}]]
 @param policy The accepted array.
 @param appid The application id. If null the facet id is used.
 */
+ (NSString*) authenticationRequestWithPolicy:(NSArray*)policy application:(NSString*)appid;

/*!
 @brief Create a FIDO authentication request with an Open Policy
 @param appid The application id. If null the facet id is used.
 */
+ (NSString*) authenticationRequestWithApplication:(NSString*)appid;

/*!
 @brief Update an existing FIDO request
 @param request The fido request message
 @param username The username.
 */
+ (NSString*) updateRequest:(NSString*)request username:(NSString*)username;

/*!
 @brief Update an existing FIDO request
 @param request The fido request message
 @param accepted The accepted policy.
 @param username The username.
 */
+ (NSString*) updateRequest:(NSString*)request accepted:(NSArray*)accepted username:(NSString*)username;

/*!
 @brief Update an existing FIDO request
 @param request The fido request message
 @param extensions The extensions
 */
+ (NSString*) updateRequest:(NSString*)request extensions:(NSDictionary*)extensions;

/*!
 @brief Create a FIDO deregistration request
 @param aaid The aaid.
 @param appid The application id. If null the facet id is used.
 */
+ (NSString*) deregistrationRequestWithAaid:(NSString*)aaid application:(NSString*)appid;

/*!
 @brief Create a FIDO deregistration request
 @param aaid The aaid.
 @param username The username.
 @param appid The application id. If null the facet id is used.
 */
+ (NSString*) deregistrationRequestWithAaid:(NSString*)aaid username:(NSString*)username application:(NSString*)appid;

@end
