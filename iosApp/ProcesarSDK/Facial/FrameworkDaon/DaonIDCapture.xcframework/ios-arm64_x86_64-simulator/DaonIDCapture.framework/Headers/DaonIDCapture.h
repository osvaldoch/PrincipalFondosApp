#ifndef DAON_ID_CAPTURE_API
#define DAON_ID_CAPTURE_API

#include <vector>
#include <string>

#include "DaonIDCaptureException.h"

#ifdef __ANDROID__
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <fstream>

#elif defined(__APPLE__) && defined(__MACH__)
/* Apple OSX and iOS (Darwin). */
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE == 1
// iOS
#elif TARGET_OS_MAC == 1
#define DFQ_IMAGE_API_ENABLED
#endif
#else
#define DCP_IMAGE_API_ENABLED
#endif


#ifdef __ANDROID__

#ifndef PNG_USE_ARM_NEON
#define PNG_USE_ARM_NEON
#endif // !PNG_USE_ARM_NEON


#endif // __ANDROID__

class DaonIDCapture {
public:

	// preset docuement shapes
	static constexpr double ID_CARD = 1.5858;
	static constexpr double	PASSPORT = 1.4205;
	static constexpr double A4_PORT = 0.7071;
	static constexpr double A4_LAND = 1.4143;
	static constexpr double VERT_ID_CARD = 1 / ID_CARD;
	// other shapes can be set using DaonIDConfiguration.setIDShape(width,height);

	static const char* version() noexcept;

	struct SearchBox {
		// to restrict the edge search to a particular region wthin the frame
		// if x = -1 and y = -1 (default initialisation), then the entire frame will be searched
	public:
		int x {-1};
		int y {-1};
		int width {-1};
		int height {-1};

		SearchBox() {
		}

		SearchBox(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
		}
	};

	struct DocumentPoints {
		// to run quality algorithm on pre-selected region of the frame 
	public:
		int UpperLeft_x{ 0 };
		int UpperLeft_y{ 0 };
		int UpperRight_x{ 0 };
		int UpperRight_y{ 0 };
		int LowerRight_x{ 0 };
		int LowerRight_y{ 0 };
		int LowerLeft_x{ 0 };
		int LowerLeft_y{ 0 };

		DocumentPoints() {
		}
	};

	struct DaonIDConfiguration {
	private:
		std::vector<double> IDShape{ ID_CARD };	// list of expected ID shapes (default = ID1 Card only)
		double IDPhotoShape{ 0.75 };
		bool failFast{ true };	// exit quality algorithm if basic geometric checks fail, skipping glare/blur detection (default = true)
		bool enforceFace{ false }; // fail the document if no face is found inside the document area
#if !defined(__ANDROID__) && !defined(__APPLE__)
		bool enableBarcodeReading{ false };// fail the document if no barcode is found inside the document area
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
		bool returnAllImages{ false };
		bool fullQuality{ true };
		int paddingWidth{ 10 };
		int paddingColor{ 0 };	// default to black
		float croppingTolerance{ 0 };
		//int DPI{ 300 };	// min DPI of returned image
		int minDPI{ 0 }; // min DPI of returned image
		int maxDPI{ 0 }; // max DPI of returned image

#if !defined(__ANDROID__) && !defined(__APPLE__)
		bool tryRotate{ true };
		bool tryHarder{ true };
		bool tryInvert{ false };
		bool tryDownscale{ true };
		int downscaleFactor{ 3 };
		int downscaleThreshold{ 1000 };
		int maxNumberOfSymbols{ 1 };
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
#ifdef EXTRA_PREPROC
		bool extraPreProc = false;
#endif // EXTRA_PREPROC
	public:
		void setIDShape(std::vector<double> tmp_IDShapes);
		void setIDShape(double tmp_IDShape);
		void setIDShape(int width, int height); // set the width and height of the target document
		void setIDPhotoShape(int width, int height);
		void setIDPhotoShape(double);
		void setFailFast(bool tmp_failFast);
		void setEnforceFace(bool tmp_enforceFace);
#if !defined(__ANDROID__) && !defined(__APPLE__)
		void setEnableBarcodeReading(bool tmp_enableBarcodeReading);
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
		void setReturnAllImages(bool tmp_returnAllImages);
		void setFullQuality(bool tmp_fullQuality);
		void setIDPaddingWidth(int p);
		void setIDPaddingColor(int c);
		void setIDCroppingTolerance(float t);
		void setDPImin(int dpi);
		void setDPImax(int dpi);

#if !defined(__ANDROID__) && !defined(__APPLE__)
		void setTryRotate(bool tmp_tryRotate);
		void setTryHarder(bool tmp_tryHarder);
		void setTryInvert(bool tmp_tryInvert);
		void setTryDownscale(bool tmp_tryDownscale);
		void setDownscaleFactor(int tmp_downscaleFactor);
		void setDownscaleThreshold(int tmp_downscaleThreshold);
		void setMaxNumberOfSymbols(int tmp_maxNumberOfSymbols);
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
#ifdef EXTRA_PREPROC
		void setExtraPreProc(bool preproc);
#endif

