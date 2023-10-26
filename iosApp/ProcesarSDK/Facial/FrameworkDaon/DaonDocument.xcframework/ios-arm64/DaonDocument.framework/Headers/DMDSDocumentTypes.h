
#import <Foundation/Foundation.h>

/*!
 @unsorted
 @abstract Contains all possible document types that may be used when initialising the scaning options (see documentTypes in @link DMDSOptions.h DMDSOptions @/link).
 */
@interface DMDSDocumentTypes : NSObject

/*! Generic Id Document */
extern NSString * const kIdDocument;
extern NSString * const kIdDocumentCombined;



/*!
 Edge Detection (this will capture any document by searching for a rectangle's edges). No OCR will be performed.
 
 Note - this should not be used with any other document type.
 */
extern NSString * const kEdgeDetection;
extern NSString * const kEdgeDetection_A4;
extern NSString * const kEdgeDetection_A4_Landscape;
extern NSString * const kEdgeDetection_A4_Portrait;
extern NSString * const kEdgeDetection_ID1;
extern NSString * const kEdgeDetection_ID2;
extern NSString * const kEdgeDetection_ID3;
extern NSString * const kEdgeDetection_Custom;
extern NSString * const kBarcode;


/*! Australian Drivers Licence - Front */
extern NSString * const kAustralianDL;
/*! Australian Drivers Licence - Back */
extern NSString * const kAustralianDLBack;


/*! Austrian Identity Card - Front */
extern NSString * const kAustrianFrontID;
/*! Austrian Identity Card - Back */
extern NSString * const kAustrianBackID;
/*! Austrian Passport */
extern NSString * const kAustrianPassport;
/*! Austrian Drivers Licence */
extern NSString * const kAustrianDL;


/*! Brunei Identity Card - Front */
extern NSString * const kBruneianFrontID;
/*! Brunei Identity Card - Back */
extern NSString * const kBruneianBackID;
/*! Brunei Military Identity Card - Front */
extern NSString * const kBruneianMilitaryFrontID;
/*! Brunei Military Identity Card - Back */
extern NSString * const kBruneianMilitaryBackID;
/*! Brunei Residence Permit - Front */
extern NSString * const kBruneianResidencePermitFront;
/*! Brunei Residence Permit - Back */
extern NSString * const kBruneianResidencePermitBack;

/*! Czech Identity Card - Front */
extern NSString * const kCzechFrontID;
/*! Czech Identity Card - Back */
extern NSString * const kCzechBackID;

/*! Croatian Identity Card - Front */
extern NSString * const kCroatianFrontID;
/*! Croatian Identity Card - Back */
extern NSString * const kCroatianBackID;

/*! Colombia Identity Card - Front */
extern NSString * const kColombiaFrontID;
/*! Colombia Identity Card - Back */
extern NSString * const kColombiaBackID;
/*! Colombia Drivers licence Front*/
extern NSString * const kColombiaFrontDL;

/*! Cyprus Identity Card - Front */
extern NSString * const kCyprusFrontID;
/*! Cyprus Identity Card - Back */
extern NSString * const kCyprusBackID;
/*! Cyprus Old Identity Card - Front */
extern NSString * const kCyprusOldFrontID;
/*! Cyprus Old Identity Card - Back */
extern NSString * const kCyprusOldBackID;

/*! Egypt Identity Card - Front */
extern NSString * const kEgyptFrontID;

/*! EU Drivers License */
extern NSString * const kEudl;

/*! German Identity Card - Front */
extern NSString * const kGermanFrontID;
/*! German Identity Card - Back */
extern NSString * const kGermanBackID;
/*! German Identity Card - Old */
extern NSString * const kGermanOldID;
/*! German Passport */
extern NSString * const kGermanPassport;
/*! German Drivers Licence - Front */
extern NSString * const kGermanFrontDL;
/*! German Drivers Licence - Back */
extern NSString * const kGermanBackDL;


/*! HongKong Identity Card - Front */
extern NSString * const kHongKongFrontID;

/*! Indonesian Identity Card - Front */
extern NSString * const kIndonesianFrontID;

/*! Ireland Drivers License - Front */
extern NSString * const kIrelandDL;

/*! Italy Drivers Licence - Front */
extern NSString * const kItalianFrontDL;

