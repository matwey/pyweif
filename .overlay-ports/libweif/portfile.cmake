vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO matwey/libweif
    REF 0.2.6
    SHA512 542a375cae3caafe7ab9c8bb41bff90c33c92272dbc9836fc0d070f5dce0de7ea9ae1a5ce1a4a68a37714b73e6bd0e8b86ee9056668dd94585e09f08a2dc3823
    USE_TARBALL_API
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DBUILD_DOCS:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DBUILD_TESTS:BOOL=OFF
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
