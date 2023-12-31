//
// MBSloveniaIdFrontRecognizer.h
//
// Created by juraskrlec on 19/03/2019
// Copyright © Microblink Ltd. All rights reserved.
//

#import "MBRecognizer.h"
#import "MBSloveniaIdFrontRecognizerResult.h"

#import "MBGlareDetection.h"
#import "MBFaceImage.h"
#import "MBEncodeFaceImage.h"
#import "MBFaceImageDpi.h"
#import "MBFullDocumentImage.h"
#import "MBEncodeFullDocumentImage.h"
#import "MBFullDocumentImageDpi.h"
#import "MBFullDocumentImageExtensionFactors.h"
#import "MBSignatureImage.h"
#import "MBSignatureImageDpi.h"
#import "MBEncodeSignatureImage.h"

NS_ASSUME_NONNULL_BEGIN

/**
* Recognizer which can scan front side of Slovenia ID.
*/
MB_CLASS_AVAILABLE_IOS(13.0) MB_CLASS_DEPRECATED("Use MBBlinkIdSingleSideRecognizer or MBBlinkIdMultiSideRecognizer.") MB_FINAL
@interface MBSloveniaIdFrontRecognizer : MBRecognizer<NSCopying, MBGlareDetection, MBFaceImage, MBEncodeFaceImage, MBFaceImageDpi, MBFullDocumentImage, MBEncodeFullDocumentImage, MBFullDocumentImageDpi, MBFullDocumentImageExtensionFactors, MBSignatureImage, MBSignatureImageDpi, MBEncodeSignatureImage>

MB_INIT

/**
 * Result of scanning SloveniaIdFrontRecognizer
 */
@property (nonatomic, strong, readonly) MBSloveniaIdFrontRecognizerResult *result;

/**
* Defines if date of expiry of Slovenian ID card should be extracted.
*
* Default: YES
*/
@property (nonatomic, assign) BOOL extractDateOfExpiry;

/**
* Defines if given names of Slovenian ID owner should be extracted.
*
* Default: YES
*/
@property (nonatomic, assign) BOOL extractGivenNames;

/**
* Defines if nationality of Slovenian ID owner should be extracted.
*
* Default: YES
*/
@property (nonatomic, assign) BOOL extractNationality;

/**
* Defines if sex of Slovenian ID owner should be extracted.
*
* Default: YES
*/
@property (nonatomic, assign) BOOL extractSex;

/**
* Defines if surname of Slovenian ID owner should be extracted.
*
* Default: YES
*/
@property (nonatomic, assign) BOOL extractSurname;

@end

NS_ASSUME_NONNULL_END
