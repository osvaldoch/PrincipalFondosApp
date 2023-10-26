

#import <UIKit/UIKit.h>

@class DMDSResult;

NS_ASSUME_NONNULL_BEGIN

/*!
 @unsorted
 @abstract This protocol provides meaningful and detailed notifications for the user to interact with when a custom camera overlay is used for scanning.

 A view controller that conforms to this protocol is responsible for specifying the UI elements and handling their actions.
 Once the capture manager (DMDSCaptureManager) has been initialised with a view controller that conforms to this protocol, you should then provide
 the view controller with access to the capture manager, so that it can be used to control the UI at various stages.
 This can be achieved by simply declaring a property of type DMDSCaptureManager within your view controller, and setting this once the capture manager is successfully initialised.
 */
@protocol DMDSDirectScanDelegate <NSObject>

/**
 @abstract Called when the scanning session completes successfully.

 @param scanningResult   The @link DMDSResult.h DMDSResult @/link object containing the final results for the successful scanning session.
 */
- (void)documentScannedWithResult:(DMDSResult *)scanningResult;

/**
 @abstract Called when an error occurs during the scanning session

 @param error      Error containing detailed information. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 */
- (void)documentScanFailedWithError:(NSError *)error;



NS_ASSUME_NONNULL_END

@end
