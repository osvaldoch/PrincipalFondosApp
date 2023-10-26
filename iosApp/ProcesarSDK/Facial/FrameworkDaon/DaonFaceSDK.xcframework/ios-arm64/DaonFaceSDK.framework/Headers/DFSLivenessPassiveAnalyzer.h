//
//  DFSLivenessDaonAnalyzer.h
//  DaonFaceSDK
//
//  Created by Jonny Mortensen on 5/12/21.
//  Copyright © 2021 Daon. All rights reserved.
//

#import <DaonFaceSDK/DFSLicensedAnalyzer.h>


NS_ASSUME_NONNULL_BEGIN

#define kDFSConfigLivenessStartDelayKey @"LivenessStartDelay"
#define kDFSConfigLivenessTimeoutKey @"LivenessTimeout"
#define kDFSConfigLivenessMinFramesKey @"LivenessMinFrames"
#define kDFSConfigLivenessThresholdKey @"LivenessThreshold"

#define kDFSConfigLivenessTemplateKey @"LivenessTemplate"
#define kDFSConfigLivenessTemplateQualityKey @"LivenessTemplateQuality"


@interface DFSLivenessPassiveAnalyzer : NSObject <DFSLicensedAnalyzer>

+ (NSString*) module;

@end


NS_ASSUME_NONNULL_END
