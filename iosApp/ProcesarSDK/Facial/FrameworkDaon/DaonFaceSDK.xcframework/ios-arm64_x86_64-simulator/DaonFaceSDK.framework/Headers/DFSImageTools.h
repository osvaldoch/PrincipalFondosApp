//
//  DFSImageTools.h
//  DaonFaceSDK
//
//  Created by Jonny Mortensen on 3/4/14.
//  Copyright (c) 2014-2015 Daon. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 * @header DFSImageTools
 * @discussion The DFSImageTools object provides methods for converting and manipulating images.
 *
 * <pre>
 * @textblock
 * // Grayscale and crop
 *
 * - (void) verifyImage:(CVPixelBufferRef)image didUpdateWithInfo:(NSDictionary*)info {
 *
 *  CGRect rect = [info[kFaceRectangleKey] CGRectValue];
 *  if (!CGRectIsEmpty(rect)) {
 *      UIImage *img = [DFSImageTools imageWithPixelBuffer:image];
 *      UIImage* gray = [DFSImageTools grayscaleImage:img];
 *      UIImage* crop = [DFSImageTools cropImage:gray toRect:rect];
 *  }
 *}
 * @/textblock
 * </pre>
 */

@interface DFSImageTools : NSObject

/*!
 * @abstract Creates and returns an image object from the contents of a CVPixelBuffer object.
 * @param pixelBuffer The pixel buffer
 * @return An image object initialized with the contents of the image buffer object.
 */
+ (UIImage*) imageWithPixelBuffer:(CVPixelBufferRef)pixelBuffer;

/*!
 * @abstract Creates and returns an image object from the contents of YUV data.
 * @param data The YUV buffer
 * @param size The image size
 * @return An image object initialized with the contents of the image buffer object.
 */
+ (UIImage*) imageWithData:(NSData*)data imageSize:(CGSize)size;

/*!
 * @abstract Creates and returns an image object from a Core Image object.
 * @param ciImage The Core Image object
 * @return A UIImage object
 */
+ (UIImage*) imageWithCIImage:(CIImage*)ciImage;

/*!
 * @abstract Creates and returns an CVPixelBuffer reference from a Core Image object.
 * @param image The Core Image object
 * @return A CVPixelBuffer reference
 * @discussion The necessary memory is allocated based on the pixel dimensions, format, and extended pixels
 * described in the pixel buffer’s attributes. Call CVPixelBufferRelease() when done with this buffer.
 */
+ (CVPixelBufferRef) createPixelBufferWithImage:(CIImage *)image;

/*!
 * @abstract Creates and returns 8 bit channel data.
 * @param image The image object
 * @param channelIndex The channel index, e.g. R = 0, G = 1, B = 2, A = 3
 * @return A byte array with the given channel data
 * @discussion The necessary memory is allocated based on the pixel dimensions. Call free() when done with the data.
 */
+ (unsigned char*) createEightBitDataFromImage:(UIImage*)image channel:(int)channelIndex;

/*!
 * @abstract Creates and returns an image object from the contents of an 8 bit byte array.
 * @param raw A byte array with image data, e.g, a single channel
 * @param len The length of the byte array
 * @param size The image size (width and height)
 * @return An image object initialized with the contents of the byte array.
 */
+ (UIImage*) imageWithEightBitGrayscaleData:(unsigned char*)raw length:(size_t)len imageSize:(CGSize)size;

/*!
 * @abstract Creates and returns an image object from an RGBA byte array.
 * @param raw A byte array with RGBA image data
 * @param len The length of the byte array
 * @param size The image size (width and height)
 * @return An image object initialized with the contents of the byte array.
 */
+ (UIImage*) imageWithRGBData:(unsigned char*)raw length:(NSUInteger)len imageSize:(CGSize)size;


/*!
* @abstract Creates and returns the 32 bit RGBA or 24-bit RGB data.
* @param image The image object
* @return A byte array with RGB(A) data
* @discussion The necessary memory is allocated based on the pixel dimensions.
*/
+ (NSData*) RGBDataWithImage:(UIImage*)image;

/*!
 * @abstract Determines if an image has an alpha channel
 * @param image The image
 * @return True if the image contains alpha data
 */
+ (BOOL) hasAlpha: (UIImage*)image;

/*!
 * @abstract Removes transparency from an image object.
 * @param image The image object
 * @return A byte array with R data
 */
+ (UIImage*) removeTransparency:(UIImage*)image;

/*!
 * @abstract Apply a mask to an image.
 * @param image The image object
 * @param maskImage The image object with the mask.
 * @return An image object with the mask applied.
 */
+ (UIImage*) maskImage:(UIImage *)image withMask:(UIImage *)maskImage;

/*!
 * @abstract Crop image.
 * @param image The image object.
 * @param rect The area to crop.
 * @return An image object with the content and size of the provided rectangle.
 */

+ (UIImage*) cropImage:(UIImage*)image toRect:(CGRect)rect;


/*!
 * @abstract Create a grayscale image from an image object.
 * @param image The image object
 * @return An image object as grayscale.
 */
+ (UIImage*) grayscaleImage:(UIImage*)image;


/*!
 * @abstract Rotate image.
 * @param image The image object
 * @param degrees The number of degress to rotate
 * @return A rotated image object.
 */
+ (UIImage*) rotateImage:(UIImage*)image degrees:(int)degrees;

/*!
 * @abstract Rotate image.
 * @param image The image object
 * @param orientation The UIImageOrientation to rotate to.
 * @return A rotated image object.
 */
+ (UIImage*) rotateImage:(UIImage*)image toOrientation:(UIImageOrientation)orientation;

/*!
 * @abstract Scale image.
 * @param image The image object
 * @param newSize The new size of the image
 * @return A scaled image object.
 */
+ (UIImage*) scaleImage:(UIImage*)image size:(CGSize)newSize;

/*!
 * @abstract Determines if an image meets an expected size requirement
 * @param image The image
 * @param expectedSize The size we expect the image to be
 * @return Whether or not the given image is of the correct size.
 */
+ (BOOL) isImage:(UIImage*)image correctSize:(CGSize)expectedSize;

/*!
 * @abstract Determines if a pixel buffer meets an expected size requirement
 * @param pixelBuffer The pixel buffer
 * @param expectedSize The size we expect the pixel buffer to be
 * @return Whether or not the given pixel buffer is of the correct size.
 */
+ (BOOL) isPixelBuffer:(CVPixelBufferRef)pixelBuffer correctSize:(CGSize)expectedSize;

/*!
 * @abstract Creates a copy of a CVPixelBufferRef's data, this duplicates the data, not the reference
 * The user is responsible for calling CVPixelBufferRelease on the object
 * @param pixelBuffer the pixel buffer to copy
 */
+ (CVPixelBufferRef) createDuplicatePixelBuffer:(CVPixelBufferRef)pixelBuffer;

/*!
 * @abstract Returns the number of degrees the image is rotated counter clock-wise
 * from UIInterfaceOrientationLandscapeLeft
 * @param orientation the UIInterfaceOrientation
 */
+ (int) rotationDegreesForOrientation:(UIInterfaceOrientation)orientation;

+ (UIImage *) adjustImage:(UIImage*)image;

+ (NSArray<UIImage*>*) splitImage:(UIImage *)image segments:(int)segments padding:(float)padding;

@end

