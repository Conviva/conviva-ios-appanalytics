//
//  NSData+CAT_GZIP.h
//  Pods
//
//  Created by Butchi Peddi on 12/03/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSData (CAT_GZIP)

- (BOOL)isGzippedData;
- (nullable NSData *)gzippedDataWithCompressionLevel:(float)level;
- (nullable NSData *)gzippedData;

@end

NS_ASSUME_NONNULL_END
