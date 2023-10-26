
#import <UIKit/UIKit.h>
#import "DMDSRecognitionMode.h"
@class DMDSMrzDetectionMetadata;
@class DMDSDocumentDetectionMetadata;
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
@protocol DMDSCustomScanDelegate <NSObject>

@optional

/*!
 @abstract Called when the scanning session detects an MRZ within a document.
 This occurs during the scanning session (prior to the scanning session producing the final results and calling the documentScannedWithResult: delegate method).
 
 @param mrzDetected      Detection metadata object (@link DMDSMrzDetectionMetadata.h DMDSMrzDetectionMetadata @/link) containing the location of the MRZ that was detected within the scanning region.
 */
- (void)mrzDetected:(DMDSMrzDetectionMetadata *)mrzDetected;

/*!
 @abstract Called when the scanning session detects a document's edges.
 This occurs during the scanning session (prior to the scanning session producing the final results and calling the documentScannedWithResult: delegate method).

 @param documentDetected     Detection metadata object (@link DMDSDocumentDetectionMetadata.h DMDSDocumentDetectionMetadata @/link) containing the location of document that was detected within the scanning region.
 */
- (void)documentDetected:(DMDSDocumentDetectionMetadata *)documentDetected;

/*!
 @abstract Called when the scanning session times out.
 This is based on the duration set within DMDSOptions.scanningDuration, as well as DMDSOptions.fallbackToEdgeDetectionDuration
 if DMDSOptions.fallbackToEdgeDetection is enabled.
 
 It is up to the calling application to decide what action should be performed next. For example, the the calling app could dismiss or
 pause the scanning view controller or contiue to capture another document.

 @param error      Error containing the reason why scanning process failed. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 */
- (void)detectionTimeoutWithError:(NSError *)error;

/**
 @abstract Called when the scanning session completes successfully.

 @param scanningResult   The @link DMDSResult.h DMDSResult @/link object containing the final results for the successful scanning session.
 */
- (void)documentScannedWithResult:(DMDSResult *)scanningResult;

/**
 @abstract Called when an error occurs during the scanning session

 @param error  Error containing detailed information. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 @param result Partial result that holds obtained results until error occured
 */
- (void)documentScanFailedWithError:(NSError *)error
                             result:(DMDSResult* _Nullable) result;

/**
 @abstract Called when an error occurs during the scanning session

 @param error  Error containing detailed information. The error code will map to DMDSErrorCode. See @link DMDSError.h DMDSError @/link for further information.
 
 Use the other documentScanFailedWithError method as this method is obsolete and not called anymore.
 */
- (void)documentScanFailedWithError:(NSError *)error __deprecated;



/**
 @abstract If DMDSOptions.fallbackToEdgeDetection is enabled, this will be called when document recognition gives up, and the
 framework switches over to edge detection. This will be after the amount of seconds specified by DMDSOptions.fallbackToEdgeDetectionDuration.
 */
- (void)fallingBackToEdgeDetection;

/**
 @abstract Called when glare has been detected.
 
 @param glare   True if glare has been detected, false is no glare detected. Callback is called only on changes in glare detection state.
 */
- (void)didDetectGlareWithResult:(BOOL)glare;

/**
 @abstract Called when scanning of the first side has finished.
 
 */
- (void)firstSideRecognitionFinished:(DMDSRecognitionMode)recognitionMode;

@end

NS_ASSUME_NONNULL_END
