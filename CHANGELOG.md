# Changelog

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

