//
//  DIDCScanDelegate.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 09/07/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DIDCResult;
@class DIDCDetection;

NS_ASSUME_NONNULL_BEGIN

/*!
 @unsorted
 @abstract This protocol provides meaningful and detailed notifications for the user to interact with when a custom camera overlay is used for scanning.

 A view controller that conforms to this protocol is responsible for specifying the UI elements and handling their actions.
 Once the capture manager (DMDSCaptureManager) has been initialised with a view controller that conforms to this protocol, you should then provide
 the view controller with access to the capture manager, so that it can be used to control the UI at various stages.
 This can be achieved by simply declaring a property of type DMDSCaptureManager within your view controller, and setting this once the capture manager is successfully initialised.
 */
@protocol DIDCScanDelegate <NSObject>

/**
 @abstract Called when the scanning session completes successfully.

 @param scanningResult   The @link DMDSResult.h DMDSResult @/link object containing the final results for the successful scanning session.
 */
- (void)documentScannedWithResult:(DIDCResult *)scanningResult;

/*!
 @abstract Called when the scanning session detects a document's edges.
 This occurs during the scanning session (prior to the scanning session producing the final results and calling the documentScannedWithResult: delegate method).

 @param documentDetected     Detection metadata object (@link DMDDetection.h DMDSDetection @/link) containing the location of document that was detected within the scanning region.
 */

@optional
- (void)documentDetected:(DIDCDetection *)documentDetected;



/**
 @abstract Called when an error occurs during the scanning session

 @param error      Error containing detailed information. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 */
@optional
- (void)documentScanFailedWithError:(NSError *)error;


/**
 @abstract Called when an error occurs during the scanning session

 @param error      Error containing detailed information. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 */
@optional
- (void)documentScanInfo:(NSDictionary *)info;




NS_ASSUME_NONNULL_END

@end
