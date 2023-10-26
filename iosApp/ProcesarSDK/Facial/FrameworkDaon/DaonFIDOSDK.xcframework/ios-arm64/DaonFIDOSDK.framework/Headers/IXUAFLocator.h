/*!
 @header IXUAFLocator
 Locator
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


typedef void (^Block)(CLLocation* location);

@interface IXUAFLocator : NSObject <CLLocationManagerDelegate>
{
	CLLocationManager *locationmanager;
    CLLocation *currentLocation;
    id delegate;
    BOOL locating;

}

+ (IXUAFLocator*) sharedInstance;

/*!
 @brief Run locator for 30 seconds
 */
- (void) locate;

/*!
 @brief Start locator
 @param accuracy The location accuracy.
 @param timeout The location timeout in seconds.
 */
- (void) locateWithAccuracy:(CLLocationAccuracy)accuracy timeout:(NSTimeInterval)timeout;

/*!
 @brief Stop locating
 */
- (void) cancelUpdatingLocation; 

/*!
 @brief Get current location
 @discussion This method should be called after a call to locate or locateWithAccuracy:timout. 
 */
- (CLLocation*) location;

@end
