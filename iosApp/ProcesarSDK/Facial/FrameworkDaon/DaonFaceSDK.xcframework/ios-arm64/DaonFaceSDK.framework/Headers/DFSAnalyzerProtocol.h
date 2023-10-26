//
//  Analyzer.h
//  DaonFaceSDK
//
//  Copyright © 2015-18 Daon. All rights reserved.
//

#ifndef Analyzer_h
#define Analyzer_h

#import <CoreVideo/CVPixelBuffer.h>
#import <UIKit/UIKit.h>

#import <DaonFaceSDK/DFSModuleProtocol.h>

typedef NS_ENUM(int, DFSAnalyzerImageOrientation) {
    DFSAnalyzerImageOrientationUp,     // (0) raw pixel array corresponds to the "upright" image, so no rotation correction is applied
    DFSAnalyzerImageOrientationRight,  // (1) raw pixel array is rotated 90 degrees clockwise rotation (specific to Android devices)
    DFSAnalyzerImageOrientationLeft,   // (2) raw pixel array is rotated 90 degrees counterclockwise rotation (specific to iOS devices)
};

typedef NS_ENUM(int, DFSAnalyzerImageFormat) {
    DFSAnalyzerImageFormatYUV,     // (0) 8 bit grayscale, YUV
    DFSAnalyzerImageFormatRGB,     // (1) RGB (1 byte each for Red, Green, Blue)
    DFSAnalyzerImageFormatRGBA,    // (2) RGBA (1 byte each for Red, Green, Blue, Alpha)
};


@protocol DFSAnalyzerProtocol <DFSModuleProtocol>

- (NSDictionary*_Nullable) analyzeData:(NSData*_Nonnull)buffer
                             timestamp:(long long)ms;

// Single frame
- (NSDictionary*_Nullable) analyzeData:(NSData*_Nonnull)buffer;

@end

#endif /* Analyzer_h */
