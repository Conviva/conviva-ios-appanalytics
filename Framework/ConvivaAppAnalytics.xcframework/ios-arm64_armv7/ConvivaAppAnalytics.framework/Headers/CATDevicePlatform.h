//
//  CATDevicePlatform.h
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
//  Copyright: Copyright © 2021 Snowplow Analytics.
//  License: Apache License Version 2.0
//

#import <Foundation/Foundation.h>

typedef NS_CLOSED_ENUM(NSUInteger, CATDevicePlatform) {
    CATDevicePlatformWeb = 0,
    CATDevicePlatformMobile,
    CATDevicePlatformDesktop,
    CATDevicePlatformServerSideApp,
    CATDevicePlatformGeneral,
    CATDevicePlatformConnectedTV,
    CATDevicePlatformGameConsole,
    CATDevicePlatformInternetOfThings,
} NS_SWIFT_NAME(CATDevicePlatform);

NSString *CATDevicePlatformToString(CATDevicePlatform devicePlatform);
CATDevicePlatform CATStringToDevicePlatform(NSString *devicePlatformString);
