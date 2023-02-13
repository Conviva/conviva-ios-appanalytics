# conviva-ios-appanalytics
Use Application Analytics to autocollect events and track application specific events and state changes.

# Initialization
* SPM
   * https://github.com/conviva/conviva-ios-appanalytics
* Cocoapods
   * Add below line in pods file
     * pod 'ConvivaAppAnalytics', '0.2.7'

* Manual Download
  * Download and unzip the package from Downloads. During the build phase, add ConvivaAppAnalytics.xcframework to Link Binary with Libraries section 
  in  xcode. This package contains the frameworks for both, iOS and tvOS.

* Link the following system frameworks to Link Binary with Libraries section in xcode:

  * UIKit
  * Foundation
  * CoreTelephony (iOS only)
  * FMDB (version 2.7 or above)
  * In Other Linker Flags section in Xcode, add "-ObjC".
  * To refer to the Conviva classes from your source code, add the following import statements:

```swift
//Swift
import ConvivaAppAnalytics
```

```objective-c
//Objc
@import ConvivaAppAnalytics;

```

# Initialize the top level object

```swift
//Swift

var tracker = CATAppAnalytics.createTracker(customerKey: "<YOUR_CUSTOMER_KEY_ADVISED_BY_Conviva>", appName: "<YOUR_APP_NAME_ADVISED_BY_Conviva>")
```

```objective-c
//ObjC

CATTracker *tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"<YOUR_CUSTOMER_KEY_ADVISED_BY_Conviva>" appName:@"<YOUR_APP_NAME_ADVISED_BY_Conviva>"];
```

# Set the user id (viewer id)
```swift
tracker.subject.userId = @"user_id";
```

# Custom event tracking to track your application specific events and state changes
Use trackCustomEvent() to track all kinds of events. This API provides 2 fields to describe the tracked events. 
  * eventName  - Name of the custom event.
  * eventData  – Any type of data in string format.

The following example shows the implementation of the 'onClick' 
event listener to any element:

```swift
let data = "{\"identifier1\": \"test\",\"identifier2\": 1,\"identifier3\":true}"
self.tracker.trackCustomEvent("your-event-name", data: data);

```

# Screen view tracking
When user navigates between screens, user journey is tracked by reading the class names of UIViewController classes. Name of the screens can be customized using below code as per the bussiness needs.

```objective-c
* ObjC:
* //Declare property like below
* @property(copy, nonatomic)NSString *catViewId;
* //Add below line in viewDidLoad method
* self.catViewId = @“Customizable name”;
```
```swift
* Swift:
* //Add below property in view controller
* @objc var catViewId:String = “App Analytics View”
```

# Custom Tags Support
Support is added to pass custom data as key-val pairs which are available in each event triggered by sdk and passed to backend. Below are the new api additions to support Custom Tags.

```objective-c
// Setter API

/**
 * Set custom tags.
 * Pass custom tags
 * @param tags Dictionary of Key-Val pairs.
 */
- (void)setCustomTags:(NSDictionary *)tags;

// Usage
NSDictionary* tags = @{
    @"Key1": @"Value1",
    @"Key2": @"Value2",
};
[self.tracker setCustomTags:tags];

// Clear API
/**
 * Clears all custom tags.
 */
- (void)clearCustomTags;

// Usage
[self.tracker clearCustomTags];

/**
 * Clears custom tags which are matching keys as passed in.
 * Keys of tags to be cleared
 * @param tagKeys tagKeys.
 */
- (void)clearCustomTags:(NSArray *)tagKeys;

// Usage
NSArray* keys = @[ @"Key1", @"Key2", @"Key3" ];
[self.tracker clearCustomTags:keys];

```


# Note: If user of this sdk also uses ConvivaSDK for Experience Insights/Ad Insights, ConvivaSDK version must be 4.0.28 or above to be compatable with ConvivaAppAnalytics version 0.2.3 or above
# To enable automatic collection of playback events, ConvivaSDK 4.0.32 or above must be used.
 
