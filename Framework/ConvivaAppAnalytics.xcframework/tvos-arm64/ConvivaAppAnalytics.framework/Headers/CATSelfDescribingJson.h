//
//  CATSelfDescribingJson.h
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
//  Authors: Joshua Beemster
//  Copyright: Copyright (c) 2021 Snowplow Analytics Ltd
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>

@class CATPayload;

/*!
 @class CATSelfDescribingJson
 @brief The class that represents self-describing JSONs.

 This class holds the information of a self-describing JSON.

 @see CATPayload
 */
NS_SWIFT_NAME(CATSelfDescribingJson)
@interface CATSelfDescribingJson : NSObject

/// the schema URI for this self-describing JSON.
@property (nonatomic) NSString *schema;
/// Data of the self-describing JSON.
@property (nonatomic, readonly) NSObject *data;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @brief Initializes a newly allocated CATSelfDescribingJson.

 @param schema A valid schema string.
 @param data Data to set for data field of the self-describing JSON, should be an NSDictionary.
 @return An CATSelfDescribingJson.
 */
- (instancetype)initWithSchema:(NSString *)schema andData:(NSObject *)data NS_DESIGNATED_INITIALIZER;

/*!
 @brief Initializes a newly allocated CATSelfDescribingJson.

 @param schema A valid schema string.
 @param data Dictionary to set for data field of the self-describing JSON.
 @return An CATSelfDescribingJson.
 */
- (instancetype)initWithSchema:(NSString *)schema andDictionary:(NSDictionary *)data;

/*!
 @brief Initializes a newly allocated CATSelfDescribingJson.

 @param schema A valid schema string.
 @param data Payload to set for data field of the self-describing JSON.
 @return An CATSelfDescribingJson.
 */
- (instancetype)initWithSchema:(NSString *)schema andPayload:(CATPayload *)data;

/*!
 @brief Initializes a newly allocated CATSelfDescribingJson.

 @param schema A valid schema URI.
 @param data Self-describing JSON to set for data field of the self-describing JSON.
 @return An CATSelfDescribingJson.
 */
- (instancetype)initWithSchema:(NSString *)schema andSelfDescribingJson:(CATSelfDescribingJson *)data;

/*!
 @brief Sets the data field of the self-describing JSON.

 @param data An NSObject to be nested into the data.
 */
- (void) setDataWithObject:(NSObject *)data;

/*!
 @brief Sets the data field of the self-describing JSON.

 @param data An CATPayload to be nested into the data.
 */
- (void) setDataWithPayload:(CATPayload *)data;

/*!
 @brief Sets the data field of the self-describing JSON.

 @param data A self-describing JSON to be nested into the data.
 */
- (void) setDataWithSelfDescribingJson:(CATSelfDescribingJson *)data;

/*!
 @brief Returns the internal NSDictionary of the self-describing JSON.

 @return The self-describing JSON as an NSDictionary.
 */
- (NSDictionary<NSString *, NSObject *> *) getAsDictionary;

/*!
 @brief Returns a string description of the internal dictionary.

 @return The description of the dictionary.
 */
- (NSString *) description;

@end
