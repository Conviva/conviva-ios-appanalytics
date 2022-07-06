# conviva-ios-appanalytics
Use Application Analytics to autocollect events and track application specific events and state changes.

# Initialization

* SPM
  * https://github.com/conviva/conviva-ios-appanalytics

* Cocoapods
 * Add below line in pods file
   * pod 'ConvivaAppAnalytics', '0.2.3'

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

//Swift
```

import ConvivaAppAnalytics

```

//Objc
```

@import ConvivaAppAnalytics;

```

# Initialize the top level object

//Swift
```

var tracker = CATAppAnalytics.createTracker(customerKey: "<YOUR_CUSTOMER_KEY_ADVISED_BY_Conviva>", appName: "<YOUR_APP_NAME_ADVISED_BY_Conviva>")

```

//ObjC
```

CATTracker *tracker = [CATAppAnalytics createTrackerWithCustomerKey:@"<YOUR_CUSTOMER_KEY_ADVISED_BY_Conviva>" appName:@"<YOUR_APP_NAME_ADVISED_BY_Conviva>"];

```

# Set the user id (viewer id)
```

tracker.subject.userId = @"user_id";

```

# Custom event tracking to track your application specific events and state changes
Use trackCustomEvent() to track all kinds of events. This API provides 2 fields to describe the tracked events. 
  * eventName  - Name of the custom event.
  * eventData  – Any type of data in string format.

The following example shows the implementation of the 'onClick' 
event listener to any element:


```

let data = "{\"identifier1\": \"test\",\"identifier2\": 1,\"identifier3\":true}"

self.tracker.trackCustomEvent("your-event-name", data: data);

```
 
