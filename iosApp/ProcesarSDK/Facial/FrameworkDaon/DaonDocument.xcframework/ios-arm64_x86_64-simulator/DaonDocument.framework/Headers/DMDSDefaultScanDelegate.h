
#import <Foundation/Foundation.h>

@class DMDSResult;

@protocol DMDSDefaultScanDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Protocol for obtaining scanning results when using the Default UI.
 */
@protocol DMDSDefaultScanDelegate <NSObject>

/*!
 @abstract The document scanning session found a document.
 
 Called when a document has been successfully detected and scanned.

 Delegates the processing of the successful scanning result to the calling application. It is up to the
 calling app to decide what action should be performed next. E.g. the the calling app could dismiss or
 pause the scanningViewController or contiue to capture another document.
 
 This method is the default way for getting access to results of scanning.
 
 @param cameraViewController Scanning view controller (@link DMDSCameraController.h DMDSCameraController@/link) responsible for document scanning.
 @param scanningResult       The @link DMDSResult.h DMDSResult @/link object which contains information about the document which was recognised and scanned.
 */
- (void)documentScanned:(UIViewController*)cameraViewController result:(DMDSResult*)scanningResult;

/*!
 @abstract Called when the scanning session times out.
 This is based on the duration set within DMDSOptions.scanningDuration, as well as DMDSOptions.fallbackToEdgeDetectionDuration
 if DMDSOptions.fallbackToEdgeDetection is enabled.

 It is up to the calling application to decide what action should be performed next. For example, the the calling app could dismiss or
 pause the scanning view controller or contiue to capture another document.

 @param cameraViewController Scanning view controller (@link DMDSCameraController.h DMDSCameraController@/link) responsible for scanning.
 @param error                Error containing reason why the scanning process failed. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 @param scanningResult       The @link DMDSResult.h DMDSResult @/link object containing the final results for the successful scanning session.
 */
- (void)documentScanFailed:(UIViewController*)cameraViewController error:(NSError *)error result:(DMDSResult*)scanningResult;

@end

NS_ASSUME_NONNULL_END
