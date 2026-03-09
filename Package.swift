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
            url: "https://github.com/Conviva/conviva-ios-appanalytics/raw/1.8.1/Framework/ConvivaAppAnalytics.xcframework.zip",
            checksum: "582fa92ee977e784ad116b5935c3bdd986cff753382cf2d61607be906dab72b6"),
    ]
)
