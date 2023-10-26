//
//  DASMultiAuthenticator.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 4/28/17.
//  Copyright © 2017 Daon. All rights reserved.
//

#ifndef DASMultiAuthenticator_h
#define DASMultiAuthenticator_h

/*!
 @typedef DASAuthenticatorPolicyType
 @brief Categorizes the different types of policy supported by the DASMultiAuthenticator protocol.
 @constant DASAuthenticatorPolicyTypeAND            Sequential display of a set of authenticators. All must be used.
 @constant DASAuthenticatorPolicyTypeOR             Choose one authenticator from a set of authenticators.
 @constant DASAuthenticatorPolicyTypeMultipleChoice Paged UI mode.
 */
typedef NS_ENUM (NSInteger, DASAuthenticatorPolicyType)
{
    DASAuthenticatorPolicyTypeAND               = 0,
    DASAuthenticatorPolicyTypeOR                = 1,
    DASAuthenticatorPolicyTypeMultipleChoice    = 2,
};

/*!
 @brief A protocol for classes that wish to provide Multi-Authenticator functionality.
 @discussion The Multi-Authenticator provides the ability to register or authenticate with multiple authenticators, either with a fixed set
 or by providing a choice to the user.
 */
@protocol DASMultiAuthenticator <NSObject>

/*!
 @brief The current factor @link DASAuthenticatorFactor @/link being collected.
 */
@property (nonatomic, readonly) DASAuthenticatorFactor activeFactor;

/*!
 @brief Begins data collection
 @param factorsAndKeys An NSArray of authenticator groups, each group made up of an NSDictionary that maps @link DASAuthenticatorFactor @/link types (in a NSNumber object) to an NSArray of keys (NSString objects).
 @param factorsAndExtensions An NSDictionary that maps @link DASAuthenticatorFactor @/link types (in a NSNumber object) to an NSDictionary mapping extension name to extension value (Both NSString).
 @param registerChosenKeys Whether or not to present the collection UI in registration or authentication mode.
 @param delegate Object implementing the @link DASAuthenticatorDelegate @/link protocol to receive completion / failure messages.
 */
- (void) collectDataForFactorsAndKeys:(NSArray<NSDictionary*>*)factorsAndKeys
                 factorsAndExtensions:(NSDictionary<NSNumber*, NSDictionary*>*)factorsAndExtensions
                   registerChosenKeys:(BOOL)registerChosenKeys
                             delegate:(id<DASAuthenticatorDelegate>)delegate;

@end

#endif /* DASMultiAuthenticator_h */
