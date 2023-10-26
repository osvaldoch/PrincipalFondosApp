/*!
 @header IXUAFTransaction
 FIDO transaction and transaction confirmation.
 @copyright Daon. All rights reserved.
 @updated 2018-05-20
 */

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSInteger, IXUAFTransactionContentType)
{
    IXUAFTransactionContentTypeUnknown  = 0,
    IXUAFTransactionContentTypePNG      = 1,
    IXUAFTransactionContentTypeText     = 2
};

@interface IXUAFTransaction : NSObject


- (id)initWithDictionary:(NSDictionary *)dictionary;


/*!
 @brief Accept or reject transaction
 */
- (void) accept:(BOOL)accept;

/*!
 @brief Get content type
 */
- (IXUAFTransactionContentType) contentType;

/*!
 @brief Get PNG image or TEXT content
 */
- (NSData*) content;



@end
