//
//  ConvivaAppAnalytics.swift
//  AdvancedExample
//
//  Created by Butchi Peddi on 01/02/22.
//  Copyright © 2022 Google, Inc. All rights reserved.
//

import Foundation
import ConvivaAppAnalytics


/*
 This class is responsible to stat conviva app analytics monitoring and enables to report custom events.
 Conviva App Analytics monitors
 1. App Life Cycle (Install/Foreground/Background)
 2. Screen Navigation
 3. Platform details
 4. Exceptions
 */

@objc class ConvivaAppAnalytics : NSObject {
    
    /* Singleton intance which monitors entire app */
    @objc static let sharedInstance = ConvivaAppAnalytics()
    override init() {
        super.init()
        startTracking()
    }
    
    func trackerConfigs() -> CATTrackerConfiguration {
        let trackerConfig = CATTrackerConfiguration()
            .base64Encoding(false)
            .sessionContext(true)
            .platformContext(true)
            .lifecycleAutotracking(true)
            .screenViewAutotracking(true)
            .screenContext(true)
            .applicationContext(true)
            .exceptionAutotracking(true)
            .installAutotracking(true)
        
        return trackerConfig;
    }
    
    func sessionConfigs() -> CATSessionConfiguration {
        
        let sessionConfig = CATSessionConfiguration(foregroundTimeoutInSeconds: 10, backgroundTimeoutInSeconds: 10)
        return sessionConfig;
    }
    
    func startTracking() {
        
        let networkConfig = CATNetworkConfiguration(endpoint: "https://appgw.conviva.com", method: .post);
        let trackerConfig = trackerConfigs();
        let sessionConfig = sessionConfigs();
        let tracker = CATAppAnalytics.createTracker(namespace: "ConvivaAnalytics", customerKey: "345128905673421",network: networkConfig, configurations: [trackerConfig,sessionConfig])
        
        tracker.subject?.userId = "User123"
    }
    
    func trackButtonClick(button:UIButton) {
        
        let data = "{\"lable\": \(button.currentTitle!),\"property\": \(String(describing: type(of: button)))}"
        CATAppAnalytics.defaultTracker()?.trackCustomEvent("button_click", data: data)
    
    }
 
    func setCustomTags (category:String?, data:String?) {
        
        if let _ = data, data!.count > 0{
            
            guard let dict = convertToDictionary(text:data!) else { return  };
            
            self.tracker?.setCustomTags( dict)
            
        }
        else {
            self.tracker?.clearCustomTags()
        }
    }
    
    func clearTags(tags:[String]) {
        self.tracker?.clearCustomTags(tags)
    }
    
    func clearTags() {
        // Clears all tags
        self.tracker?.clearCustomTags()
    }
 
    func sendRawEvent (name:String?, data:String?) {
        
        if  let _ = name{
            self.tracker?.trackCustomEvent(name!, data: data);
        }
        
    }
 
   func onLogOut {
     CATAppAnalytics.defaultTracker()?.subject?.userId = nil;
   }
}

