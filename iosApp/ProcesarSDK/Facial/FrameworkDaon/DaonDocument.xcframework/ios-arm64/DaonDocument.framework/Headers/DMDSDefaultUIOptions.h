
#import <UIKit/UIKit.h>

/*!
 @abstract Settings class with all possible customizable settings for the Default UI.
 */
@interface DMDSDefaultUIOptions : NSObject <NSCopying>

/*!
 If YES, the Default UI will display the preview of the captured document.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL showScanCompleteVisualFeedback;

/*!
 If YES, the Default UI will allow manual adjustments to the cropping boundary of the document image captured.
 
 The adjustments can be made in the preview available when showScanCompleteVisualFeedback is set to YES.
 
 This will only occur when using document recognition (i.e. setting specific document typess within DMDSOptions.documentTypes.
 
 This will not occur when using direct edge detection (i.e. kEdgeDetection is set within DMDSOptions.documentTypes), or if
 DMDSOptions.fallbackToEdgeDetection is enabled, and the document is captured as a part of edge detection.

 Default: NO.
 */
@property (nonatomic, assign) BOOL allowManualCroppingDocumentRecognition;

/*!
 If YES, Default UI will allow manual adjustments to the cropping boundary of the document image captured.
 
 The adjustments can be made in the preview available when showScanCompleteVisualFeedback is set to YES.
 
 This will only occur when using edge detection (i.e. kEdgeDetection is set within DMDSOptions.documentTypes), or if
 DMDSOptions.fallbackToEdgeDetection is enabled, and the document is captured as a part of edge detection.
 
 This will not occur when using document recognition (i.e. setting specific document types within DMDSOptions.documentTypes).
 
 Default: NO.
 */
@property (nonatomic, assign) BOOL allowManualCroppingEdgeDetection;

/*!
 If YES, the Default UI will play a camera sound and vibrate when the document has been successfully captured.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL playScanCompleteVisualAudioFeedback;

/*!
 Define the portion of the screen in which the scanning will be performed in when the device is in portrait orientation.
 
 For example:
 <pre>
 CGRectMake(0.05, 0.22, 0.9, 0.36)
 </pre>
 
 This defines a portion of the screen which starts at
    5% from the left border,
    22% from the top,
    covers 90% of screen width,
    and 36% of screen height.
 
 Default: CGRectMake(0.05, 0.22, 0.9, 0.36).
 */
@property (nonatomic, assign) CGRect portraitScanningRegion;

/*!
 Define the portion of the screen in which the scanning will be performed in when the device is in portrait orientation AND portrait document mode such as the South African Green Book document.
 
 For example:
 <pre>
 CGRectMake(0.175, 0.15, 0.65, 0.50)
 </pre>
 
 This defines a portion of the screen which starts at
 17.5% from the left border,
 15% from the top,
 covers 65% of screen width,
 and 50% of screen height.
 
 Default: CGRectMake(0.175, 0.15, 0.65, 0.50).
 */
@property (nonatomic, assign) CGRect portraitPortraitScanningRegion;
    
/*!
 Define the portion of the screen in which the scanning will be performed in when the device is in landscape orientation.
 
 For example:
 <pre>
 CGRectMake(0.15, 0.05, 0.65, 0.77)
 </pre>
 
 This defines a portion of the screen which starts at
    15% from the left border,
    5% from the top,
    covers 65% of screen width,
    and 77% of screen height.
 
 Default: CGRectMake(0.15, 0.05, 0.65, 0.77).
 */
@property (nonatomic, assign) CGRect landscapeScanningRegion;

/*!
 With this property you can hide the scanning region corners.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL showBoundary;

/*!
 If YES, the Default UI will show real-time scanning feedback by displaying a border around the edges of a document (and MRZ if applicable) when it is detected.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL showScanningFeedback;

/*!
 If YES, the Default UI will display a cancel button during scanning, and in the preview/cropping screen if showScanCompleteVisualFeedback is enabled.
 
 If the view controller is displayed inside a navigation view controller, this is reasonable to set to NO to allow the user to use the buttons in the navigation bar.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL showCancelButton;

/*!
 If YES, the Default UI will display a torch button.
 
 Default: YES.
 */
@property (nonatomic, assign) BOOL showTorchButton;

/*!
 Outline color of the document (and MRZ if applicable) border overlay color displayed during the scanning process.
 
 This is only relevant if showScanningFeedback is enabled.
 
 This also controls the outline color of the document within the preview screen when cropping is enabled.
 
 Default: [UIColor colorWithRed: 34/255.0 green: 139/255.0 blue: 34/255.0 alpha: 1].
 */
@property (nonnull, nonatomic, strong) UIColor *overlayColor;

/*!
 Scanning region corner color.
 
 Default: [UIColor whiteColor].
 */
@property (nonnull, nonatomic, strong) UIColor *rectangleColor;

/*!
 Scanning region corner line thickness in points.
 
 Default: 3.
 */
@property (nonatomic, assign) int rectangleCornerThickness;

/*!
 Scanning region corner line lenght in points.
 
 Default: 16.
 */
@property (nonatomic, assign) int rectangleCornerLength;

/*!
 Message label font for the label displayed beneath the scanning region.
 
 Default: [UIFont systemFontOfSize: 18].
 */
@property (nonnull, nonatomic, strong) UIFont *messageTextFont;

/*!
 Message text for the label displayed beneath the scanning region describing what actions to perform.
 
 Default: "Line up your identity document to fit in frame."
 */
@property (nonnull, nonatomic, strong) NSString *instructionsMessage;

/*!
 Message text to be appended to the label displayed beneath the scanning region alerting the user when we have switched back to edge detection after the scanningDuration timeout.
 
 Default: "\n\nFell back to edge detection."
 */
@property (nullable, nonatomic, strong) NSString *fellBackToEdgeDetectionMessage;

/*!
 Message text to be appended to the label displayed beneath the scanning region alerting the user that glare has been detected.
 
 Default: "\n\nGlare detected - please slightly move document to eliminate glare."
 */
@property (nullable, nonatomic, strong) NSString *glareDetectedMessage;

/*!
 Message text for the label displayed beneath the scanning region once a document has been captured.
 
 Default: "Document captured".
 */
@property (nonnull, nonatomic, strong) NSString *capturedMessage;

/*!
 Message label color for the label displayed beneath the scanning region.
 
 Default: [UIColor whiteColor].
 */
@property (nonnull, nonatomic, strong) UIColor *messageTextColor;

/*!
 Cancel button font.
 
 Default: [UIFont systemFontOfSize: 14].
 */
@property (nonnull, nonatomic, strong) UIFont *cancelButtonTextFont;

/*!
 Cancel button color.
 
 Default: [UIColor whiteColor].
 */
@property (nonnull, nonatomic, strong) UIColor *cancelButtonTextColor;

/*!
 Bottom bar color for all screens.
 
 Default: [UIColor blackColor].
 */
@property (nonnull, nonatomic, strong) UIColor *bottomBarColor;

/*!
 Color of the space around the scanning region.
 
 Default: [[UIColor blackColor] colorWithAlphaComponent: 0.7].
 */
@property (nonnull, nonatomic, strong) UIColor *scanningBorderColor;

/*!
 Initialises DMDSDefaultCameraOptions with default values.
 
 See individual properties for default values.
 
 @return Initialised DMDSDefaultCameraOptions object.
 */
- (nonnull instancetype)init;

/*!
 @abstract Return the description of the relevant properties of this object at runtime for debugging purposes.
 */
- (NSString * _Nonnull)description;

@end