/*! Jordan Identity Card - Front */
extern NSString * const kJordanFrontID;
/*! Jordan Identity Card - Back */
extern NSString * const kJordanBackID;

/*! Kuwait Identity Card - Front */
extern NSString * const kKuwaitFrontID;
/*! Kuwait Identity Card - Back */
extern NSString * const kKuwaitBackID;


/*! Malaysian Drivers License - Front */
extern NSString * const kMalaysianDLFront;
/*! Malaysian MyKad Identity Card - Front */
extern NSString * const kMalaysianFrontID;
/*! Malaysian MyKad Identity Card - Back */
extern NSString * const kMalaysianBackID;
/*! Malaysian IKad Identity Card - Front */
extern NSString * const kMalaysianIKADFront;
/*! Malaysian MyTentera Identity Card - Front */
extern NSString * const kMalaysianMyTenteraFront;
/*! Malaysian MyKas - Front */
extern NSString * const kMalaysianMyKasFront;
/*! Malaysian MyPr - Front */
extern NSString * const kMalaysianMyPrFront;

/*! Mexico Voter ID - Front */
extern NSString * const kMexicoFrontVoterID;


/*! Morocco Identity Card - Front */
extern NSString * const kMoroccoFrontID;
/*! Morocco Identity Card - Back */
extern NSString * const kMoroccoBackID;

/*! New Zealand Drivers Licence - Front */
extern NSString * const kNewZealandDLFront;

/*! Nigeria Drivers Licence - Front */
extern NSString * const kNigeriaFrontDL;
/*! Nigeria Drivers Licence - Back */
extern NSString * const kNigeriaBackDL;

/*! Passport */
extern NSString * const kPassport;

/*! Polish Identity Card - Front */
extern NSString * const kPolishFrontID;
/*! Polish Identity Card - Back */
extern NSString * const kPolishBackID;

/*! Romania Identity Card - Front */
extern NSString * const kRomaniaFrontID;

/*! Slovak Identity Card - Front */
extern NSString * const kSlovakFrontID;
/*! Slovak Identity Card - Back */
extern NSString * const kSlovakBackID;

/*! Slovenian Identity Card - Front */
extern NSString * const kSlovenianFrontID;
/*! Slovenian Identity Card - Back */
extern NSString * const kSlovenianBackID;

/*! Singapore Identity Card - Front */
extern NSString * const kSingaporeFrontID;
/*! Singapore Identity Card - Back */
extern NSString * const kSingaporeBackID;
/*! Singapore Drivers Licence - Front */
extern NSString * const kSingaporeFrontDL;

/*! Spain Drivers Licence - Front */
extern NSString * const kSpainFrontDL;

/*! Sweden Drivers Licence - Front */
extern NSString * const kSwedenFrontDL;

/*! Switzerland Identity Card - Front */
extern NSString * const kSwitzerlandFrontID;
/*! Switzerland Identity Card - Back */
extern NSString * const kSwitzerlandBackID;
/*! Switzerland Passport */
extern NSString * const kSwitzerlandPassport;
/*! Switzerland Drivers Licence - Front */
extern NSString * const kSwitzerlandFrontDL;

/*! South African Green ID Book */
extern NSString * const kSouthAfricanGreenBookID;
/*! South African Smart ID Card - Back */
extern NSString * const kSouthAfricanSmartBackID;

/*! United Arab Emirates Identity Card - Front */
extern NSString * const kUnitedArabEmiratesFrontID;
/*! United Arab Emirates Identity Card - Back */
extern NSString * const kUnitedArabEmiratesBackID;
/*! United Arab Emirates Drivers Licence - Front */
extern NSString * const kUnitedArabEmiratesFrontDL;

/*! UK Drivers Licence - Front */
extern NSString * const kUKFrontDL;

/*! US Drivers License - Front */
extern NSString * const kUsdlFront;
/*! US Drivers License - Back */
extern NSString * const kUsdl;

/*! MRZ readable documents */
extern NSString * const kMrz;


/*! Barcode readable documents */
extern NSString * const kIdBarcodeDocument;

extern NSString * const kBarcodeCardDocument;



// Deprecated

/*! Serbian Identity Card - Front */
extern NSString * const kSerbianFrontID;
/*! Serbian Identity Card - Back */
extern NSString * const kSerbianBackID;


@end
