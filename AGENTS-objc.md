# Conviva iOS App Analytics - Objective-C Snippets

Only read this file if the target project uses Objective-C. Imports are in AGENTS.md Section 8.

**Every snippet below must be wrapped in `@try`/`@catch (NSException *)` with a `tracker == nil` (or `tracker != nil`) check, per AGENTS.md Section 4a.** AI-generated integration code MUST NOT crash the host app.

**`@import Foundation;` -- conditional add-if-missing:** `NSException` and `NSLog` are part of `Foundation`. Add `@import Foundation;` at the top of the file **only if the file does not already have a direct Foundation import** (`@import Foundation;` or `#import <Foundation/Foundation.h>`). Do not rely on transitive availability via UIKit. If a direct Foundation import is already present, skip.

---

## Initialization

Insert at the beginning of `application:didFinishLaunchingWithOptions:`. Add `@import ConvivaAppAnalytics;` if not already present, and `@import Foundation;` if no direct Foundation import is already present.

```objc
@import Foundation;          // add only if not already imported (direct, not transitive)
@import ConvivaAppAnalytics; // add only if not already imported

@try {
    id<CATTrackerController> tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"YOUR_CUSTOMER_KEY" appName:@"YOUR_APP_NAME"];
    if (tracker == nil) {
        NSLog(@"Conviva tracker init returned nil");
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva tracker init failed: %@", exception);
}
```

**Full AppDelegate example:**

```objc
@import Foundation;          // add only if not already imported
@import ConvivaAppAnalytics; // add only if not already imported

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    @try {
        id<CATTrackerController> tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"YOUR_CUSTOMER_KEY" appName:@"YOUR_APP_NAME"];
        if (tracker == nil) {
            NSLog(@"Conviva tracker init returned nil");
        }
    } @catch (NSException *exception) {
        NSLog(@"Conviva tracker init failed: %@", exception);
    }

    return YES;
}

@end
```

---

## Retrieve Tracker

After initialization, retrieve the tracker instance in any class. Always wrap and nil-check before use:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker == nil) {
        NSLog(@"Conviva defaultTracker returned nil");
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva defaultTracker failed: %@", exception);
}
```

---

## User ID

Place immediately after successful login or registration at the convergence point.

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        tracker.subject.userId = userId;
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva setUserId failed: %@", exception);
}
```

Clear on logout:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        tracker.subject.userId = nil;
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva clearUserId failed: %@", exception);
}
```

---

## Custom Events

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        NSDictionary *eventData = @{
            @"identifier1": @"test",
            @"identifier2": @(1),
            @"identifier3": @(YES)
        };
        [tracker trackCustomEvent:@"your-event-name" eventData:eventData];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva trackCustomEvent failed: %@", exception);
}
```

---

## Custom Tags

Set:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        NSDictionary *tags = @{
            @"Key1": @"Value1",
            @"Key2": @"Value2"
        };
        [tracker setCustomTags:tags];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva setCustomTags failed: %@", exception);
}
```

Clear specific tags:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        [tracker clearCustomTags:@[@"Key1", @"Key2"]];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva clearCustomTags failed: %@", exception);
}
```

Clear all tags:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        [tracker clearAllCustomTags];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva clearAllCustomTags failed: %@", exception);
}
```

---

## Revenue Event

Minimal:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        CATRevenueEvent *event = [[CATRevenueEvent alloc]
            initWithTotalOrderAmount:@(49.99)
                       transactionId:@"ORD-12345"
                            currency:@"USD"];
        [tracker trackRevenueEvent:event];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva trackRevenueEvent failed: %@", exception);
}
```

Full:

```objc
@try {
    id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
    if (tracker != nil) {
        CATRevenueEventItem *item1 = [[CATRevenueEventItem alloc]
            initWithProductId:@"p1"
                         name:@"Widget"
                    unitPrice:@(19.99)
                     quantity:@(2)];

        CATRevenueEventItem *item2 = [[CATRevenueEventItem alloc]
            initWithProductId:@"p2"
                         name:@"Gadget"
                    unitPrice:@(19.99)
                     quantity:@(1)];

        CATRevenueEvent *event = [[CATRevenueEvent alloc]
            initWithTotalOrderAmount:@(59.97)
                       transactionId:@"ORD-12345"
                            currency:@"USD"];
        event.taxAmount       = @(5.00);
        event.shippingCost    = @(4.99);
        event.discount        = @(10.00);
        event.cartSize        = @(3);
        event.paymentMethod   = @"card";
        event.paymentProvider = @"Stripe";
        event.items           = @[item1, item2];
        event.extraMetadata   = @{@"promoCode": @"SAVE10", @"campaignId": @"summer-sale"};

        [tracker trackRevenueEvent:event];
    }
} @catch (NSException *exception) {
    NSLog(@"Conviva trackRevenueEvent failed: %@", exception);
}
```

---

## Override UIViewController Screen Name

```objc
// ExampleViewController.h
@interface ExampleViewController : UIViewController
@property (copy, nonatomic) NSString *catViewId;
@end

// ExampleViewController.m
@implementation ExampleViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.catViewId = @"Home Screen View";
}

@end
```
