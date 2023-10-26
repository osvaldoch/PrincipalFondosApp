//
// File:   DaonIDCaptureException.h
// Author:
// Created: 2021
//
// Derived from DFV3 "DaonFaceV3Exception.h"
//

#ifndef DAON_IDCAPTURE_EXCEPTION_H
#define DAON_IDCAPTURE_EXCEPTION_H

#include <string>
#include <sstream>
#include <stdexcept>

#ifndef DAON_EXPORT
#ifdef __ANDROID__
#define DAON_EXPORT  __attribute__ ((visibility ("default")))
#elif defined(__APPLE__) && defined(__MACH__)
/* Apple OSX and iOS (Darwin). */
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE == 1 || TARGET_OS_SIMULATOR == 1
#define DAON_EXPORT  __attribute__ ((visibility ("default")))
#else
#define DAON_EXPORT 
#endif
#else
#define DAON_EXPORT 
#endif
#endif

class DAON_EXPORT DaonIDCaptureException : public std::exception
{
public:

    const static int ERR_CONFIG_FILE_READ = 0x4b05f1bc;  // error reading config XML
    const static int ERR_DOCUMENT_CONFIG = 0x87944ee6;  // error in config struct
    const static int ERR_DOCUMENT_FACE_INIT = 0x4be50f8e;  // face detector intialisation error
    const static int ERR_DOCUMENT_FACE_PROC = 0x4be84dd4;  // face detector processing error
    const static int ERR_DOCUMENT_FRAMEPROC = 0xd44833ff;  // frame processing error
    const static int ERR_DOCUMENT_IMAGE = 0x25bb5517;  // problem with image provided to feature extractor
    const static int ERR_DOCUMENT_IMAGEREAD = 0x7f73432d;  // error reading document image
    const static int ERR_DOCUMENT_IMGPROC = 0xa4934a55;  // image processing error
    const static int ERR_DOCUMENT_INIT = 0x19fdcdb4;  // error initialising IDCapture API
    const static int ERR_DOCUMENT_INPUT = 0x25bc0386;  // invalid input parameter
    const static int ERR_DOCUMENT_PREPROC = 0x1f4af535;  // image pre-processing error
    const static int ERR_DOCUMENT_SEARCH = 0xa24f314c;  // error in search-box struct
    const static int ERR_EYE_DISTANCE_CALCULATION = 0x36de36cd;  // error calculating eye-distance measure
    const static int ERR_FACE_DETECTION = 0x554d1303;  // error detecting face in the image data
    const static int ERR_FACE_LANDMARKS = 0x195604b9;  // error extracting face landmarks
    const static int ERR_FACE_TRACK_INIT = 0xf24fac6;  // error initializing face track
    const static int ERR_FACE_TRACK_UPDATE = 0xee6534ff;  // error updating face track
    const static int ERR_FRAME_SIZE = 0xe8ca7b3;  // error frame size consistency
    const static int ERR_IMAGE_FORMAT = 0x3d266f7b;  // unsupported image format
    const static int ERR_IMAGE_OPEN = 0xc8abb2ce;  // error opening image
    const static int ERR_IMAGE_ORIENTATION = 0x9d4c98ac;  // unknown image orientation
    const static int ERR_IMAGE_READ = 0xc8ace61a;  // error reading image
    const static int ERR_IMAGE_SIZE = 0xc8ad6c85;  // invalid image size
    const static int ERR_IMAGE_WRITE = 0x4d3c5bbb;  // error writing image
    const static int ERR_JNI = 0x11f85;  // Android/JNI errors
    const static int ERR_MODEL_FILE = 0x9c1f20f2;  // error in model file loading
    const static int ERR_NO_MODEL_FILE = 0xe8bb7a30;  // model file not found
    const static int ERR_REGION_OF_INTEREST_EXTRACTION = 0x72d1435f;  // error extracting the region of interest
    const static int ERR_SYS_ALLOC = 0xfbf1db03;  // allocation error
    const static int ERR_UNKNOWN = 0x19d1382a;  // unknown error thrown
    const static int ERR_VIDEO_OPEN = 0xbe3c3bae;  // error opening video file
    const static int ERR_VIDEO_READ = 0xbe3d6efa;  // error readiing video
    const static int ERR_WRONG_USAGE = 0x93c4404f;

