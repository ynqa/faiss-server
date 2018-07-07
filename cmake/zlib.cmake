set(ZLIB_VERSION 1.2.11)
set(ZLIB_URL https://zlib.net/zlib-${ZLIB_VERSION}.tar.gz)

ExternalProject_Add(zlib
    PREFIX zlib
    URL ${ZLIB_URL}
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/zlib
)
