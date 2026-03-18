//
//  CATRevenueEventItem.h
//  Pods
//
//  Created by Sandeep Madineni on 16/03/26.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Item for a revenue/purchase event.
 All fields optional. Use extraMetadata for arbitrary item-level key/value pairs.
 */
@interface CATRevenueEventItem : NSObject

@property (nonatomic, copy, nullable) NSString *productId;
@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *sku;
/**
 Category can be a single string or multiple categories.
 If you set a single category string, it will be wrapped as a single-element array in the payload.
 */
@property (nonatomic, copy, nullable) NSArray<NSString *> *category;
@property (nonatomic, strong, nullable) NSNumber *unitPrice; // Double
@property (nonatomic, strong, nullable) NSNumber *quantity;  // Int
@property (nonatomic, strong, nullable) NSNumber *discount;  // Double
@property (nonatomic, copy, nullable) NSString *brand;
@property (nonatomic, copy, nullable) NSString *variant;
/**
 Extra item-level metadata. Forwarded as-is under `extraMetadata` on each item.
 Must be a plain NSDictionary (no arrays/primitives at the top level).
 */
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *extraMetadata;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Convenience initializer for common fields.
 */
- (instancetype)initWithProductId:(nullable NSString *)productId
                             name:(nullable NSString *)name
                              sku:(nullable NSString *)sku
                         category:(nullable NSArray<NSString *> *)category
                        unitPrice:(nullable NSNumber *)unitPrice
                         quantity:(nullable NSNumber *)quantity
                         discount:(nullable NSNumber *)discount
                            brand:(nullable NSString *)brand
                          variant:(nullable NSString *)variant
                    extraMetadata:(nullable NSDictionary<NSString *, id>*)extraMetadata;


/**
 Returns the item as a JSON-ready dictionary, following the spec’s field names.
 - Removes nil/empty optional fields.
 - If category is empty, it’s omitted.
 - If extraMetadata isn’t a plain NSDictionary, it’s omitted.
 */
- (NSDictionary<NSString *, id> *)toDictionary;

@end

NS_ASSUME_NONNULL_END
