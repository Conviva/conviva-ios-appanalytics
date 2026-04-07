# Conviva iOS App Analytics - Troubleshooting

Companion to AGENTS.md. Read only when a build failure or runtime issue occurs.

---

## Supported HTTP Clients

| Client | Supported |
|---|---|
| `NSURLSession` | Yes |
| `NSURLConnection` | Yes |
| Third-party libraries built on `NSURLSession` / `NSURLConnection` | Yes |
| `AVPlayer` (default implementation) | No |
| `URL.getContent()` / custom stream-based | No |

---

## Request / Response Body Collection

Collected only when all conditions are true:

| Condition | Detail |
|---|---|
| Size | < 10 KB and `Content-Length` present |
| Content-Type | `application/json` or `text/plain` |
| Format | `NSDictionary`, nested `NSDictionary`, or `NSArray` |

---

## Request / Response Header Collection

Collected only when all conditions are true:

| Condition | Detail |
|---|---|
| Format | `NSDictionary` only (nested `NSDictionary` and `NSArray` not supported) |

---

## Common Issues

**Issue 1 - Build fails: "Undefined symbols" or "No such module 'ConvivaAppAnalytics'"**
Fix: Verify the framework is properly linked. For SPM / Manual install, ensure `UIKit`, `Foundation`, and `CoreTelephony` (iOS only) are added under Build Phases -> Link Binary With Libraries. Ensure `-ObjC` is set in Other Linker Flags.

**Issue 2 - Build fails: "Use of unresolved identifier 'CATAppAnalytics'"**
Fix: Add the correct import at the top of the file:
- Swift: `import ConvivaAppAnalytics`
- ObjC: `@import ConvivaAppAnalytics;`

**Issue 3 - Wrong initialization API used**
Fix: Use only `CATAppAnalytics.createTracker(customerKey:appName:)` (Swift) or `[CATAppAnalytics createTrackerWithCustomerKey:appName:]` (ObjC). Do not use the `namespace:customerKey:network:configurations:` variant or pass any configuration objects.

**Issue 4 - SwiftUI button_click / screen_view events not appearing**
Fix: Auto-collection of `button_click` and `screen_view` is not supported in SwiftUI. Use `.convivaAnalyticsButtonClick(title:)` on Button views and `.convivaAnalyticsScreenView(name:)` on screen-level views. See AGENTS-swift.md -> "SwiftUI".

**Issue 5 - Runtime crash in multi-SDK app (ISA-swizzling conflict)**
Fix: Add `CATGeneratedClassDisposeDisabled` as a Boolean with value `YES` in the app's `Info.plist`. This prevents crashes when multiple SDKs use ISA-swizzling (e.g. Firebase, Conviva Video Sensor).

**Issue 6 - AVPlayer network requests not captured**
This is a known limitation. Auto-collection of network requests from the default `AVPlayer` implementation is not supported.

**Issue 7 - CocoaPods: "Unable to find a specification for 'ConvivaAppAnalytics'"**
Fix: Run `pod repo update` to refresh the local spec repo. Verify the exact version string from GitHub Releases.

**Issue 8 - Events not appearing in Pulse dashboard**
Fix: Verify `CUSTOMER_KEY` is correct and matches the environment (dev vs prod). Check network connectivity. Validate at Pulse App -> Activation Module -> Live Lens.
