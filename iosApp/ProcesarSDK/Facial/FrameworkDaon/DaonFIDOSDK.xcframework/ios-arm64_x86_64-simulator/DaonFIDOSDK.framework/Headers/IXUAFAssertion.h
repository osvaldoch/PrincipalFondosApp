//
//  IXUAFAssertion.h
//  DaonFIDOSDK
//
//  Created by Jonny Mortensen on 3/12/21.
//  Copyright © 2021 Jonny Mortensen. All rights reserved.
//

#ifndef IXUAFAssertion_h
#define IXUAFAssertion_h

#import "IXUAFExtensions.h"

static NSString * const IXUAFAssertionParameterContext   = @"context";
static NSString * const IXUAFAssertionParameterDelegate  = @"delegate";

@protocol IXUAFAssertion <NSObject>

- (void) signWithExtensions:(IXUAFExtensions*)extensions
                 parameters:(NSDictionary*)params
                 completion:(void (^)(NSDictionary * assertion, NSError* error))completion;

@end

#endif /* IXUAFAssertion_h */
