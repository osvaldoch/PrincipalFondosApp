
/*!
 @abstract DaonDocument SDK master include for all classes.
 */

#import <UIKit/UIKit.h>

// Capture Manager
#import <DaonDocument/DMDSCaptureManager.h>
#import <DaonDocument/DMDSCameraController.h>
#import <DaonDocument/DMDSDocumentAnalyzer.h>

// Protocols
#import <DaonDocument/DMDSCustomScanDelegate.h>
#import <DaonDocument/DMDSDefaultScanDelegate.h>
#import <DaonDocument/DMDSDirectScanDelegate.h>

// Options
#import <DaonDocument/DMDSOptions.h>

// Utilities
#import <DaonDocument/DMDSUtilities.h>

// Models
#import <DaonDocument/DMDSError.h>
#import <DaonDocument/DMDSDocumentDetectionMetadata.h>
#import <DaonDocument/DMDSMrzDetectionMetadata.h>
#import <DaonDocument/DMDSBarcodeType.h>
#import <DaonDocument/DMDSDocumentCaptureType.h>
#import <DaonDocument/DMDSDewarpPolicy.h>
#import <DaonDocument/DMDSDocument.h>
#import <DaonDocument/DMDSResult.h>
#import <DaonDocument/DMDSDocumentTypes.h>
#import <DaonDocument/DMDSRecognitionMode.h>
#import <DaonDocument/DMDSVideoResolution.h>
#import <DaonDocument/DMDSDefaultUIOptions.h>
#import <DaonDocument/DMDSExtensionFactors.h>
#import <DaonDocument/DMDSFace.h>
#import <DaonDocument/DMDSQuadrangle.h>
#import <DaonDocument/DMDSCompressFormat.h>

@interface DaonDocument : NSObject

/*!
 @abstract Get the current version of this framework.
 @return String representation of the version of this framework.
 */
+ (NSString * _Nonnull)version;

@end
