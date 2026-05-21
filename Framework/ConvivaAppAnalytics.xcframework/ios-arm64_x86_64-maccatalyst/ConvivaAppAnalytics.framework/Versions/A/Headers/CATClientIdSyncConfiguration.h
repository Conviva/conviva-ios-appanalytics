//
//  CATClientIdSyncConfiguration.h
//  Snowplow
//
//  Copyright (c) 2013-2026 Conviva, Inc. All rights reserved.
//
//  Models the `clid_sync` node that controls propagation of the native
//  Client ID into in-app WebViews:
//
//      "clid_sync": {
//          "wv_cke":  { "en": true, "domains": [".example.com"] },
//          "wv_brdg": { "en": true }
//      }
//
//  This type can be supplied by the host app via
//  `createTracker(... configurations:)`. Until remote config arrives, the
//  app's values apply. Once remote config arrives, remote values override
//  only the fields the remote payload actually sent — fields/sub-nodes
//  that the remote payload omits remain at the app-supplied (or default)
//  values.
//

#import "CATConfiguration.h"

#if SNOWPLOW_TARGET_IOS

@class CATWebViewCookieConfiguration;
@class CATWebViewBridgeConfiguration;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATClientIdSyncConfiguration)
@interface CATClientIdSyncConfiguration : CATConfiguration

/// Cookie-channel configuration. Never `nil` once initialised.
@property (nonatomic, strong) CATWebViewCookieConfiguration *wvCke;

/// JavaScript-bridge channel configuration. Never `nil` once initialised.
@property (nonatomic, strong) CATWebViewBridgeConfiguration *wvBrdg;

/// Default initialiser. Builds default `wvCke` / `wvBrdg` sub-configs.
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END

#endif
