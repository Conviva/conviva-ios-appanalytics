//
//  SPSnowplow.h
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
#import "CATTrackerController.h"
#import "CATNetworkConfiguration.h"
#import "CATTrackerConfiguration.h"
#import "CATRemoteConfiguration.h"
#import "CATConfigurationBundle.h"

NS_ASSUME_NONNULL_BEGIN

@class CATServiceProvider;
@class CATConfigurationProvider;

/**
 * Entry point to instance a new Snowplow tracker.
 */
NS_SWIFT_NAME(CATAppAnalytics)
@interface CATAppAnalytics : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

/// Remote Configuration

/**
 * Setup a single or a set of tracker instances which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The trackers configuration is automatically download from the endpoint indicated in the `RemoteConfiguration`
 * passed as argument. For more details see `RemoteConfiguration`.
 *
 * The method is asynchronous and you can receive the list of the created trackers in the callbacks once the trackers are created.
 * The callback can be called multiple times in case a cached configuration is ready and later a fetched configuration is available.
 * You can also pass as argument a default configuration in case there isn't a cached configuration and it's not able to download
 * a new one. The downloaded configuration updates the cached one only if the configuration version is greater than the cached one.
 * Otherwise the cached one is kept and the callback is not called.
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param remoteConfiguration The remote configuration used to indicate where to download the configuration from.
 * @param customerKey - Customer Key.
 * @param defaultBundles The default configuration passed by default in case there isn't a cached version and it's able to download a new one.
 * @param onSuccess The callback called when a configuration (cached or downloaded) is set It passes the list of the namespaces associated
 *                  to the created trackers.
 */
+ (void)setupWithRemoteConfiguration:(CATRemoteConfiguration *)remoteConfiguration
                         customerKey:(NSString*)customerKey
         defaultConfigurationBundles:(nullable NSArray<CATConfigurationBundle *> *)defaultBundles
                           onSuccess:(void(^)(NSArray<NSString *> * _Nullable namespaces))onSuccess NS_SWIFT_NAME(setup(remoteConfiguration:customerKey:defaultConfiguration:onSuccess:));

/**
 * Reconfigure, create or delete the trackers based on the configuration downloaded remotely.
 * The trackers configuration is automatically download from the endpoint indicated in the `RemoteConfiguration`
 * previously used to setup the trackers.
 *
 * The method is asynchronous and you can receive the list of the created trackers in the callbacks once the trackers are created.
 * The downloaded configuration updates the cached one only if the configuration version is greater than the cached one.
 * Otherwise the cached one is kept and the callback is not called.
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey - Customer Key.
 * @param onSuccess The callback called when a configuration (cached or downloaded) is set It passes the list of the namespaces associated
 *                  to the created trackers.
 */
+ (void)refreshIfRemoteUpdate:(NSString*)customerKey
                    onSuccess:(void(^)(NSArray<NSString *> * _Nullable namespaces))onSuccess
                    NS_SWIFT_NAME(refresh(onSuccess:customerKey:));

/// Standard Configuration

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey appName:(NSString*)appName NS_SWIFT_NAME(createTracker(customerKey:appName:));


