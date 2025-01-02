//
//  CISEmitterConfiguration.h
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
#import "CATEventStore.h"
#import "CATRequestCallback.h"

/*!
 @brief An enum for buffer options.
 */
typedef NS_ENUM(NSUInteger, CATBufferOption) {
    /**
     * Sends both GET and POST requests with only a single event.  Can cause a spike in
     * network traffic if used in correlation with a large amount of events.
     */
    CATBufferOptionSingle = 1,
    /**
     * Sends POST requests in groups of 10 events.  This is the default amount of events too
     * package into a POST.  All GET requests will still emit one at a time.
     */
    CATBufferOptionDefaultGroup = 10,
    /**
     * Sends POST requests in groups of 25 events.  Useful for situations where many events
     * need to be sent.  All GET requests will still emit one at a time.
     */
    CATBufferOptionLargeGroup = 25,
    CATBufferOptionHeavyGroup __deprecated_enum_msg("Use BufferOption.largeGroup instead.") = CATBufferOptionLargeGroup
} NS_SWIFT_NAME(CATBufferOption);


NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATEmitterConfigurationProtocol)
@protocol CATEmitterConfigurationProtocol

/**
 * Sets whether the buffer should send events instantly or after the buffer
 * has reached it's limit. By default, this is set to BufferOption Default.
 */
@property () CATBufferOption bufferOption;
/**
 * Maximum number of events collected from the EventStore to be sent in a request.
 */
@property () NSInteger emitRange;
/**
 * Maximum number of threads working in parallel in the tracker to send requests.
 */
@property () NSInteger threadPoolSize;
/**
 * Maximum amount of bytes allowed to be sent in a payload in a GET request.
 */
@property () NSInteger byteLimitGet;
/**
 * Maximum amount of bytes allowed to be sent in a payload in a POST request.
 */
@property () NSInteger byteLimitPost;
/**
 * Callback called for each request performed by the tracker to the collector.
 */
@property (nullable) id<CATRequestCallback> requestCallback;

/**
 * It indicates whether Batching feature is enabled or not.
 */

@property () BOOL batchingEnabled;

/**
 * It indicates the batching interval in seconds.
 */

@property () NSInteger batchingIntervalInSec;

/**
 * It indicates which are the urgent events.
 */

@property(strong) NSArray<NSString *> *urgentEvents;

@end

/**
 * It allows the tracker configuration from the emission perspective.
 * The EmitterConfiguration can be used to setup details about how the tracker should treat the events
 * to emit to the collector.
 */
NS_SWIFT_NAME(CATEmitterConfiguration)
@interface CATEmitterConfiguration : CATConfiguration <CATEmitterConfigurationProtocol>

/**
 * Custom component with full ownership for persisting events before to be sent to the collector.
 * If it's not set the tracker will use a SQLite database as default EventStore.
 */
@property (nullable) id<CATEventStore> eventStore;

/**
 * It sets a default EmitterConfiguration.
 * Default values:
 *         bufferOption = BufferOption.Single;
 *         emitRange = 5;
 *         threadPoolSize = 2;
 *         byteLimitGet = 40000;
 *         byteLimitPost = 40000;
 */
- (instancetype)init;

/**
 * Sets whether the buffer should send events instantly or after the buffer
 * has reached it's limit. By default, this is set to BufferOption Default.
 */
SP_BUILDER_DECLARE(CATBufferOption, bufferOption)
/**
 * Maximum number of events collected from the EventStore to be sent in a request.
 */
SP_BUILDER_DECLARE(NSInteger, emitRange)
/**
 * Maximum number of threads working in parallel in the tracker to send requests.
 */
SP_BUILDER_DECLARE(NSInteger, threadPoolSize)
/**
 * Maximum amount of bytes allowed to be sent in a payload in a GET request.
 */
SP_BUILDER_DECLARE(NSInteger, byteLimitGet)
/**
 * Maximum amount of bytes allowed to be sent in a payload in a POST request.
 */
SP_BUILDER_DECLARE(NSInteger, byteLimitPost)
/**
 * Callback called for each request performed by the tracker to the collector.
 */
SP_BUILDER_DECLARE_NULLABLE(id<CATRequestCallback>, requestCallback)

/**
 * Custom component with full ownership for persisting events before to be sent to the collector.
 * If it's not set the tracker will use a SQLite database as default EventStore.
 */
SP_BUILDER_DECLARE_NULLABLE(id<CATEventStore>, eventStore)

/**
 * It indicates whether Batching feature is enabled or not.
 */

SP_BUILDER_DECLARE(BOOL, batchingEnabled)

/**
 * It indicates the batching interval in seconds.
 */

SP_BUILDER_DECLARE(NSInteger, batchingIntervalInSec)

/**
 * It indicates which are the urgent events.
 */

SP_BUILDER_DECLARE(NSArray<NSString *> *, urgentEvents)

@end

NS_ASSUME_NONNULL_END
