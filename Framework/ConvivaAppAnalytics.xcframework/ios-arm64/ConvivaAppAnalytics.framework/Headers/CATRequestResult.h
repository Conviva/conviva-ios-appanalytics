//
//  CISRequestResult.h
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

NS_SWIFT_NAME(CATRequestResult)
@interface CATRequestResult : NSObject

/// Returns the success of the request operation.
@property (nonatomic, readonly) BOOL isSuccessful;
/// Returns the stored index array, needed to remove the events after sending.
@property (nonatomic, readonly) NSArray<NSNumber *> *storeIds;

/// http status code
@property (nonatomic, readonly) NSInteger statusCode;

@property (nonatomic, readonly) BOOL overSize;

/// Remote config version from CTP
@property (nonatomic, readonly) NSString *rcv;

/**
 * Creates a request result object
 * @param statusCode http status code
 * @param storeIds the event indexes in the database
 */
- (instancetype)initWithStatusCode:(NSInteger)statusCode storeIds:(NSArray<NSNumber *> *)storeIds overSize:(BOOL)overSize rcv:(NSString *)rcv;

- (BOOL) shouldRetry;

@end