    static std::string errorToString(int err) { 
        switch (err) {
            case ERR_CONFIG_FILE_READ: return "ERR_CONFIG_FILE_READ";
            case ERR_DOCUMENT_CONFIG: return "ERR_DOCUMENT_CONFIG";
            case ERR_DOCUMENT_FACE_INIT: return "ERR_DOCUMENT_FACE_INIT";
            case ERR_DOCUMENT_FACE_PROC: return "ERR_DOCUMENT_FACE_PROC";
            case ERR_DOCUMENT_FRAMEPROC: return "ERR_DOCUMENT_FRAMEPROC";
            case ERR_DOCUMENT_IMAGE: return "ERR_DOCUMENT_IMAGE";
            case ERR_DOCUMENT_IMAGEREAD: return "ERR_DOCUMENT_IMAGEREAD";
            case ERR_DOCUMENT_IMGPROC: return "ERR_DOCUMENT_IMGPROC";
            case ERR_DOCUMENT_INIT: return "ERR_DOCUMENT_INIT";
            case ERR_DOCUMENT_INPUT: return "ERR_DOCUMENT_INPUT";
            case ERR_DOCUMENT_PREPROC: return "ERR_DOCUMENT_PREPROC";
            case ERR_DOCUMENT_SEARCH: return "ERR_DOCUMENT_SEARCH";
            case ERR_EYE_DISTANCE_CALCULATION: return "ERR_EYE_DISTANCE_CALCULATION";
            case ERR_FACE_DETECTION: return "ERR_FACE_DETECTION";
            case ERR_FACE_LANDMARKS: return "ERR_FACE_LANDMARKS";
            case ERR_FACE_TRACK_INIT: return "ERR_FACE_TRACK_INIT";
            case ERR_FACE_TRACK_UPDATE: return "ERR_FACE_TRACK_UPDATE";
            case ERR_FRAME_SIZE: return "ERR_FRAME_SIZE";
            case ERR_IMAGE_FORMAT: return "ERR_IMAGE_FORMAT";
            case ERR_IMAGE_OPEN: return "ERR_IMAGE_OPEN";
            case ERR_IMAGE_ORIENTATION: return "ERR_IMAGE_ORIENTATION";
            case ERR_IMAGE_READ: return "ERR_IMAGE_READ";
            case ERR_IMAGE_SIZE: return "ERR_IMAGE_SIZE";
            case ERR_IMAGE_WRITE: return "ERR_IMAGE_WRITE";
            case ERR_JNI: return "ERR_JNI";
            case ERR_MODEL_FILE: return "ERR_MODEL_FILE";
            case ERR_NO_MODEL_FILE: return "ERR_NO_MODEL_FILE";
            case ERR_REGION_OF_INTEREST_EXTRACTION: return "ERR_REGION_OF_INTEREST_EXTRACTION";
            case ERR_SYS_ALLOC: return "ERR_SYS_ALLOC";
            case ERR_UNKNOWN: return "ERR_UNKNOWN";
            case ERR_VIDEO_OPEN: return "ERR_VIDEO_OPEN";
            case ERR_VIDEO_READ: return "ERR_VIDEO_READ";
            case ERR_WRONG_USAGE: return "ERR_WRONG_USAGE";
            default: return "Unknown";
        }
    }
	
	DaonIDCaptureException();
    
	DaonIDCaptureException(int errCode);
    
    // Need a copy constructor, because the runtime of the compiler is allowed to insist on it when it throws an object of this type, even if it doesn't actually make a copy. When I make
    // a copy, I need to capture whatever is in the stringstream object. Note: in many cases, attempting to copy an iostream object leads to errors, so the copy constructor here
    // constructs a brand new mstream object.
	DaonIDCaptureException(const DaonIDCaptureException &that);
    
    // Virtual dtor needed? Not really, but here it is anyway.
    virtual ~DaonIDCaptureException() throw () { };
    
    // When I finally get this object to an exception handler, (hopefully catching by reference) I want to display the error message that I've inserted. To do that, I just capture whatever
    // is in the mWhat string object concatenated with anything that might be in the stringstring mStream object, and return it. (Odds are that only one of them will contain anything,
    // depending on whether or not the copy constructor was called.
    const char *what() const throw ();
    
    const int errorCode();
    
    // The template function used to create insertion operators for all of the various types of objects one might insert into this guy.
    template<typename T> DaonIDCaptureException& operator<<(const T& t)
    {
        m_ssStream << t;
        return *this;
    }
    
private:
    mutable std::stringstream m_ssStream;
    mutable std::string m_strWhat;
    int m_errCode;
};


#endif // DAON_IDCAPTURE_EXCEPTION_H
