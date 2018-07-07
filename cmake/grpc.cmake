set(GRPC_VERSION v1.13.0)
set(GRPC_URL https://github.com/grpc/grpc/archive/${GRPC_VERSION}.zip)

ExternalProject_Add(grpc
    PREFIX grpc
    URL ${GRPC_URL}
    DEPENDS c-ares protobuf zlib
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
          ${_CMAKE_ARGS_OPENSSL_ROOT_DIR}
          -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc
)
