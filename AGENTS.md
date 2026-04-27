# Conviva iOS App Analytics - AI Integration Contract

Single source of truth. Governs: Cursor, Claude Code, Codex, ChatGPT, Gemini CLI, Copilot, Xcode AI, and all other agents. This file always wins over any conflicting documentation.

## Workflow

1. State: "I have read AGENTS.md and will follow its contract."
2. **STOP and ask the developer for all inputs in Section 3.** This is your very first action. Do not scan files, do not read code, do not write code, do not do anything else until the developer has answered all four questions. Wait for their response.
3. After receiving all four answers, seed task list from Section 15.
4. Execute Sections 4-14 in order. Every Section 15 row must appear in your response.
5. **Automate what you can:** Write all code changes yourself (imports, initialization, userId, events). For CocoaPods, edit the Podfile and run `pod install`. For SPM/Manual, edit the `.pbxproj` to add the `-ObjC` linker flag, then write all code changes, and provide SPM package/framework setup as a consolidated developer instruction block at the end. Do not ask the developer to perform steps that you can automate.
6. If you cannot proceed without violating a rule, stop and ask.

---

## 1. Non-Negotiable Rules

1. Use only APIs, imports, dependencies, and procedures defined in this file.
2. Do not invent, guess, or hallucinate Conviva APIs, class names, imports, frameworks, or configuration.
3. Do not mix instructions from other Conviva SDKs (VSI, JS, Android, legacy iOS SDKs).
4. Prompt the developer for all required inputs. Never assume or hardcode them.
5. Apply minimal, localized changes only - no refactors, no comment cleanup, no unrelated edits.
6. PII Protection: Never pass email, phone, full name, IMEI, or IP address to Conviva. Use only non-PII identifiers (opaque provider UID, account ID, stored UUID). If none found, do not implement userId tracking - ask developer (see Sections 3c, 3d, 9).
7. If you cannot proceed without violating a rule, stop and ask.
8. Never present a UI element as a trackable button candidate without first confirming it is a SwiftUI `Button` via source code inspection.

---

## 2. SDK Identity

