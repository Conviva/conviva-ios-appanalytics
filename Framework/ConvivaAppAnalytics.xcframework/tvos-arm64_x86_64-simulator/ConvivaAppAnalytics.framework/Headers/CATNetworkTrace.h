// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/** Possible checkpoint states of network trace */
typedef NS_ENUM(NSInteger, CATNetworkTraceCheckpointState) {
  CATNetworkTraceCheckpointStateUnknown,

  // Network request has been initiated.
  CATNetworkTraceCheckpointStateInitiated,

  // Network request is completed (All necessary uploads for the request is complete).
  CATNetworkTraceCheckpointStateRequestCompleted,

  // Network request has received its first response. There could be more.
  CATNetworkTraceCheckpointStateResponseReceived,

  // Network request has completed (Could be network error/request successful completion).
  CATNetworkTraceCheckpointStateResponseCompleted
};

@protocol CATNetworkResponseHandler <NSObject>

/**
 * Records the size of the file that is uploaded during the request.
 *
 * @param URL The URL object that is being used for uploading from the network request.
 */
- (void)didUploadFileWithURL:(nullable NSURL *)URL;

/**
 * Records the amount of data that is fetched during the request. This can be called multiple times
 * when the network delegate comes back with some data.
 *
 * @param data The data object as received from the network request.
 */
- (void)didReceiveData:(nullable NSData *)data response:(nullable NSURLResponse *)response;

/**
 * Records the size of the file that is fetched during the request. This can be called multiple
 * times when the network delegate comes back with some data.
 *
 * @param URL The URL object as received from the network request.
 */
- (void)didReceiveFileURL:(nullable NSURL *)URL;

/**
 * Records the end state of the network request. This is usually called at the end of the network
 * request with a valid response or an error.
 *
 * @param response Response of the network request.
 * @param error Error with the network request.
 */
- (void)didCompleteRequestWithResponse:(nullable NSURLResponse *)response
                                 error:(nullable NSError *)error;

@end

/**
 * CATNetworkTrace object contains information about an NSURLRequest. Every object contains
 * information about the URL, type of request, and details of the response.
 */
NS_EXTENSION_UNAVAILABLE("Conviva Performance is not supported for extensions.")
NS_SWIFT_NAME(CATNetworkTrace)
@interface CATNetworkTrace : NSObject <CATNetworkResponseHandler>

/** @brief request body. */
@property(nonatomic, nullable, strong) id requestBody;

/** @brief response body. */
@property(nonatomic, nullable, strong) id responseBody;

/** @brief response headers. */
@property(nonatomic, nullable, strong) NSDictionary *responseHeaders;

/** @brief query params. */
@property(nonatomic, nullable, strong) NSDictionary *queryParams;

/** @brief The size of the request. The value is in bytes. */
@property(nonatomic) int64_t requestSize;

/** @brief The response size for the request. The value is in bytes. */
@property(nonatomic) int64_t responseSize;

/** @brief The HTTP response code for the request. */
@property(nonatomic) int32_t responseCode;

/** @brief The duration for the api call. */
@property(nonatomic) double duration;

/** @brief Yes if a valid response code is set, NO otherwise. */
@property(nonatomic) BOOL hasValidResponseCode;

/** @brief The content type of the request as received from the server. */
@property(nonatomic, copy, nullable) NSString *responseContentType;

/** @brief The checkpoint states for the request. The key to the dictionary is the value referred in
 * enum CATNetworkTraceCheckpointState mentioned above. The value is the number of seconds since the
 * reference date.
 */
@property(nonatomic, readonly, nullable) NSDictionary<NSString *, NSNumber *> *checkpointStates;

/** @brief The network request object. */
@property(nonatomic, readonly, nullable) NSURLRequest *URLRequest;

/** @brief The URL string with all the query params cleaned. The URL string will be of the format:
 *  scheme:[//[user:password@]host[:port]][/]path.
 */
@property(nonatomic, readonly, nullable) NSString *trimmedURLString;

/** @brief The URL string with all the details.
 */
@property(nonatomic, readonly, nullable) NSString *urlString;

