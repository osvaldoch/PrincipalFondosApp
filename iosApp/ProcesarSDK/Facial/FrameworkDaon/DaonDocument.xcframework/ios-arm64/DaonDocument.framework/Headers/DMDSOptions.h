
#import <Foundation/Foundation.h>

#import "DMDSBarcodeType.h"
#import "DMDSVideoResolution.h"
#import "DMDSDewarpPolicy.h"
#import "DMDSCompressFormat.h"

@class DMDSDefaultUIOptions;
@class DMDSExtensionFactors;


/*!
 @abstract Settings class with all possible options to control the document scanning session.
 */
@interface DMDSOptions : NSObject <NSCopying>

/*!
 License key for unlocking the scanning library.
 */
@property (nonnull, nonatomic, strong) NSString *licenseKey;

/*!
 Specify which type(s) of documents should be recognized during the scanning process.
 
 For example, to recognize Passports and UK Drivers Licenses: [NSMutableSet setWithObjects:kPassport, kUkdl, nil];
 
 To use edge detection only (without recognizing a specific document, to just receive a cropped and dewarped document and face (if faceDetection is enabled without extracting any text), set this to kEdgeDetection only. kEdgeDetection should never be set at the same time as other document types.
 For example: [NSMutableSet setWithObjects:kEdgeDetection, nil];
 
 Default: [NSMutableSet setWithObjects: kPassport, kEudl, kUsdl, nil];
 @see DMDSDocumentTypes.h DMDSDocumentTypes
 */
@property (nonnull, nonatomic, strong) NSMutableSet<NSString *> *documentTypes;

/*!
 Lock/unlock support for additional screen orientations. To allow for changes in orientation, your application will also need to support these orientations.
 
 Set it to YES if you want camera view controller to autorotate.
 
 Default: NO.
 */
@property (nonatomic, assign) BOOL lockScanningAspect;

/*!
 Scanning duration in seconds.
 
 This only relates to the document recognition scanning duration if you are using fallback
 edge detection (where fallbackToEdgeDetection is set to true).
 
 Default: 10.
 */
@property (nonatomic, assign) int scanningDuration;

/*!
 Enable/disable face detection.
 
 If enabled and the document type is expected to contain a face, the document scanning will only be successful when the face image is found and
 the global face quality score is greater than or equal to faceQualityScoreThreshold.
 The face image will be returned in the DMDSResult object along with the quality score and quality measures.
 
 Default: NO.
 */
@property (nonatomic, assign) BOOL faceDetection;

/*!
 Set the minimum global face quality score for the face image on the document.
 
 This should be set between 0 and 1, where 0 is the lowest quality score.
 
 If faceDetection is enabled and the document type is expected to contain a face, the document scanning will only be successful when the face image is found and
 the global face quality score is greater than or equal to this value.
 
 Default: 0.4.
 */
@property (nonatomic, assign) float faceQualityScoreThreshold;

/*!
 Enable/disable edge detection as a fallback method to extract the cropped and deskewed
 document image when the document is not recognised within the duration set by 'scanningDuration'.
 
 When using the default scanning method, this should be a seamless transition from document recognition to edge detection
 where there is no change in the UI.
 
 Default: NO.
 */
@property (nonatomic, assign) BOOL fallbackToEdgeDetection;

/*!
 Set the duration in seconds for the fallback edge detection duration after the scanningDuration.
 
 For example, if 'fallbackToEdgeDetectionDuration' is set to 60 and 'scanningDuration' is set to 120, then
 the first 120 seconds will use document recognition, followed by the next 60 seconds of edge detection.
 
 Default: 10.
 */
@property (nonatomic, assign) int fallbackToEdgeDetectionDuration;

/*!
Specify which type of edge detection should be used during the fallback to edge detection scanning.

@see DMDSDocumentTypes.h DMDSDocumentTypes for available edge detection types
*/

@property (nonnull, nonatomic, strong) NSString *fallbackToEdgeDetectionDocumentType;


/*!
Minimum number of stable detections required for detection to be successful.
 Default: 6.
 */
@property (nonatomic, assign) int stableEdgeDetectionsNumber;

/*!
 Whether document scanning should be started immediately. If set to NO, calling code should start scanning explicitly by calling "startScanning".
 
 Default: YES
 */
@property (nonatomic, assign) BOOL autoStartScanning;


/*!
 Settings for the Default UI.
 
 This is only used when initialising a scanning session with the Default UI.
 */
@property (nonnull, nonatomic, strong) DMDSDefaultUIOptions *defaultUIOptions;

/*!
 Initialises DMDSOptions with default values.
 
 See individual properties for default values.
 
 @return Initialised DMDSOptions object.
 */
- (nonnull instancetype)init;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString * _Nonnull)description;

/*!
 Set the DPI of the processed image. Defaults to 300.
 
 A DPI setting below 300 could fail to process properly on the server.
 
 Default: 300.
 */
@property (nonatomic, assign) float defaultProcessedImageDPI;

