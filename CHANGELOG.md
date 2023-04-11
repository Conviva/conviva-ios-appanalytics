# Changelog

## 0.2.9 (04/11/2023)
* Added required support for flutter.Please refer https://pub.dev/packages/conviva_tracker for more details on how to integrate Conviva AppAnalytics to Flutter iOS apps.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.8 (04/14/2023)
* Added support to auto collect network request(http/https) performance metrics.Supports both NSURLSession and NSURLConnection frameworks.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.7 (02/13/2023)
* Improved screen view tracking by filtering out unnecessary system view controllers. 
* Added x-client-id header field for all events for inernal event routing.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.6 (01/02/2023)
* Fixed an issue where app id set by customer is overwritten by bundle id.
* Using latest schema(1-0-4) for video to app events.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.5 (11/18/2022)
* Support to capture the playback events automatically from ConvivaSDK and reporting to AppAnalytics. If customer does not use ConvivaSDK for Experience Insights/Ad Insights, there is no impact on the event collection and everything else should work seamlessly.
** Note: To enable automatic collection of playback events, ConvivaSDK 4.0.32 or above must be used.
** Note: If user of this sdk also uses ConvivaSDK for Experience Insights/Ad Insights, ConvivaSDK version must be 4.0.28 or above to be compatable with ConvivaAppAnalytics version 0.2.4 or above

## 0.2.4 (11/03/2022)
* Custom Tags support
** Support is added to pass custom data as key-val pairs which are available in each event triggered by sdk and passed to backend.
* Event Index and previous event timestamps are added for each event.
* Event Index and first event timestamp of current session are added for each event.
** Note: If user of this sdk also uses ConvivaSDK for Experience Insights/Ad Insights, ConvivaSDK version must be 4.0.28 or above to be compatable with ConvivaAppAnalytics version 0.2.4 or above

## 0.2.3 (09/01/2022)
* Remote Configuraation support to enable/disable features from backend portal
** Ex: Enable/Disable button click tracking, screen view tracking, installAutotracking etc 
* Renamed buttonClickAutotracking to userClickAutoTracking and deprecated buttonClickAutotracking property which is used to enable/disable button click tracking
* Support to add flag to client id keychain item to access in background as well
** Note: If user of this sdk also uses ConvivaSDK for Experience Insights/Ad Insights, ConvivaSDK version must be 4.0.28 or above to be compatable with ConvivaAppAnalytics version 0.2.3 or above

## 0.2.2 (05/27/2022)
* Fixed clid duplication issue
* Support for low power mode
* Monitor cpu usage of the app

## 0.2.1 (04/25/2022)
* Fixed library version reporting issue

## 0.2.1 (04/25/2022)
* Fixed library version reporting issue

## 0.2.0 (04/19/2022)
* Auto capture of UIButton clicks
* Screen view tracking for both iOS and tvOS
* Periodic heart beat and api to control heart beat frequency and provision to disable
* Screen View load time measuring
* App load time measuring
* Simple tracker initialization api with only two arguments customer key and app name
* Customized user agent string
* Provision to disable method swizzling for screen view and button click auto collection

