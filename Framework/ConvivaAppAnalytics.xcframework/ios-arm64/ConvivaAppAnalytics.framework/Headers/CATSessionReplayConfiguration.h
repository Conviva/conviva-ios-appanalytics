//
//  CATSessionReplayConfiguration.h
//  Pods
//
//  Created by Generated on 23/12/25.
//

#import "CATConfiguration.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*
typedef NS_ENUM(NSInteger, CATSessionReplayQuality) {
    CATSessionReplayQualityLow = 0,
    CATSessionReplayQualityMedium = 1,
    CATSessionReplayQualityHigh = 2,
};
*/
NS_SWIFT_NAME(CATSessionReplayConfigurationProtocol)
@protocol CATSessionReplayConfigurationProtocol

///**
// * To enable or disable the session replay feature.
// * Maps to JSON: "enabled"
// */
//@property (nonatomic, assign) BOOL enabled;
//
///**
// * Sampling percentage (0-100).
// * Maps to JSON: "sampling.pct"
// */
//@property (nonatomic, assign) NSInteger samplingPct;
//
///**
// * Network endpoint used for session replay uploads.
// * Maps to JSON: "networkConfiguration.endpoint"
// */
//@property (nonatomic, copy, nullable) NSString *networkEndpoint;
//
///**
// * Emitter upload interval in seconds.
// * Maps to JSON: "emitterConfiguration.uploadInterval"
// */
//@property (nonatomic, assign) NSInteger emitterUploadInterval;
//
///**
// * Emitter policy expiry time in seconds.
// * Maps to JSON: "emitterConfiguration.policyExpiryTime"
// */
//@property (nonatomic, assign) NSInteger emitterPolicyExpiryTime;
//
///**
// * Throttle delay in milliseconds for the mobile recorder.
// * Maps to JSON: "mobRecorderConfiguration.throttleDelayMs"
// */
//@property (nonatomic, assign) NSInteger mobThrottleDelayMs;
//
///**
// * Session replay quality setting.
// * Maps to JSON: "mobRecorderConfiguration.quality"
// */
//@property (nonatomic, assign) CATSessionReplayQuality mobQuality;
//
///**
// * Session replay quality setting.
// * Maps to JSON: "mobRecorderConfiguration.compressionQuality"
// */
//@property (nonatomic, assign) NSInteger mobCompressionQuality;
//
///**
// * Whether to mask all input fields.
// * Maps to JSON: "mobRecorderConfiguration.maskAllInputs"
// */
//@property (nonatomic, assign) BOOL mobMaskAllInputs;
//
///**
// * List of input categories to mask.
// * Maps to JSON: "mobRecorderConfiguration.maskInputOptions"
// */
//@property (nonatomic, copy, nullable) NSArray<NSString *> *mobMaskInputOptions;
//
///**
// * Whether to mask all images.
// * Maps to JSON: "mobRecorderConfiguration.maskAllImages"
// */
//@property (nonatomic, assign) BOOL mobMaskAllImages;
//
///**
// * Whether to mask all system views.
// * Maps to JSON: "mobRecorderConfiguration.maskAllSystemViews"
// */
//@property (nonatomic, assign) BOOL mobMaskAllSystemViews;

@property (nonatomic, copy) NSDictionary* dict;

@end

NS_SWIFT_NAME(CATSessionReplayConfiguration)
@interface CATSessionReplayConfiguration : CATConfiguration <CATSessionReplayConfigurationProtocol>

