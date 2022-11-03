//
//  Snowplow.h
//  Snowplow
//
//  Copyright (c) 2013-2021 Snowplow Analytics Ltd. All rights reserved.
//
//  This program is licensed to you under the Apache License Version 2.0,
//  and you may not use this file except in compliance with the Apache License
//  Version 2.0. You may obtain a copy of the Apache License Version 2.0 at
//  http://www.apache.org/licenses/LICENSE-2.0.
//
//  Unless required by applicable law or agreed to in writing,
//  software distributed under the Apache License Version 2.0 is distributed on
//  an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
//  express or implied. See the Apache License Version 2.0 for the specific
//  language governing permissions and limitations there under.
//
//  Authors: Jonathan Almeida, Joshua Beemster
//  Copyright: Copyright (c) 2013-2021 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>

// Macros to define what OS is running:
// 1. iOS: iOS == 1; OSX == 1; tvOS == 0 ; watchOS == 0
// 2. OSX: iOS == 0; OSX == 1; tvOS == 0
// 3. TV:  iOS == 1; OSX == 1; tvOS == 1
#define SNOWPLOW_TARGET_IOS (TARGET_OS_IPHONE && TARGET_OS_MAC && !(TARGET_OS_TV) && !(TARGET_OS_WATCH))
#define SNOWPLOW_TARGET_OSX (!(TARGET_OS_IPHONE) && TARGET_OS_MAC && !(TARGET_OS_TV))
#define SNOWPLOW_TARGET_TV  (TARGET_OS_IPHONE && TARGET_OS_MAC && TARGET_OS_TV)
#define SNOWPLOW_TARGET_WATCHOS (TARGET_OS_WATCH)

// Macros for iOS Versions
#if SNOWPLOW_TARGET_IOS
#import <UIKit/UIDevice.h>
#define SNOWPLOW_iOS_8_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
#define SNOWPLOW_iOS_9_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0)
#endif

// Macros for builder pattern
#define SP_ESCAPE(...) __VA_ARGS__
#define SP_BUILDER_DECLARE(type, prop) - (instancetype)prop:(type)value NS_SWIFT_NAME(prop(_:));
#define SP_BUILDER_DECLARE_NULLABLE(type, prop) - (instancetype)prop:(nullable type)value NS_SWIFT_NAME(prop(_:));
#define SP_BUILDER_METHOD(type, prop) - (instancetype)prop:(type)value { self.prop = value; return self; }
#define SP_DIRTYFLAG(prop) @property BOOL prop##Updated;
#define SP_DIRTY_GETTER(type, prop) - (type)prop { return (!self.sourceConfig || self.prop##Updated) ? super.prop : self.sourceConfig.prop; }


@interface CATConstants : NSObject

// --- Version

extern NSString * const kCATVersion;
extern NSString * const kCATVersionPrefix;

// --- Dictionary keys

extern NSString * const kCATInstallationUserId;

// --- Emitter

extern NSString * const kCATContentTypeHeader;
extern NSString * const kCATAcceptContentHeader;
extern NSInteger  const kCATDefaultBufferTimeout;
extern NSString * const kCATEndpointPost;
extern NSString * const kCATEndpointGet;

// --- Schema Paths

extern NSString * const kCATIglu;
extern NSString * const kCATSnowplowVendor;
extern NSString * const kCATSchemaTag;
extern NSString * const kCATPayloadDataSchema;
extern NSString * const kCATUserTimingsSchema;
extern NSString * const kCATScreenViewSchema;
extern NSString * const kCATUnstructSchema;
extern NSString * const kCATContextSchema;
extern NSString * const kCATMobileContextSchema;
extern NSString * const kCATDesktopContextSchema;
extern NSString * const kCATSessionContextSchema;
extern NSString * const kCATScreenContextSchema;
extern NSString * const kCATGeoContextSchema;
extern NSString * const kCATConsentWithdrawnSchema;
extern NSString * const kCATConsentDocumentSchema;
extern NSString * const kCATConsentGrantedSchema;
extern NSString * const kCATPushNotificationSchema;
extern NSString * const kCATApplicationContextSchema;
extern NSString * const kCATBackgroundSchema;
extern NSString * const kCATForegroundSchema;
extern NSString * const kCATErrorSchema;
extern NSString * const kCATApplicationInstallSchema;
extern NSString * const kCATGdprContextSchema;
extern NSString * const kCATDiagnosticErrorSchema;
extern NSString * const kCATConvivaEventInfoSchema;
extern NSString * const kCATConvivaCustomTagsSchema;