		void addIDShape(int width, int height); // set the width and height of the target document
		void addIDShape(double tmp_IDShape); // set the aspect ratio of the target document

		static bool testIDShape(std::vector<double> tmp_IDShapes);
		static bool testIDShape(double tmp_IDShape);
		static bool testIDShape(int width, int height);
		static bool testIDPhotoShape(int width, int height);
		static bool testIDPhotoShape(double);
		static bool testIDPaddingWidth(int p);
		static bool testIDPaddingColor(int c);
		static bool testIDCroppingTolerance(float t);
		static bool testDPImin(int dpi);

		std::vector<double> getIDShape() const;
		double getIDPhotoShape() const;
		bool getFailFast() const;	// exit quality algorithm if basic geometric checks fail, skipping glare/blur detection (default = true)
		bool getEnforceFace() const; // fail the document if no face is found inside the document area
#if !defined(__ANDROID__) && !defined(__APPLE__)
		bool getEnableBarcodeReading() const;
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
		bool getReturnAllImages() const;
		bool getFullQuality() const;
		int getPaddingWidth() const;
		int getIDPaddingColor() const;
		float getCroppingTolerance() const;
		int getDPImin() const;
		int getDPImax() const;
#if !defined(__ANDROID__) && !defined(__APPLE__)
		bool getTryRotate() const;
		bool getTryHarder() const;
		bool getTryInvert() const;
		bool getTryDownscale() const;
		int getDownscaleFactor() const;
		int getDownscaleThreshold() const;
		int getMaxNumberOfSymbols() const;
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)
#ifdef EXTRA_PREPROC
		bool getExtraPreProc() const;
#endif
	};


	struct DaonIDResult {
		// result struct
	public:
		bool isAvailable{ false };
		int UpperLeftX{ 0 };
		int UpperLeftY{ 0 };
		int UpperRightX{ 0 };
		int UpperRightY{ 0 };
		int LowerRightX{ 0 };
		int LowerRightY{ 0 };
		int LowerLeftX{ 0 };
		int LowerLeftY{ 0 };

#if !defined(__ANDROID__) && !defined(__APPLE__)
		struct Barcode {
		public:
			bool isFound{ false };
			int UpperLeftX{ 0 };
			int UpperLeftY{ 0 };
			int UpperRightX{ 0 };
			int UpperRightY{ 0 };
			int LowerLeftX{ 0 };
			int LowerLeftY{ 0 };
			int LowerRightX{ 0 };
			int LowerRightY{ 0 };
			std::string Text{ "" };
			double Orientation{ 0 };
			std::string ECLevel{ "" };
			bool isMirrored{ false };
			bool isInverted{ false };
		} barcode;
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)

		struct Quality {
			// documetn quality - scores set to -1 if unavaialble
		public:
			bool isAvailable{ false };
			double Summary{ -1 };
			// "Geometric Quality" - how does shape of the document fit expected shape?
			double AspectRatio{ -1 };
			double Size{ -1 };
			double VertDistort{ -1 };
			double HorizDistort{ -1 };
			double MinInternalAngle{ -1 };
			double MaxInternalAngle{ -1 };
			double SumInternalAngle{ -1 };
			// "Appearance Quality" - how clear is the appearnce of the document?
			double GlareAdaptive{ -1 };
			double GlareFixed{ -1 };
			double LocalBlur{ -1 };
			double GlobalBlur{ -1 };
			// Supplemental quality measures relating to OCR DPI requirements
			// DPI (dots per inch) scores require knowledge about the real-world width of the document.
			// Therefore, DPI score is only valid if id type is set to ID_CARD, VERT_ID_CARD, or PASSPORT
			// For use-defined shapes, the API does not know the real-world width, and so cannot make a DPI calculation.
			int IDSourceWidth{ -1 };		// width (pixels) of doucment in source image
			int IDSourceHeight{ -1 };		// height (pixels) of document in source image
			int DPIsource{ -1 };			// DPI of document in source image
			int IDDewarpedWidth{ -1 };		// width (pixels) of dewarped document image (excluding padding)
			int IDDewarpedHeight{ -1 };		// height (pixels) of dewarped document image (excluding padding)
			int DPIdewarped{ -1 };			// DPI of dewarped image

		} quality;

		struct Face {
			// face co-ordinates are relative to dewarped ID document.
		public:
			bool isFound{ false };
			int UpperLeftX{ 0 };
			int UpperLeftY{ 0 };
			int LowerRightX{ 0 };
			int LowerRightY{ 0 };
		} face;
	};


	// initialise and clean up:
	DaonIDCapture(std::string DFQ_dir);
