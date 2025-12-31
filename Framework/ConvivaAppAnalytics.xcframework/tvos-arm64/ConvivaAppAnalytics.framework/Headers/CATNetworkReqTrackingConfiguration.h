//
//  CATCustomEventTrackingConfiguration.m
//  Pods
//
//  Created by Butchi Peddi on 04/08/22.
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"
#import "CATConditionalCollectionConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

@interface CATNetworkReqTrackingConfiguration : CATConditionalCollectionConfiguration

@property(assign, readonly) BOOL enabled;

@property(assign, readonly) int32_t rbl; //max supported request/response body length in KB

@property(assign, readonly) int32_t maxQueryLength; //max supported request query params length in KB

@property(strong, readonly) NSArray *blocklist;

@property(strong, readonly) NSArray *collectattr;

@property (assign, readwrite) BOOL isRQBCollectionEnabled;

@property (assign, readwrite) BOOL isRSBCollectionEnabled;

- (instancetype) initWithBlocklist:(NSArray *)blocklist;

- (instancetype) initWithDictionary:(NSDictionary<NSString *, NSObject *> *)dict;

- (id)copyWithZone:(nullable NSZone *)zone;

- (BOOL) allBlocked;

- (BOOL) isBlockedEndpoint:(NSString*)endpoint;

- (void) setBlocklistItems:(NSArray * _Nonnull)blocklist;

- (BOOL) isNetworkRequestTrackingDisabled;

- (void) updateCollectAttributes;

@end

NS_ASSUME_NONNULL_END