| Field | Value |
|---|---|
| Product | Conviva DPI |
| Platform | iOS / iPadOS / tvOS |
| SDK Name | Conviva iOS App Analytics SDK |
| GitHub Repo | [Conviva/conviva-ios-appanalytics](https://github.com/Conviva/conviva-ios-appanalytics) |
| Framework | `ConvivaAppAnalytics.xcframework` |
| Module | `ConvivaAppAnalytics` |
| Min iOS | 12.0 |
| Min tvOS | 12.0 |

---

## 3. Required Inputs - STOP and Ask Before Doing Anything

**Your first action must be asking these questions.** Do not scan the project, do not read files, do not write any code until the developer has answered all four questions below. This applies to all project types: UIKit, SwiftUI, Objective-C, Swift, or mixed.

Collect all inputs from the developer in a single prompt. Use **structured selectable options** (not plain text) wherever the input has a fixed set of choices. For free-text inputs, ask the developer to provide the value.

**Selectable options (present as clickable choices):**

| Input | Options |
|---|---|
| `INSTALL_METHOD` | (a) Swift Package Manager, (b) CocoaPods, (c) Manual framework |

**Do not recommend, rank, or label any option as preferred or recommended.** Present all options neutrally and let the developer choose.

**Free-text inputs (ask developer to provide):**

| Input | Description |
|---|---|
| `CUSTOMER_KEY` | Conviva Customer Key - never guess or hardcode |
| `APP_NAME` | App name string passed to tracker initialization - never guess or hardcode |
| `SDK_VERSION` | Exact SDK version - look up the latest version from [GitHub Releases](https://github.com/Conviva/conviva-ios-appanalytics/releases) and present it to the developer as a reference (e.g. "The latest version is X.Y.Z"). The developer may confirm it or provide a different version. Never auto-select a version without the developer's confirmation. |

All four inputs are mandatory. If the developer skips any, ask again before writing code. Do not proceed without all four values.

**Do not guess or infer `CUSTOMER_KEY` or `APP_NAME`.** Do not use the Xcode project name as `APP_NAME`. Do not extract `CUSTOMER_KEY` from existing code. The developer must explicitly provide these values themselves.

---

## 3a. Project Scanning - Read Each File Once

Do not re-read a file already in context. If a prior tool call or subagent has already returned a file's content, use it from context - do not open it again.

| File | Extract | How |
|---|---|---|
| `AppDelegate.swift` or `AppDelegate.m` | Full `application(_:didFinishLaunchingWithOptions:)` method; existing imports | Partial - method body + imports only |
| SwiftUI `@main App` struct (e.g. `*App.swift`) | Full `init()` or `body` if no `init`; existing imports | Partial - `init()` + imports |
| `SceneDelegate.swift` or `SceneDelegate.m` | Check presence only | Partial - first 10 lines |
| `Podfile` | Full contents | Full (typically < 50 lines) |
| `*.xcodeproj/project.pbxproj` | Check for `ConvivaAppAnalytics` already present; locate app target `XCBuildConfiguration` sections for linker flag edits (Section 5b/5c) | Full read |
| `Package.swift` (app's, not SDK's) | Check for `ConvivaAppAnalytics` dependency | Grep only |
| `Info.plist` | Check for `CATGeneratedClassDisposeDisabled` key | Grep only |
| Any `.swift` file in app target | Check if project contains Swift files (needed for ObjC-only project detection - see Section 5d) | Grep for `*.swift` in app source dirs |
| Auth hooks (login / logout) | Every function triggering login or logout; lowest-layer convergence point per operation | Targeted - grep first, then single partial read |

**Do NOT read:** View controllers, views, storyboards, xibs, asset catalogs, test targets, any file not in the table above. Exception: auth hooks must be found regardless of which file they are in.

**Subagent scope:** Return only: AppDelegate or SwiftUI App entry point method; imports; Podfile contents; whether ConvivaAppAnalytics is already present; Info.plist CATGeneratedClassDisposeDisabled check. Do not read view controllers, views, or test files.

---

## 3b. App Lifecycle Detection

Determine which app lifecycle the project uses:

| Pattern | Detection | Initialization Point |
|---|---|---|
| **UIKit (AppDelegate)** | `AppDelegate.swift` or `AppDelegate.m` with `@UIApplicationMain` or `@main` | `application(_:didFinishLaunchingWithOptions:)` |
| **UIKit (SceneDelegate)** | `SceneDelegate.swift` present | Still use `AppDelegate.application(_:didFinishLaunchingWithOptions:)` |
| **SwiftUI** | `@main struct SomeApp: App` | `init()` of the `App` struct |

If both `AppDelegate` and SwiftUI `@main App` exist, prefer `AppDelegate` - the SwiftUI `App` may delegate to it via `@UIApplicationDelegateAdaptor`.

---

## 3c. Auth Hook Scan - Discovery Only, No Implementation Yet

Grep all `.swift` and `.m` files for:
```
(login|logout|signIn|signOut|authenticate|signup|signUp|register|createUser|createAccount)
```
Record: file path, function name, line number.

For each login / registration method: trace all callers down the call chain to the single lowest-layer function where the actual auth provider call is made. This is the **convergence point** - place `userId = ` here only. If callers share no convergence point, place the call at each independent path.

For logout: trace all callers to the single lowest-layer function where the actual provider sign-out is called. This is the convergence point - place `userId = nil` here only.

Registration / signup creates a new authenticated session - treat identically to login.

Do not read files yet - just identify convergence points. Proceed to Section 9 for implementation.

**If only PII identifiers found:** do not implement userId tracking. Report in Section 15: which methods were found, why each is unsafe, and instruct the developer: "No non-PII identifier available. Implement one of: (1) opaque provider UID, (2) custom UUID stored at first launch, (3) backend account ID. Do not use email, phone, or full name."

**Non-PII vs PII:**

| Identifier | PII? | Safe? |
|---|---|---|
| Opaque UID (Firebase UID, Auth0 ID, custom backend ID) | No | YES |
| Stored UUID (deterministic per user) | No | YES |
| Backend account ID (opaque numeric/alphanumeric) | No | YES |
| Email address | Yes | NO |
| Phone number | Yes | NO |
| Full name / display name | Yes | NO |
| IP address | Yes | NO |
| IDFA / IDFV | Yes | NO |

---

## 3d. PII Rules

Never pass to Conviva: email, phone, full name, display name, IDFA, IDFV, IP address, or any personally identifiable information. If the only available identifier is PII, stop - do not implement userId tracking. Safe alternatives: opaque provider UID, UUID stored at first launch, backend account ID.

---

## 4. Core Rules

- **Automate what you can:** Write all code changes and safe build setting edits yourself. Do not ask the developer to perform steps that you can automate. Only defer steps to the developer when they require Xcode GUI interaction or risky `.pbxproj` modifications (e.g. adding new objects with UUIDs).
- Initialize exactly once: `CATAppAnalytics.createTracker(customerKey:appName:)` - no namespace, network config, configuration arrays, builders, or extra arguments.
- Entry point: existing `AppDelegate` method `application(_:didFinishLaunchingWithOptions:)`, or SwiftUI `App.init()`. Never create a new AppDelegate.
- Insert Conviva call at the beginning of the entry point method, before any other application logic but after `super` calls (if any). In SwiftUI `App.init()`, place it as the first statement.
- Import only `ConvivaAppAnalytics` - never `ConvivaAppAnalytics.Private`, individual header names, or internal symbols.
- Set `userId` immediately after `createTracker(...)` if a non-PII identifier is available. Update on login, registration, logout, and account switch. Never use PII. If no guest identifier exists, ask developer.
- For CocoaPods: edit the `Podfile` directly to append `pod 'ConvivaAppAnalytics'` - never modify existing pods or targets. Run `pod install` yourself.
- For SPM: edit the `.pbxproj` to add `-ObjC` to `OTHER_LDFLAGS` (see Section 5b). Provide the SPM package addition as developer instructions at the end.
- For Manual: edit the `.pbxproj` to add `-ObjC` to `OTHER_LDFLAGS` (see Section 5c). Provide the framework setup as developer instructions at the end.
- **Always ensure `CATGeneratedClassDisposeDisabled = YES`** is present in the app's Info.plist (see Section 12). This is mandatory for every integration -- do not skip, do not ask, just do it. If the project has no physical `Info.plist`, do NOT create one named `Info.plist` -- follow Section 12 Scenario B to avoid "Multiple commands produce" build errors.
- **Always wrap every Conviva call in language-appropriate exception/nil handling** so AI-generated integration code can never crash the host app **and never alter host-app launch behavior**. ObjC: `@try`/`@catch (NSException *)` plus a `tracker == nil` check that only logs. Swift: assign + nil-check + log on `createTracker`; rely on optional chaining (`tracker?.x`) or `if let` for subsequent calls. See Section 4a for full rules and the per-language import requirement.

---

## 4a. Try-catch and Nil-check Requirement (mandatory)

This rule applies to every Conviva call the agent inserts: `createTracker`, `defaultTracker`, `subject.userId =`, `trackCustomEvent`, `setCustomTags`, `clearCustomTags`, `clearAllCustomTags`, `trackRevenueEvent`, and any future tracker method. AI-generated integration code MUST NOT be able to crash the host app -- wrap every call as specified below.

### Objective-C (`.m` / `.mm`)

- Wrap every Conviva call in `@try { ... } @catch (NSException *exception) { NSLog(@"... failed: %@", exception); }`.
- Inside the `@try` block, check `if (tracker == nil)` (for `defaultTracker`) or `if (tracker != nil)` (before invoking instance methods) and `NSLog` on nil. For `createTracker`, log when the returned tracker is nil but still complete the surrounding method normally.
- **Import requirement -- conditional add-if-missing:** `NSException` and `NSLog` are part of `Foundation`. Add `@import Foundation;` at the top of the file **only if the file does not already have a direct Foundation import** (`@import Foundation;` or `#import <Foundation/Foundation.h>`). Do NOT rely on transitive availability via UIKit -- add it explicitly when missing. If a direct Foundation import is already present, skip. Place `@import Foundation;` immediately above `@import ConvivaAppAnalytics;` when both are being added.

### Swift (`.swift`)

- `CATAppAnalytics.createTracker(customerKey:appName:)` is an Objective-C method that returns an optional and does NOT throw Swift errors. Use a simple nil-check (never `do/try/catch`, never `guard let ... else { return ... }`) to log a failed init.
- **Never let a Conviva init failure short-circuit host-app launch.** Do NOT use `guard let tracker = ... else { return false }` in `application(_:didFinishLaunchingWithOptions:)` -- returning `false` tells iOS the app failed to handle the launch URL/activity, which is a host-app behavior that must never depend on telemetry-SDK initialization. Do NOT use `guard let _ = ... else { return }` in a SwiftUI `App.init()` -- it would skip any subsequent initialization the developer adds.
- **Correct pattern -- log on nil, continue normally:**
  ```swift
  let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
  if tracker == nil {
      print("Conviva tracker init returned nil")
  }
  ```
- `CATAppAnalytics.defaultTracker()` also returns an optional. Use optional chaining (`tracker?.x`) for subsequent calls -- this is the Swift-idiomatic equivalent of "if not nil, do" and is a no-op when the tracker is nil. No `guard` is required for the default-tracker retrieval pattern when the snippet only chains one call.
- For multi-statement blocks that build an event (e.g. `CATRevenueEvent`, item arrays), prefer `if let tracker = CATAppAnalytics.defaultTracker() { ... }` so the construction is skipped entirely when the tracker is nil. `if let` here only skips the body of the block, not the surrounding host-app code.
- **Import requirement:** `if let`, nil-checks, and optional chaining are Swift built-ins -- no additional import is required. The only Conviva import is `import ConvivaAppAnalytics` (already governed by Section 8).

### Why this is enforced

Any AI tool integrating Conviva must produce code that cannot crash the host app even if the tracker fails to initialize, returns nil unexpectedly, or throws an Objective-C exception.

---

## 5. Installation

Use the `INSTALL_METHOD` chosen by the developer in Section 3, then apply only the matching method below. **Perform every automatable step yourself. Only defer to the developer for steps that genuinely require the Xcode GUI.**

### 5a. CocoaPods

The agent MUST perform all of these steps directly - do not ask the developer:

| Step | Agent Action |
|---|---|
| 1 | Edit the `Podfile`: append `pod 'ConvivaAppAnalytics', '<SDK_VERSION>'` inside the app target block |
| 2 | Run `pod install` in the terminal |
| 3 | Inform developer to open `.xcworkspace` instead of `.xcodeproj` (if not already) |

CocoaPods handles system framework linkage and linker flags automatically via the podspec. No build settings changes needed.

### 5b. Swift Package Manager

The agent automates the build settings edit and all code changes. The SPM package addition requires Xcode GUI and is deferred to the developer.

**Agent-automated - linker flag (do this yourself):**

1. Read the `.xcodeproj/project.pbxproj` file.
2. In the `PBXNativeTarget` section, find the app target (`productType = "com.apple.product-type.application"`). Record its UUID.
3. Find the `XCConfigurationList` for that target, then find all `XCBuildConfiguration` entries it references (typically Debug and Release).
4. In each `XCBuildConfiguration`, add `-ObjC` to `OTHER_LDFLAGS`:
   - If `OTHER_LDFLAGS` does not exist, add: `OTHER_LDFLAGS = ("-ObjC",);`
   - If it exists as a list, append `"-ObjC"` to it.
   - If it already contains `"-ObjC"`, skip.
5. After editing, run `plutil -lint <path>/project.pbxproj` to verify the file is still valid.
6. If `plutil -lint` reports errors, revert your changes and include the linker flag in the developer instructions instead.

System frameworks (`UIKit`, `Foundation`, `CoreTelephony`) are auto-linked by Xcode when modules are enabled (the default). Do not add them to `PBXFrameworksBuildPhase` unless the project has `CLANG_MODULES_AUTOLINK = NO`.

**Agent-automated - code changes (do this yourself):**

Proceed immediately through Sections 6-10: write the import, initialization, userId, and any custom event/tag code. Do not wait for the developer to complete the SPM package setup.

**MANDATORY developer instructions - SPM package (you MUST include this block in your response):**

After completing all code changes and the linker flag edit, you MUST provide the developer the exact block below. Replace `<SDK_VERSION>` with the value the developer gave you in Section 3. Do not skip this block. Do not replace it with "open Xcode" or "Xcode will auto-resolve". Do not let Xcode pick a version automatically.

```
XCODE SETUP REQUIRED (one-time):
1. File → Add Package Dependencies → enter URL:
   https://github.com/conviva/conviva-ios-appanalytics
2. Set version rule to "Exact Version" → <SDK_VERSION>
3. Add "ConvivaAppAnalytics" to your app target.
```

### 5c. Manual Install

The agent automates the build settings edit and all code changes. The developer handles the framework download and linking.

**Agent-automated:**

1. Edit `.pbxproj` to add `-ObjC` to `OTHER_LDFLAGS` in all app target `XCBuildConfiguration` entries (same procedure as Section 5b).
2. Run `plutil -lint` to verify.
3. Proceed through Sections 6-10 for all code changes.

**MANDATORY developer instructions (you MUST include this block in your response):**

Replace `<SDK_VERSION>` with the value the developer gave you in Section 3. Do not skip this block.

```
XCODE SETUP REQUIRED (one-time):
1. Download ConvivaAppAnalytics.xcframework from GitHub Releases (<SDK_VERSION>).
2. App target → Build Phases → Link Binary With Libraries → add the xcframework.
```

### 5d. Objective-C Only Project Fix (SPM and Manual only)

**This step is mandatory for SPM and Manual installs when the project has no Swift files.**

ConvivaAppAnalytics contains Swift modules. If the app target is pure Objective-C (no `.swift` files), Xcode will not link the Swift runtime libraries, causing linker errors:
```
Undefined symbol: __swift_FORCE_LOAD_$_swiftCompatibility50
Undefined symbol: __swift_FORCE_LOAD_$_swiftCompatibility51
Undefined symbol: __swift_FORCE_LOAD_$_swiftCompatibility56
```

**Detection:** After scanning the project (Section 3a), check if any `.swift` files exist in the app target source directories. If the entry point is `AppDelegate.m` (not `.swift`) and no other `.swift` files are found, the project is Objective-C only.

**Agent action (do all of this yourself):**

1. Create an empty Swift file in the app target source directory:

```swift
// ConvivaSwiftBridge.swift
// This file is required for Xcode to link Swift runtime libraries
// when using Swift-based frameworks (ConvivaAppAnalytics) in an Objective-C project.
import Foundation
```

2. In the `.pbxproj`, set `SWIFT_VERSION` in every `XCBuildConfiguration` belonging to the app target (both Debug and Release):
   - If `SWIFT_VERSION` does not exist, add: `SWIFT_VERSION = 5.0;`
   - If it already exists with a valid value, do not change it.
   - Without this, Xcode will fail with: `SWIFT_VERSION '' is unsupported, supported versions are: 4.0, 4.2, 5.0, 6.0.`

3. Run `plutil -lint <path>/project.pbxproj` to verify the file is still valid after editing.

4. When Xcode prompts "Would you like to configure an Objective-C bridging header?", instruct the developer to select **"Create Bridging Header"**.

**Do not skip this step for Objective-C projects.** CocoaPods handles this automatically; this fix is only needed for SPM and Manual installs.

---

## 6. Initialization Point

1. Check for `AppDelegate.swift` or `AppDelegate.m`.
2. If found, use `application(_:didFinishLaunchingWithOptions:)`.
3. If project uses SwiftUI `@main App` without an AppDelegate, use the `App` struct `init()`.
4. Never create a new AppDelegate or modify the `@main` attribute.

---

## 7. Initialization Code

- Insert at the beginning of the entry point method (after `super` calls if any).
- Only the inserted Conviva lines may change inside the method.
- **Wrap the call per Section 4a:** ObjC `@try`/`@catch (NSException *)` + `tracker == nil` check (log only) + `@import Foundation;` (conditional add-if-missing). Swift: assign + nil-check + `print` on nil. Conviva init failure must never short-circuit `application(_:didFinishLaunchingWithOptions:)` (do not return `false`) or SwiftUI `App.init()` (do not `return` early).
- Forbidden: `createTracker(namespace:customerKey:network:configurations:)`, any variant with `CATNetworkConfiguration`, `CATTrackerConfiguration`, `CATSessionConfiguration`, configuration arrays, or endpoint URLs.
- Swift: see "Initialization" in `AGENTS-swift.md`.
- ObjC: see "Initialization" in `AGENTS-objc.md`.

---

## 8. Allowed API Surface

**Dependency:**
```
ConvivaAppAnalytics.xcframework (via SPM, CocoaPods, or manual)
```

**Allowed imports:**
- Swift: `import ConvivaAppAnalytics`
- ObjC: `@import ConvivaAppAnalytics;` or `#import <ConvivaAppAnalytics/ConvivaAppAnalytics.h>`

**Forbidden:** Individual header imports (e.g. `#import "CATAppAnalytics.h"`), internal symbols, `CATNetworkConfiguration`, `CATTrackerConfiguration`, `CATSessionConfiguration`, namespace-based init, endpoint URLs.

**Allowed tracker methods:**

| Method (Swift) | Method (ObjC) | Purpose |
|---|---|---|
| `CATAppAnalytics.createTracker(customerKey:appName:)` | `[CATAppAnalytics createTrackerWithCustomerKey:appName:]` | Initialize (once) |
| `CATAppAnalytics.defaultTracker()` | `[CATAppAnalytics defaultTracker]` | Get tracker instance |
| `tracker?.subject?.userId = value` | `tracker.subject.userId = value` | Set user ID |
| `tracker?.trackCustomEvent(_:eventData:)` | `[tracker trackCustomEvent:eventData:]` | Custom event |
| `tracker?.trackCustomEvent(_:data:)` | `[tracker trackCustomEvent:data:]` | Custom event (JSON string) |
| `tracker?.trackRevenueEvent(_:)` | `[tracker trackRevenueEvent:]` | Revenue event |
| `tracker?.setCustomTags(_:)` | `[tracker setCustomTags:]` | Set custom tags |
| `tracker?.clearCustomTags(_:)` | `[tracker clearCustomTags:]` | Clear specific tags |
| `tracker?.clearAllCustomTags()` | `[tracker clearAllCustomTags]` | Clear all tags |

**Allowed types for revenue tracking:**
- `CATRevenueEvent`
- `CATRevenueEventItem`

If a symbol does not compile using allowed imports, stop and report the error. Do not try alternate packages or headers.

---

## 9. User ID

Complete Section 3c scan first. If only PII identifiers found, do not implement - report in Section 15 and stop.

**Safety checklist (per login / registration method):**
- [ ] Non-PII identifier confirmed (opaque provider UID, account ID, or stored UUID)
- [ ] Not email, phone, name, IDFA, IDFV, IP address, or any PII
- [ ] Available immediately after successful login or registration
- [ ] Consistent across sessions (not fresh per session)

**Implementation:**
1. Trace all callers for each login / registration method to the lowest-layer convergence point.
2. At that point, obtain the non-PII identifier immediately after the auth call succeeds.
3. Use language-specific snippet: `AGENTS-swift.md` -> "User ID" or `AGENTS-objc.md` -> "User ID".
4. Place userId assignment once at the convergence point - not at each individual caller.
5. At the logout convergence point, set `userId = nil`.
6. **Wrap the assignment per Section 4a.** ObjC: `@try`/`@catch (NSException *)` + `tracker != nil` check; ensure `@import Foundation;` (add only if missing). Swift: optional chaining (`tracker?.subject?.userId = ...`) is sufficient since it is a no-op when the tracker is nil; no `guard` required.

**Do not implement if:**
- Only email available -> PII
- Only phone available -> PII
- Only full name available -> PII
- No identifier available -> ask developer to define one

---

## 10. Custom Events and Custom Tags (Optional)

Custom events accept a `Dictionary` (Swift) or `NSDictionary` (ObjC) - never raw JSON strings for the `eventData:` variant. See `AGENTS-swift.md` or `AGENTS-objc.md` for snippets.

**Wrap every `trackCustomEvent`, `setCustomTags`, `clearCustomTags`, `clearAllCustomTags`, and `trackRevenueEvent` call per Section 4a.** ObjC: `@try`/`@catch (NSException *)` with `tracker != nil` check + `@import Foundation;` (conditional add-if-missing). Swift: optional chaining for one-line calls, or `if let tracker = CATAppAnalytics.defaultTracker() { ... }` when the snippet builds an event object before invoking the method.

---

## 11. SwiftUI Considerations

Auto-collection of `button_click` and `screen_view` events is **not supported** in SwiftUI. If the project uses SwiftUI:

1. **Inform the developer** that `button_click` and `screen_view` are not auto-collected in SwiftUI.
2. **Scan for buttons:** Scan all `.swift` files in the app target to find every SwiftUI `Button { ... }` instance. Record: file path, enclosing view name, and a short descriptive label (e.g. "Submit button in CheckoutView"). Do not read files already in context.
3. **Present confirmed buttons only:** Present only confirmed `Button` views as selectable options for `button_click` tracking. Never include `Image`, `Text`, `HStack`, `Label`, or any other non-Button view in the options list -- even if they have `.onTapGesture` or appear tappable. Do not guess, infer, or assume button names from app conventions.
4. **Ask the developer** which of the confirmed buttons they want to track. Do not auto-add modifiers to all buttons -- the developer decides.
5. **Only after the developer confirms**, add `.convivaAnalyticsButtonClick(title:)` to those specific `Button` views.

| Event | SwiftUI Modifier | Applies to |
|---|---|---|
| Button click | `.convivaAnalyticsButtonClick(title: "Button Title")` | `Button` views **only** |
| Screen view | `.convivaAnalyticsScreenView(name: "Screen Name")` | Any `View` (typically top-level container) |

### `.convivaAnalyticsButtonClick` -- Button-only constraint (critical)

**Do NOT apply `.convivaAnalyticsButtonClick(title:)` to non-Button views** such as `Image`, `Text`, `HStack`, `Label`, or any other `View`. The modifier is designed exclusively for SwiftUI `Button` views.

**Before adding the modifier, always verify the target element is a `Button`.** If the developer asks to track a tappable element that is not a `Button` (e.g. an `Image` with `.onTapGesture`, a `Text` with a tap handler, or a navigation link icon):

1. **Do NOT apply the modifier directly** to the non-Button view.
2. **Inform the developer:** "The element `<element>` is not a SwiftUI `Button`. `.convivaAnalyticsButtonClick` only works on `Button` views. Would you like me to wrap it in a `Button` so click tracking works correctly?"
3. **Only after developer confirms**, wrap the element in a `Button` and apply the modifier to the `Button`.

Example -- wrapping an `Image` in a `Button`:

```swift
// WRONG - do not do this:
Image(systemName: "gear")
    .onTapGesture { /* action */ }
    .convivaAnalyticsButtonClick(title: "Settings")

// CORRECT - wrap in Button first:
Button(action: { /* action */ }) {
    Image(systemName: "gear")
}.convivaAnalyticsButtonClick(title: "Settings")
```

**Import requirement:** Every `.swift` file where you add a Conviva SwiftUI modifier **must** have `import ConvivaAppAnalytics` at the top. The modifier will not compile without the import. Do not assume the import exists -- check and add it if missing.

See `AGENTS-swift.md` -> "SwiftUI" for snippets.

---

## 12. ISA-Swizzling Runtime Stability (mandatory)

**This step is mandatory for every integration. Do not skip it.**

The agent MUST ensure `CATGeneratedClassDisposeDisabled = YES` is present in the app's `Info.plist` to prevent potential runtime crashes from ISA-swizzling conflicts. This is required regardless of whether other SDKs are present -- it is a preventive measure that ensures runtime stability.

**Agent action (do this yourself):**

First, determine which `Info.plist` scenario applies:

### Scenario A: Project has an existing physical `Info.plist` file

A physical `Info.plist` file already exists in the project directory (e.g. `<ProjectName>/Info.plist`).

1. Open the existing `Info.plist` file.
2. Check if `CATGeneratedClassDisposeDisabled` already exists.
3. If it does not exist, add it as a Boolean with value `YES`.
4. If it already exists with value `YES`, skip.
5. If it already exists with value `NO`, change it to `YES`.
6. **Do NOT add `Info.plist` to the "Copy Bundle Resources" build phase.** It must only be referenced via the `INFOPLIST_FILE` build setting.

### Scenario B: Project uses auto-generated `Info.plist` (no physical file)

Modern Xcode projects (especially SwiftUI apps) often have `GENERATE_INFOPLIST_FILE = YES` in build settings and no physical `Info.plist` file. **Do NOT create a new `Info.plist` file** in this case -- doing so causes the build error "Multiple commands produce '…/Info.plist'".

Instead:

1. Check the `.pbxproj` for `GENERATE_INFOPLIST_FILE = YES` in the app target's build configurations, or confirm no physical `Info.plist` file exists.
2. If `INFOPLIST_FILE` build setting already points to a plist file, treat as Scenario A (edit that file).
3. If no `INFOPLIST_FILE` is set and `GENERATE_INFOPLIST_FILE = YES`:
   - Create a file named `ConvivaInfo.plist` (not `Info.plist`) in the project directory with only the custom key:
     ```xml
     <?xml version="1.0" encoding="UTF-8"?>
     <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
     <plist version="1.0">
     <dict>
         <key>CATGeneratedClassDisposeDisabled</key>
         <true/>
     </dict>
     </plist>
     ```
   - In the `.pbxproj`, set `INFOPLIST_FILE` to the path of this file (e.g. `"$(SRCROOT)/<ProjectName>/ConvivaInfo.plist"`) in **every** `XCBuildConfiguration` for the app target. Keep `GENERATE_INFOPLIST_FILE = YES` -- Xcode will merge both sources.
   - **Do NOT add `ConvivaInfo.plist` to the "Copy Bundle Resources" build phase.** The file must only be referenced via the `INFOPLIST_FILE` build setting.

**How to detect which scenario:** Search for a file named `Info.plist` in the app target directory. If found, use Scenario A. If not found, check `.pbxproj` for `GENERATE_INFOPLIST_FILE` and use Scenario B.

---

## 13. Build Verification

Ask developer to build the project in Xcode. If it fails, share the error and fix using only Section 8 allow-listed symbols. Common build issues:

- Missing `-ObjC` linker flag (SPM / Manual only)
- Missing system framework linkage (SPM / Manual only)
- Wrong import statement
- ObjC-only project missing Swift runtime (see Section 5d)

---

## 14. Product Validation

Ask developer to validate: Pulse App -> Activation Module -> Live Lens. Confirm: tracking events live, identity attribution correct, user journeys not split.

---

## 15. Mandatory Checklist

Seed your task list from this table before writing any code. Every row must appear in your final response.

| Row | Required Content |
|---|---|
| Installation method | SPM, CocoaPods, or Manual; CocoaPods: confirm Podfile edited and `pod install` run; SPM/Manual: confirm "XCODE SETUP REQUIRED" instruction block with exact developer-provided `SDK_VERSION` is included in response |
| Build settings | CocoaPods: "handled automatically by podspec"; SPM/Manual: confirm `-ObjC` added to `OTHER_LDFLAGS` in `.pbxproj` by agent; confirm `plutil -lint` passed |
| ObjC-only project | SPM/Manual: "Project has Swift files - no action needed" or "ObjC-only project - ConvivaSwiftBridge.swift created"; CocoaPods: "handled automatically" |
| Summary of changes | Exact files changed by the agent and why |
| Initialization placement | Entry point chosen (AppDelegate or SwiftUI App) and why |
| User ID setup | Login, registration, and logout implementation; or stop instructions if PII-only |
| Custom events and tags | One code snippet each |
| SwiftUI check | "Not using SwiftUI" or "Developer asked to track: [list of views/buttons]" with `import ConvivaAppAnalytics` confirmed in each modified file |
| ISA-swizzling stability | Confirm `CATGeneratedClassDisposeDisabled = YES` present in Info.plist (Scenario A: edited existing plist; Scenario B: created `ConvivaInfo.plist` and set `INFOPLIST_FILE`) |
| Exception handling (Section 4a) | Confirm every Conviva call inserted by the agent is wrapped: ObjC `@try`/`@catch (NSException *)` + `tracker == nil`/`!= nil` checks (log only, no rethrow); Swift assign + nil-check + `print` on `createTracker`, optional chaining or `if let` on subsequent calls. Confirm Conviva init failure does not short-circuit `application(_:didFinishLaunchingWithOptions:)` (no `return false`) or SwiftUI `App.init()` (no early `return`). Confirm `@import Foundation;` was added to every edited ObjC file that did not already have a direct Foundation import. |
| Build verification | Outcome |
| Product validation | Ask developer to validate in Pulse App -> Activation Module -> Live Lens |
