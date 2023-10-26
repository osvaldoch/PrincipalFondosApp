//
//  DMDSRecognitionMode.h
//  DaonDocument
//
//  Created by jdudukovic on 21.9.21.
//  Copyright © 2021 Daon. All rights reserved.
//

#ifndef DMDSRecognitionMode_h
#define DMDSRecognitionMode_h

/*!
 @abstract A list of all possible document recognition modes, i.e how each side of the document was scanned.
 @constant DMDSRecognitionModeNone                                No recognition performed.
 @constant DMDSRecognitionModeMRZId                              Recognition of mrz document (does not include visa and passport)
 @constant DMDSRecognitionModeMRZVisa                          Recognition of visa mrz.
 @constant DMDSRecognitionModeMRZPassport                   Recognition of passport mrz.
 @constant DMDSRecognitionModePhotoId                             Recognition of documents that have face photo on the front.
 @constant DMDSRecognitionModeFullRecognition                 Detailed document recognition.
 @constant DMDSRecognitionModeBarcodeId                         Recognition of barcode document.

 
 */
typedef NS_ENUM (NSInteger, DMDSRecognitionMode)
{
    DMDSRecognitionModeNone                 = 0,
    DMDSRecognitionModeMRZId                = 1,
    DMDSRecognitionModeMRZVisa              = 2,
    DMDSRecognitionModeMRZPassport          = 3,
    DMDSRecognitionModePhotoId              = 4,
    DMDSRecognitionModeFullRecognition      = 5,
    DMDSRecognitionModeBarcodeId            = 6
};

#endif /* DMDSRecognitionMode_h */
