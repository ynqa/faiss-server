set(GRPC_VERSION v1.13.0)
set(GRPC_URL https://github.com/grpc/grpc/archive/${GRPC_VERSION}.zip)
set(GRPC_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc-external/include)
set(GRPC_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc-external/lib)

ExternalProject_Add(grpc-external
    PREFIX grpc
    URL ${GRPC_URL}
    DEPENDS c-ares-external protobuf-external zlib-external
    CMAKE_CACHE_ARGS
          -DgRPC_INSTALL:BOOL=ON
          -DgRPC_BUILD_TESTS:BOOL=OFF
          -DgRPC_PROTOBUF_PROVIDER:STRING=package
          -DgRPC_PROTOBUF_PACKAGE_TYPE:STRING=CONFIG
          -DProtobuf_DIR:PATH=${_FINDPACKAGE_PROTOBUF_CONFIG_DIR}
          -DgRPC_ZLIB_PROVIDER:STRING=package
          -DZLIB_ROOT:STRING=${CMAKE_CURRENT_BINARY_DIR}/zlib
          -DgRPC_CARES_PROVIDER:STRING=package
          -Dc-ares_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/c-ares/lib/cmake/c-ares
          -DgRPC_SSL_PROVIDER:STRING=package
          -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc
)
