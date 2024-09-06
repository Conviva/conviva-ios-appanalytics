//
//  CATContextGenerator.h
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
//  Copyright: Copyright © 2021 Snowplow Analytics.
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>
#import "CATEventBase.h"

@class CATSelfDescribingJson;
@class CATSchemaRuleset;

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Block signature for context generators, takes event information and generates a context.
 @param event informations about the event to process.
 @return a user-generated self-describing JSON.
 */
typedef NSArray<CATSelfDescribingJson *> * _Nullable (^SPGeneratorBlock)(id<CATInspectableEvent> event);

/*!
 @brief Block signature for context filtering, takes event information and decide if the context needs to be generated.
 @param event informations about the event to process.
 @return weather the context has to be generated.
*/
typedef BOOL (^SPFilterBlock)(id<CATInspectableEvent> event);

#pragma mark - SPContextGenerator

/*!
 @protocol CATContextGenerator
 @brief A context generator used to generate global contexts.
 */
NS_SWIFT_NAME(CATContextGenerator)
@protocol CATContextGenerator <NSObject>

/*!
 @brief Takes event information and decide if the context needs to be generated.
 @param event informations about the event to process.
 @return weather the context has to be generated.
 */
- (BOOL)filterFromEvent:(id<CATInspectableEvent>)event;

/*!
 @brief Takes event information and generates a context.
 @param event informations about the event to process.
 @return a user-generated self-describing JSON.
 */
- (nullable NSArray<CATSelfDescribingJson *> *)generatorFromEvent:(id<CATInspectableEvent>)event;

@end

#pragma mark - SPGlobalContext

NS_SWIFT_NAME(CATGlobalContext)
@interface CATGlobalContext : NSObject

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;

/*!
 Initialize a Global Context generator with a custom CATContextGenerator.
 @param generator Implementation of CATContextGenerator protocol.
 */
- (instancetype)initWithContextGenerator:(id<CATContextGenerator>)generator;

/*!
 Initialize a Global Context generator with static contexts.
 @param staticContexts Static contexts added to all the events.
 */
- (instancetype)initWithStaticContexts:(NSArray<CATSelfDescribingJson *> *)staticContexts;
/*!
 Initialize a Global Context generator with a generator block.
 @param generator Generator block able to generate multiple contexts.
 */
- (instancetype)initWithGenerator:(SPGeneratorBlock)generator;

/*!
 Initialize a Global Context generator with static contexts and a ruleset filter.
 @param staticContexts Static contexts added to all the events conforming with `ruleset`.
 @param ruleset Rule set to apply to events to check weather or not the contexts have to be added.
 */
- (instancetype)initWithStaticContexts:(NSArray<CATSelfDescribingJson *> *)staticContexts ruleset:(nullable CATSchemaRuleset *)ruleset;
/*!
 Initialize a Global Context generator with static contexts and a ruleset filter.
 @param generator Generator block able to generate multiple contexts.
 @param ruleset Rule set to apply to events to check weather or not the contexts have to be added.
 */
- (instancetype)initWithGenerator:(SPGeneratorBlock)generator ruleset:(nullable CATSchemaRuleset *)ruleset;

/*!
 Initialize a Global Context generator with static contexts and a ruleset filter.
 @param staticContexts Static contexts added to all the events conforming with `ruleset`.
 @param filter Filter to apply to events to check weather or not the contexts have to be added.
 */
- (instancetype)initWithStaticContexts:(NSArray<CATSelfDescribingJson *> *)staticContexts filter:(nullable SPFilterBlock)filter;
/*!
 Initialize a Global Context generator with static contexts and a ruleset filter.
 @param generator Generator block able to generate multiple contexts.
 @param filter Filter to apply to events to check weather or not the contexts have to be added.
 */
- (instancetype)initWithGenerator:(SPGeneratorBlock)generator filter:(nullable SPFilterBlock)filter NS_DESIGNATED_INITIALIZER;

/*!
 Generate contexts based on event details and internal filter and generator.
 @param event Event details used to filter and generate contexts.
 @return Generated contexts.
 */
- (NSArray<CATSelfDescribingJson *> *)contextsFromEvent:(id<CATInspectableEvent>)event;

@end

NS_ASSUME_NONNULL_END
