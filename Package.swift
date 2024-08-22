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
            url: "https://github.com/Conviva/conviva-ios-appanalytics/raw/0.2.29/Framework/ConvivaAppAnalytics.xcframework.zip",
            checksum: "011d15d0bfbafb3d3a9d5313d9338121e445c1831e51dc86503d15907b1bea7b"),
    ]
)
