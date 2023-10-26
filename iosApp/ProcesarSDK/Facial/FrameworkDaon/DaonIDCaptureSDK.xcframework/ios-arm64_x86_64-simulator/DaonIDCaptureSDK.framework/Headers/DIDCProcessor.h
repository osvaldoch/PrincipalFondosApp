//
//  IDCProcessor.h
//  idcapturetest
//
//  Created by Jovan Dudukovic on 03/02/2020.
//  Copyright © 2020 Coulter, Iain. All rights reserved.
//

#import "DIDCResult.h"
#import "DIDCOptions.h"
#import "DIDCSearchBox.h"
#import "DIDCScanDelegate.h"

@interface DIDCProcessor : NSObject<DIDCScanDelegate>


-  (DIDCResult*_Nullable) processDocumentImage:(UIImage*_Nonnull) image
                                  searchBox: (DIDCSearchBox* _Nullable) searchBox
                                       quality: (bool) quality
                                   orientation: (bool) orientation
                                  documentType:(NSString*_Nonnull) documentType;

- (void) initDocumentScanning:(NSString*_Nonnull) licence //todo move license to options and read file from path
                      options: (DIDCOptions*_Nonnull) options
                     delegate: (_Nonnull id<DIDCScanDelegate>)delegate;

- (void) processDocumentFrame:(UIImage*_Nonnull) image
                        reset: (bool) reset
                    searchBox: (DIDCSearchBox* _Nullable) searchBox
                      quality: (bool) quality
                  orientation: (bool) orientation
                 documentType:(NSString*_Nonnull) documentType;



- (nullable DIDCResultQuality*) getFrameQuality:(UIImage* _Nonnull)image
                                        docType:(NSString* _Nonnull) documentType;

- (nullable DIDCResultQuality*) getFrameQualityWithCoordinates:(UIImage* _Nonnull)image
                                                       corners:(DIDCDetection* _Nonnull) corners
                                                 docType: documentType;

- (instancetype _Nonnull) init;

- (NSString*_Nonnull)description;

@end
