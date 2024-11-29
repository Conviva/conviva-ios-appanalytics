//
//  CISTrackerConfiguration.h
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
//  Authors: Alex Benini
//  Copyright: Copyright (c) 2013-2021 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"
#import "CATDevicePlatform.h"
#import "CATLoggerDelegate.h"

@class CATCustomEventTrackingConfiguration;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATTrackerConfigurationProtocol)
@protocol CATTrackerConfigurationProtocol

/**
 * Identifer of the app.
 */
@property () NSString *appId;

/**
 * It sets the device platform the tracker is running on.
 */
@property () CATDevicePlatform devicePlatform;
/**
 * It indicates whether the JSON data in the payload should be base64 encoded.
 */
@property () BOOL base64Encoding;

/**
 * It sets the log level of tracker logs.
 */
@property () CATLogLevel logLevel;
/**
 * It sets the logger delegate that receive logs from the tracker.
 */
@property (nullable) id<CATLoggerDelegate> loggerDelegate;

/**
 * Whether application context is sent with all the tracked events.
 */
@property () BOOL applicationContext;
/**
 * Whether mobile/platform context is sent with all the tracked events.
 */
@property () BOOL platformContext;
/**
 * Whether geo-location context is sent with all the tracked events.
 */
@property () BOOL geoLocationContext;
/**
 * Whether session context is sent with all the tracked events.
 */
@property () BOOL sessionContext;
/**
 * Whether deepLink context is sent with all the ScreenView events.
 */
@property () BOOL deepLinkContext;
/**
 * Whether screen context is sent with all the tracked events.
 */
@property () BOOL screenContext;
/**
 * Whether enable automatic tracking of ScreenView events.
 */
@property () BOOL screenViewAutotracking;
/**
 * Whether enable automatic tracking of background and foreground transitions.
 */
@property () BOOL lifecycleAutotracking;
/**
 * Whether enable automatic tracking of install event.
 */
@property () BOOL installAutotracking;
/**
 * Whether enable crash reporting.
 */
@property () BOOL exceptionAutotracking;
/**
 * Whether enable diagnostic reporting.
 */
@property () BOOL diagnosticAutotracking;
/**
 * Decorate the v_tracker field in the tracker protocol.
 * @note Do not use. Internal use only.
 */
@property (nonatomic, nullable) NSString *trackerVersionSuffix;

/**
 * Whether enable app load time.
 */
@property () CATPrewarmDetectionMode prewarmDetectionMode;

/**
 * Whether enable button click auto tracking.
 */
@property () BOOL buttonClickAutotracking DEPRECATED_MSG_ATTRIBUTE("Use userClickAutotracking instead");

/**
 * Whether enable user click auto tracking.
 */
@property () BOOL userClickAutotracking;

/**
 * Whether to enable/disable perodic heart beat.
 */
@property () BOOL enablePeriodicHeartbeat;

/**
 *  Perodic heart beat interval.
 */
@property () NSInteger periodicHeartbeatInterval;


/**
 * Whether enable custom event tracking
 */
@property () CATCustomEventTrackingConfiguration* customEventTrackingConfiguration;

@end

/**
 * This class represents the configuration of the tracker and the core tracker properties.
 * The TrackerConfiguration can be used to setup the tracker behaviour indicating what should be
 * tracked in term of automatic tracking and contexts/entities to track with the events.
 */
NS_SWIFT_NAME(CATTrackerConfiguration)
@interface CATTrackerConfiguration : CATConfiguration <CATTrackerConfigurationProtocol>

/**
 * It sets a default TrackerConfiguration.
 * Default values:
 *         devicePlatform = DevicePlatform.Mobile;
 *         base64encoding = false;
 *         logLevel = LogLevel.OFF;
 *         loggerDelegate = null;
 *         sessionContext = false;
 *         deepLinkContext = false;
 *         applicationContext = false;
 *         platformContext = true;
 *         geoLocationContext = false;
 *         screenContext = false;
 *         screenViewAutotracking = false;
 *         lifecycleAutotracking = false;
 *         installAutotracking = false;
 *         exceptionAutotracking = false;
 *         diagnosticAutotracking = false;
 *         buttonClickAutotracking = false;
 *         userClickAutotracking = false;
 *         enablePeriodicHeartbeat = false;
 *         periodicHeartbeatInterval = 40; //secs
 *         customEventTracking = true;
 *
 */
- (instancetype)init;

/**
 * Identifer of the app.
 */
SP_BUILDER_DECLARE(NSString *, appId)
/**
 * It sets the device platform the tracker is running on.
 */
SP_BUILDER_DECLARE(CATDevicePlatform, devicePlatform)
/**
 * It indicates whether the JSON data in the payload should be base64 encoded.
 */
SP_BUILDER_DECLARE(BOOL, base64Encoding)
/**
 * It sets the log level of tracker logs.
 */
SP_BUILDER_DECLARE(CATLogLevel, logLevel)
/**
 * It sets the logger delegate that receive logs from the tracker.
 */
SP_BUILDER_DECLARE_NULLABLE(id<CATLoggerDelegate>, loggerDelegate)
/**
 * Whether application context is sent with all the tracked events.
 */
SP_BUILDER_DECLARE(BOOL, applicationContext)
/**
 * Whether mobile/platform context is sent with all the tracked events.
 */
SP_BUILDER_DECLARE(BOOL, platformContext)
/**
 * Whether geo-location context is sent with all the tracked events.
 */
SP_BUILDER_DECLARE(BOOL, geoLocationContext)
/**
 * Whether session context is sent with all the tracked events.
 */
SP_BUILDER_DECLARE(BOOL, sessionContext)
/**
 * Whether screen context is sent with all the tracked events.
 */
SP_BUILDER_DECLARE(BOOL, screenContext)
/**
 * Whether deepLink context is sent with all the ScreenView events.
 */
SP_BUILDER_DECLARE(BOOL, deepLinkContext)
/**
 * Whether enable automatic tracking of ScreenView events.
 */
SP_BUILDER_DECLARE(BOOL, screenViewAutotracking)
/**
 * Whether enable automatic tracking of background and foreground transitions.
 */
SP_BUILDER_DECLARE(BOOL, lifecycleAutotracking)
/**
 * Whether enable automatic tracking of install event.
 */
SP_BUILDER_DECLARE(BOOL, installAutotracking)
/**
 * Whether enable crash reporting.
 */
SP_BUILDER_DECLARE(BOOL, exceptionAutotracking)
/**
 * Whether enable diagnostic reporting.
 */
SP_BUILDER_DECLARE(BOOL, diagnosticAutotracking)
/**
 * Internal use only.
 */
SP_BUILDER_DECLARE(NSString *, trackerVersionSuffix)

/**
 * Whether enable app load time.
 */
SP_BUILDER_DECLARE(CATPrewarmDetectionMode, prewarmDetectionMode)

/**
 * Whether enable automatic tracking of button click events.
 */
SP_BUILDER_DECLARE(BOOL, buttonClickAutotracking)

/**
 * Whether enable automatic tracking of user click events.
 */
SP_BUILDER_DECLARE(BOOL, userClickAutotracking)

/**
 * Whether to enable/disable perodic heart beat.
 */
SP_BUILDER_DECLARE(BOOL, enablePeriodicHeartbeat)

/**
 * Perodic heart beat interval.
 */
SP_BUILDER_DECLARE(NSInteger, periodicHeartbeatInterval)

@end

NS_ASSUME_NONNULL_END
