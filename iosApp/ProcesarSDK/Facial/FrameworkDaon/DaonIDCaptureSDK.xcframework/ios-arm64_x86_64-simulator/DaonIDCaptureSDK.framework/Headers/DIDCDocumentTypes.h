//
//  DIDCDocumentTypes.h
//  DaonIDCaptureSDK
//
//  Created by Jovan Dudukovic on 23/08/2020.
//  Copyright © 2020 Daon. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@unsorted
@abstract Contains document types that may be used when initialising the scaning options
*/

@interface DIDCDocumentTypes : NSObject


extern NSString * const kCardId1;
extern NSString * const kPassport;
extern NSString * const kA4_Landscape;
extern NSString * const kA4_Portrait;
extern NSString * const kCardId1Vertical;

@end

NS_ASSUME_NONNULL_END
