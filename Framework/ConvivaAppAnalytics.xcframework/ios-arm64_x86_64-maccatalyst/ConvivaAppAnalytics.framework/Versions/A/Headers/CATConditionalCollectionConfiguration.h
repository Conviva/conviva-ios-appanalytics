//
//  CATConditionalCollectionModule.h
//  Pods
//
//  Created by Sandeep Madineni on 20/01/25.
//

#import <Foundation/Foundation.h>
#import "CATConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

@interface CATConditionalCollectionConfiguration : CATConfiguration

@property(strong, nonatomic, nullable) NSArray *collect;

@property(strong, nonatomic, nullable) NSArray *block;

@property(strong, nonatomic, nullable) NSCache *cache;

/**
 Evaluates whether an event associated with a given key and attributes should be collected based on predefined rules.

 @param key The unique identifier to cache data. For example, "url".
 @param attributes A dictionary of attributes providing additional context for the event. These attributes are used in the evaluation process.
                   Example:
                   @{
                       @"sch": @"https",
                       @"host": @"httpbin.org",
                       @"path": @"/get",
                       @"rsc": @"200",
                       @"dur": @"1012.65"
                   }
 @return A `CATConditionalCollectionStatusNo` The event should not be collected:
         - `CATConditionalCollectionStatusYes`: The event should be collected.
         - `CATConditionalCollectionStatusUnknown`: Unknown.
 */

- (CATConditionalCollectionStatus)shouldCollectEventForKey:(NSString *)key withAttributes:(NSDictionary *)attributes;

@end

NS_ASSUME_NONNULL_END
