
#import <UIKit/UIKit.h>

/*!
 @abstract Represents the face extracted from the scanned document.
 */
@interface DMDSFace : NSObject

/*!
 @abstract  The face image extracted from the scanned document.
 */
@property (nonatomic, strong) UIImage* faceImage;

/*!
 @abstract  The quality score for the face image extracted from the scanned document.
 */
@property (nonatomic, assign) double qualityScore;

/*!
 @abstract  The quality results of the extracted face image. The data is keyed by the name of the extracted element.
 */
@property (nonatomic, strong) NSDictionary* qualityMeasures;

/*!
 @internal
 @abstract  Initialise a DMDSFace object.
 @return    A new DMDSFace object.
 @discussion This is primarily for internal framework usage.
 */
- (id)initWithImage:(UIImage *)faceImage qualityScore:(double)qualityScore qualityMeasures:(NSDictionary*)qualityMeasures;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString*)description;

@end
