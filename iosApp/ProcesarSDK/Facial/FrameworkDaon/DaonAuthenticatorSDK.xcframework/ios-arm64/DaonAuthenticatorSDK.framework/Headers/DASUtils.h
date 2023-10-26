//
//  DASUtils.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/7/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

/*!
 @brief Provides a number of common utility methods that can be used across the SDK and in custom view controllers.
 */
@interface DASUtils : NSObject

/*!
 @functiongroup Bundles
 */

/*!
 @brief Returns all of the bundles available to the application.
 @return An NSArray of all NSBundle objects contained within the application installation.
*/
+ (NSArray<NSBundle*>*) allBundles;

/*!
 @brief Searches through all available bundles and returns the file path to the specified resource.
 @param resource The file name of the resource.
 @param resourceType The file type of the resource.
 @return The file path to the requested resource.
 */
+ (NSString*) getPathInAllBundlesForResource:(NSString*)resource ofType:(NSString*)resourceType;

/*!
 @brief Searches through all available bundles and returns the bundle that contains the specified resource.
 @param resource The file name of the resource.
 @param resourceType The file type of the resource.
 @return The NSBundle that contains the requested resource.
 */
+ (NSBundle*) bundleForResource:(NSString*)resource ofType:(NSString*)resourceType;



/*!
 @functiongroup Localisation
 */

/*!
 @brief Searches through all available bundles and returns the localisation for a specified key.
 @param key The localisation key. See the DAS-Localizable.strings file for all potential keys and values.
 @return The localized NSString.
 */
+ (NSString*) localise:(NSString*)key;



/*!
 @functiongroup Errors
 */

/*!
 @brief Returns the localized error message for a specific @link DASAuthenticatorError @/link type.
 @param error The @link DASAuthenticatorError @/link error.
 @return An NSString with the localized error message for the @link DASAuthenticatorError @/link type.
 */
+ (NSString*) stringForError:(DASAuthenticatorError)error;

/*!
 @brief Creates a new NSError object for an @link DASAuthenticatorError @/link error with the default localized error message.
 @param error The @link DASAuthenticatorError @/link error.
 @return An NSError with the @link DASAuthenticatorError @/link error and localized message.
 */
+ (NSError*) errorForError:(DASAuthenticatorError)error;

/*!
 @brief Creates a new NSError object for an @link DASAuthenticatorError @/link error with a custom message.
 @param error The @link DASAuthenticatorError @/link error.
 @param description The string to use as the NSLocalizedDescriptionKey value.
 @return An NSError with the @link DASAuthenticatorError @/link error and custom message.
 */
+ (NSError*) errorForError:(DASAuthenticatorError)error description:(NSString*)description;

/*!
 @brief Creates a new NSError object for an @link DASAuthenticatorError @/link error whose localisation includes a string format specifier.
 @param error The @link DASAuthenticatorError @/link error.
 @param value The integer to use in the error localisation.
 @return An NSError with the @link DASAuthenticatorError @/link error and localized message.
 */
+ (NSError*) errorForError:(DASAuthenticatorError)error integerArgument:(NSInteger)value;

/*!
 @brief Converts a Local Authentication error into a @link DASAuthenticatorError @/link error.
 @param localAuthError The Local Authentication error to convert.
 @return An NSError with the correct @link DASAuthenticatorError @/link error and localized message. If no valid error is found, then the Local Authentication error is returned.
 */
+ (NSError*) errorForLocalAuthError:(NSError*)localAuthError;

/*!
 @brief Pulls out an errors underlying error if available, or returns the passed in error.
 @param error The error that potentially has an underlying error.
 @return If present, the NSError contained in the userInfo dictionary (under the NSUnderlyingErrorKey) for the passed in error. If not present it will return the passed in error.
 */
+ (NSError*) underlyingErrorForError:(NSError*)error;

/*!
 @brief Determines whether or not a client error should be transmitted to the server for an ADoS authentication. Typically
 this will be for errors the server has no way to know about such as timeouts.
 @param error The error that occurred.
 @return YES if the error should be reported to the server.
 */
+ (BOOL) reportADoSErrorToServer:(NSError*)error;



/*!
 @functiongroup Images
 */

/*!
 @brief Searches through all available bundles and returns the first image with a specified name.
 @param imageName The name of the image to find.
 @return The loaded image.
 */
+ (UIImage*) loadImageNamed:(NSString*)imageName;

/*!
 @brief Base64 decode an image string.
 @param encodedImage The image Base64 encoded to a string.
 @return The decoded UIImage.
 */
+ (UIImage*) base64DecodeImage:(NSString*)encodedImage;

/*!
 @brief Rotates an image to a specific orientation.
 @param image The image to rotate.
 @param orientation The requested image orientation.
 @return The rotated image.
 */
+ (UIImage*) rotateImage:(UIImage*)image toOrientation:(UIImageOrientation)orientation;

/*!
 @brief Resizes an image to a specific size.
 @param image The image to resize.
 @param newSize The requested image size.
 @return The resized image.
 */
+ (UIImage*) resizeImage:(UIImage*)image toSize:(CGSize)newSize;



/*!
@functiongroup Video
*/

/*!
 @brief Determines the current AVCaptureVideoOrientation for new video setup based on the status bar orientation.
 @return The current AVCaptureVideoOrientation.
 */
+ (AVCaptureVideoOrientation) videoOrientation;



/*!
 @functiongroup Device Information
 */

/*!
 @brief Determines if the current device is running iOS 9 and above.
 @return YES if the iOS version is >= 9.
 */
+ (BOOL) isIos9AndAbove;

/*!
 @brief Determines if the current device is running iOS 11 and above.
 @return YES if the iOS version is >= 11.
 */
+ (BOOL) isIos11AndAbove;

