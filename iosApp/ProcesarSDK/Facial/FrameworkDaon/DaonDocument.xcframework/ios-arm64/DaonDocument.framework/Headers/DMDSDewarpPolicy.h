//
//  DMDSDewarpPolicy.h
//  DaonDocument
//
//  Created by jdudukovic on 8.2.23..
//  Copyright © 2023 Daon. All rights reserved.
//

#ifndef DMDSDewarpPolicy_h
#define DMDSDewarpPolicy_h

/*!
 @abstract A list of available dewarping policies for edge detection recognizers.
 @constant DMDSNoUpscaling No upscaling done for processed image
 @constant DMDSDPIBased Dewarping based on DPI settings

*/

typedef NS_ENUM (NSInteger, DMDSDewarpPolicy)
{
    DMDSNoUpscaling         = 0,
    DMDSDPIBased            = 1
};


#endif /* DMDSDewarpPolicy_h */
