//
//  DASAuthenticatorCollectorInfo.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/26/18.
//  Copyright © 2018 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief Provides information for a specific registration / authenticator collection event.
 @discussion When providing your own view controllers for display, this will allow you to specify the view controller and whether or not you will be displaying it yourself.
 */
@interface DASAuthenticatorCollectorInfo : NSObject

/*!
 @brief A reference to your custom view controller.
 */
@property (nonatomic) UIViewController *collectionViewController;

/*!
 @brief Whether or not you will be displaying the view controller yourself.
 @note NOTE
 If you claim responsibility for presenting the view controller, you must also dismiss it yourself.
 */
@property (nonatomic) BOOL clientIsResponsibleForPresentation;

/*!
 @brief Instantiates a new @link DASAuthenticatorCollectorInfo @/link object with information for a specific registration / authenticator event.
 @param viewController A reference to your custom view controller.
 @param clientWillPresent Whether or not you will be displaying the view controller yourself.
 @result A new @link DASAuthenticatorCollectorInfo @/link object.
 */
- (id) initWithViewController:(UIViewController*)viewController clientWillPresent:(BOOL)clientWillPresent;

@end
