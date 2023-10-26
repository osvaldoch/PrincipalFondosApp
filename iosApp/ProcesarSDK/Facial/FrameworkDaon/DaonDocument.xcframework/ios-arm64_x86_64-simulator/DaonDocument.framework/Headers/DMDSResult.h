
#import <UIKit/UIKit.h>

@class DMDSFace;
@class DMDSDocument;

/*!
 @abstract Contains the captured data for a scanned document.
 */
@interface DMDSResult : NSObject

/*!
 @abstract The captured document.
 */
@property (nonatomic, strong) DMDSDocument* document;

/*!
 @abstract The face extracted from the document.
 */
@property (nonatomic, strong) DMDSFace* face;

/*!
 @internal
 @abstract  Initialise a DMDSResult object.
 @return    A new DMDSResult object.
 @discussion This is primarily for internal framework usage.
 */
- (id)initWithDocument:(DMDSDocument *) document face:(DMDSFace *)face;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString*)description;

@end