/** @brief Error object received with the network response. */
@property(nonatomic, readonly, nullable) NSError *responseError;

/** Background state of the trace. */
//@property(nonatomic, readonly) CATTraceState backgroundTraceState;

/** @brief List of sessions the trace is associated with. */
//@property(nonnull, atomic, readonly) NSArray<CATSessionDetails *> *sessions;

/** @brief Serial queue to manage usage of session Ids. */
@property(nonatomic, readonly, nonnull) dispatch_queue_t sessionIdSerialQueue;

/**
 * Associate a network trace to an object project. This uses ObjC runtime to associate the network
 * trace with the object provided.
 *
 * @param networkTrace Network trace object to be associated with the provided object.
 * @param object The provided object to whom the network trace object will be associated with.
 */
+ (void)addNetworkTrace:(nonnull CATNetworkTrace *)networkTrace toObject:(nonnull id)object;

/**
 * Gets the network trace associated with the provided object. If the network trace is not
 * associated with the object, return nil. This uses ObjC runtime to fetch the object.
 *
 * @param object The provided object from which the network object would be fetched.
 * @return The network trace object associated with the provided object.
 */
+ (nullable CATNetworkTrace *)networkTraceFromObject:(nonnull id)object;

/**
 * Remove the network trace associated with the provided object. If the network trace is not
 * associated with the object, does nothing. This uses ObjC runtime to remove the object.
 *
 * @param object The provided object from which the network object would be removed.
 */
+ (void)removeNetworkTraceFromObject:(nonnull id)object;

/**
 * Creates an instance of the CATNetworkTrace with the provided URL and the HTTP method.
 *
 * @param URLRequest NSURLRequest object.
 * @return An instance of CATNetworkTrace.
 */
- (nullable instancetype)initWithURLRequest:(nonnull NSURLRequest *)URLRequest
    NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)init NS_UNAVAILABLE;

/**
 * Records the begining of the network request. This is usually called just before initiating the
 * request.
 */
- (void)start;

/**
 * Checkpoints a particular state of the network request. Checkpoint states are listed in the enum
 * CATNetworkTraceCheckpointState mentioned above.
 *
 * @param state A state as mentioned in enum CATNetworkTraceCheckpointState.
 */
- (void)checkpointState:(CATNetworkTraceCheckpointState)state;

/**
 * Provides the time difference between the provided checkpoint states in seconds. If the starting
 * checkpoint state is greater than the ending checkpoint state, the return value will be negative.
 * If either of the states does not exist, returns 0.
 *
 * @param startState The starting checkpoint state.
 * @param endState The ending checkpoint state.
 * @return Difference between the ending checkpoint state and starting checkpoint state in seconds.
 */
- (NSTimeInterval)timeIntervalBetweenCheckpointState:(CATNetworkTraceCheckpointState)startState
                                            andState:(CATNetworkTraceCheckpointState)endState;
/**
 * Checks if the network trace is valid.
 *
 * @return true if the network trace is valid.
 */
- (BOOL)isValid;


/**
 * Retrieves the timestamp for a specific network trace checkpoint.
 *
 * @param state The network trace checkpoint state for which the timestamp is requested.
 *              This is a value of type `CATNetworkTraceCheckpointState`, representing
 *              various stages in a network operation, such as request start, response received, etc.
 *
 * @return The time interval in seconds since the Unix epoch (January 1, 1970, 00:00:00 UTC)
 *         for the specified checkpoint. Returns 0 if the timestamp for the given state is not available.
 *
 * @discussion Use this method to track the timing of different network trace checkpoints.
 *             It is helpful for performance monitoring and debugging purposes.
 *
 * @example
 * // Example usage
 * CATNetworkTraceCheckpointState state = CATNetworkTraceCheckpointStateRequestStarted;
 * NSTimeInterval timestamp = [networkTrace timeSinceEpochForState:state];
 * NSLog(@"Timestamp for request start: %f", timestamp);
 */
- (NSTimeInterval)timeSinceEpochForState:(CATNetworkTraceCheckpointState)state;

- (void)filterNetworkRequestData;

@end
