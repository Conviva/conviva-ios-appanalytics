# conviva-ios-appanalytics
Use Application Analytics to autocollect events and track application specific events and state changes.

# Initialization

* Install the Conviva library

* Download and unzip the package from Downloads. During the build phase, add ConvivaAppAnalytics.xcframework to Link Binary with Libraries section in xcode. This package contains the frameworks for both, iOS and tvOS.

* Link the following system frameworks to Link Binary with Libraries section in xcode:

* UIKit

* Foundation

* CoreTelephony (iOS only)

* FMDB (version 2.7 or above)

In Other Linker Flags section in Xcode, add "-ObjC".

To refer to the Conviva classes from your source code, add the following import statements:

//Swift
import ConvivaAppAnalytics

//Objc
@import ConvivaAppAnalytics;

# Initialize the top level object

//Swift
let networkConfig = CATNetworkConfiguration(endpoint: "https://appgw.conviva.com", method: .post);
CATAppAnalytics.createTracker(namespace: "AppAnalytics", customerKey: "345128905673421", network: networkConfig)

//ObjC
CATNetworkConfiguration *networkConfig = [[CATNetworkConfiguration alloc] initWithEndpoint:@"https://appgw.conviva.com" method:SPHttpMethodPost];
[CATAppAnalytics createTrackerWithNamespace:@"AppAnalytics" customerKey:@"678367802" network:networkConfig];

# Set the user id (viewer id)
tracker.subject.userId = @"user_id";

# Extend tracking to track your application specific events and state changes
Use the structured event type to track all kinds of events. This event type provides 5 fields to describe the tracked events. The semantics of the values for these 5 fields are flexible and could be customized.

category - Define a broad classification of categories for various types of events, such as button, user actions, state, etc.

action - Define the type of action. For example, click, scroll, submit, add to cart, etc.

label - Label the item under the action or subject of the action.

property - Define the properties associated with the event.

value - Define the value (float number). For example, scroll position, total number of items added to a cart, etc.

Structured event = Structured("my-category", "my-action")
.label("my-label")
.property("my-property")
.value(5);
tracker.track(event);

**Note: If your tracked event cannot be described by the structured event type, please contact your Conviva representative to define the appropriate custom extension.**

