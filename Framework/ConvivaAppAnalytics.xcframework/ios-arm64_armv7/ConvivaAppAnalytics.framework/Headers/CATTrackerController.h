//
//  CATTrackerController.h
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
#import "CATTrackerConfiguration.h"
#import "CATNetworkConfiguration.h"

#import "CATSubjectController.h"
#import "CATSessionController.h"
#import "CATEmitterController.h"
#import "CATNetworkController.h"
#import "CATGDPRController.h"
#import "CATGlobalContextsController.h"

#import "CATEventBase.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATTrackerController)
@protocol CATTrackerController <CATTrackerConfigurationProtocol>

/** Version of the tracker. */
@property (readonly, nonatomic) NSString *version;
/**
 * Whether the tracker is running and able to collect/send events.
 * See `pause()` and `resume()`.
 */
@property (readonly, nonatomic) BOOL isTracking;
/**
 * Namespace of the tracker.
 * It is used to identify the tracker among multiple trackers running in the same app.
 */
@property (readonly, nonatomic) NSString *namespace;

/**
 * SubjectController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic, nullable) id<CATSubjectController> subject;
/**
 * SessionController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic, nullable) id<CATSessionController> session;
/**
 * NetworkController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic, nullable) id<CATNetworkController> network;
/**
 * EmitterController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic) id<CATEmitterController> emitter;
/**
 * GdprController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic) id<CATGDPRController> gdpr;
/**
 * GlobalContextsController.
 * @apiNote Don't retain the reference. It may change on tracker reconfiguration.
 */
@property (readonly, nonatomic) id<CATGlobalContextsController> globalContexts;

/**
 * Track the event.
 * The tracker will take care to process and send the event assigning `event_id` and `device_timestamp`.
 * @param event The event to track.
 */
- (void)track:(CATEvent *)event;

/**
 * Track custom event.
 * The tracker will pass name and data.
 * @param name The event name.
 * @param data The event data.
 */
- (void)trackCustomEvent:(NSString *)name data:(nonnull NSString*)data;

/**
 * Track custom event.
 * The tracker will pass name and data.
 * @param name The event name.
 * @param eventData The event data.
 */
- (void)trackCustomEvent:(NSString *)name eventData:(nonnull id)eventData;

/**
 * Track custom tags.
 * Pass custom tags
 * @param tags Tags.
 */
- (void)setCustomTags:(NSDictionary *)tags;

/**
 * Track custom tags.
 * Pass custom tags
 * @param category category.
 * @param tags Tags.
 */
- (void)setCustomTags:(NSString *)category tags:(NSDictionary *)tags;

/**
 * Removes all custom tags.
 *
 */
- (void) clearCustomTags;

/**
 * Removes all custom tags.
 *
 */
- (void)clearAllCustomTags;

/**
 * Set custom tags.
 * Pass custom tags
 * @param tagKeys tagKeys.
 */
- (void)clearCustomTags:(NSArray *)tagKeys;

/**
 * Pause the tracker.
 * The tracker will stop any new activity tracking but it will continue to send remaining events
 * already tracked but not sent yet.
 * Calling a track method will not have any effect and event tracked will be lost.
 */
- (void)pause;
/**
 * Resume the tracker.
 * The tracker will start tracking again.
 */
- (void)resume;

@end

NS_ASSUME_NONNULL_END
