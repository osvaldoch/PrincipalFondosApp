//
//  DASMetadataControllerProtocol.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 2/13/19.
//  Copyright © 2019 Daon. All rights reserved.
//

#ifndef DASMetadataControllerProtocol_h
#define DASMetadataControllerProtocol_h

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>

/*!
 @brief A protocol for classes that wish to provide metadata scanning functionality.
 */
@protocol DASMetadataControllerProtocol <DASControllerProtocol>

/*!
 @brief Instructs the controller to configure the camera and begin scanning for the specific AVMetadataObjectType types.
 @discussion As soon as a relevant object is detected, it will be returned via the delegate (@link DASMetadataControllerDelegate @/link)
 @link metadataControllerCompletedWithImage:contents: @/link method.
 */
- (void) start;

@end

#endif /* DASMetadataControllerProtocol_h */
