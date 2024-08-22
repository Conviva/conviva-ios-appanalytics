//
//  CATEventBase.h
//  Snowplow
//
//  Copyright (c) 2021 Snowplow Analytics Ltd. All rights reserved.
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
//  Authors: Joshua Beemster
//  Copyright: Copyright (c) 2021 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>
#import "CATSelfDescribingJson.h"
#import "CATConstants.h"
#import "CATTrackerStateSnapshot.h"

@class CATPayload;
@class CATTracker;

/// An enum for screen types.
typedef NS_ENUM(NSInteger, CATScreenType) {
    // sourced from `View Controller Catalog for iOS`
    CATScreenTypeDefault,
    CATScreenTypeNavigation,
    CATScreenTypeTabBar,
    CATScreenTypePageView,
    CATScreenTypeSplitView,
    CATScreenTypePopoverPresentation,
    CATScreenTypeModal,
    CATScreenTypeCombined
} NS_SWIFT_NAME(CATScreenType);

NSString * _Nullable stringWithSPScreenType(CATScreenType screenType);

NS_ASSUME_NONNULL_BEGIN

/// The inspectable properties of the event used to generate contexts.
NS_SWIFT_NAME(CATInspectableEvent)
@protocol CATInspectableEvent <NSObject>

/// The schema of the event
@property (nonatomic, readonly, nullable) NSString *schema;
/// The name of the event
@property (nonatomic, readonly, nullable) NSString *eventName;
/// The payload of the event
@property (nonatomic, readonly) NSDictionary<NSString *, NSObject *> *payload;

/// The tracker state at the time the event was sent.
@property (nonatomic, readonly) id<CATTrackerStateSnapshot> state;

/// Add payload values to the event.
/// @param payload Map of values to add to the event payload.
/// @return Whether or not the values have been successfully added to the event payload.
- (BOOL)addPayloadValues:(NSDictionary<NSString *, NSObject *> *)payload;

@end


/// This class has the basic functionality needed to represent all events
NS_SWIFT_NAME(CATEvent)
@interface CATEvent : NSObject

/// The user event timestamp in milliseconds (epoch time).
@property (nonatomic, nullable) NSDate *trueTimestamp;

/// The contexts attached to the event.
@property (nonatomic) NSMutableArray<CATSelfDescribingJson *> *contexts;

/// The payload of the event.
@property (nonatomic, readonly) NSDictionary<NSString *, NSObject *> *payload;

SP_BUILDER_DECLARE_NULLABLE(NSDate *, trueTimestamp)
SP_BUILDER_DECLARE(NSMutableArray<CATSelfDescribingJson *> *, contexts)

/**
 * Hook method called just before the event processing in order to execute special operations.
 * @note Internal use only - Don't use in production, it can change without notice.
 */
- (void)beginProcessingWithTracker:(CATTracker *)tracker;

/**
 * Hook method called just after the event processing in order to execute special operations.
 * @note Internal use only - Don't use in production, it can change without notice.
 */
- (void)endProcessingWithTracker:(CATTracker *)tracker;
@end

/// The properties for all the self-describing events.
NS_SWIFT_NAME(CATSelfDescribingAbstract)
@interface CATSelfDescribingAbstract : CATEvent

/// The schema of the event.
@property (nonatomic, readonly) NSString *schema;

@end

/// The properties for all the self-describing events.
NS_SWIFT_NAME(CATPrimitiveAbstract)
@interface CATPrimitiveAbstract : CATEvent

/// The name of the event.
@property (nonatomic, readonly) NSString *eventName;

@end

NS_ASSUME_NONNULL_END
