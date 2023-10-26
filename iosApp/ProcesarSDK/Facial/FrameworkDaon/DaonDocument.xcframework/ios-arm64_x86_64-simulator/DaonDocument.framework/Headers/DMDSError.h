
#import <Foundation/Foundation.h>

/*!
 @abstract A list of all possible error codes for all errors returned by this framework.
 @constant DMDSErrorCodeUnknownInitialisationError              Unknown error during initialisation.
 @constant DMDSErrorCodeEmptyOptions                            No options were supplied when initialising scanning.
 @constant DMDSErrorCodeMissingDocumentTypes                    No document type was set.
 @constant DMDSErrorCodeEdgeDetectionWithDocumentRecognition    Edge detection should not be used with other document types.
 @constant DMDSErrorCodeInvalidOptions                          Options supplied when initialising scanning are invalid. See console for more details.
 @constant DMDSErrorCodeSimulatorNotSupported                   Simulator running is not supported.
 @constant DMDSErrorCodeNotInitFaceSDK                          Initialization of FaceSDK failed.
 
 @constant DMDSErrorCodeDocumentNotFound                        Document scanning failed as there was no document detected in the allotted time.
 @constant DMDSErrorCodeDocumentNotRecognized                   Document scanning failed as the document could not be recognised.
 @constant DMDSErrorCodeFaceNotFound                            Document scanning failed as the face on document could not be recognised.
 @constant DMDSErrorCodeUnsupportedOrientation                  Unsupported device orientation.
 @constant DMDSErrorCodeCameraAccessUnauthorized                Camera access unauthorized.
 @constant DMDSErrorCodeScanningLibraryError                    Internal error from scanning library.
 @constant DMDSErrorCodeBadScanningResult                       Result of scanning not passing quality check and scanning can't resume

 */
typedef NS_ENUM(NSInteger, DMDSErrorCode)
{
    DMDSErrorCodeUnknownInitialisationError             = 1001,
    DMDSErrorCodeEmptyOptions                           = 1002,
    DMDSErrorCodeMissingDocumentTypes                   = 1003,
    DMDSErrorCodeEdgeDetectionWithDocumentRecognition   = 1004,
    DMDSErrorCodeInvalidOptions                         = 1005,
    DMDSErrorCodeSimulatorNotSupported                  = 1006,
    DMDSErrorCodeCouldNotInitFaceSDK                    = 1007,
    DMDSErrorCodeCustomEdgeDetectionInvalidSize         = 1008,
    DMDSErrorCodeBlinkIDFailedInit                      = 1009,

    DMDSErrorCodeDocumentNotFound                       = 2001,
    DMDSErrorCodeDocumentNotRecognized                  = 2002,
    DMDSErrorCodeFaceNotFound                           = 2003,
    DMDSErrorCodeUnsupportedOrientation                 = 2004,
    DMDSErrorCodeCameraAccessUnauthorized               = 2005,
    DMDSErrorCodeScanningLibraryError                   = 2006,
    DMDSErrorCodeBadScanningResult                      = 2007

};

/*!
 @internal
 @abstract Error handling class for all errors within this framework.
 */
@interface DMDSError : NSObject

/*!
 @internal
 @abstract    Generate a new NSError from a DMDSErrorCode.
 @param       errorCode   DMDSErrorCode for error.
 @return      A new NSError object.
 @discussion This is primarily for internal framework usage.
 */
+ (NSError *_Nonnull)errorForCode:(NSUInteger)errorCode;

@end
