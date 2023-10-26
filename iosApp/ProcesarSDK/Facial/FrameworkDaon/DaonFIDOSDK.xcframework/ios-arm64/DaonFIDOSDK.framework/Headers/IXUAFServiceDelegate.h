/*!
 @header IXUAFServiceDelegate
 SDK delegate for for handling FIDO related communication with a Relying Party.
 @copyright Daon. All rights reserved.
 @updated 2019-01-20
 */

#ifndef IXUAFServiceDelegate_h
#define IXUAFServiceDelegate_h

#import <Foundation/Foundation.h>

@protocol IXUAFServiceDelegate <NSObject>

/*!
 @brief Get a FIDO registration message, e.g. from a server.
 @discussion The registration call, registerWithCompletionHandler, will call this method when a registration message is needed.
 @param params The request parameters, username, etc.
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestRegistrationWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                          handler:(nonnull void (^)(NSString* _Nullable message, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestRegistration(parameters:handler:));

/*!
 @brief Send FIDO registration message to the server.
 @discussion The registration call, registerWithCompletionHandler, will call this method when the user has registered an authenticator and a registration message has been created.
 @param uafMessage The FIDO registration message
 @param params Request parameters, e.g username, request, etc. in case of a step-up authentication, etc.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceRegisterWithMessage:(NSString* _Nonnull)uafMessage
                         parameters:(NSDictionary<NSString*, id>* _Nullable)params
                            handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRegister(message:parameters:handler:));

/*!
 @brief Get a FIDO authentication message, e.g. from a server.
 @discussion The authentication API will call this method when an authentication message is needed.
 @param params The request parameters, e.g. username.
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestAuthenticationWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                            handler:(nonnull void (^)(NSString* _Nullable message, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestAuthentication(parameters:handler:));

/*!
 @brief Send FIDO authentication message to the server.
 @discussion The authentication API will call this method when the user has authenticated and an authentication message has been created.
 @param uafMessage The FIDO authentication message
 @param params Request parameters, e.g username, request, etc. in case of a step-up authentication, etc.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceAuthenticateWithMessage:(NSString* _Nonnull)uafMessage
                             parameters:(NSDictionary<NSString*, id>* _Nullable)params
                                handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceAuthenticate(message:parameters:handler:));

/*!
 @brief Send FIDO message to the server.
 @discussion The API will call this method to submit ADOS data to the server.
 @param uafMessage The FIDO registration/authentication message
 @param username The optional user name. May be provided in case of a step-up authentication.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceUpdateWithMessage:(NSString* _Nonnull)uafMessage
                         username:(NSString*_Nullable)username
                          handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceUpdate(message:username:handler:));

/*!
 @brief Get a FIDO de-registration message, e.g. from a server.
 @discussion The de-registration calls will call this method when a de-registration message is needed.
 @param aaid The AAID to deregister.
 @param params Request parameters, e.g username, FIDO application id, etc.
 @param handler The handler should return the FIDO message and/or any errors.
 */
- (void) serviceRequestDeregistrationWithAaid:(NSString* _Nonnull)aaid
                                   parameters:(NSDictionary<NSString*, id>* _Nullable)params
                                      handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestDeregistration(aaid:parameters:handler:));

/*!
 @brief Get the FIDO registration policy, e.g. from a server.
 @discussion The checkRegistrations call will call this method when needed.
 @param params Request parameters, e.g username, FIDO application id, etc.
 @param handler The handler should return the FIDO policy and/or any errors.
 */
- (void) serviceRequestRegistrationPolicyWithParameters:(NSDictionary<NSString*, NSString*>* _Nullable)params
                                                handler:(nonnull void (^)(NSString* _Nullable policy, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestRegistrationPolicy(parameters:handler:)) __deprecated;

/*!
 @brief Send authentication attempt data to the server.
 @discussion The API will call this method after a failed attempt. This is not called for an ADOS authenticator, since the server already have the necessary information.
 @param info The attempt information provided by the SDK.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceUpdateWithAttempt:(NSDictionary<NSString*, id>* _Nonnull)info
                          handler:(nonnull void (^)(NSString* _Nullable response, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceUpdate(attempt:handler:));


@optional

- (void) serviceInitializeWithParameters:(NSDictionary<NSString*, NSString*>* _Nullable)params
                                 handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceInitialize(parameters:handler:));

/*!
 @brief Initiate access to the service.
 @discussion Invoked when calling IXUAF API requestServiceAccess. When using the default RPSA communication, this delegate will create the account or log in the user if a password is used.
 @param params Request parameters.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceRequestAccessWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                    handler:(nonnull void (^)(NSString* _Nullable message, NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRequestAccess(parameters:handler:));

/*!
 @brief Revoke access to the service.
 @discussion Invoked when calling IXUAF API revokeServiceAccess.
 @param params Request parameters.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceRevokeAccessWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                   handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceRevokeAccess(parameters:handler:));

/*!
 @brief Delete the user/account.
 @discussion Invoked when calling IXUAF API delete(user)
 @param params Request parameters.
 @param handler The handler should return the FIDO response message and/or any errors.
 */
- (void) serviceDeleteUserWithParameters:(NSDictionary<NSString*, id>* _Nullable)params
                                   handler:(nonnull void (^)(NSError* _Nullable error))handler NS_SWIFT_NAME(serviceDeleteUser(parameters:handler:));

@end


#endif /* IXUAFServiceDelegate_h */
