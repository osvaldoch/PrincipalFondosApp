
#import <UIKit/UIKit.h>

/*!
 Represents a quadrangle (arbitrary geometric object with 4 different corner points).
 */
@interface DMDSQuadrangle : NSObject

/*!
 Upper left point
 */
@property (nonatomic, assign) CGPoint upperLeft;

/*!
 Upper right point
 */
@property (nonatomic, assign) CGPoint upperRight;

/*!
 Lower left point
 */
@property (nonatomic, assign) CGPoint lowerLeft;

/*!
 Lower right point
 */
@property (nonatomic, assign) CGPoint lowerRight;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString*)description;

@end
