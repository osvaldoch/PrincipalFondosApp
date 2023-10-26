//
//  DMDSDocumentCaptureType.h
//  DaonDocument
//
//  Created by Neil Johnston on 9/26/18.
//  Copyright © 2018 Daon. All rights reserved.
//

#ifndef DMDSDocumentCaptureType_h
#define DMDSDocumentCaptureType_h

/*!
 @abstract A list of all possible document capture types, i.e how the SDK came to this result.
 @constant DMDSDocumentCaptureTypeUnknown                   Unknown capture type.
 @constant DMDSDocumentCaptureTypeDocumentRecognition       Requested document type was recognised and scanned.
 @constant DMDSDocumentCaptureTypeEdgeDetection             Requested document type was edge detection only.
 @constant DMDSDocumentCaptureTypeFallBackEdgeDetection     Document recognition gave up, and the framework switched over to edge detection.
 @constant DMDSDocumentCaptureTypeBarCodeAndEdgeDetection   Document recognition involved bar code recognition, followed by edge detection.
 @constant DMDSDocumentCaptureTypeBarCodeOnly   Document recognition using bar code recognition only
 */
typedef NS_ENUM (NSInteger, DMDSDocumentCaptureType)
{
    DMDSDocumentCaptureTypeUnknown                  = 0,
    DMDSDocumentCaptureTypeDocumentRecognition      = 1,
    DMDSDocumentCaptureTypeEdgeDetection            = 2,
    DMDSDocumentCaptureTypeFallBackEdgeDetection    = 3,
    DMDSDocumentCaptureTypeBarCodeAndEdgeDetection  = 4,
    DMDSDocumentCaptureTypeBarCodeOnly              = 5
};

#endif /* DMDSDocumentCaptureType_h */
