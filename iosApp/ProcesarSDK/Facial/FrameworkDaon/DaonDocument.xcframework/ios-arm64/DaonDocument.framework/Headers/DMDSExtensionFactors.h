

#import <UIKit/UIKit.h>

/*!
 @abstract Settings class with all possible customizable settings for the Default UI.
 */
@interface DMDSExtensionFactors : NSObject <NSCopying>

/*!
 Value by which to extend top side of the scanned document image. Image will be extended by 5% for extension factor of 0.05.
 
 Default: 0.03
 */
@property (nonatomic, assign) float extensionFactorTop;


/*!
 Value by which to extend right side of the scanned document image. Image will be extended by 5% for extension factor of 0.05.
 
 Default: 0.03
 */
@property (nonatomic, assign) float extensionFactorRight;



/*!
 Value by which to extend bottom side of the scanned document image. Image will be extended by 5% for extension factor of 0.05.
 
 Default: 0.03
 */
@property (nonatomic, assign) float extensionFactorBottom;



/*!
 Value by which to extend left side of the scanned document image. Image will be extended by 5% for extension factor of 0.05.
 
 Default: 0.03
 */
@property (nonatomic, assign) float extensionFactorLeft;



/*!
 Initialises DMDSDefaultCameraOptions with default values.
 
 See individual properties for default values.
 
 @return Initialised DMDSDefaultCameraOptions object.
 */
- (nonnull instancetype)init;


/*!
 Initialises DMDSExtensionFactors with specified values.
  
 @return Initialised DMDSExtensionFactors object.
 */
- (nonnull instancetype) initWithTop: (float) top
                               right: (float) right
                              bottom: (float) bottom
                                left: (float) left;


/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString * _Nonnull)description;

@end