///**
// * To enable or disable the session replay feature.
// * Maps to JSON: "enabled"
// */
//@property (nonatomic, assign) BOOL enabled;
//
///**
// * Sampling percentage (0-100).
// * Maps to JSON: "sampling.pct"
// */
//@property (nonatomic, assign) NSInteger samplingPct;
//
///**
// * Network endpoint used for session replay uploads.
// * Maps to JSON: "networkConfiguration.endpoint"
// */
//@property (nonatomic, copy, nullable) NSString *networkEndpoint;
//
///**
// * Emitter upload interval in seconds.
// * Maps to JSON: "emitterConfiguration.uploadInterval"
// */
//@property (nonatomic, assign) NSInteger emitterUploadInterval;
//
///**
// * Emitter policy expiry time in seconds.
// * Maps to JSON: "emitterConfiguration.policyExpiryTime"
// */
//@property (nonatomic, assign) NSInteger emitterPolicyExpiryTime;
//
///**
// * Throttle delay in milliseconds for the mobile recorder.
// * Maps to JSON: "mobRecorderConfiguration.throttleDelayMs"
// */
//@property (nonatomic, assign) NSInteger mobThrottleDelayMs;
//
///**
// * Session replay quality setting.
// * Maps to JSON: "mobRecorderConfiguration.quality"
// */
//@property (nonatomic, assign) CATSessionReplayQuality mobQuality;
//
///**
// * Session replay quality setting.
// * Maps to JSON: "mobRecorderConfiguration.compressionQuality"
// */
//@property (nonatomic, assign) NSInteger mobCompressionQuality;
//
///**
// * Whether to mask all input fields.
// * Maps to JSON: "mobRecorderConfiguration.maskAllInputs"
// */
//@property (nonatomic, assign) BOOL mobMaskAllInputs;
//
///**
// * List of input categories to mask.
// * Maps to JSON: "mobRecorderConfiguration.maskInputOptions"
// */
//@property (nonatomic, copy, nullable) NSArray<NSString *> *mobMaskInputOptions;
//
///**
// * Whether to mask all images.
// * Maps to JSON: "mobRecorderConfiguration.maskAllImages"
// */
//@property (nonatomic, assign) BOOL mobMaskAllImages;
//
///**
// * Whether to mask all system views.
// * Maps to JSON: "mobRecorderConfiguration.maskAllSystemViews"
// */
//@property (nonatomic, assign) BOOL mobMaskAllSystemViews;


@property (nonatomic, copy) NSDictionary* dict;

- (instancetype)init;

/**
// * To enable or disable the session replay feature.
// */
//SP_BUILDER_DECLARE(BOOL, enabled)
//
///**
// * Sampling percentage (0-100).
// */
//SP_BUILDER_DECLARE(NSInteger, samplingPct)
//
///**
// * Network endpoint used for session replay uploads.
// */
//SP_BUILDER_DECLARE_NULLABLE(NSString *, networkEndpoint)
//
///**
// * Emitter upload interval in seconds.
// */
//SP_BUILDER_DECLARE(NSInteger, emitterUploadInterval)
//
///**
// * Emitter policy expiry time in seconds.
// */
//SP_BUILDER_DECLARE(NSInteger, emitterPolicyExpiryTime)
//
///**
// * Throttle delay in milliseconds for the mobile recorder.
// */
//SP_BUILDER_DECLARE(NSInteger, mobThrottleDelayMs)
//
///**
// * Session replay quality setting.
// */
//SP_BUILDER_DECLARE(CATSessionReplayQuality, mobQuality)
//
///**
// * Session replay quality setting.
// */
//SP_BUILDER_DECLARE(NSInteger, mobCompressionQuality)
//
///**
// * Whether to mask all input fields.
// */
//SP_BUILDER_DECLARE(BOOL, mobMaskAllInputs)
//
///**
// * List of input categories to mask.
// */
//SP_BUILDER_DECLARE_NULLABLE(NSArray<NSString *> *, mobMaskInputOptions)
//
///**
// * Whether to mask all images.
// */
//SP_BUILDER_DECLARE(BOOL, mobMaskAllImages)
//
///**
// * Whether to mask all system views.
// */
//SP_BUILDER_DECLARE(BOOL, mobMaskAllSystemViews)
//
///**
// * Convenience accessor to check whether Session Replay is enabled.
// */
//- (BOOL)isSessionReplayEnabled;
//
///**
// * Convenience accessor to get the emitter upload interval as NSTimeInterval.
// */
//- (NSTimeInterval)getEmitterUploadInterval;
//
///**
// * Convenience accessor to get the policy expiry time as NSTimeInterval.
// */
//- (NSTimeInterval)getEmitterPolicyExpiryTime;

@end

NS_ASSUME_NONNULL_END
