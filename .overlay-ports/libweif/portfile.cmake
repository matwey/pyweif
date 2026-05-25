vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO matwey/libweif
    REF 0.2.3
    SHA512 a96403adb0cf27e04333c93eef3880db6075fd993f68586412c01eeec5440757e8ec7b751a8ebca4e0c1db0586069275ba8d4bf28259a704a4d9ba0e3fd7360c
    USE_TARBALL_API
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DBUILD_DOCS:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DBUILD_TESTS:BOOL=OFF
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
