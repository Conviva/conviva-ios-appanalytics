// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.
import PackageDescription

let package = Package(
    name: "ConvivaAppAnalytics",
    platforms: [
        .iOS(.v12),
        .tvOS(.v12)
    ],
 
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "ConvivaAppAnalytics",
            targets: ["ConvivaAppAnalytics"])
    ],
   dependencies: [
    ],
    targets: [
        .binaryTarget(
            name: "ConvivaAppAnalytics",
            url: "https://github.com/Conviva/conviva-ios-appanalytics/raw/1.0.3/Framework/ConvivaAppAnalytics.xcframework.zip",
            checksum: "84628571af35547e026c62ae5fa2e4a8481d3daef27480293c815862f3f17c90"),
            linkerSettings: [
                .linkedFramework("UIKit", .when(platforms: [.iOS,.tvOS])),
                .linkedFramework("Foundation", .when(platforms: [.iOS,.tvOS])),
                .linkedFramework("CoreTelephony", .when(platforms: [.iOS])),
                .unsafeFlags(["-ObjC"], .when(platforms: [.iOS,.tvOS])),
            ]
    ]
)
