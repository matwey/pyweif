vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO matwey/libweif
    REF 0.2.2
    SHA512 5de2c4ef7c3aa115c139e8a2fa9925d0146e2c353a710d58aed48708d7cc1bc58bd96da5adc636533a3933e38701e1dd5ad0ece7841418c01fd739b17e68133c
    USE_TARBALL_API
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS -DBUILD_DOC:BOOL=OFF -DBUILD_EXAMPLE:BOOL=OFF -DBUILD_TEST:BOOL=OFF
)
vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
