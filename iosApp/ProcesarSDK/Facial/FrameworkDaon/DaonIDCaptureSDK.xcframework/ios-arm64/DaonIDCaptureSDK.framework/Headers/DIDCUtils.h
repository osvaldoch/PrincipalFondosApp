//
//  DIDCUtils.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 04/02/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DIDCResult.h"

//#import "DaonIDCaptureApi.h"

NS_ASSUME_NONNULL_BEGIN

@interface DIDCUtils : NSObject

+ (void )loadImagePaths:(__strong NSString*_Nonnull[_Nonnull]) imagePaths;



+ (UIImage *)drawLinesOnImage:(UIImage *)img
                           ll:(CGPoint) ll
                           lr:(CGPoint) lr
                           ur:(CGPoint) ur
                           ul:(CGPoint) ul;


+ (double)getLastFrameTime;
   

+ (double)getTotalTime;


+ (void)startTimeMeasure:(bool)restartSession;


+ (NSString*) localise:(NSString*)key;

+ (double) getIdShapeFromDocType:(NSString*) docType;



    
@end

NS_ASSUME_NONNULL_END
