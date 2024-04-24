//
//  CATNetworkConnection.h
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
#import "CATRequest.h"
#import "CATRequestResult.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief An enum for HTTP method types.
 */
typedef NS_ENUM(NSInteger, CATHttpMethod) {
    /*! GET request. */
    CATHttpMethodGet,
    /*! POST request. */
    CATHttpMethodPost
} NS_SWIFT_NAME(CATHttpMethodOptions);

/*!
 @brief An enum for HTTP security.
 */
typedef NS_ENUM(NSInteger, CATProtocol) {
    /*! Use HTTP. */
    CATProtocolHttp,
    /*! Use HTTP over TLS. */
    CATProtocolHttps
} NS_SWIFT_NAME(CATProtocolOptions);

/**
 * Interface for the component that
 * sends events to the collector.
 */
NS_SWIFT_NAME(CATNetworkConnection)
@protocol CATNetworkConnection <NSObject>

/**
 * Send requests to the collector.
 * @param requests to send,
 * @return results of the sending operation.
 */
- (NSArray<CATRequestResult *> *)sendRequests:(NSArray<CATRequest *> *)requests;

/**
 * @return http method used to send requests to the collector.
 */
- (CATHttpMethod)httpMethod;

/**
 * @return URL of the collector.
 */
- (NSURL *)url;

- (void)setEncoding:(NSString*)encoding;

@end

NS_ASSUME_NONNULL_END
