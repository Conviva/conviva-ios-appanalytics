//
//  CATButtonClickTracker.m
//  Pods
//
//  Created by Butchi Peddi on 05/04/22.
//

#import "CATEventBase.h"
#import "CATSelfDescribingJson.h"

NS_ASSUME_NONNULL_BEGIN

 /// A button click event.
 NS_SWIFT_NAME(CATButtonClickEvent)

@interface CATButtonClickEvent : CATSelfDescribingAbstract

/// Type of the element.
 @property (nonatomic, nullable) NSString *elementType;

 /// Identifier of the element.
 @property (nonatomic, nullable) NSString *elementId;

 /// Name of the element.
 @property (nonatomic, nullable) NSString *elementName;

 /// Element class name.
 @property (nonatomic, nullable) NSString *elementClasses;

 /// Text of the element.
 @property (nonatomic, nullable) NSString *elementText;

 /// Value of the element.
 @property (nonatomic, nullable) NSString *elementValue;

 //- (instancetype)init NS_UNAVAILABLE;

 /// Type of the element.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementType)
 /// Identifier of the element.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementId)
 /// Name of the element.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementName)
 /// Element class name.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementClasses)
 /// Text of the element.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementText)
 /// Value of the element.
 SP_BUILDER_DECLARE_NULLABLE(NSString *, elementValue)

@end

NS_ASSUME_NONNULL_END
