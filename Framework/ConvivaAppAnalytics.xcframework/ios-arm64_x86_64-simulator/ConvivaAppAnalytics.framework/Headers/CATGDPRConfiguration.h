//
//  CATGDPRConfiguration.h
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
#import "CATConfiguration.h"


typedef NS_ENUM(NSInteger, CISGdprProcessingBasis) {
    CISGdprProcessingBasisConsent = 0,
    CISGdprProcessingBasisContract = 1,
    CISGdprProcessingBasisLegalObligation = 2,
    CISGdprProcessingBasisVitalInterest = 3,
    CISGdprProcessingBasisPublicTask = 4,
    CISGdprProcessingBasisLegitimateInterests = 5
} NS_SWIFT_NAME(GDPRProcessingBasis);


NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(CATGDPRConfigurationProtocol)
@protocol CATGDPRConfigurationProtocol

/** Basis for processing. */
@property (nonatomic, readonly) CISGdprProcessingBasis basisForProcessing;
/** ID of a GDPR basis document. */
@property (nonatomic, readonly, nullable) NSString *documentId;
/** Version of the document. */
@property (nonatomic, readonly, nullable) NSString *documentVersion;
/** Description of the document. */
@property (nonatomic, readonly, nullable) NSString *documentDescription;

@end

/**
 * This class allows the GDPR configuration of the tracker.
 */
NS_SWIFT_NAME(CATGDPRConfiguration)
@interface CATGDPRConfiguration : CATConfiguration <CATGDPRConfigurationProtocol>

/**
 * Enables GDPR context to be sent with each event.
 * @param basisForProcessing GDPR Basis for processing.
 * @param documentId ID of a GDPR basis document.
 * @param documentVersion Version of the document.
 * @param documentDescription Description of the document.
 */
- (instancetype)initWithBasis:(CISGdprProcessingBasis)basisForProcessing
                   documentId:(nullable NSString *)documentId
              documentVersion:(nullable NSString *)documentVersion
          documentDescription:(nullable NSString *)documentDescription
NS_SWIFT_NAME(init(basis:documentId:documentVersion:documentDescription:));

@end

NS_ASSUME_NONNULL_END
