
#import <UIKit/UIKit.h>

@class DMDSCameraController;
@class DMDSOptions;
@protocol DMDSDefaultScanDelegate;
@protocol DMDSCustomScanDelegate;
@protocol DMDSDirectScanDelegate;
@protocol MBScanningRecognizerRunnerDelegate;

/*!
 @unsorted
 @abstract This class controls the document capture session, and includes methods to initialise and manage sessions.
 */


// using "clang diagnostic ignored" to suppressing "Cannot find protocol definition" warning
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"


@interface DMDSCaptureManager: NSObject //<MBScanningRecognizerRunnerDelegate>

#pragma clang diagnostic pop


@property (nonatomic, strong) DMDSOptions * _Nullable options;
@property (nonatomic, weak) id<DMDSDefaultScanDelegate> _Nullable delegate;
@property (nonatomic, strong) DMDSCameraController * _Nullable cameraController;

/*!
 @abstract  This method creates a camera view controller which is responsible for displaying the camera input.
            This method will use the Default UI.
 
 @param delegate             The @link DMDSDefaultScanDelegate.h DMDSDefaultScanDelegate @/link object which will receive notifications for scanning events.
 @param options              Options (@link DMDSOptions.h DMDSOptions@/link) to control the scanning session and UI.
 @param completionHandler    Completion handler to be called after initialisation with an error object. If the error is nil, the initialisation was successful.
 
 @discussion Example Usage:
 <pre>
 DMDSOptions* options = [[DMDSOptions alloc] init];
 options.licenseKey = kLicenseKey; // Example license key
 options.documentTypes = [NSMutableSet setWithObjects:kPassport, nil];  // Only recognise Passports

 [_captureManager defaultCaptureWithDelegate:self cameraOptions:options completionHandler:^(NSError* error) {
    if (error) return [self displayError:@"Initialisaton Error" message:[error localizedDescription]];
    [self presentViewController:(UIViewController*)_captureManager.cameraController animated:YES completion:nil];
 }];
 </pre>
 */
- (void) defaultCaptureWithDelegate:(_Nonnull id<DMDSDefaultScanDelegate>)delegate
                      cameraOptions:(DMDSOptions * _Nonnull)options
                  completionHandler:(void (NS_NOESCAPE ^_Nonnull)(NSError * _Nullable error))completionHandler;


/*!
 @abstract  This method creates a camera view controller which is responsible for displaying the camera input.
            With this method you can specify a custom overlay to be used for the camera display.
 
 @param controller           A UIViewController that conforms to the @link DMDSCustomScanDelegate.h DMDSCustomScanDelegate @/link protocol which will receive notifications for scanning events.
 @param options              Options (@link DMDSOptions.h DMDSOptions@/link) to control the scanning session and UI.
 @param completionHandler    Completion handler to be called after initialisation with an error object. If the error is nil, the initialisation was successful.
 
 @discussion Example Usage:
 <pre>
 DMDSOptions* options = [[DMDSOptions alloc] init];
 options.licenseKey = _licenseKey; // Set the license key
 options.documentTypes = [NSMutableSet setWithObjects:kPassport, nil]; // Only recognise Passports
 
 VCCustomOverlay* vcCustomOverlay = [self.storyboard instantiateViewControllerWithIdentifier:@"VCCustomOverlay"];
 
 // Create the Capture Manager that contains the camera view controller
 [_captureManager customCaptureWithOverlay:vcCustomOverlay cameraOptions:options completionHandler:^(NSError* error) {
    if (error) return [self displayError:@"Initialisaton Error" message:[error localizedDescription]];
    [self presentViewController:(UIViewController*)_captureManager.cameraController animated:YES completion:nil];
 }];
 </pre>
 */
- (void) customCaptureWithOverlay:(UIViewController<DMDSCustomScanDelegate> * _Nonnull)controller
                    cameraOptions:(DMDSOptions * _Nonnull)options
                completionHandler:(void (NS_NOESCAPE ^_Nonnull)(NSError * _Nullable error))completionHandler;

/*!
 @abstract Reset the document types to be recognised, without the need to re-initialise the camera view controller.
           This may be called during a scanning session to seamlessly change the types of documents that are recognised.
 @param documentTypes        A set containing the document types to be recognised.
 
 @discussion Example Usage:
 <pre>
 [_captureManager updateDocumentTypes:[[NSMutableSet alloc] initWithArray:@[kGermanFrontID]]];
 </pre>
 @see DMDSPreferences.h
 */

- (void)updateDocumentTypes:(NSMutableSet<NSString *> * _Nullable)documentTypes;

/*!
 @abstract Set the scanning region.

 @param rect        This defines a portion of the screen in which the scanning will be performed.
                    Given as a CGRect with unit coordinating system.
 
 @discussion Example Usage:
 <pre>
 [_captureManager setScanningRegion:CGRectMake(0.2f, 0.5f, 0.4f, 0.3f)];
 </pre>
 This defines a portion of the screen at
    20% from the left border,
    50% from the top,
    covering 40% of screen width,
    and 30% of screen height.

 */
- (void)setScanningRegion:(CGRect)rect;

/*!
 @abstract Stop the scanning session without dismissing the camera view.
 */
- (void)stopScanning;

/*!
 @abstract Restart the scanning session using the options that were used during initialisation.
 */
- (void)restartScanning;

/*!
 @abstract Start the scanning session using the options that were used during initialisation.
 */
- (void)startScanning;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString * _Nonnull)description;


@end
