//
//  DMDSVideoResolution.h
//  DaonDocument
//
//  Created by jdudukovic on 8.2.23..
//  Copyright © 2023 Daon. All rights reserved.
//

#ifndef DMDSVideoResolution_h
#define DMDSVideoResolution_h


/*!
 @abstract A list of all available camera video resolution options.
 @constant DMDSResolution2160P            2160P(4K) video will always be used
 @constant DMDSResolution1080P          1080p video will always be used
 @constant DMDSResolutionOptimal        The library will calculate optimal resolution
*/

typedef NS_ENUM (NSInteger, DMDSVideoResolution)
{
    DMDSResolution2160P              = 0,
    DMDSResolution1080P              = 1,
    DMDSResolutionOptimal            = 2
};

#endif /* DMDSVideoResolution_h */

