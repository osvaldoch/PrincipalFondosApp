
#import <UIKit/UIKit.h>

#import <DaonDocument/DMDSDocumentCaptureType.h>
#import <DaonDocument/DMDSRecognitionMode.h>


@class DMDSQuadrangle;

/*!
 @abstract Represents a scanned document.
 */
@interface DMDSDocument : NSObject

/*!
 @abstract The information extracted from the document via OCR. The data is keyed by the name of the extracted element.
 */
@property (nonatomic, strong) NSDictionary* textExtracted;
/*!
 @abstract The quality score associated with the captured processed document image.
 */
@property (nonatomic, assign) double qualityScore;
/*!
 @abstract The captured document image after processing has been applied - i.e. the document has been cropped and de-skewed.
 */
@property (nonatomic, strong) UIImage* processedImage;

/*!
 @abstract The captured document image before any image processing has been applied (aside for it being rotated to the correct orientation).
 */
@property (nonatomic, strong) UIImage* unprocessedImage;

/*!
 @abstract The captured document image for the back side after processing has been applied - i.e. the document has been cropped and de-skewed.
 */
@property (nonatomic, strong) UIImage* processedImageBack;

/*!
 @abstract The captured document image for the back side before any image processing has been applied (aside for it being rotated to the correct orientation).
 */
@property (nonatomic, strong) UIImage* unprocessedImageBack;

/*!
 @abstract Data from the quality analysis image
 */

@property (nonatomic, strong) NSData* qualityImageProcessed;


/*!
 @abstract Data from the quality analysis image back side
 */

@property (nonatomic, strong) NSData* qualityImageProcessedBack;


/*!
 @abstract The image of the user signature found in the document
 */
@property (nonatomic, strong) UIImage* signatureImage;


/*!
 @abstract The image of the barcode found in the document
 */
@property (nonatomic, strong) UIImage* unprocessedBarcodeImage;


/*!
 @abstract The location of the processed image within the unprocessed image.
 
 Contains 4 points of detected document's corners. Measurements are in pixels, and are based on the distance from the top left corner of the 'unprocessedImage' image.
 */
@property (nonatomic, strong) DMDSQuadrangle* processedDocumentCoordinates;

/*!
 @abstract The location of the processed image within the unprocessed image for back side.
 
 Contains 4 points of detected document's corners. Measurements are in pixels, and are based on the distance from the top left corner of the 'unprocessedImageBack' image.
 */
@property (nonatomic, strong) DMDSQuadrangle* processedDocumentCoordinatesBack;


/*!
 @brief The type of document that has been captured, or 'kEdgeDetection' if it was captured through edge detection.
 */
@property (nonatomic, strong) NSString* documentType;

/*!
 @brief how the SDK came to capture this result
 */
@property (nonatomic) DMDSDocumentCaptureType captureType;


/*!
 @brief how the SDK recognized the front side of the document
 */
@property (nonatomic) DMDSRecognitionMode recognitionMode;


/*!
 @brief how the SDK recognized the back side of the document
 */
@property (nonatomic) DMDSRecognitionMode backSideRecognitionMode;


/*
 * The information extracted from the document via OCR. The data is keyed by the name of the extracted element.
 */
@property (nonatomic, strong) NSDictionary* visualResult;


/*
 * The information extracted from front side of the document via OCR. The data is keyed by the name of the extracted element.
 */
@property (nonatomic, strong) NSDictionary* frontVisualResult;

/*
 * The information extracted from back side of the document via OCR. The data is keyed by the name of the extracted element.
 */

@property (nonatomic, strong) NSDictionary* backVisualResult;

/*
 * The information extracted from MZR. The data is keyed by the name of the extracted element.
 */

@property (nonatomic, strong) NSDictionary* mrzResult;

/*
 * The information extracted from Barcode. The data is keyed by the name of the extracted element.
 */

@property (nonatomic, strong) NSDictionary* barcodeResult;




/*!
 @internal
 @abstract  Initialise a DMDSDocument object.
 @return    A new DMDSDocument object.
 @discussion This is primarily for internal framework usage.
 */
- (id)initWithText:(NSDictionary*)textExtracted
      qualityScore:(double)qualityScore
    processedImage:(UIImage*)processedImage
  unprocessedImage:(UIImage*)unprocessedImage
processedImageBack:(UIImage*)processedImageBack
unprocessedImageBack:(UIImage*)unprocessedImageBack
qualityImageProcessed:(NSData*)qualityImageProcessed
qualityImageProcessedBack:(NSData*)qualityImageProcessedBack
    signatureImage:(UIImage*)signatureImage
documentCoordinates:(DMDSQuadrangle*)documentCoordinates
documentCoordinatesBack:(DMDSQuadrangle*)documentCoordinatesBack
      visualResult:(NSDictionary *)visual
 frontVisualResult:(NSDictionary *)frontVisual
  backVisualResult:(NSDictionary *)backVisual
         mrzResult:(NSDictionary *)mrz
     barcodeResult:(NSDictionary *)barcode
      documentType:(NSString*)documentType;



/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString*)description;

@end
