//
//  DASAuthenticatorBase.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 11/9/16.
//  Copyright © 2016 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>
#import <DaonAuthenticatorSDK/DASAuthenticatorError.h>

// Forward Declarations
@protocol DASAuthenticatorContext;
@protocol DASAuthenticatorDelegate;
@protocol DASCaptureControllerProtocol;
@protocol DASStorageProvider;
@class DASAuthenticatorCollectorInfo;
@class DASDefaultContext;

/*!
 @typedef DASAuthenticatorUIAction
 @brief Categorizes the different UI actions that an authenticator can perform.
 @constant DASAuthenticatorUIActionNone         Default.
 @constant DASAuthenticatorUIActionRegister     Registration is in progress.
 @constant DASAuthenticatorUIActionAuthenticate Authentication is in progress.
 */
typedef NS_ENUM (NSUInteger, DASAuthenticatorUIAction)
{
    DASAuthenticatorUIActionNone           = 0,
    DASAuthenticatorUIActionRegister       = 1,
    DASAuthenticatorUIActionAuthenticate   = 2
};

/*!
 @brief A base class for all classes wishing to provide @link DASAuthenticator @/link behavior.
 */
@interface DASAuthenticatorBase : NSObject <DASAuthenticator>
{
    @protected
        /*!
         @brief The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
         */
        id<DASAuthenticatorContext> context;

        /*!
         @brief The current action that is taking place.
         */
        DASAuthenticatorUIAction currentUIAction;
    
        /*!
         @brief The @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator events.
         */
        id<DASAuthenticatorDelegate> currentDelegate;
    
        /*!
         @brief The @link DASCaptureControllerProtocol @/link derived object that is currently executing custom client capture code.
         */
        id<DASCaptureControllerProtocol> currentCaptureController;
    
        /*!
         @brief A @link DASStorageProvider @/link derived object responsible for providing key management and storage capabilities.
         */
        id<DASStorageProvider> storageProvider;

        /*!
         @brief The key name (NSString) that was provided to the @link register:extensions:delegate: @/link method.
         */
        NSString *currentKey;
    
        /*!
         @brief The key names (NSString) that were provided to the @link authenticate:extensions:delegate: @/link method.
         */
        NSArray *currentKeys;
    
        /*!
         @brief The time at which the current registration or authentication started.
         */
        NSDate *currentStartTime;
    
        /*!
         @brief The @link DASAuthenticatorSigningAlgorithm @/link type that was provided at instantiation.
         */
        DASAuthenticatorSigningAlgorithm signingAlgorithm;
    
        /*!
         @brief Whether or not the authenticator has been invalidated (had its keys removed). This currently only happens when the device Touch/Face ID enrollment has been changed outside of your application.
         */
        BOOL invalidated;
    
        /*!
         @brief Whether or not the authenticator already had registration data available when @link register:extensions:delegate: @/link was called. This will be the case when FIDO is being used with multiple accounts.
         */
        BOOL hadDataBeforeRegister;
}

/*!
 @functiongroup Instantiation
 */

/*!
 @brief Instantiates a new @link DASAuthenticatorBase @/link object.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing the authenticators key.
 @return A new @link DASAuthenticatorBase @/link object.
 */
- (id) initWithAlgorithm:(DASAuthenticatorSigningAlgorithm)algorithm;



/*!
 @functiongroup Images
 */

/*!
 @brief Loads the authenticator icon.
 @param name The name of the icon.
 @return A UIImage for the named image, or a default one.
 */
- (UIImage*) loadIconWithName:(NSString*)name;



/*!
 @functiongroup State
 */

/*!
 @brief Removes all encrypted data files associated with this authenticator.
 */
- (void) clearEnrolledData;

/*!
 @brief Determines if there are encrypted data files associated with this authenticator.
 */
- (BOOL) isDataStored;



/*!
 @functiongroup Collection
 */

/*!
 @brief Instantiates a new @link DASAuthenticatorCollectorInfo @/link object with information for a specific registration / authenticator event.
 @discussion The @link createCollectionUIWithContext:delegate: @/link method will pass through the following steps in order to determine which UIViewController should be stored in the new @link DASAuthenticatorCollectorInfo @/link object:
 1) Calls @link onViewControllerForFactor:context: @/link to see if the client has implemented the method and has provided a custom UIViewController.
 2) If #1 is nil, calls the newer @link onCollectionViewControllerForFactor:context: @/link method to see if the client has implemented the method and has provided a custom UIViewController and whether they will be responsible for presentation.
 3) If #2 is nil, checks to see if the client has provided a modified version of our default UIViewController for the current authenticator.
 4) If #3 is nil, uses our default UIViewController for the current authenticator.
 @param context The @link DASAuthenticatorContext @/link object with which a custom view controller can register or authenticate.
 @param delegate The @link DASAuthenticatorDelegate @/link derived object that will be notified of authenticator events.
 @return A new @link DASAuthenticatorCollectorInfo @/link object.
 */
- (DASAuthenticatorCollectorInfo*) createCollectionUIWithContext:(id<DASAuthenticatorContext>)context delegate:(id<DASAuthenticatorDelegate>)delegate;

/*!
 @brief Attempts to present the UIViewController for the current authenticator.
 @discussion Calls @link createCollectionUIWithContext:delegate: @/link to create the @link DASAuthenticatorCollectorInfo @/link object then either presents the contained UIViewController as the root of a UINavigationController or lets the client display it themselves.
 @param hostViewController The UIViewController from which to present the authenticator UIViewController.
 */
- (void) attemptUIPresentationFromHost:(UIViewController*)hostViewController;

/*!
 @brief Empty method which should be implemented by all sub-classes to create the @link DASAuthenticatorContext @/link for the concrete authenticator and begin presentation using @link attemptUIPresentationFromHost: @/link.
 @param hostViewController The UIViewController from which to present the authenticator UIViewController.
 @param forRegistration YES if the user is expected to register, NO if the user is expected to authenticate.
 @param extensions An NSDictionary mapping extension keys to values (Both NSString).
 @param keys An NSDictionary mapping @link DASAuthenticatorFactor @/link types (in NSNumber objects) to an NSArray containing the names of all keys required.
 */
- (void) presentCollectionUIOnHostVC:(UIViewController*)hostViewController forRegistration:(BOOL)forRegistration extensions:(NSDictionary*)extensions keys:(NSArray*)keys;

/*!
 @brief Builds the response extensions and provides them to either @link onRegisterComplete:extensions:keys: @/link or @link onAuthenticateComplete:keys: @/link to complete the current registration or authentication.
 */
- (void) onCollectionCompletion;

/*!
 @brief Completes the current registration or authentication with an error by calling @link onFailed:code:message: @/link.
 @param errorObject The NSError that caused the failure. If error code is @link DASAuthenticatorErrorCancelled @/link and registration is in progress, Any newly registered keys will be cleaned up (unregistered).
 */
- (void) onCollectionFailureWithErrorObject:(NSError*)errorObject;
    
@end
