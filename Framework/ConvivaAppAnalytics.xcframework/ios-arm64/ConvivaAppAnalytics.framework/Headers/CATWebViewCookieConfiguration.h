//
//  CATWebViewCookieConfiguration.h
//  Snowplow
//
//  Copyright (c) 2013-2026 Conviva, Inc. All rights reserved.
//
//  Models the `clid_sync.wv_cke` sub-node:
//
//      "clid_sync": {
//          "wv_cke":  { "en": true, "domains": [".example.com", ".partner.com"] },
//          "wv_brdg": { "en": true }
//      }
//
//  Defaults (when neither app config nor remote config supplies a value):
//      en       = YES
//      domains  = @[]   (no domains to seed; reconciliation will delete any
//                         previously-written cookies and write nothing —
//                         functionally equivalent to the kill-switch path.)
//
//  This type is consumed only as the `wv_cke` sub-node of
//  `CATClientIdSyncConfiguration`. Host apps must wrap it in a
//  `CATClientIdSyncConfiguration` and pass that to
//  `createTracker(... configurations:)`; a standalone
//  `CATWebViewCookieConfiguration` is not recognised by the
//  service-provider / remote-config merge paths and will be ignored.
//
//  Merge contract (see `CATRemoteConfigMgr -mergeClientConfigs:withRemoteConfig:`):
//    * Remote values override only the fields the remote payload actually
//      sent (`enPresent` / `domains.count > 0`).
//    * Missing or empty `domains` from remote preserves the existing
//      app-supplied (or cached) value.
//

#import "CATConfiguration.h"

#if SNOWPLOW_TARGET_IOS

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATWebViewCookieConfiguration)
@interface CATWebViewCookieConfiguration : CATConfiguration

/// Master enable flag for the cookie-injection channel.
@property (nonatomic, assign) BOOL en;

/// Domains on which the SDK should seed the CLID cookie. Wire shape is
/// preserved faithfully here; downstream consumers are responsible for
/// filtering out nil / empty / whitespace-only entries before use.
@property (nonatomic, copy) NSArray<NSString *> *domains;

/// Default initialiser (en=YES, domains=@[]).
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END

#endif
