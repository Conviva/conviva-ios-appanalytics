//
//  CATClickConfiguration.h
//  Pods
//
//  Created by Shubham Kumar Gupta on 06/01/25.
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"
#import "CATConditionalCollectionConfiguration.h"

NS_SWIFT_NAME(CATClickConfigurationProtocol)
@protocol CATClickConfigurationProtocol

/**
 * Whether to enable or disable click tracking
 */
@property () BOOL en;

@end

NS_ASSUME_NONNULL_BEGIN
NS_SWIFT_NAME(CATClickConfiguration)
@interface CATClickConfiguration : CATConditionalCollectionConfiguration<CATClickConfigurationProtocol>

/**
 * It sets a default TrackerConfiguration.
 * Default values:
 *         en = true;
 */

- (instancetype)init;

- (instancetype) initWithDictionary:(NSDictionary<NSString *, NSObject *> *)dict;

- (id)copyWithZone:(nullable NSZone *)zone;

/**
 * Whether to enable or disable click tracking.
 */
SP_BUILDER_DECLARE(BOOL, en)

@end

NS_ASSUME_NONNULL_END
