//
//  DASMetadataControllerDelegate.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 2/13/19.
//  Copyright © 2019 Daon. All rights reserved.
//

#ifndef DASMetadataControllerDelegate_h
#define DASMetadataControllerDelegate_h

/*!
 @brief A protocol for classes that wish to be notified of metadata scanning events from an @link DASMetadataControllerProtocol @/link derived object.
 */
@protocol DASMetadataControllerDelegate <DASControllerProtocol>

/*!
 @brief Used to notify a conforming object that metadata scanning has started.
*/
- (void) metadataControllerScanningStarted;

/*!
 @brief Used to notify a conforming object that metadata scanning completed successfully.
 @param image An image of the metadata object that was scanned.
 @param contents The UT8 encoded contents of the metadata object that was scanned.
 */
- (void) metadataControllerCompletedWithImage:(UIImage*)image contents:(NSData*)contents;

/*!
 @brief Used to notify a conforming object that metadata scanning failed with an error.
 @param error The error that caused scanning to fail.
 */
- (void) metadataControllerCompletedWithError:(NSError*)error;

@end

#endif /* DASMetadataControllerDelegate_h */

