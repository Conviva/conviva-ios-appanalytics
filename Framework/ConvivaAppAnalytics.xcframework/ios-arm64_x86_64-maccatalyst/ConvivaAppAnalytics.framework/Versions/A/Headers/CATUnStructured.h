//
//  CATUnStructured.h
//  iOSConvivaSDK
//
//  Created by Butchi Peddi on 04/02/22.
//  Copyright © 2022 Conviva. All rights reserved.
//

#import "CATEventBase.h"

NS_ASSUME_NONNULL_BEGIN

/// A structured event.
NS_SWIFT_NAME(CATUnStructured)
@interface CATUnStructured : CATSelfDescribingAbstract

@property (nonatomic, readonly) NSString *data;
@property (nonatomic, readonly) NSString *name;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString*)name data:(NSString *)data;

SP_BUILDER_DECLARE_NULLABLE(NSString *, name)
SP_BUILDER_DECLARE_NULLABLE(NSString *, data)

@end

NS_ASSUME_NONNULL_END
