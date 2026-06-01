vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO matwey/libweif
    REF 0.2.4
    SHA512 151de6a841f4a00ecc894782f3165d26921fd9278c96584560265cada854af6b63d17ecf49a837ece66b13a970b01100a57d2bc59c43d78aa2ba5a2ca8e489c5
    USE_TARBALL_API
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DBUILD_DOCS:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DBUILD_TESTS:BOOL=OFF
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
