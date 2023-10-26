
#import <UIKit/UIKit.h>

@class DMDSQuadrangle;

/*!
 @abstract Represents the location of a document detected.
 */
@interface DMDSDocumentDetectionMetadata : NSObject

/*!
 @abstract  Exact location of the document detected within the full image.
            Contains the coordinates to the 4 corners of the detected document.
 */
@property (nonatomic, strong) DMDSQuadrangle* detectionLocation;

/*!
 @abstract  Whether or not the detected documented fills the scanning area.
            Based on DMDSOptions scanningRegionFillPercent property.
 */
@property (nonatomic) BOOL documentFillsScanningArea;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString*)description;

@end
