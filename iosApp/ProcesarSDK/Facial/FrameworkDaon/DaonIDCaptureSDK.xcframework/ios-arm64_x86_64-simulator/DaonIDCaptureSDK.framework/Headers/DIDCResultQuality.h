//
//  DIDCResultQuality.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 11/06/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DIDCResultQuality : NSObject


@property double summary;

@property  double aspectRatio;

@property  double  size;

@property  double  vertDistort;

@property  double  horizDistort;

@property  double  minInternalAngle;

@property  double  maxInternalAngle;

@property  double  sumInternalAngle;

@property  double  glareAdaptive;

@property  double  glareFixed;

@property  double  localBlur;

@property  double globalBlur;

- (NSString *)description ;

@end

NS_ASSUME_NONNULL_END