/*!
 The Barcode Type if the Doc Type to be scanned is kBarcode
 
 Default: DMDSBarcodeTypeNone
 */
@property (nonatomic, assign) DMDSBarcodeType barcodeType;

/*!
 The percent of the scanning region that the scanned document should fill in order for processing to be successful.
 Either height or width needs to be filled in order for scanning to proceed, otherwise it will be ignored.

 
 Range: 0.0 to 1.0
 Default: 0.5 (50%)
 */
@property (nonatomic, assign) float scanningRegionFillPercent;


/*!
 Whether Glare detection should be used.
 
 Default: YES;
 */
@property (nonatomic, assign) BOOL glareDetection;

/**
 * Whether glare events should be filtered by Document SDK or not.
 *
 * Default: YES
 */
@property (nonatomic, assign) BOOL glareCallbackFiltering;


/*!
 Aspect ratio of the document, must be positive. Default value as in Passport (ISO-7810)
 
 Default: 1.42045455;
 */
@property (nonatomic, assign) float customEdgeDetectionAspectRatio;



/*!
 * Physical size of document in inches. Default value as in Passport (ISO-7810)

 Default:  3.465;
 */
@property (nonatomic, assign) float customEdgeDetectionPhysicalSizeInInches;

/*!
 Tolerance for edge detection algorithm in landscape scanning mode. Higher tolerance will increase detection rate.
 
 Default: 0.24;
 */
@property (nonatomic, assign) float edgeDetectionLandscapeScaleTolerance;


/*!
 Tolerance for edge detection algorithm in portrait scanning mode. Higher tolerance will increase detection rate.

 Default: 0.16;
 */
@property (nonatomic, assign) float edgeDetectionPortraitScaleTolerance;


/*!
 Whether detection of ID1, ID2 and ID3 cards should be done for vertical orientation. Otherwise edge detection works only for horizontal position.
 
 Default: NO;
 */
@property (nonatomic, assign) BOOL edgeDetectionVerticalCardScan;



/*!
Specify license key for face SDK. If not specified faceSDK will use license.txt file in project .

@see DMDSDocumentTypes.h DMDSDocumentTypes for available edge detection types
*/

@property (nonnull, nonatomic, strong) NSString *faceSDKLicenseKey;



/*!
 Image Extension factors by which scanned document image will be extended.
 
 @see DMDSExtensionFactors for default value
 */
@property (nullable, nonatomic, strong) DMDSExtensionFactors *extensionFactors;


/*!
 Whether or not we should perform barcode extraction when scanning for RSA Green Book ID.
 
 Default value is FALSE, thus we are extracting barcode data, if it fails we are failing overall scan.
 
 Default: NO;
 */
@property (nonatomic, assign) BOOL greenBookIdFastScan;


/*!
 Whether returning of unverified results is allowed. Unverified result is result that is parsed,
 
but check digits are incorrect. By default, this is set to 'false'.
 
 Default: NO;
 */
@property (nonatomic, assign) BOOL allowUnverifiedMrzResults;



/*!
 Anonymization is performed on recognizer result for both OCR and images.

 
 Default: NO;
 */
@property (nonatomic, assign) BOOL anonymizeResults;


/*!
 * Configure white border around processed document image.
 *
 * Range: 0 to 200
 *
 * Default: 0px
 */
@property (nonatomic, assign) int documentBorderWidth;


/*!
 * Whether to detect and discart bad quality frames.
 *
 * Default: false
 */
@property (nonatomic, assign) BOOL qualityFilter;



/*!
 * When using quality filter, frames with blur values below maxLocalBlur will be rejected.
 *
 * Default: 1.84f
 */
@property (nonatomic, assign) float maxLocalBlur;


/*!
 *  When using quality filter, frames with adaptive glare values between minAdaptiveGlare and maxAdaptiveGlare will be rejected.
 *
 * Default: 0.1f
 */
@property (nonatomic, assign) float minAdaptiveGlare;


/*!
 *  When using quality filter, frames with adaptive glare values between minAdaptiveGlare and maxAdaptiveGlare will be rejected.
 *
 * Default: 0.2f
 */
@property (nonatomic, assign) float maxAdaptiveGlare;

/*!
 *  When using quality filter, which format to use when returning quality image data
 *
 *
 * Default: JPEG
 */
@property (nonatomic, assign) DMDSCompressFormat qualityImageCompressFormat;


/*!
 * Video resolution preset that will be used when choosing camera resolution for scanning.
 *
 * Default value: DMDSResolution2160P
 */
@property (nonatomic, assign) DMDSVideoResolution videoResolution;


/*!
 *  Whether to disable detection of unrecognized documents. Applies only to IdDocument and IdDocumentCombined document types
 *
 * Default: NO
 */
@property (nonatomic, assign) bool disablePhotoIdMode;


/*!
 *
 * TODO: write dewarping policy doc
 * Default: DPIBased...
 */

@property (nonatomic, assign) DMDSDewarpPolicy  dewarpPolicy;


@end
