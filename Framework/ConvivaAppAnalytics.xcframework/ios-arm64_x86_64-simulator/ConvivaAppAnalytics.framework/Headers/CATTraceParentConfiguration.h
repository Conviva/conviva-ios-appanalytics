//
//  CATTraceParentConfiguration.m
//  Pods
//
//  Created by Butchi Peddi on 02/26/24.
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

@class CATNetworkReqTrackingConfiguration;

NS_SWIFT_NAME(CATTraceParentConfigurationProtocol)
@protocol CATTraceParentConfigurationProtocol

@property(assign, nonatomic) BOOL enabled;

@property(assign, nonatomic) BOOL force;

@property(copy, nullable) NSArray* targetUrl;

@end

@interface CATTraceParentConfiguration : CATConfiguration <CATTraceParentConfigurationProtocol>

- (instancetype) init;

- (BOOL) isTraceparentURLMatching:(NSString*)url;

- (BOOL) shallAddTraceparentHeaderToUrl:(NSString*)url;

SP_BUILDER_DECLARE(BOOL, enabled)

SP_BUILDER_DECLARE(BOOL, force)

SP_BUILDER_DECLARE(NSArray *, targetUrl)

@end

NS_ASSUME_NONNULL_END
