//
//  DASFaceTemplateControllerProtocol.h
//  DaonAuthenticatorFace
//
//  Created by Neil Johnston on 5/15/20.
//  Copyright © 2020 Daon. All rights reserved.
//

#ifndef DASFaceTemplateControllerProtocol_h
#define DASFaceTemplateControllerProtocol_h

// Blocks
typedef void (^FaceTemplateAuthenticationHandler) (bool passed, NSNumber *score, NSError *error);

#import <DaonAuthenticatorSDK/DASAuthenticatorContext.h>

@protocol DASFaceTemplateControllerProtocol <DASControllerProtocol>

/**
 * @brief Authenticate a template against the enrolled image.
 * @param templateData template to be authenticated
 */
- (void) authenticateTemplate:(NSData*)templateData resultHandler:(FaceTemplateAuthenticationHandler)handler;

@end

#endif /* DASFaceTemplateController_h */
