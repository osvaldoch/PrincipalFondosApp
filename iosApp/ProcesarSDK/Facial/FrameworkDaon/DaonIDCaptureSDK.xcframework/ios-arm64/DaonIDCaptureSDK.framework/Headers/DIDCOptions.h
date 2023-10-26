//
//  DIDCOptions.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 08/07/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//


#import <Foundation/Foundation.h>

#import "DIDCExtensionFactors.h"
/*!
 @abstract Settings class with all possible options to control the document scanning session.
 */
@interface DIDCOptions : NSObject <NSCopying>

/*!
 License key for unlocking the scanning library.
 */
@property (nonnull, nonatomic, strong) NSString *licenseKey;

/*!
 
 */
@property (nonnull, nonatomic, strong) NSString *documentType;

/*!
 Default: NO
 */
@property (nonatomic, assign) BOOL scanVertical;

/*!
 Default: 0.45
 */
@property (nonatomic, assign) float frameQualityThreshold;

/*!
 Default
 */

@property (nonatomic, assign) BOOL faceDetection;

/*!
 
 Default:
 */
@property (nonatomic, assign) float faceQualityScoreThreshold;

/*!
 Default: 15.0
 
 */
@property (nonatomic, assign) float horizontalDistortThreshold;

/*!
 Default: 15.0

 */
@property (nonatomic, assign) float verticalDistortThreshold;


/*!

 Default: 75.0
*/

@property (nonatomic, assign) float minInternalAngle;


/*!

 Default: 105.0
*/

@property (nonatomic, assign) float maxInternalAngle;


/*!

 Default: 0.04
*/

@property (nonatomic, assign) float glareFixedThreshold;

/*!

 Default: 1.1
*/

@property (nonatomic, assign) float glareAdaptiveThreshold;

/*!

 Default: 1.84
*/

@property (nonatomic, assign) float blurThreshold;



/*!

 Default: 0.3
*/

@property (nonatomic, assign) float aspectRatioThreshold;


/*!

 Default: 0.8
*/

@property (nonatomic, assign) float scanningRegionFill;


/*!

 Default: 0.15
*/

// todo disambiguate size and scanningRegionFill
@property (nonatomic, assign) float size;


/*!

 Default: 0.06
*/

@property (nonatomic, assign) float cropTolerance;



/*!

 Default: 0
*/

// todo disambiguate size and scanningRegionFill
@property (nonatomic, assign) int paddingWidth;


/*!

 Default: false
*/

// whether to return PNG or JPG data
@property (nonatomic, assign) bool returnPNGData;


/*!
Minimum number of stable detections required for detection to be successful.
 Default: 2.
 */
@property (nonatomic, assign) int stableEdgeDetectionsNumber;

/*!
 Initialises DMDSOptions with default values.
 
 See individual properties for default values.
 
 @return Initialised DMDSOptions object.
 */
- (nonnull instancetype)init;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString* _Nonnull)description;

@end
