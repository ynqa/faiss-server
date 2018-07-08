set(GRPC_VERSION v1.13.0)
set(GRPC_URL https://github.com/grpc/grpc/archive/${GRPC_VERSION}.zip)

set(GRPC_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/include)
set(GRPC_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/grpc/lib/libgrpc.a)
set(GRPC_GRPC++_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/grpc/lib/libgrpc++.a)
set(GRPC_GRPC++_REFLECTION_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/grpc/lib/libgrpc++_reflection.a)
set(GRPC_CPP_PLUGIN ${CMAKE_CURRENT_BINARY_DIR}/grpc/bin/grpc_cpp_plugin)

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
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc
)
