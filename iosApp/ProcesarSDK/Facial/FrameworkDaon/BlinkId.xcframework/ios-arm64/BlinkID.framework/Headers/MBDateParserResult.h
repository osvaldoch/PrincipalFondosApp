//
//  MBDateParserResult.h
//  MicroblinkDev
//
//  Created by Jura Skrlec on 12/03/2018.
//

#import <Foundation/Foundation.h>

#import "MBMicroblinkDefines.h"
#import "MBParserResult.h"

@class MBDate;

NS_ASSUME_NONNULL_BEGIN

/**
 * MBDateParser that can extract date from OCR result.
 */
MB_CLASS_AVAILABLE_IOS(13.0)
@interface MBDateParserResult : MBParserResult <NSCopying>

MB_INIT_UNAVAILABLE

/**
 * Extracted date.
 */
@property (nonatomic, strong, readonly) MBDate *date;

@end

NS_ASSUME_NONNULL_END
