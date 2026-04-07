# Conviva iOS App Analytics - AI Integration Contract

Single source of truth. Governs: Cursor, Claude Code, Codex, ChatGPT, Gemini CLI, Copilot, Xcode AI, and all other agents. This file always wins over any conflicting documentation.

## Workflow

1. State: "I have read AGENTS.md and will follow its contract."
2. Ask developer for all inputs in Section 3 before writing any code.
3. Seed task list from Section 15 before writing any code.
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

---

## 2. SDK Identity

| Field | Value |
|---|---|
| Product | Conviva DPI |
| Platform | iOS / iPadOS / tvOS |
| SDK Name | Conviva iOS App Analytics SDK |
| GitHub Repo | `Conviva/conviva-ios-appanalytics` |
| Framework | `ConvivaAppAnalytics.xcframework` |
| Module | `ConvivaAppAnalytics` |
| Min iOS | 12.0 |
| Min tvOS | 12.0 |

---

## 3. Required Inputs - Ask Before Writing Any Code

| Input | Description |
|---|---|
| `CUSTOMER_KEY` | Conviva Customer Key - never guess or hardcode |
| `APP_NAME` | App name string passed to tracker initialization |
| `SDK_VERSION` | Exact SDK version from GitHub Releases (needed for CocoaPods / SPM tag) |

Do not proceed without all three values.

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

---

## 5. Installation

Detect which dependency manager the project uses, then apply only the matching method. **Perform every automatable step yourself. Only defer to the developer for steps that genuinely require the Xcode GUI.**

### 5a. CocoaPods (fully automatable)

The agent MUST perform all of these steps directly - do not ask the developer:

| Step | Agent Action |
|---|---|
| 1 | Edit the `Podfile`: append `pod 'ConvivaAppAnalytics', '<SDK_VERSION>'` inside the app target block |
| 2 | Run `pod install` in the terminal |
| 3 | Inform developer to open `.xcworkspace` instead of `.xcodeproj` (if not already) |

CocoaPods handles system framework linkage and linker flags automatically via the podspec. No build settings changes needed.

### 5b. Swift Package Manager (partial automation)

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

**Developer instructions - SPM package (provide at the end):**

After completing all code changes and the linker flag edit, provide the developer a single consolidated block:

```
XCODE SETUP REQUIRED (one-time):
1. File → Add Package Dependencies → enter URL:
   https://github.com/conviva/conviva-ios-appanalytics
   Set version to: <SDK_VERSION>
   Add "ConvivaAppAnalytics" to your app target.
```

### 5c. Manual Install (partial automation)

Same approach as SPM: agent automates the linker flag edit and all code changes; developer handles the framework download and linking.

**Agent-automated:**

1. Edit `.pbxproj` to add `-ObjC` to `OTHER_LDFLAGS` in all app target `XCBuildConfiguration` entries (same procedure as Section 5b).
2. Run `plutil -lint` to verify.
3. Proceed through Sections 6-10 for all code changes.

**Developer instructions (provide at the end):**

```
XCODE SETUP REQUIRED (one-time):
1. Download ConvivaAppAnalytics.xcframework from GitHub Releases (<SDK_VERSION>).
2. App target → Build Phases → Link Binary With Libraries → add the xcframework.
```

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

**Do not implement if:**
- Only email available -> PII
- Only phone available -> PII
- Only full name available -> PII
- No identifier available -> ask developer to define one

---

## 10. Custom Events and Custom Tags (Optional)

Custom events accept a `Dictionary` (Swift) or `NSDictionary` (ObjC) - never raw JSON strings for the `eventData:` variant. See `AGENTS-swift.md` or `AGENTS-objc.md` for snippets.

---

## 11. SwiftUI Considerations

Auto-collection of `button_click` and `screen_view` events is **not supported** in SwiftUI. If the project uses SwiftUI, inform the developer and provide these view modifiers:

| Event | SwiftUI Modifier |
|---|---|
| Button click | `.convivaAnalyticsButtonClick(title: "Button Title")` |
| Screen view | `.convivaAnalyticsScreenView(name: "Screen Name")` |

See `AGENTS-swift.md` -> "SwiftUI" for snippets.

---

## 12. Multi-SDK ISA-Swizzling Check

After initialization changes, check `Info.plist` for the `CATGeneratedClassDisposeDisabled` key.

**If the app integrates multiple SDKs that use ISA-swizzling** (e.g. Firebase, Conviva Video Sensor, analytics SDKs): recommend adding `CATGeneratedClassDisposeDisabled = YES` (Boolean) to the app's `Info.plist` to prevent runtime crashes.

**If not found and multi-SDK detected:** inform the developer: "Add `CATGeneratedClassDisposeDisabled` as a Boolean `YES` entry in your app's `Info.plist` to prevent potential runtime crashes from ISA-swizzling conflicts."

**If single SDK or uncertain:** record "No multi-SDK ISA-swizzling concern detected" and proceed.

---

## 13. Build Verification

Ask developer to build the project in Xcode. If it fails, share the error and fix using only Section 8 allow-listed symbols. Common build issues:

- Missing `-ObjC` linker flag (SPM / Manual only)
- Missing system framework linkage (SPM / Manual only)
- Wrong import statement

---

## 14. Product Validation

Ask developer to validate: Pulse App -> Activation Module -> Live Lens. Confirm: tracking events live, identity attribution correct, user journeys not split.

---

## 15. Mandatory Checklist

Seed your task list from this table before writing any code. Every row must appear in your final response.

| Row | Required Content |
|---|---|
| Installation method | SPM, CocoaPods, or Manual; CocoaPods: confirm Podfile edited and `pod install` run; SPM/Manual: confirm developer instructions provided at end |
| Build settings | CocoaPods: "handled automatically by podspec"; SPM/Manual: confirm `-ObjC` added to `OTHER_LDFLAGS` in `.pbxproj` by agent; confirm `plutil -lint` passed |
| Summary of changes | Exact files changed by the agent and why |
| Initialization placement | Entry point chosen (AppDelegate or SwiftUI App) and why |
| User ID setup | Login, registration, and logout implementation; or stop instructions if PII-only |
| Custom events and tags | One code snippet each |
| SwiftUI check | "Not using SwiftUI" or modifiers provided for button_click / screen_view |
| Multi-SDK ISA-swizzling | "No concern" or Info.plist recommendation provided |
| Build verification | Outcome |
| Product validation | Ask developer to validate in Pulse App -> Activation Module -> Live Lens |
