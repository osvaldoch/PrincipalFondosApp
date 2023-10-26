
#import <UIKit/UIKit.h>
#import <AvailabilityMacros.h>
#import "DMDSRecognitionMode.h"

@class DMDSQuadrangle;
@class DMDSOptions;
@class DMDSExtensionFactors;
@class DMDSFace;


/*!
 @abstract This is a utilities class that contains methods that may be of use to an application integrating with this framework.
 */
@interface DMDSUtilities : NSObject

/*!
 @abstract  Crop an image based on specific coordinates.
 @param     originalImage   Original image to crop. Ensure the image orientation matches the coordinates.
 @param     coordinates     Coordinates to crop the image. These must be in pixels, based on the top left corner of the original image.
 @return    Cropped image.
 */
+ (UIImage*) cropImage:(UIImage*)originalImage withCoordinates:(DMDSQuadrangle*)coordinates;

/*!
 @abstract  Add a pixel border around an image.
            This is being used when returning the processed document image in order to work with the server-side processing.
 @param     image   The original image to add the padding to.
 @return    Padded image.
 */
+ (UIImage*) padImageForServerProcessing:(UIImage*)image
                         forDocumentType:(NSString*)documentType
                             paddingSize: (int) paddingSize;



+ (UIImage*) padImage: (UIImage*)image
      forDocumentType: (NSString*)documentType
   captureOrientation: (UIInterfaceOrientation) captureOrientation
withDetectionLocation: (DMDSQuadrangle*) detectionLocation
 withExtensionFactors: (DMDSExtensionFactors*) extensionFactors
 fromUnprocessedImage: (UIImage*) unprocessedImage;
    
/*!
 
 @abstract Validates if a number is a valid luhn number.
 @param luhnString The string to check
 @return true if string is valid huhn number
*/
+ (BOOL) isValidLuhn:(NSString*)luhnString;

+ (NSArray<NSString*>*) getAvailableDocumentTypes;

+ (BOOL) containsEdgeDetection:(DMDSOptions*)options;

+ (BOOL) requiresPortraitScanRegion:(DMDSOptions*)options;

+ (BOOL) includesFaceImage:(DMDSOptions*)options;

+ (NSString*) encodeBase64Jpeg:(UIImage*)image DEPRECATED_ATTRIBUTE;

+ (NSString*)encodeBase64Jpeg:(UIImage*)image withQuality:(float)quality DEPRECATED_ATTRIBUTE;

+ (NSString*) encodeBase64Jpeg:(UIImage*)image withDPI:(int)dpi DEPRECATED_ATTRIBUTE;

+ (void) writeUImageToDocuments:(UIImage*)image;

+ (UIImage*) rotateImage:(UIImage*)image degrees:(float)degrees;

+ (UIImage *)cropImageToRect:(UIImage *)image toRect:(CGRect)rect;

+ (UIImage *) cropImageDMDS:(UIImage *)originalImage withCoordinates:(DMDSQuadrangle *)coordinates;

+ (NSString*) localise:(NSString*)key;

+ (BOOL) isCombinedScanDocument:(DMDSOptions*)options;

+ (DMDSRecognitionMode) mapToDMDSRecognitionMode:(int)recognitionMode;

+ (UIImage*) adjustDocumentOrientation:(UIImage*)processedImage
                              withFace:(DMDSFace*) face
                            orientation:(int)orientation;

+ (UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)newSize;

+ (DMDSQuadrangle*) adjustCoordinates:(DMDSQuadrangle*) coordinates
                           addPadding: (DMDSExtensionFactors*) extension;

@end
