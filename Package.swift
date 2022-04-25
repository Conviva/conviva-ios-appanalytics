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
            targets: ["ConvivaAppAnalyticsTarget"])
    ],
   dependencies: [
        .package(
            name: "FMDB", 
            url: "https://github.com/ccgus/fmdb",
            .upToNextMajor(from: "2.7.7"))
    ],
    targets: [
        .target(
            name: "ConvivaAppAnalyticsTarget",
            dependencies: [
                .target(name: "ConvivaAppAnalytics"),.product(name: "FMDB", package: "FMDB")
            ],
	    path: "PlatformExcludes"
        ),
        .binaryTarget(
            name: "ConvivaAppAnalytics",
            url: "https://github.com/Conviva/conviva-ios-appanalytics/raw/0.2.1/Framework/ConvivaAppAnalytics.xcframework.zip",
            checksum: "e18ee81299fad8fa92222ca2a456dc97961b4c596ea6e4abbcefedf94e940bae"),
    ]
)
