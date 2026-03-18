//
//  CATRevenueEvent.h
//  Pods
//
//  Created by Sandeep Madineni on 16/03/26.
//

#import <Foundation/Foundation.h>
#import "CATRevenueEventItem.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Revenue/purchase event.
 Required: totalOrderAmount, transactionId, currency.
 Use extraMetadata for arbitrary order-level key/value pairs.
 */
@interface CATRevenueEvent : NSObject

// ── Required ──────────────────────────────────────────────
@property (nonatomic, strong) NSNumber *totalOrderAmount; // Double; must be finite
@property (nonatomic, copy)   NSString *transactionId;    // non-empty
@property (nonatomic, copy)   NSString *currency;         // non-empty, e.g., "USD"

// ── Optional ──────────────────────────────────────────────
@property (nonatomic, strong, nullable) NSNumber *taxAmount;       // Double
@property (nonatomic, strong, nullable) NSNumber *shippingCost;    // Double
@property (nonatomic, strong, nullable) NSNumber *discount;        // Double
@property (nonatomic, strong, nullable) NSNumber *cartSize;        // Int
@property (nonatomic, copy,   nullable) NSString *paymentMethod;
@property (nonatomic, copy,   nullable) NSString *paymentProvider;
@property (nonatomic, copy,   nullable) NSArray<CATRevenueEventItem *> *items;
/**
 Extra order-level metadata.
 Must be a plain NSDictionary (no arrays/primitives at the top level).
 */
@property (nonatomic, copy,   nullable) NSDictionary<NSString *, id> *extraMetadata;

// Designated initializer
- (instancetype)initWithTotalOrderAmount:(NSNumber *)totalOrderAmount
                           transactionId:(NSString *)transactionId
                                currency:(NSString *)currency NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/**
 Validates required fields per spec.
 - totalOrderAmount must be finite (no NaN/Inf).
 - transactionId must be non-empty (after trimming).
 - currency must be non-empty (after trimming).
 Returns YES if valid; NO otherwise.
 If NO, populate `errorMessage` (optional) with a human-readable reason to log.
 */
- (BOOL)validateRequiredFieldsWithError:(NSString * _Nullable * _Nullable)errorMessage;

@end

NS_ASSUME_NONNULL_END
