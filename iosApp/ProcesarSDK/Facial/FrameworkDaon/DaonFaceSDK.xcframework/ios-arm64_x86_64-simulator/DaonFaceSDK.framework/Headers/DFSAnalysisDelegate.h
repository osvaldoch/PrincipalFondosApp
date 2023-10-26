//
//  DFSAnalysisDelegate.h
//  DaonFaceSDK
//
//  Created by Neil Johnston on 12/11/15.
//  Copyright © 2015 Daon. All rights reserved.
//

#import <CoreVideo/CVPixelBuffer.h>
#import <UIKit/UIKit.h>

#import <DaonFaceSDK/DFSResult.h>

/*!
 @brief Delegate for feedback on image analysis.
 */
@protocol DFSAnalysisDelegate <NSObject>

/*!
 @brief Called when analysis has completed for a particular UIImage.
 @param result The analysis result.
 */
- (void) analysisResult:(NSDictionary*_Nonnull)result NS_SWIFT_NAME(analysis(result:));


@end


/*!
 @brief Liveness Delegate
 */
@protocol DFSLivenessAnalysisDelegate <NSObject>

- (void) analysisResult:(DFSResult*_Nonnull)result alert:(DFSLivenessAlert)alert NS_SWIFT_NAME(analysis(result:alert:));
- (void) analysisResult:(DFSResult*_Nonnull)result didDetectEvent:(DFSLivenessEvent) event NS_SWIFT_NAME(analysis(result:didDetectEvent:));

@optional

- (void) analysisResult:(DFSResult*_Nonnull)result didChangeState:(DFSLivenessState)state NS_SWIFT_NAME(analysis(result:didChangeState:));
- (void) analysisResult:(DFSResult*_Nonnull)result NS_SWIFT_NAME(analysis(result:));

@end

