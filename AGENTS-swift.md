# Conviva iOS App Analytics - Swift Snippets

Only read this file if the target project uses Swift. Imports are in AGENTS.md Section 8.

---

## Initialization

Insert at the beginning of `application(_:didFinishLaunchingWithOptions:)` (UIKit) or `init()` (SwiftUI App). Add the import if not already present.

```swift
import ConvivaAppAnalytics

let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
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
        let tracker = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")

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
        let _ = CATAppAnalytics.createTracker(customerKey: "YOUR_CUSTOMER_KEY", appName: "YOUR_APP_NAME")
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

After initialization, retrieve the tracker instance in any class:

```swift
let tracker = CATAppAnalytics.defaultTracker()
```

---

## User ID

Place immediately after successful login or registration at the convergence point.

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

```swift
let tracker = CATAppAnalytics.defaultTracker()
let eventData: [String: Any] = [
    "identifier1": "test",
    "identifier2": 1,
    "identifier3": true
]
tracker?.trackCustomEvent("your-event-name", eventData: eventData)
```

---

## Custom Tags

Set:

```swift
let tracker = CATAppAnalytics.defaultTracker()
let tags: [String: Any] = ["Key1": "Value1", "Key2": "Value2"]
tracker?.setCustomTags(tags)
```

Clear specific tags:

```swift
tracker?.clearCustomTags(["Key1", "Key2"])
```

Clear all tags:

```swift
tracker?.clearAllCustomTags()
```

---

## Revenue Event

Minimal:

```swift
let tracker = CATAppAnalytics.defaultTracker()
let event = CATRevenueEvent(
    totalOrderAmount: 49.99,
    transactionId: "ORD-12345",
    currency: "USD"
)
tracker?.trackRevenueEvent(event)
```

Full:

```swift
let tracker = CATAppAnalytics.defaultTracker()

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

tracker?.trackRevenueEvent(event)
```

---

## SwiftUI

Auto-collection of `button_click` and `screen_view` is not supported in SwiftUI. Ask the developer which views and buttons to track, then add modifiers only to those specific locations.

**Every file using these modifiers must have `import ConvivaAppAnalytics` at the top.**

**Button click tracking:**

```swift
import SwiftUI
import ConvivaAppAnalytics

// ...

Button("Submit") {
    // action
}.convivaAnalyticsButtonClick(title: "Submit")
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
