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
            url: "https://github.com/Conviva/conviva-ios-appanalytics/raw/1.2.0/Framework/ConvivaAppAnalytics.xcframework.zip",
            checksum: "e1c49e26b1b686e7c9ac693359138d542a9eefdf7ab839d20ad84a6a9cf41e7e"),
    ]
)
