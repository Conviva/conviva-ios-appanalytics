# Changelog

## 1.7.0 (12/16/2025)
* Added support to report Ad session events to DPI (Attempt, End, etc.).
* Improved App Load Time metric by collecting more data.

## 1.6.0 (11/19/2025)
* Crash and ANR reporting has been improved with MetricKit for users on iOS 14+. This delivers deeper insights and faster fixes for a more stable app experience.

## 1.5.0 (10/13/2025)
## 🚀 Enhancements
- **Added Remote Config Support for Request/Response Body Sub-Field Collection Limits**  
  Introduced remote configuration to control the maximum size of request and response bodies eligible for sub-field collection.  
  - **Default limit:** 10 KB  
  - **Maximum recommended limit:** 256 KB (to prevent performance overhead)

## ⚙️ Improvements
- Internal performance and stability optimizations


## 1.1.4 (09/23/2025)
* Resolved an issue where certain network requests on Apple mobile platforms were not being captured by the DPI module.

## 1.2.1 (08/05/2025)
* Improved the Visual Activation system to dynamically update the positions of clickable elements during and after user scroll interactions in complex view hierarchies.

## 1.2.0 (07/31/2025)
* Supports Conviva Visual Activation.

## 1.1.3 (05/21/2025)
* Supports the traceparent header generation and collection.

## 1.0.3 (03/14/2025)
* Sends events enabled by default in code till config is available. Once config is available, honours strictly config.
* Fixed crash issue if both conviva and Firebase are used by app.

## 1.0.2 (02/27/2025)
* Provides flexibility with control of the click event collection, based on any element title, element type, element name, etc.
**NOTE**: To enable controlled collection of click events (iOS), contact Conviva Support.

## 1.0.1 (02/14/2025)
* Introduces Intelligent Collection of Network Request Feature designed to optimize data collection while ensuring flexibility and  actionable insights with reduced volume:
  * Controls network request volume through Activation rules (Collect or Block), which override previous URL-based blocklists.
  * Supports URL-based filtering using hostname, path, scheme, and filtering based on duration and response status code.
**NOTE**: By default, this feature is not enabled during Activation. To enable it, please contact the Conviva Support team. Existing customers will not be impacted if the feature remains disabled, as all changes are fully backward compatible.
* Internal improvements and optimisations

## 1.0.0 (02/01/2025)
* Introduces Event Batching Feature with configurable payload size and interval which is enabled by default to efficiently use the network
* Using dedicated low priority threads(with minimal count) to minimise the impact on application performance
* Clearing remote config cache on customer key or sensor version change
* Improvements to stability of the sdk by efficiently handling synchronisation across threads
* Enhances sending logic by using asynchronous http send mechanism and with decent timeouts

## 0.2.31 (20/09/2024)
* <b>Remote config enhancements:</b>
  * Implements exponential backoff for remote config fetch attempts in case of failures, with a maximum of 3 attempts, each separated by a 5-second interval
  * Enhances version checking for remote config
  * Enhances the remote config fetch timestamp based on server responses
* <b>Retry Logic enhancements:</b>
  * Enhances the retry logic to delete the db entries in response to avoid piling up events on failure cases
* <b>Logging enhancements:</b>
  * Logs all error messages to console
* <b>Other enhancements:</b>
  * Reports custom events properly even if data passed is not valid json.

## 0.2.30 (06/09/2024)
* Supports sending periodic heart beats when application is active in background due to playback.
* Introduces API for setting the conviva identifier.

## 0.2.29 (22/08/2024)
* *Screen views* in SwiftUI apps can now be tracked using the View extension function .convivaAnalyticsScreenView(name: "Screen Name") which sends a custom event with name conviva_custom_screenview(cv_csv) which needs to be mapped per customer account.
* *Button clicks* in SwiftUI apps can now be tracked using the Button extension function .convivaAnalyticsButtonClick(title: "Button Title").
* *Picker (Segment Control)* in SwiftUI apps are now tracked.

## 0.2.28 (08/05/2024)
* Stability improvements

## 0.2.26 (06/27/2024)
* Added support to auto collect network request(http/https) performance metrics for URLSession Asynchronous methods.

## 0.2.25 (06/07/2024)
* Optimised the retry mechanism of events in case of failures.

## 0.2.24 (05/17/2024)
* Removed external dependency of FMDB.
* Fixed random crashes.

## 0.2.23 (04/24/2024)
* Optimizes the payload size by applying *gzip encryption* and *schema optimisation*.
* Supports custom gateway URL by using the unique `CUSTOMER_KEY` associated to each customer.
* Renames the remote configuration URL domain to `*.conviva.com`.
* Updates the default block list of the *Network Request Tracking* feature.
* Reduces the payload size of Network Request Event by limiting the default attributes to targetUrl, method, responseStatusCode and duration. However, the retention of request/response body/header attributes remain unchanged.

## 0.2.22 (03/18/2024)
* Enhances network request & response collection feature to capture Array type data.
* Enhances network request feature by adding collection of query parameters as part as target url.
* Minor fix added to the collection of content-type in network request feature.
* Added the few extensions to default blocklist and removed remote_config.json from blocklist

## 0.2.21 (02/13/2024)
* Privacy manifest support added.

## 0.2.20 (01/04/2024)
* Minor changes in button click event.

## 0.2.19 (11/24/2023)
* Fixes the random crashes.

## 0.2.18 (10/27/2023)
* Enhances network request & response collection feature to capture limited (json only, size limit 10kb) and controlled set of information from headers and body.

## 0.2.16 (09/28/2023)
* Added few video extensions and analytics solutions to the default blocklist of network request tracking collection.

## 0.2.15 (08/14/2023)
* Fixed an issue where remote configuration of blocking/unblocking URLs for network request tracking is not applied.
* Fixed event index duplication issue.

## 0.2.14 (07/17/2023)
* Added Crash Exception Handling.
* Added trackCustomEvent API which accepts Object as an argument.
* Minor changes to Network Request Collection.

## 0.2.13 (06/12/2023)
* Enhances applying of the remote configuration at an interval of cacheRefreshInterval which is set to 30 mins by default.
* Fixes the issue of duplicate instance id when the application is crashed and relaunched.
* Enhances the auto collection of screen_view event, by excluding the child views tracking.
* Auto Capture of Segment Control Tracking.
* Reporting Keychain errors as diagnostic errors.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.12 (05/04/2023)
* Added required support for React Native apps.Please refer https://www.npmjs.com/package/@convivainc/conviva-react-native-appanalytics for more details on how to integrate Conviva AppAnalytics to React Native iOS apps.
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

## 0.2.10 (04/26/2023)
* Added event index to client id schema which is useful for efficient session management. 
** Note: Compatable with ConvivaSDK 4.0.34/ConvivaAVFoundation 4.0.40 or above.

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

