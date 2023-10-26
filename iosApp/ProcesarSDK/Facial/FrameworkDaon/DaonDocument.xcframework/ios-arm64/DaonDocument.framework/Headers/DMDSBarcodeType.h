//
//  DMDSBarcodeType.h
//  DaonDocument
//
//  Created by Neil Johnston on 10/4/18.
//  Copyright © 2018 Daon. All rights reserved.
//

#ifndef DMDSBarcodeType_h
#define DMDSBarcodeType_h

/*!
 @abstract Enum defining the Barcode Types supported
 @constant DMDSBarcodeTypeNone          No type specified.
 @constant DMDSBarcodeTypeQR            QR Code.
 @constant DMDSBarcodeTypeDataMatrix    Data Matrix 2D barcode.
 @constant DMDSBarcodeTypeUPCE          UPCE barcode.
 @constant DMDSBarcodeTypeUPCA          UPCA barcode.
 @constant DMDSBarcodeTypeEAN8          EAN 8 barcode.
 @constant DMDSBarcodeTypeEAN13         EAN 13 barcode.
 @constant DMDSBarcodeTypeCODE128       Code 128 barcode.
 @constant DMDSBarcodeTypeCODE39        Code 39 barcode.
 @constant DMDSBarcodeTypeITF           ITF barcode.
 @constant DMDSBarcodeTypeAZTEC         Aztec 2D barcode.
 @constant DMDSBarcodeTypePDF417        PDF417 2D barcode.

 */
typedef NS_ENUM (NSInteger, DMDSBarcodeType)
{
    DMDSBarcodeTypeNone         = 0,
    DMDSBarcodeTypeQR           = 1,
    DMDSBarcodeTypeDataMatrix   = 2,
    DMDSBarcodeTypeUPCE         = 3,
    DMDSBarcodeTypeUPCA         = 4,
    DMDSBarcodeTypeEAN8         = 5,
    DMDSBarcodeTypeEAN13        = 6,
    DMDSBarcodeTypeCODE128      = 7,
    DMDSBarcodeTypeCODE39       = 8,
    DMDSBarcodeTypeITF          = 9,
    DMDSBarcodeTypeAZTEC        = 10,
    DMDSBarcodeTypePDF417       = 11
};

#endif /* DMDSBarcodeType_h */
