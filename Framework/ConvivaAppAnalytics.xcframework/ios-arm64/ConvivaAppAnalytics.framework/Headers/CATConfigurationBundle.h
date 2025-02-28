//
//  CATConfigurationBundle.h
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

#import "CATConfiguration.h"
#import "CATNetworkConfiguration.h"
#import "CATTrackerConfiguration.h"
#import "CATSubjectConfiguration.h"
#import "CATSessionConfiguration.h"
#import "CATEmitterConfiguration.h"
#import "CATClickConfiguration.h"
//#import "CATCustomEventTrackingConfiguration.h"

@class CATCustomEventTrackingConfiguration;
@class CATNetworkReqTrackingConfiguration;
@class CATDiagnosticInfoConfiguration;

NS_ASSUME_NONNULL_BEGIN

/**
 * This class represents the default configuration applied in place of the remote configuration.
 */
NS_SWIFT_NAME(CATConfigurationBundle)
@interface CATConfigurationBundle : CATConfiguration

@property (nonatomic, nonnull, readonly) NSString *namespace;
@property (nonatomic, nullable) CATNetworkConfiguration *networkConfiguration;
@property (nonatomic, nullable) CATTrackerConfiguration *trackerConfiguration;
@property (nonatomic, nullable) CATSubjectConfiguration *subjectConfiguration;
@property (nonatomic, nullable) CATSessionConfiguration *sessionConfiguration;
@property (nonatomic, nullable) CATCustomEventTrackingConfiguration *customEventTrackingConfiguration;
@property (nonatomic, nullable) CATNetworkReqTrackingConfiguration *networkReqTrackingConfiguration;
@property (nonatomic, nullable) CATEmitterConfiguration *emitterConfiguration;
@property (nonatomic, nullable) CATDiagnosticInfoConfiguration *diagnosticInfoConfiguration;
@property (nonatomic, nullable) CATClickConfiguration *clickcc;

@property (nonatomic, nonnull, readonly) NSArray<CATConfiguration *> *configurations;

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;

- (instancetype)initWithNamespace:(NSString *)namespace;
- (instancetype)initWithNamespace:(NSString *)namespace networkConfiguration:(nullable CATNetworkConfiguration *)networkConfiguration;

@end

NS_ASSUME_NONNULL_END
