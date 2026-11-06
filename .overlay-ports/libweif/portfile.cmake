vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO matwey/libweif
    REF 0.2.7
    SHA512 08ea7cabc0092564da001f02424d151403d19c951e2afd67efcaeaf9a464086ef84af2c9cc604ebd4a82058bd68b3d67451508b8252b9dc983e112a3e12214df
    USE_TARBALL_API
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DBUILD_DOCS:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DBUILD_TESTS:BOOL=OFF
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