#ifdef __ANDROID__
	DaonIDCapture(const AAssetManager *assetManager, std::string DFQ_dir);
#endif
	~DaonIDCapture();
	
	//process frame:
	// this will locate ID document and perform quality checks from raw image input
	// perform quality checks on a previously located id
	// unsigned char *pix_buff - Raw Pixel Data Array
	// long width - Upright Frame Width(actual frame width, irrespective of the Raw Pixel Array Format)
	// long height - Upright Frame Height(actual frame width, irrespective of the Raw Pixel Array Format)
	// int orientation - Raw Image Data Rotation
	//
	//		orientation == "0" = > raw pixel array corresponds to the "upright" image, so no rotation correction is applied
	//		orientation == "1" = > raw pixel array is rotated 90 degrees clockwise rotation
	//		orientation == "2" = > raw pixel array is rotated 90 degrees counterclockwise rotation(specific to iOS devices)
	//
	// int format - Raw Image Data Format
	//
	//		format == "0" = > 8 bit grayscale
	//		format == "1" = > RGB(1 byte each for Red, Green, Blue)
	//		format == "2" = > RGBA(1 byte each for Red, Green, Blue, Alpha)
	//
	// DaonIDConfiguration configParams  - struct containing config parameters (see above for details)
	//
	// const SearchBox &searchRange - specify a search box within the frame where the ID is expected to be found
	//	
	// Returns DaonIDResult - result struct contining result for current frame
	DaonIDResult processRawFrame(
		unsigned char *pix_buff, long width, long height, int orientation, int format,	// pixel buffer
		const DaonIDConfiguration &configParams,	// configuration
		const SearchBox &searchRange = SearchBox()	// search range
	);

	// perform quality checks on a previously located id
	// unsigned char *pix_buff - Raw Pixel Data Array
	// long width - Upright Frame Width(actual frame width, irrespective of the Raw Pixel Array Format)
	// long height - Upright Frame Height(actual frame width, irrespective of the Raw Pixel Array Format)
	// int orientation - Raw Image Data Rotation
	//
	//		orientation == "0" = > raw pixel array corresponds to the "upright" image, so no rotation correction is applied
	//		orientation == "1" = > raw pixel array is rotated 90 degrees clockwise rotation
	//		orientation == "2" = > raw pixel array is rotated 90 degrees counterclockwise rotation(specific to iOS devices)
	//
	// int format - Raw Image Data Format
	//
	//		format == "0" = > 8 bit grayscale
	//		format == "1" = > RGB(1 byte each for Red, Green, Blue)
	//		format == "2" = > RGBA(1 byte each for Red, Green, Blue, Alpha)
	//
	// DaonIDConfiguration configParams  - struct containing config parameters (see above for details)
	//
	// DocumentPoints idCorners - id corner locations.
	//					If idCorners not provided then analyse the whole image
	//
	// Returns DaonIDResult - result struct contining result for current frame
	DaonIDResult processQuality(
		unsigned char *pix_buff, long width, long height, int orientation, int format,	// pixel buffer
		const DaonIDConfiguration &configParams,	// configuration
		DocumentPoints idCorners
	);
	DaonIDResult processQuality(
		unsigned char *pix_buff, long width, long height, int orientation, int format,	// pixel buffer
		const DaonIDConfiguration &configParams	// configuration
	);
	

