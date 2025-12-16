//
//  CATUtils.m
//  Pods
//
//  Created by Butchi Peddi on 04/02/22.
//

#import <Foundation/Foundation.h>
#import "CATSelfDescribingJson.h"

@interface CATUtils : NSObject

+ (id)getClientId;
+ (BOOL)setClientId:(NSString *)newClientId;
+ (NSInteger)getInstanceId;
+ (void) removeInstanceId;

//+ (NSInteger)getClientIdEventIndex;
//+ (void)setClientIdEventIndex:(NSInteger)clientIdEventIndex;

+ (CATSelfDescribingJson *) getConvivaContext:(NSString*)customerKey;
+ (NSString*) userAgentString;

+ (NSDictionary *)collectAttributes:(NSDictionary *)payloadInfo withConfig:(NSArray *)collectAttributesConfig andAttributesPayload:(NSDictionary *)attributesPayloadInfo;
+ (NSDictionary *)filterAttributes:(NSDictionary *)attributesPayloadInfo withConfig:(NSArray *)attributeKeysToCompare andIsCaseInSensitive:(BOOL)isCaseInSensitive;
+ (BOOL)matchesConditions:(NSDictionary *)conditions forPayloadInfo:(NSDictionary *)payloadInfo;


+ (BOOL)compare:(NSString *)string withAnotherString:(NSString *)anotherString options:(BOOL)caseInsensitive;
+ (BOOL)compareIntegerNumber:(long)number withAnotherNumber:(long)anotherNumber operator:(NSString *)operatorToApply;
+ (BOOL)compareDecimalNumber:(double)number withAnotherNumber:(double)anotherNumber operator:(NSString *)operatorToApply;
+ (BOOL)isValidClientId:(NSString *)clientId;


+ (dispatch_queue_t)catSharedQueue;
+ (BOOL)isCATSharedQueue;
+ (void)dispatchAsyncToCATSharedQueue:(dispatch_block_t)block;
+ (void)dispatchAsyncToCATSharedQueue:(dispatch_block_t)block after:(NSTimeInterval)interval;
+ (void)optionalDispatchSyncToCATSharedQueue:(dispatch_block_t)block;
+ (void)dispatchSyncToCATSharedQueue:(dispatch_block_t)block;
+ (void)optionalDispatchAsyncToCATSharedQueue:(dispatch_block_t)block;
+ (void)optionalDispatchAsyncToCATSharedQueue:(dispatch_block_t)block after:(NSTimeInterval)interval;


//+ (dispatch_queue_t)catSenderQueue;
+ (BOOL)isCATSenderQueue;
+ (void)dispatchAsyncToCATSenderQueue:(dispatch_block_t)block;
+ (void)dispatchAsyncToCATSenderQueue:(dispatch_block_t)block after:(NSTimeInterval)interval;
+ (void)dispatchSyncToCATSenderQueue:(dispatch_block_t)block;
+ (void)optionalDispatchAsyncToCATSenderQueue:(dispatch_block_t)block;
+ (void)optionalDispatchAsyncToCATSenderQueue:(dispatch_block_t)block after:(NSTimeInterval)interval;
+ (NSDictionary *)getConfigInfoFor:(NSString *)targetUrl withData:(NSDictionary*)data;
+ (BOOL)hasKey:(NSString *)key attributes:(NSArray*)attributes;
+ (NSString *)stringByTrimmingURLString:(NSURLRequest *)URLRequest;
+ (NSString *)filteredKeysFromJSONString:(NSString *)jsonString allowedKeys:(NSArray<NSString *> *)allowedKeys;
+ (NSString *)filteredKeysFromJSON:(NSDictionary *)dict allowedKeys:(NSArray<NSString *> *)allowedKeys;
+ (NSString *)truncateString:(NSString *)str toLength:(NSInteger)maxLength;
@end
