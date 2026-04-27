# Conviva iOS App Analytics - Swift Snippets

Only read this file if the target project uses Swift. Imports are in AGENTS.md Section 8.

**Safety contract (per AGENTS.md Section 4a):** `CATAppAnalytics.createTracker(customerKey:appName:)` is an Objective-C method that returns an optional and does NOT throw Swift errors. Use a simple nil-check + `print` on `createTracker` -- never `do/try/catch`, and never `guard let ... else { return ... }` in `application(_:didFinishLaunchingWithOptions:)` or SwiftUI `App.init()`. Conviva is telemetry; an init failure must never short-circuit host-app launch. Use optional chaining (`tracker?.x`) for subsequent calls -- this is a no-op when the tracker is nil. For multi-statement event-construction blocks, prefer `if let tracker = CATAppAnalytics.defaultTracker() { ... }` so the construction is skipped when the tracker is nil (this only skips the block, not surrounding host-app code). No additional imports required -- `if let`, nil-checks, and optional chaining are Swift built-ins.

---

## Initialization

Insert at the beginning of `application(_:didFinishLaunchingWithOptions:)` (UIKit) or `init()` (SwiftUI App). Add the import if not already present.

```swift
import ConvivaAppAnalytics

// Note: CATAppAnalytics.createTracker is an Objective-C method and does not throw Swift errors.
// Log on nil and continue -- never short-circuit host-app launch on a Conviva init failure.
let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
if tracker == nil {
    print("Conviva tracker init returned nil")
}
```

**UIKit AppDelegate example:**

```swift
import ConvivaAppAnalytics

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    func application(
        _ application: UIApplication,
        didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]? = nil
    ) -> Bool {
        // Note: CATAppAnalytics.createTracker is an Objective-C method and does not throw Swift errors.
        // Log on nil and continue -- Conviva is telemetry, an init failure must not affect app launch.
        let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
        if tracker == nil {
            print("Conviva tracker init returned nil")
        }

        return true
    }
}
```

**SwiftUI App example:**

```swift
import SwiftUI
import ConvivaAppAnalytics

@main
struct YourApp: App {
    init() {
        // Note: CATAppAnalytics.createTracker is an Objective-C method and does not throw Swift errors.
        // Log on nil and continue -- do not `return` early, that would skip any subsequent initialization.
        let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
        if tracker == nil {
            print("Conviva tracker init returned nil")
        }
    }

    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
```

---

## Retrieve Tracker

After initialization, retrieve the tracker instance in any class. Use optional chaining for subsequent calls -- it is a no-op when the tracker is nil:

```swift
let tracker = CATAppAnalytics.defaultTracker()
```

---

## User ID

Place immediately after successful login or registration at the convergence point. Optional chaining keeps this safe when the tracker is nil:

```swift
let tracker = CATAppAnalytics.defaultTracker()
tracker?.subject?.userId = userId
```

Clear on logout:

```swift
let tracker = CATAppAnalytics.defaultTracker()
tracker?.subject?.userId = nil
```

---

## Custom Events

For multi-statement blocks that build the event data, prefer `if let` so construction is skipped when the tracker is nil:

```swift
if let tracker = CATAppAnalytics.defaultTracker() {
    let eventData: [String: Any] = [
        "identifier1": "test",
        "identifier2": 1,
        "identifier3": true
    ]
    tracker.trackCustomEvent("your-event-name", eventData: eventData)
}
```

---

## Custom Tags

Set:

```swift
if let tracker = CATAppAnalytics.defaultTracker() {
    let tags: [String: Any] = ["Key1": "Value1", "Key2": "Value2"]
    tracker.setCustomTags(tags)
}
```

Clear specific tags (single-line; optional chaining is sufficient):

```swift
let tracker = CATAppAnalytics.defaultTracker()
tracker?.clearCustomTags(["Key1", "Key2"])
```

Clear all tags:

```swift
let tracker = CATAppAnalytics.defaultTracker()
tracker?.clearAllCustomTags()
```

---

## Revenue Event

Minimal -- use `if let` so the `CATRevenueEvent` is not constructed when the tracker is nil:

```swift
if let tracker = CATAppAnalytics.defaultTracker() {
    let event = CATRevenueEvent(
        totalOrderAmount: 49.99,
        transactionId: "ORD-12345",
        currency: "USD"
    )
    tracker.trackRevenueEvent(event)
}
```

Full:

```swift
if let tracker = CATAppAnalytics.defaultTracker() {
    let item1 = CATRevenueEventItem()
    item1.productId = "p1"
    item1.name = "Widget"
    item1.unitPrice = 19.99
    item1.quantity = 2

    let item2 = CATRevenueEventItem()
    item2.productId = "p2"
    item2.name = "Gadget"
    item2.unitPrice = 19.99
    item2.quantity = 1

    let event = CATRevenueEvent(
        totalOrderAmount: 59.97,
        transactionId: "ORD-12345",
        currency: "USD"
    )
    event.taxAmount = 5.00
    event.shippingCost = 4.99
    event.discount = 10.00
    event.cartSize = 3
    event.paymentMethod = "card"
    event.paymentProvider = "Stripe"
    event.items = [item1, item2]
    event.extraMetadata = ["promoCode": "SAVE10", "campaignId": "summer-sale"]

    tracker.trackRevenueEvent(event)
}
```

---

## SwiftUI

Auto-collection of `button_click` and `screen_view` is not supported in SwiftUI. Scan all `.swift` files to find confirmed `Button` views, present them as selectable options to the developer, and add modifiers only to developer-confirmed locations. See AGENTS.md Section 11 for the full procedure.

**Every file using these modifiers must have `import ConvivaAppAnalytics` at the top.**

**Button click tracking (Button views ONLY):**

`.convivaAnalyticsButtonClick(title:)` must ONLY be applied to SwiftUI `Button` views. Do NOT apply it to `Image`, `Text`, `HStack`, `Label`, or any other non-Button view -- even if that view is tappable via `.onTapGesture` or a `NavigationLink`.

Before adding this modifier, **always verify the target element is a `Button` via source code inspection**. Never present non-Button views as trackable candidates. If the developer requests tracking on a non-Button element, ask whether to wrap it in a `Button` first.

```swift
import SwiftUI
import ConvivaAppAnalytics

// CORRECT - modifier on a Button:
Button("Submit") {
    // action
}.convivaAnalyticsButtonClick(title: "Submit")
```

```swift
// WRONG - modifier on Image (will not track correctly):
Image(systemName: "gear")
    .onTapGesture { /* action */ }
    .convivaAnalyticsButtonClick(title: "Settings")

// CORRECT - wrap Image in Button first:
Button(action: { /* action */ }) {
    Image(systemName: "gear")
}.convivaAnalyticsButtonClick(title: "Settings")
```

**Screen view tracking:**

```swift
import SwiftUI
import ConvivaAppAnalytics

struct DetailView: View {
    var body: some View {
        VStack {
            Text("Item Detail")
        }
        .convivaAnalyticsScreenView(name: "Detail Screen")
    }
}
```

---

## Override UIViewController Screen Name

Override the default screen name tracked for a UIViewController:

```swift
class ExampleViewController: UIViewController {
    @objc var catViewId: String = "Home Screen View"
}
```
