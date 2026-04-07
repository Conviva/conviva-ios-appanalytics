# Conviva iOS App Analytics - Objective-C Snippets

Only read this file if the target project uses Objective-C. Imports are in AGENTS.md Section 8.

---

## Initialization

Insert at the beginning of `application:didFinishLaunchingWithOptions:`. Add the import if not already present.

```objc
@import ConvivaAppAnalytics;

id<CATTrackerController> tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"YOUR_CUSTOMER_KEY" appName:@"YOUR_APP_NAME"];
```

**Full AppDelegate example:**

```objc
@import ConvivaAppAnalytics;

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    id<CATTrackerController> tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"YOUR_CUSTOMER_KEY" appName:@"YOUR_APP_NAME"];

    return YES;
}

@end
```

---

## Retrieve Tracker

After initialization, retrieve the tracker instance in any class:

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
```

---

## User ID

Place immediately after successful login or registration at the convergence point.

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
tracker.subject.userId = userId;
```

Clear on logout:

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
tracker.subject.userId = nil;
```

---

## Custom Events

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
NSDictionary *eventData = @{
    @"identifier1": @"test",
    @"identifier2": @(1),
    @"identifier3": @(YES)
};
[tracker trackCustomEvent:@"your-event-name" eventData:eventData];
```

---

## Custom Tags

Set:

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
NSDictionary *tags = @{
    @"Key1": @"Value1",
    @"Key2": @"Value2"
};
[tracker setCustomTags:tags];
```

Clear specific tags:

```objc
[tracker clearCustomTags:@[@"Key1", @"Key2"]];
```

Clear all tags:

```objc
[tracker clearAllCustomTags];
```

---

## Revenue Event

Minimal:

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
CATRevenueEvent *event = [[CATRevenueEvent alloc]
    initWithTotalOrderAmount:@(49.99)
               transactionId:@"ORD-12345"
                    currency:@"USD"];
[tracker trackRevenueEvent:event];
```

Full:

```objc
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];

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
