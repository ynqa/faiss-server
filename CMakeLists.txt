project(faiss-server)
cmake_minimum_required(VERSION 3.11.4)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(ExternalProject)
# gRPC dependencies
include(zlib)
include(c-ares)

include(protobuf)
include(grpc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
subdirs(src)
