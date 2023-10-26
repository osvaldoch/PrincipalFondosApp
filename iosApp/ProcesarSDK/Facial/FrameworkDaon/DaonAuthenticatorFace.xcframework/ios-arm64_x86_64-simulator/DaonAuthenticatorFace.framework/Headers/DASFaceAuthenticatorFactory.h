//
//  DASFaceAuthenticatorFactory.h
//  DaonAuthenticatorFace
//
//  Created by Neil Johnston on 2/6/18.
//  Copyright © 2018 Daon. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

// Forward Declarations
@protocol DASADoSControllerProtocol;
@protocol DASAuthenticatorContext;
@protocol DASFaceControllerDelegate;
@protocol DASFaceControllerProtocol;
@protocol DASFaceControllerProtocol;
@protocol DASFaceMatcherProtocol;
@protocol DASFaceTemplateControllerProtocol;
@class DaonFaceSDK;

/*!
 @brief Provides a number of class factory methods for creating Face related controllers.
 */
@interface DASFaceAuthenticatorFactory : NSObject

// MARK:- Controllers - Legacy

/*!
 @brief Instantiates a new @link DASFaceControllerProtocol @/link derived object responsible for providing access to face registration and authentication functionality.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param previewView The UIView upon which the video preview will be drawn.
 @param delegate The @link DASFaceControllerDelegate @/link derived object that will be notified of face collection events.
 @return A new object conforming to the @link DASFaceControllerProtocol @/link protocol.
 */
+ (id<DASFaceControllerProtocol>) createFaceControllerWithContext:(id<DASAuthenticatorContext>)context
                                                          preview:(UIView*)previewView
                                                         delegate:(id<DASFaceControllerDelegate>)delegate
                                                           NS_SWIFT_NAME(createFaceController(context:preview:delegate:));

/*!
 @brief Instantiates a new @link DASADoSControllerProtocol @/link derived object responsible for delivering ADoS face data to a server.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @return A new object conforming to the @link DASADoSControllerProtocol @/link protocol.
 */
+ (id<DASADoSControllerProtocol>) createADoSControllerWithContext:(id<DASAuthenticatorContext>)context;



// MARK:- Template controllers

/*!
@brief Instantiates a new @link DASFaceTemplateControllerProtocol @/link derived object responsible for providing access to face template authentication functionality.
@param context The @link DASAuthenticatorContext @/link object with which a custom view controller or capture controller can authenticate.
@return A new object conforming to the @link DASFaceTemplateControllerProtocol @/link protocol.
*/
+ (id<DASFaceTemplateControllerProtocol>) createFaceTemplateControllerWithContext:(id<DASAuthenticatorContext>)context;


// MARK:- Matchers

/*!
 @brief Instantiates a new @link DASFaceMatcherProtocol @/link derived object responsible for enrolling or authenticating a face template.
 @param context The @link DASAuthenticatorContext @/link object with which the face matcher can configure its parameters.
 @return A new object conforming to the @link DASFaceMatcherProtocol @/link protocol.
 */
+ (id<DASFaceMatcherProtocol>) createFaceMatcherWithContext:(id<DASAuthenticatorContext>)context;
   
@end