#ifndef EMSCRIPTEN
#ifdef DCP_IMAGE_API_ENABLED
	// locate ID document and perform quality checks on encoded JPEG 
	// SearchBox &searchRange  - optional search range to apply to frame
	//						if searchRange not provided, search full frame
	//						if searchRange provided, search only inside this area
	//						will throw a DaonIDCaptureException if searchRange is outside range of jpeg image
	DaonIDResult processEncodedFrame(
		char *pix_buff, int len,
		const DaonIDConfiguration &configParams
	);
	DaonIDResult processEncodedFrame(
		char *pix_buff, int len,
		const DaonIDConfiguration &configParams,
		const SearchBox &searchRange
	);
	DaonIDResult processEncodedFrame(
		unsigned char *pix_buff, int len,
		const DaonIDConfiguration &configParams,
		const SearchBox &searchRange = SearchBox()
	);

	// perform quality checks on a previously located id from encoded JPEG
	// this will throw a DaonIDCaptureException if id location is outside range of jpeg image
	DaonIDResult processQuality(
		unsigned char *pix_buff, int len,	// pixel buffer
		const DaonIDConfiguration &configParams,	// configuration
		DocumentPoints idCorners		// id position {upperLeft_x, upperLeft_y, upperRight_x, upperRight_y, lowerRight_x, lowerRight_y, lowerLeft_x, lowerLeft_y};
	);
	DaonIDResult processQuality(
		char *pix_buff, int len,	// pixel buffer
		const DaonIDConfiguration &configParams,	// configuration
		DocumentPoints idCorners		// id position {upperLeft_x, upperLeft_y, upperRight_x, upperRight_y, lowerRight_x, lowerRight_y, lowerLeft_x, lowerLeft_y};
	);
	DaonIDResult processQuality(
		unsigned char *pix_buff, int len,	// pixel buffer
		const DaonIDConfiguration &configParams	// configuration
	);
	DaonIDResult processQuality(
		char *pix_buff, int len,	// pixel buffer
		const DaonIDConfiguration &configParams	// configuration
	);
#endif
#endif // !EMSCRIPTEN


	// "Video" processing
	//
	// Off by default when class is initialised.
	//
	// when video processing is turned on:
	//			on each call to processFrame(), the frame result is compared to the previous stored result.
	//			If the new result has higher quality than the previous result, then the stored result is updated. Otherwise, the new
	//			result is discarded.
	// when video processsing is off:
	//			on each call to processFrame() the previous result is cleared. If the result of the current frame  meets the minimum
	//			quality requirements, then a successful result is recorded. 
	//
	// Clear the current stored result and initialises result tracking.
	void startVideoProcess();
	void stopVideoProcess();

	// Methods to return results
	// 
	// If no candidate document was found:
	//		all co-ordinate results will return 0
	//		and all quality results will return -1
	//
	// If a document candidate was found, but this candidate fails internal quality checks:
	//		co-ordinate results will return candidate position
	//		some geometric quality (aspect ratio, size, etc) results may be available
	//		appearance quality (blur, glare, etc) will return -1
	//
	bool isResultAvailable();	// is a docuemnt result available
	bool isResultUpdated();		// if video processing on, was the internal best result updated with most recent frame?
	// document co-ordinates
	int getUpperLeftX();
	int getUpperLeftY();
	int getUpperRightX();
	int getUpperRightY();
	int getLowerRightX();
	int getLowerRightY();
	int getLowerLeftX();
	int getLowerLeftY();

	// API provides option to run full (geometric + appearance) or partial (geometric only) quality analysis
	// API provides option to exit full analysis early if basic checks fail
	// Returns true if full qualaity analysis was performed
	// Returns false if geometric only was run, or if algrithm exited early due to failed basic check 
	//		in this case, some geometric quality scores may be available
	bool isQualityAvailable();
	// document quality
	double getQuality_Summary();
	// "Geometric Quality" - how does shape of the document fit expected shape?
	double getQuality_AspectRatio();
	double getQuality_Size();
	double getQuality_VertDistort();
	double getQuality_HorizDistort();
	double getQuality_MinInternalAngle();
	double getQuality_MaxInternalAngle();
	double getQuality_SumInternalAngle();
	// "Appearance Quality" - how clear is the appearnce of the document?
	double getQuality_GlareAdaptive();
	double getQuality_GlareFixed();
	double getQuality_LocalBlur();
	// Supplemental quality measures relating to OCR DPI requirements
	// DPI (dots per inch) scores require knowledge about the real-world width of the document.
	// Therefore, DPI score is only valid if id type is set to ID_CARD, VERT_ID_CARD, or PASSPORT
	// For use-defined shapes, the API does not know the real-world width, and so cannot make a DPI calculation.
	int getQuality_IDSourceWidth();		// width (pixels) of doucment in source image
	int getQuality_IDSourceHeight();	// height (pixels) of document in source image
	int getQuality_DPIsource();			// DPI of document in source image
	int getQuality_IDDewarpedWidth();	// width (pixels) of dewarped document image (excluding padding)
	int getQuality_IDDewarpedHeight();	// height (pixels) of dewarped document image (excluding padding)
	int getQuality_DPIdewarped();		// DPI of dewarped image

	// face co-ordinates are relative to dewarped ID document.
	bool isFaceFound();
	int getFace_UpperLeftX();
	int getFace_UpperLeftY();
	int getFace_LowerRightX();
	int getFace_LowerRightY();

	int getIDWidth();
	int getIDHeight();