// --- Event Keys

extern NSString * const kCATEventPageView;
extern NSString * const kCATEventStructured;
extern NSString * const kCATEventUnstructured;
extern NSString * const kCATEventEcomm;
extern NSString * const kCATEventEcommItem;

// --- General Keys

extern NSString * const kCATSchema;
extern NSString * const kCATData;
extern NSString * const kCATEvent;
extern NSString * const kCATEid;
extern NSString * const kCATTimestamp;
extern NSString * const kCATTrueTimestamp;
extern NSString * const kCATSentTimestamp;
extern NSString * const kCATTrackerVersion;
extern NSString * const kCATAppId;
extern NSString * const kCATNamespace;
extern NSString * const kCATUid;
extern NSString * const kCATContext;
extern NSString * const kCATContextEncoded;
extern NSString * const kCATUnstructured;
extern NSString * const kCATUnstructuredEncoded;

// --- Subject

extern NSString * const kCATPlatform;
extern NSString * const kCATResolution;
extern NSString * const kCATViewPort;
extern NSString * const kCATColorDepth;
extern NSString * const kCATTimezone;
extern NSString * const kCATLanguage;
extern NSString * const kCATIpAddress;
extern NSString * const kCATUseragent;
extern NSString * const kCATNetworkUid;
extern NSString * const kCATDomainUid;

// --- Platform Generic

extern NSString * const kCATPlatformOsType;
extern NSString * const kCATPlatformOsVersion;
extern NSString * const kCATPlatformDeviceManu;
extern NSString * const kCATPlatformDeviceModel;

// --- Mobile Context

extern NSString * const kCATMobileCarrier;
extern NSString * const kCATMobileAppleIdfa;
extern NSString * const kCATMobileAppleIdfv;
extern NSString * const kCATMobileNetworkType;
extern NSString * const kCATMobileNetworkTech;
extern NSString * const kCATMobilePhysicalMemory;
extern NSString * const kCATMobileAppAvailableMemory;
extern NSString * const kCATMobileBatteryLevel;
extern NSString * const kCATMobileBatteryState;
extern NSString * const kCATMobileLowPowerMode;
extern NSString * const kCATMobileAvailableStorage;
extern NSString * const kCATMobileTotalStorage;

extern NSString * const kCATMobileCPUUsage;

// --- Application Context
extern NSString * const kCATApplicationVersion;
extern NSString * const kCATApplicationBuild;

// --- Session Context

extern NSString * const kCATSessionUserId;
extern NSString * const kCATSessionId;
extern NSString * const kCATSessionPreviousId;
extern NSString * const kCATSessionIndex;
extern NSString * const kCATSessionStorage;
extern NSString * const kCATSessionFirstEventId;
extern NSString * const kSPSessionFirstEventTimestamp;
extern NSString * const kSPSessionEventIndex;
extern NSString * const kSPSessionPreviousEventTimestamp;

// --- Geo-Location Context

extern NSString * const kCATGeoLatitude;
extern NSString * const kCATGeoLongitude;
extern NSString * const kCATGeoLatLongAccuracy;
extern NSString * const kCATGeoAltitude;
extern NSString * const kCATGeoAltitudeAccuracy;
extern NSString * const kCATGeoBearing;
extern NSString * const kCATGeoSpeed;
extern NSString * const kCATGeoTimestamp;

// --- Screen Context
extern NSString * const kCATScreenName;
extern NSString * const kCATScreenType;
extern NSString * const kCATScreenId;
extern NSString * const kCATScreenViewController;
extern NSString * const kCATScreenTopViewController;

// --- Page View Event

extern NSString * const kCATPageUrl;
extern NSString * const kCATPageTitle;
extern NSString * const kCATPageRefr;

// --- Structured Event

extern NSString * const kCATStuctCategory;
extern NSString * const kCATStuctAction;
extern NSString * const kCATStuctLabel;
extern NSString * const kCATStuctProperty;
extern NSString * const kCATStuctValue;

// --- E-commerce Transaction Event

extern NSString * const kCATEcommId;
extern NSString * const kCATEcommTotal;
extern NSString * const kCATEcommAffiliation;
extern NSString * const kCATEcommTax;
extern NSString * const kCATEcommShipping;
extern NSString * const kCATEcommCity;
extern NSString * const kCATEcommState;
extern NSString * const kCATEcommCountry;
extern NSString * const kCATEcommCurrency;

