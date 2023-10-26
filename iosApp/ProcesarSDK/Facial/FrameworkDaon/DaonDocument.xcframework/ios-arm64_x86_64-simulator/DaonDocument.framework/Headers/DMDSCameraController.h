
#import <UIKit/UIKit.h>

@class DMDSOptions;
@protocol DMDSCustomScanDelegate;
@protocol DMDSDefaultScanDelegate;
@protocol DMDSDirectScanDelegate;
@protocol MBDetectionRecognizerRunnerViewControllerDelegate;
@protocol MBScanningRecognizerRunnerViewControllerDelegate;
@protocol MBGlareRecognizerRunnerViewControllerDelegate;
@protocol MBRecognizerRunnerViewControllerDelegate;
@protocol MBScanningRecognizerRunnerDelegate;
@protocol DMDSPostProcessingDelegate;
/*!
 @unsorted
 @abstract  This is the inner view controller that controls the document capture session, and includes methods to initialise and manage sessions.
 
            The methods provided by this class are primarily for internal framework usage. Use the @link DMDSCaptureManager.h DMDSCaptureManager @/link class to control the scanning sesson. 
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
@interface DMDSCameraController : UIViewController<MBDetectionRecognizerRunnerViewControllerDelegate, MBScanningRecognizerRunnerViewControllerDelegate, MBGlareRecognizerRunnerViewControllerDelegate, MBScanningRecognizerRunnerDelegate, DMDSPostProcessingDelegate>
#pragma clang diagnostic pop

// Initialisation
- (id) initWithDelegate:(id<DMDSDefaultScanDelegate>)delegate
          cameraOptions:(DMDSOptions*)cameraOptions;
- (id) initWithOverlayViewController:(UIViewController<DMDSCustomScanDelegate>*)overlayViewController cameraOptions:(DMDSOptions*)cameraOptions;

// Configuration
- (void) updateCameraOptions:(DMDSOptions*)cameraOptions;
- (void) setScanningRegion:(CGRect)rect;
- (void) updateTotalScanningWidth:(CGFloat)width
                        andHeight:(CGFloat)height;

// Scanning
- (void) stopScanning;
- (void) stopScanningAndStopFaceAnalyser:(BOOL)stopFaceAnalyser;
- (void) restartScanning;
- (void) startScanning;

//- (void) showImage:(UIImage*)image;

@end
