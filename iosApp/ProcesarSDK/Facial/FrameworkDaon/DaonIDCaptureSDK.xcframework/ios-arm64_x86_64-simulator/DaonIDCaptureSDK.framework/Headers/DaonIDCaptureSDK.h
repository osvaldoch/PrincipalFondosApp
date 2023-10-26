

/*!
 @abstract Daon ID Capture SDK master include for all classes.
 */

#import <UIKit/UIKit.h>

// Image Processor
#import <DaonIDCaptureSDK/DIDCProcessor.h>


// Utils
#import <DaonIDCaptureSDK/DFSAudioVideo.h>
#import <DaonIDCaptureSDK/DIDCUtils.h>


// Protocols
#import <DaonIDCaptureSDK/DIDCScanDelegate.h>



// Model
#import <DaonIDCaptureSDK/DIDCDetection.h>
#import <DaonIDCaptureSDK/DIDCDocumentTypes.h>
#import <DaonIDCaptureSDK/DIDCSearchBox.h>


@interface DaonIDCaptureSDK : NSObject

/*!
 @abstract Get the current version of this framework.
 @return String representation of the version of this framework.
 */
+ (NSString * _Nonnull)version;

@end
