# conviva-ios-appanalytics
Use Application Analytics to autocollect events and track application specific events and state changes.

# Supported Platforms
* iOS(9.0 and above)
* iPadOS(13.0 and above)
* tvOS(9.0 and above)
* watchOS(TBD)

# Configuring Workspace
* SPM
   * https://github.com/conviva/conviva-ios-appanalytics
* Cocoapods
   * Add below line in pods file
     * pod 'ConvivaAppAnalytics', '0.2.29'

 **NOTE: During pod installation, if you are facing any issues with FMDB, Please update your file as below and do pod installation.**
   * Add below line in pods file
     * pod 'ConvivaAppAnalytics', '0.2.29'

* Manual Download
  * Download and unzip the package from Downloads. During the build phase, add ConvivaAppAnalytics.xcframework to Link Binary with Libraries section 
  in  xcode. This package contains the frameworks for both, iOS and tvOS.

* Link the following system frameworks to Link Binary with Libraries section in xcode:

  * UIKit
  * Foundation
  * CoreTelephony (iOS only)
  * In Other Linker Flags section in Xcode, add "-ObjC".
  * To refer to the Conviva classes from your source code, add the following import statements:

```swift
* Swift:
import ConvivaAppAnalytics
```

```objective-c
* ObjC:
@import ConvivaAppAnalytics;

```

# Initialize Conviva Tracker

It is recommended to initialize the Conviva Tracker at the earliest possible stage in the application's launch lifecycle. Ideally, this should be done in the app's entry point method, before any other application functionalities are executed.

```swift
func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil
) -> Bool
```

```swift
// Initialization
* Swift:
let tracker = CATAppAnalytics.createTracker(customerKey: customerKey, appName: appName)

// The tracker object can be fetched using the following API in the other classes than the place where createTracker is invoked using following API:
let tracker = CATAppAnalytics.defaultTracker();
```

```objective-c
// Initialization
* ObjC:
id<CATTrackerController> tracker = [CATAppAnalytics createTrackerWithCustomerKey:customerKey appName:appName];

// The tracker object can be fetched using the following API in the other classes than the place where createTracker is invoked using following API:
id<CATTrackerController> tracker = [CATAppAnalytics defaultTracker];
```

<strong>customerKey</strong> - a string to identify specific customer account. Different keys shall be used for development / debug versus production environment. Find your keys on the account info page in Pulse.

<strong>appName</strong> - a string value used to distinguish your applications. Simple values that are unique across all of your integrated platforms work best here.

# Set the user id (viewer id)
```swift
* Swift:
tracker?.subject?.userId = "user_id"
```

```objective-c
* ObjC:
tracker.subject.userId = @"user_id";
```
# Custom event tracking to track your application specific events and state changes
Use trackCustomEvent(name:data:) to track all kinds of events. This API provides 2 fields to describe the tracked events. 
  * eventName  - Name of the custom event.
  * data  – Any type of data in string format.

The following example shows the implementation of the trackCustomEvent.

```swift
* Swift:
let data = "{\"identifier1\": \"test\",\"identifier2\": 1,\"identifier3\":true}"
tracker?.trackCustomEvent("your-event-name", data: data)
```

```objective-c
* ObjC:
NSString *data = @"{\"identifier1\": \"test\",\"identifier2\": 1,\"identifier3\":true}";
[tracker trackCustomEvent:@"your-event-name" data:data];
```

Use trackCustomEvent(name:eventData) to track all kinds of events. This API provides 2 fields to describe the tracked events. 
  * eventName  - Name of the custom event.
  * eventData  – Dictionary/Array of dictionaries

The following example shows the implementation of the trackCustomEvent.

```swift
* Swift:
var eventData = ["identifier1":"test","identifier2":1,"identifier3":true] as [String : Any]
tracker?.trackCustomEvent("your-event-name", eventData: eventData)
```

```objective-c
* ObjC:
NSDictionary *data = @{@"identifier1":@"test",@"identifier2":@(1),@"identifier3":@(true)};
[self trackCustomEvent:@"your-event-name" eventData:data];
```

# Screen view tracking
When user navigates between screens, user journey is tracked by reading the class names of UIViewController classes. Name of the screens can be customized using below code as per the bussiness needs.

```swift
* Swift:
* //Add below property in view controller
* @objc var catViewId:String = "App Analytics View"
```
```objective-c
* ObjC:
* //Declare property like below
* @property(copy, nonatomic)NSString *catViewId;
* //Add below line in viewDidLoad method
* self.catViewId = @"Customizable name";
```
# Custom Tags Support
Support is added to pass custom data as key-val pairs which are available in each event triggered by sdk and passed to backend. Below are the new api additions to support Custom Tags.

```objective-c
* ObjC:
// Setter API

/**
 * Set custom tags.
 * Pass custom tags
 * @param tags Dictionary of Key-Val pairs.
 */
- (void)setCustomTags:(NSDictionary *)tags;

//Usage
NSDictionary* tags = @{
    @"Key1": @"Value1",
    @"Key2": @"Value2",
};
[tracker setCustomTags:tags];

// Clear API
/**
 * Clears all custom tags.
 */
- (void)clearCustomTags;

//Usage
[tracker clearCustomTags];

/**
 * Clears custom tags which are matching keys as passed in.
 * Keys of tags to be cleared
 * @param tagKeys tagKeys.
 */
- (void)clearCustomTags:(NSArray *)tagKeys;

//Usage
NSArray* keys = @[ @"Key1", @"Key2", @"Key3" ];
[tracker clearCustomTags:keys];

```
```swift
* Swift:
//Usage: Set custom tags
let tags = ["Key1": "Value1", "Key2": "Value2"]
tracker?.setCustomTags(tags)

//Usage: Clear all custom tags
tracker?.clearCustomTags()

//Usage: Clear custom tags
let keys = ["Key1", "Key2", "Key3"]
tracker?.clearCustomTags(keys)
```

<details>
  <summary><b>Auto-collected Events</b></summary>

##### Conviva provides a rich set of application performance metrics with the help of autocollected app events, such as _screen_view_ , _button_click_, and _network_request_.

Event | Occurrence |
------|-------------|
network_request | after receiving the network request response|
screen_view | when the screen is interacted on either first launch or relaunch|
application_error | when an error occurrs in the application|
button_click | on the button click callback|
application_background | when the application is taken to the background|
application_foreground | when the application is taken to the foreground|
application_install |when the application is launched for the first time after it's installed. (It's not the exact installed time.)|

To learn about the default metrics for analyzing the native and web applications performance, such as App Crashes, Avg Screen Load Time, and Page Loads, refer to the [App Experience Metrics](https://pulse.conviva.com/learning-center/content/app_experience/app_experience_metrics.html?tocpath=App%20Experience%7C_____8) page in the Learning Center.
</details>

#### Note: If user of this sdk also uses ConvivaSDK for Experience Insights/Ad Insights, ConvivaSDK version must be 4.0.28 or above to be compatable with ConvivaAppAnalytics version 0.2.3 or above
#### To enable automatic collection of playback events, ConvivaSDK 4.0.32 or above must be used.
 