/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                                 appName:(NSString*)appName
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:appName:configurations:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 * @param customerKey Customer key provided by conviva.
 * @param appName Uniquely identifiable app name.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey appName:(NSString*)appName namespace:(NSString *)namespace NS_SWIFT_NAME(createTracker(customerKey:appName:namespace:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:configurations:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithCustomerKey:(NSString*)customerKey
                                                 network:(CATNetworkConfiguration *)networkConfiguration
                                          configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(customerKey:network:configurations:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param endpoint The URL of the collector.
 * @param method The method for the requests to the collector (GET or POST).
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace customerKey:(NSString*)customerKey endpoint:(NSString *)endpoint method:(CATHttpMethod)method NS_SWIFT_NAME(createTracker(namespace:customerKey:endpoint:method:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace customerKey:(NSString*)customerKey network:(CATNetworkConfiguration *)networkConfiguration NS_SWIFT_NAME(createTracker(namespace:customerKey:network:));

/**
 * Create a new tracker instance which will be used inside the app to track events.
 * The app can run multiple tracker instances which will be identified by string `namespaces`.
 * The tracker will be configured with default setting and only the collector endpoint URL need
 * to be passed for the configuration.
 * For the default configuration of the tracker see `TrackerConfiguration(String)`.
 *
 * To configure tracker with more details see `createTracker(Context, String, NetworkConfiguration, Configuration...)`
 * To use the tracker as singleton see `getDefaultTracker()`
 *
 * IMPORTANT: The EventStore will persist all the events that have been tracked but not yet sent.
 * Those events are attached to the namespace.
 * If the tracker is removed or the app relaunched with a different namespace, those events can't
 * be sent to the collector and they remain in a zombie state inside the EventStore.
 * To remove all the zombie events you can an internal method `removeUnsentEventsExceptForNamespaces` on `SPSQLEventStore`
 * which will delete all the EventStores instanced with namespaces not listed in the passed list.
 *
 * @param namespace The namespace used to identify the current tracker among the possible
 *                  multiple tracker instances.
 * @param customerKey Customer key provided by conviva.
 * @param networkConfiguration The NetworkConfiguration object with settings for the communication with the
 *                collector.
 * @param configurations All the configuration objects with the details about the fine tuning of
 *                       the tracker.
 * @return The tracker instance created.
 */
+ (id<CATTrackerController>)createTrackerWithNamespace:(NSString *)namespace customerKey:(NSString*)customerKey
network:(CATNetworkConfiguration *)networkConfiguration configurations:(NSArray<CATConfiguration *> *)configurations NS_SWIFT_NAME(createTracker(namespace:customerKey:network:configurations:));

/**
 * The default tracker instance is the first created in the app, but that can be overridden programmatically
 * calling `setTrackerAsDefault(TrackerController)`.
 */
+ (nullable id<CATTrackerController>)defaultTracker;

/**
 * Using the namespace identifier is possible to get the trackerController if already instanced.
 *
 * @param namespace The namespace that identifies the tracker.
 * @return The tracker if it exist with that namespace.
 */
+ (nullable id<CATTrackerController>)trackerByNamespace:(NSString *)namespace NS_SWIFT_NAME(tracker(namespace:));

/**
 * Set the passed tracker as default tracker if it's registered as an active tracker in the app.
 * If the passed instance is of a tracker which is already removed (see `removeTracker`) then it can't become the new default tracker
 * and the operation fails.
 *
 * @param trackerController The new default tracker.
 * @return Whether the tracker passed is registered among the active trackers of the app.
 */
+ (BOOL)setTrackerAsDefault:(id<CATTrackerController>)trackerController NS_SWIFT_NAME(setAsDefault(tracker:));

/**
 * A tracker can be removed from the active trackers of the app.
 * Once it has been removed it can't be added again or set as default.
 * The unique way to resume a removed tracker is creating a new tracker with same namespace and
 * same configurations.
 * The removed tracker is always stopped.
 *
 * @param trackerController The tracker controller to remove.
 * @return Whether it has been able to remove it.
 */
+ (BOOL)removeTracker:(id<CATTrackerController>)trackerController NS_SWIFT_NAME(remove(tracker:));

/**
 * Remove all the trackers.
 * The removed tracker is always stopped.
 * See `removeTracker(TrackerController)`
 */
+ (void)removeAllTrackers NS_SWIFT_NAME(removeAllTrackers());

/**
 * @return Set of namespace of the active trackers in the app.
 */
+ (NSArray<NSString *> *)instancedTrackerNamespaces;

/**
 * @return AppAnalytics instance.
 */
+ (instancetype)sharedInstance;


+ (void) mergeClientConfigs:(NSArray<CATConfiguration *>*) clientConfigs
           withRemoteConfig:(NSArray<CATConfiguration *>*) remoteConfigs;

/**
 * @return Client Id.
 */
- (NSString*) getClientId;

/**
 * @return Get last event info.
 */
- (NSDictionary *) getLastEventInfo:(long long)eventTimestamp;



/* Remote config refresh interval */
@property (nonatomic) NSInteger remoteCfgRefreshInterval;

@property (nonatomic, nonnull, readonly) NSMutableDictionary<NSString *, CATServiceProvider *> *serviceProviderInstances;
@property (nonatomic, nullable, readonly) CATConfigurationProvider *configurationProvider;

@end

NS_ASSUME_NONNULL_END
