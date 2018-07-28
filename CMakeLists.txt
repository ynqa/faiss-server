project(faiss-server)
cmake_minimum_required(VERSION 3.11.4)
include(ExternalProject)

# c-ares
set(CARES_VERSION 1_14_0)
set(CARES_URL URL https://github.com/c-ares/c-ares/archive/cares-${CARES_VERSION}.zip)

ExternalProject_Add(c-ares
    PREFIX c-ares
    URL ${CARES_URL}
    CMAKE_CACHE_ARGS
        -DCARES_SHARED:BOOL=OFF
        -DCARES_STATIC:BOOL=ON
        -DCARES_STATIC_PIC:BOOL=ON
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/c-ares
)

# protobuf
set(PROTOBUF_VERSION v3.6.0)
set(PROTOBUF_URL https://github.com/google/protobuf/archive/${PROTOBUF_VERSION}.zip)

ExternalProject_Add(protobuf
    PREFIX protobuf
    URL ${PROTOBUF_URL}
    SOURCE_SUBDIR cmake
    CMAKE_CACHE_ARGS
        -Dprotobuf_BUILD_TESTS:BOOL=OFF
        -Dprotobuf_WITH_ZLIB:BOOL=OFF
        -Dprotobuf_MSVC_STATIC_RUNTIME:BOOL=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/protobuf
)

set(_FINDPACKAGE_PROTOBUF_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}/protobuf/lib/cmake/protobuf")

# zlib
set(ZLIB_VERSION 1.2.11)
set(ZLIB_URL https://zlib.net/zlib-${ZLIB_VERSION}.tar.gz)

ExternalProject_Add(zlib
    PREFIX zlib
    URL ${ZLIB_URL}
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/zlib
)

# gRPC
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
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc
)

# faiss
set(FAISS_VERSION v1.3.0)
set(FAISS_URL https://github.com/facebookresearch/faiss/archive/${FAISS_VERSION}.tar.gz)
set(FAISS_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/faiss/src/faiss)
set(FAISS_MAKEFILEINC_DEST ${FAISS_SOURCE}/makefile.inc)

if(APPLE)
    set(FAISS_MAKEFILEINC_SRC ${FAISS_SOURCE}/example_makefiles/makefile.inc.Mac.brew)
    ExternalProject_Add(faiss
        PREFIX faiss
        URL ${FAISS_URL}
        CONFIGURE_COMMAND cp ${FAISS_MAKEFILEINC_SRC} ${FAISS_MAKEFILEINC_DEST}
        BUILD_COMMAND cd ${FAISS_SOURCE} && make install
        INSTALL_COMMAND ""
        CMAKE_CACHE_ARGS
            -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/faiss
    )
elseif(UNIX)
    set(FAISS_MAKEFILEINC_SRC ${FAISS_SOURCE}/example_makefiles/makefile.inc.Linux)
    ExternalProject_Add(faiss
        PREFIX faiss
        URL ${FAISS_URL}
        CONFIGURE_COMMAND cp ${FAISS_MAKEFILEINC_SRC} ${FAISS_MAKEFILEINC_DEST} && cd ${FAISS_SOURCE} && ./configure LIBS=-lgomp
        BUILD_COMMAND cd ${FAISS_SOURCE} && make install
        INSTALL_COMMAND ""
        CMAKE_CACHE_ARGS
            -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/faiss
    )
endif()

# gflags
set(GFLAGS_VERSION v2.2.1)
set(GFLAGS_URL https://github.com/gflags/gflags/archive/${GFLAGS_VERSION}.zip)

ExternalProject_Add(gflags
    PREFIX gflags
    URL ${GFLAGS_URL}
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/gflags
)

# spdlog
set(SPDLOG_VERSION v0.17.0)
set(SPDLOG_URL https://github.com/gabime/spdlog/archive/${SPDLOG_VERSION}.zip)

ExternalProject_Add(spdlog
    PREFIX spdlog
    URL ${SPDLOG_URL}
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/spdlog
)
set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/spdlog/include)

# faiss-server
ExternalProject_Add(faiss-server
  PREFIX faiss-server
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_COMMAND ""
  CMAKE_CACHE_ARGS
        -DProtobuf_DIR:PATH=${_FINDPACKAGE_PROTOBUF_CONFIG_DIR}
        -Dc-ares_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/c-ares/lib/cmake/c-ares
        -DZLIB_ROOT:STRING=${CMAKE_CURRENT_BINARY_DIR}/zlib
        -DgRPC_DIR:PATH=${CMAKE_CURRENT_BINARY_DIR}/grpc/lib/cmake/grpc
  DEPENDS protobuf grpc faiss spdlog gflags
)
