//
//  CATCustomEventTrackingConfiguration.m
//  Pods
//
//  Created by Butchi Peddi on 04/08/22.
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

@interface CATNetworkReqTrackingConfiguration : CATConfiguration

@property(strong, readonly) NSArray *blocklist;

- (instancetype) initWithBlocklist:(NSArray *)blocklist;

- (instancetype) initWithDictionary:(NSDictionary<NSString *, NSObject *> *)dict;

- (id)copyWithZone:(nullable NSZone *)zone;

- (BOOL) allBlocked;

- (BOOL) isBlockedEndpoint:(NSString*)endpoint;

- (void) setBlocklistItems:(NSArray * _Nonnull)blocklist;

@end

NS_ASSUME_NONNULL_END