/*!
 @brief Determines if the current devices platform version.
 @return The platform version, e.g. "iPhone10,3"
 */
+ (NSString*) devicePlatform;

/*!
 @brief Determines if the current supports the secure enclave.
 @return YES if the secure enclave is available.
 */
+ (BOOL) deviceSupportsSecureEnclave;

/*!
 @brief Determines if Touch ID is supported by the current device.
 @return YES if biometrics are available.
 */
+ (BOOL) isTouchIDSupported;

/*!
 @brief Determines if Touch ID is currently enabled.
  @return YES if biometrics are available and the current LAContext biometryType is LABiometryTypeTouchID or iOS version is < 11.
 */
+ (BOOL) isTouchIDEnabled;

/*!
 @brief Determines if Face ID is supported by the current device.
 @return YES if Face ID is currently enabled or supported by the device.
 */
+ (BOOL) isFaceIDSupported;

/*!
 @brief Determines if Face ID is currently enabled.
 @return YES if the current LAContext biometryType is LABiometryTypeFaceID.
 */
+ (BOOL) isFaceIDEnabled;

/*!
@brief Determines if dark mode has been enabled on the device.
@return YES if dark mode is enabled.
*/
+ (BOOL) isDarkModeEnabled;



/*!
 @functiongroup View Controllers
 */

/*!
 @brief Attempts to determine the current visible UIViewController, which can then be used for presenting authenticator UIViewController.
 @return The UIViewController that the SDK believes authenticator UIViewController's should be presented from.
 */
+ (UIViewController*) determineHostViewController;

/*!
 @brief Overrides @link determineHostViewController @/link to explicitly declare the host UIViewController.
 @param viewController The UIViewController to set as the host.
 */
+ (void) setHostViewController:(UIViewController*)viewController;

/*!
 @brief Presents a given UIViewController as the root of a host UIViewController.
 @param viewController The UIViewController to present.
 @param hostViewController The UIViewController from which to present the UINavigationController.
 */
+ (void) presentNavigationControllerWithRoot:(UIViewController*)viewController fromHost:(UIViewController*)hostViewController;



/*!
 @functiongroup Tokens
 */

/*!
 @brief Generates a token.
 @return The generated token
 */
+ (NSString*) generateAuthToken;



/*!
 @functiongroup Extensions
 */

/*!
 @brief Generates the standard set of response extensions.
 @param startDate The time that registration / authentication began.
 @param currentExtensions The request extensions.
 @param authenticator The authenticator that was used.
 @param addAuthToken Whether or not to include an auth token.
 @param addLockInfo Whether to include the current authenticator state information.
 @return An NSDictionary mapping extension keys to values (Both NSString).
 */
+ (NSMutableDictionary*) buildReturnExtensionsWithStartTime:(NSDate*)startDate
                                          currentExtensions:(NSDictionary*)currentExtensions
                                              authenticator:(id<DASAuthenticator>)authenticator
                                               addAuthToken:(BOOL)addAuthToken
                                                addLockInfo:(BOOL)addLockInfo
                                               addErrorInfo:(NSError*)error;

/*!
 @brief Determines the correct response extension value for a @link DASAuthenticatorProtection @/link type.
 @param protection The @link DASAuthenticatorProtection @/link type.
 @return An NSString containing the value string depending on the protection type.
 */
+ (NSString*) extensionForKeyStoreType:(DASAuthenticatorProtection)protection;

/*!
 @brief Determines the correct response extension value for a @link DASAuthenticatorDataStore @/link type.
 @param dataStore The @link DASAuthenticatorDataStore @/link type.
 @return An NSString containing the value string depending on the dataStore type.
 */
+ (NSString*) extensionForDataStoreType:(DASAuthenticatorDataStore)dataStore;

/*!
 @brief Determines the correct response extension value for a @link DASAuthenticatorLockState @/link type.
 @param lockState The @link DASAuthenticatorLockState @/link type.
 @return An NSString containing the value string depending on the lockState type.
 */
+ (NSString*) extensionForLockState:(DASAuthenticatorLockState)lockState;


/*!
 @functiongroup Factors
 */

/*!
 @brief Determines whether a particular @link DASAuthenticatorFactor @/link type supports ADoS.
 @param factor The @link DASAuthenticatorFactor @/link type to check.
 @return YES if ADoS is supported.
 */
+ (BOOL) isADoSFactor:(DASAuthenticatorFactor)factor;

/*!
 @brief Determines whether a particular @link DASAuthenticatorFactor @/link type requires Local Authentication (Touch ID or Face ID).
 @param factor The @link DASAuthenticatorFactor @/link type to check.
 @param version The version of the authenticator that supports the given factor.
 @return YES if Local Authentication is supported.
 */
+ (BOOL) isLocalAuthenticatorFactor:(DASAuthenticatorFactor)factor version:(NSInteger)version;



/*!
 @functiongroup App-Extension Safe Methods (Work when "Require Only App-Extension-Safe API" flag is used)
 */

/*!
 @brief Sets whether the idle timer is disabled for the app.
 @param disabled A Boolean value that controls whether the idle timer is disabled for the app.
 */
+ (void) setIdleTimerDisabled:(BOOL)disabled;


/*!
 @brief Gets the current orientation of the app's status bar.
 @return The current orientation of the app's status bar.
 */
+ (UIInterfaceOrientation) statusBarOrientation;


/*!
 @functiongroup UI Constraints
 */

/*!
 @brief Adds constraints to a view which enforces that a child view is the same size as it's container view.
 @param view The view the constraint will be added to.
 @param containerView The view that has the size we want.
 @param childView The child view that needs to be made the same size as containerView.
 */
+ (void) addConstrainEqualConstraintToView:(UIView*)view containerView:(UIView*)containerView childView:(UIView*)childView;

@end