// --- E-commerce Transaction Item Event

extern NSString * const kCATEcommItemId;
extern NSString * const kCATEcommItemSku;
extern NSString * const kCATEcommItemName;
extern NSString * const kCATEcommItemCategory;
extern NSString * const kCATEcommItemPrice;
extern NSString * const kCATEcommItemQuantity;
extern NSString * const kCATEcommItemCurrency;

// --- Consent Granted Event
extern NSString * const kCATCgExpiry;

// --- Consent Withdrawn Event
extern NSString * const kCATCwAll;

// --- Consent Document Event
extern NSString * const kCATCdId;
extern NSString * const kCATCdVersion;
extern NSString * const kCATCdName;
extern NSString * const kCATCdDescription;

// --- Screen View Event

extern NSString * const kCATSvName;
extern NSString * const kCATSvType;
extern NSString * const kCATSvScreenId;
extern NSString * const kCATSvPreviousName;
extern NSString * const kCATSvPreviousType;
extern NSString * const kCATSvPreviousScreenId;
extern NSString * const kCATSvTransitionType;
extern NSString * const kCATSvViewController;
extern NSString * const kCATSvTopViewController;

// --- User Timing Event

extern NSString * const kCATUtCategory;
extern NSString * const kCATUtVariable;
extern NSString * const kCATUtTiming;
extern NSString * const kCATUtLabel;

// --- Push Notification Event

extern NSString * const kCATPushAction;
extern NSString * const kCATPushTrigger;
extern NSString * const kCATPushDeliveryDate;
extern NSString * const kCATPushCategoryId;
extern NSString * const kCATPushThreadId;
extern NSString * const kCATPushNotification;
extern NSString * const kCATPnTitle;
extern NSString * const kCATPnSubtitle;
extern NSString * const kCATPnBody;
extern NSString * const kCATPnBadge;
extern NSString * const kCATPnSound;
extern NSString * const kCATPnLaunchImageName;
extern NSString * const kCATPnUserInfo;
extern NSString * const kCATPnAttachments;
extern NSString * const kCATPnAttachmentId;
extern NSString * const kCATPnAttachmentUrl;
extern NSString * const kCATPnAttachmentType;

// --- Background Event

extern NSString * const kCATBackgroundIndex;

// --- Foreground Event

extern NSString * const kCATForegroundIndex;

// --- Error Event

extern NSString * const kCATErrorMessage;
extern NSString * const kCATErrorStackTrace;
extern NSString * const kCATErrorName;
extern NSString * const kCATErrorLanguage;

extern NSString * const kCATErrorTrackerUrl;
extern NSString * const kCATErrorTrackerProtocol;
extern NSString * const kCATErrorTrackerMethod;

// --- Install tracking

extern NSString * const kCATInstalledBefore;
extern NSString * const kCATInstallTimestamp;
extern NSString * const kCATPreviousInstallVersion;
extern NSString * const kCATPreviousInstallBuild;

// --- GDPR Context

extern NSString * const kCATBasisForProcessing;
extern NSString * const kCATDocumentId;
extern NSString * const kCATDocumentVersion;
extern NSString * const kCATDocumentDescription;

// --- Tracker Diagnostic

extern NSString * const kCATDiagnosticErrorMessage;
extern NSString * const kCATDiagnosticErrorStack;
extern NSString * const kCATDiagnosticErrorClassName;
extern NSString * const kCATDiagnosticErrorExceptionName;

/**
 * Different modes of prewarm-detection
 * KeepNone = No app start events are allowed
 * ActivePrewarm = Only detect prewarming using ActivePrewarm environment
 * DoubleDispatch = Only detect prewarming using double dispatch method
 * ActivePrewarmOrDoubleDispatch = Detect prewarming using both ActivePrewarm and double dispatch
 * KeepAll = All app start events are allowed
 */
typedef NS_ENUM(NSInteger, CATPrewarmDetectionMode) {
  CATPrewarmDetectionModeKeepNone = 0,
  CATPrewarmDetectionModeActivePrewarm = 1,
  CATPrewarmDetectionModeDoubleDispatch = 2,
  CATPrewarmDetectionModeActivePrewarmOrDoubleDispatch = 3,
  CATPrewarmDetectionModeKeepAll = 4
};

extern NSInteger const kCATDefaultHBInterval;
@end