#if !defined(__ANDROID__) && !defined(__APPLE__)
	bool isBarcodeFound();
	int getBarcode_UpperLeftX();
	int getBarcode_UpperLeftY();
	int getBarcode_UpperRightX();
	int getBarcode_UpperRightY();
	int getBarcode_LowerLeftX();
	int getBarcode_LowerLeftY();
	int getBarcode_LowerRightX();
	int getBarcode_LowerRightY();
	std::string getBarcodeText();
	double getBarcodeOrientation();
	std::string getECLevel();
	bool isBarcodeMirrored();
	bool isBarcodeInverted();
#endif // if !defined(__ANDROID__) && !defined(__APPLE__)

	// get image that was input to process frame function
	// In the case that video processing is turned on, this returns the input frame corresponding to the 
	// current saved result, which may not be the most recently processed frame.
	// If this is called before an image has been provided to the API (either through a call 
	// to  processFrame() or to processQuality()) then this function will throw a DaonIDCaptureException
	std::vector<unsigned char> getFullFrameJPEG(int qfactor = 95);
	std::vector<unsigned char> getFullFramePNG();

	// get cropped docuemnt image (no dewarping applied) encoded as JPEG
	// if result is not available, this will return an empty vector
	// int qfactor - jpeg quality factor (default = 95)
	//				should be in the range [1,100]
	//				100 = highest quality, least compression
	//				1 = lowest  quality, most compression
	std::vector<unsigned char> getCroppedIDJPEG(int qfactor = 95);
	// get cropped docuemnt image (no dewarping applied) encoded as PNG
	// if result is not available, this will return an empty vector
	std::vector<unsigned char> getCroppedIDPNG();

	// get dewarped docuemnt image (corrected for rotation/perspective distortion) encoded as JPEG
	// if result is not available, this will return an empty vector
	// int qfactor - jpeg quality factor (default = 95)
	//				should be in the range [1,100]
	//				100 = highest quality, least compression
	//				1 = lowest  quality, most compression
	std::vector<unsigned char> getDewarpedIDJPEG(int qfactor = 95);
	// get dewarped docuemnt image (corrected for rotation/perspective distortion) encoded as PNG
	// if result is not available, this will return an empty vector
	std::vector<unsigned char> getDewarpedIDPNG();

	// get id photo image (cropped from dewarped id image) encoded as JPEG
	// if result is not available, this will return an empty vector
	// double growBox - exted the cropped region to include more background area
	//				should be >=0
	//				growBox = 0 => tightly cropped face
	//				growBox = r, where r >0 => add r*width to croppign width and r*height to cropping height  
	// int qfactor - jpeg quality factor (default = 95)
	//				should be in the range [1,100]
	//				100 = highest quality, least compression
	//				1 = lowest  quality, most compression
	std::vector<unsigned char> getFaceJPEG(double growBox = 0, int qfactor = 95);
	// get id photo image (cropped from dewarped id image) encoded as PNG
	// if result is not available, this will return an empty vector
	// double growBox - exted the cropped region to include more background area
	//				should be >=0
	//				growBox = 0 => tightly cropped face
	//				growBox = r, where r >0 => add r*width to croppign width and r*height to cropping height  
	std::vector<unsigned char> getFacePNG(double growBox = 0);

#if defined(WIN32) && defined(RESEARCH) && defined(USE_OPENCV)
	bool processVideoFile(const char *fname, const DaonIDConfiguration &configParams, int rot = 0, int n = 15);
#endif

private:

	class impl;
	impl* pImpl;
};

#endif