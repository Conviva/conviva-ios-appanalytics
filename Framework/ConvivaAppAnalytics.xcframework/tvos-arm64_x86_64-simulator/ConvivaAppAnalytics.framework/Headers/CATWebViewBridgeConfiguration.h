//
//  CATWebViewBridgeConfiguration.h
//  Snowplow
//
//  Copyright (c) 2013-2026 Conviva, Inc. All rights reserved.
//
//  Models the `clid_sync.wv_brdg` sub-node:
//
//      "clid_sync": {
//          "wv_cke":  { "en": true, "domains": [...] },
//          "wv_brdg": { "en": true }
//      }
//
//  Default (when neither app config nor remote config supplies a value):
//      en = YES
//
//  This type is consumed only as the `wv_brdg` sub-node of
//  `CATClientIdSyncConfiguration`. Host apps must wrap it in a
//  `CATClientIdSyncConfiguration` and pass that to
//  `createTracker(... configurations:)`; a standalone
//  `CATWebViewBridgeConfiguration` is not recognised by the
//  service-provider / remote-config merge paths and will be ignored.
//
//  Merge contract (see `CATRemoteConfigMgr -mergeClientConfigs:withRemoteConfig:`):
//    Remote `en` overrides the app/cached value only when the remote
//    payload actually carried the field (`enPresent == YES`); otherwise
//    the existing app-supplied (or cached) value is preserved.
//

#import "CATConfiguration.h"

#if SNOWPLOW_TARGET_IOS

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATWebViewBridgeConfiguration)
@interface CATWebViewBridgeConfiguration : CATConfiguration

/// Master enable flag for the JavaScript-bridge channel.
@property (nonatomic, assign) BOOL en;

/// Default initialiser (en=YES).
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END

#endif
