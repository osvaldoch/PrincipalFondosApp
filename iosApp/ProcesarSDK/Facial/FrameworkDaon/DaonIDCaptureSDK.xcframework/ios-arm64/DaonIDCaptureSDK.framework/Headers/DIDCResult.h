//
//  DIDCResult.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 04/02/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DIDCResultQuality.h"
#import "DIDCDetection.h"

NS_ASSUME_NONNULL_BEGIN

@interface DIDCResult : NSObject

@property bool docFound;

@property UIImage* processedImage;

@property UIImage* unprocessedImage;

@property NSData* processedImageData;

@property DIDCDetection* detection;

@property (nullable) DIDCResultQuality* quality;

@property bool includeFrame;

@property double processingTime;


- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
