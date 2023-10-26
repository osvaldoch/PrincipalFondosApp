

#import <UIKit/UIKit.h>

@class DMDSOptions;
@protocol DMDSDirectScanDelegate;
@protocol MBScanningRecognizerRunnerDelegate;
@protocol MBImageProcessingRecognizerRunnerDelegate;


#pragma clang diagnostic push
// To get rid of 'No protocol definition found' warnings which are not accurate
#pragma clang diagnostic ignored "-Weverything"

/*!
 @unsorted
 @abstract This class controls the document capture session, and includes methods to initialise and manage sessions.
 */
@interface DMDSDocumentAnalyzer : NSObject<MBScanningRecognizerRunnerDelegate, MBImageProcessingRecognizerRunnerDelegate>

#pragma clang diagnostic pop

@property (weak, readonly) id<DMDSDirectScanDelegate> _Nullable delegate;


/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString * _Nonnull)description;



/*!
@abstract  This method initializes Direct document analyzer.

@param licence             Licence key for BlinkId
@param delegate             The @link DMDSDirectScanDelegate.h DMDSDirectScanDelegate @/link object which will receive notifications for scanning events.
@param completionHandler             Wait for BlinkID init, returns error if there is some problem in initialization
*/
- (instancetype _Nonnull) initWithLicence:(NSString*_Nonnull)licence
                                 delegate:(_Nonnull id<DMDSDirectScanDelegate>) delegate
                        completionHandler:(void (^ _Nonnull)(NSError * _Nullable))completionHandler;
/*!
 @abstract  This method creates a camera view controller which is responsible for displaying the camera input.
            This method will use the Default UI.
 
 @param options             Options (@link DMDSOptions.h DMDSOptions@/link) to control the scanning session and UI.
 @param imageData           Completion handler to be called after initialisation with an error object. If the error is nil, the initialisation was successful.
 
 @discussion Example Usage:
 <pre>
 NSData* imageData = UIImagePNGRepresentation(_selectedDocumentImage);
 DMDSOptions* options = [[DMDSOptions alloc] init];
 options.documentTypes = [NSMutableSet setWithObjects:kPassport, nil];  // Only recognise Passports
 documentAnalyzer = [[DMDSDocumentAnalyzer alloc] initWithLicence:licenseKey delegate:self];
 [documentAnalyzer directCaptureWithOptions:options
                    imageToProcess:imageData];
 </pre>
 */
- (void) directCaptureWithOptions:(DMDSOptions* _Nonnull)options
                   imageToProcess:(NSData* _Nonnull) imageData;


- (void)readRSABarcodeDirect:(UIImage* _Nonnull) image;
- (void) startDirectAPIOCRProcessing:(UIImage* _Nonnull) image;

    
@end
