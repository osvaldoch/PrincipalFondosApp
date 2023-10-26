//
//  DASAuthenticatorInfo.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 5/2/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>

/*!
 @brief Provides readonly information about a specific authenticator.
 */
@interface DASAuthenticatorInfo : NSObject

/*!
 @brief The @link DASAuthenticatorFactor @/link type supported by the authenticator.
 */
@property (nonatomic, readonly) DASAuthenticatorFactor authenticatorFactor;

/*!
 @brief The name of the authenticator.
 */
@property (nonatomic, readonly) NSString *authenticatorName;

/*!
 @brief The more detailed description of the authenticator.
 */
@property (nonatomic, readonly) NSString *authenticatorDescription;

/*!
 @brief The authenticators icon.
 */
@property (nonatomic, readonly) UIImage *authenticatorIcon;

/*!
 @brief The current @link DASAuthenticatorLockState @/link type of the authenticator.
 */
@property (nonatomic, readonly) DASAuthenticatorLockState authenticatorLockState;

/*!
 @brief The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970). Defaults to -1 if authenticatorLockState is not DASAuthenticatorLockStateTemporary..
 */
@property (nonatomic, readonly) long long authenticatorLockedUntil;

/*!
 @brief The @link DASAuthenticatorSigningAlgorithm @/link type used to create / access the authenticators keys.
 */
@property (nonatomic, readonly) DASAuthenticatorSigningAlgorithm authenticatorSigningAlgorithm;

/*!
 @brief A static internal id used only within the Daon Authenticator SDK.
 */
@property (nonatomic, readonly) NSString *authenticatorId;

/*!
 @brief The version of the authenticator.
 */
@property (nonatomic, readonly) NSInteger authenticatorVersion;

/*!
 @brief An NSDictionary mapping extension keys to values (Both strings), that were passed into the authenticator.
 */
@property (nonatomic, readonly) NSDictionary *authenticatorExtensions;

/*!
 @brief Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
 */
@property (nonatomic, readonly) BOOL authenticatorInvalidated;

/*!
 @brief Instantiates a new @link DASAuthenticatorInfo @/link object with information about a specific authenticator.
 @param factor The @link DASAuthenticatorFactor @/link type supported by the authenticator.
 @param name The name of the authenticator.
 @param description The more detailed description of the authenticator.
 @param icon The authenticators icon.
 @param lockState The current @link DASAuthenticatorLockState @/link type of the authenticator.
 @param lockUntil The time at which the current lock will expire. In milliseconds since 00:00:00 Coordinated Universal Time (Thursday, 1 January 1970).
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used to create / access the authenticators keys.
 @param ident A static internal id used only within the Daon Authenticator SDK.
 @param version A version of the authenticator.
 @param exts An NSDictionary mapping extension keys to values (Both strings), that were passed into the authenticator.
 @param invalidated Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
 @result A new @link DASAuthenticatorInfo @/link object.
 */
- (id) initWithFactor:(DASAuthenticatorFactor)factor
                 name:(NSString*)name
          description:(NSString*)description
                 icon:(UIImage*)icon
            lockState:(DASAuthenticatorLockState)lockState
          lockedUntil:(long long)lockUntil
            algorithm:(DASAuthenticatorSigningAlgorithm)algorithm
                   id:(NSString*)ident
              version:(NSInteger)version
           extensions:(NSDictionary*)exts
          invalidated:(BOOL)invalidated;

@end
