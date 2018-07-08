project(faiss-server)
cmake_minimum_required(VERSION 3.11.4)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(ExternalProject)
# gRPC dependencies
include(zlib)
include(c-ares)

include(protobuf)
include(grpc)
include(faiss)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
subdirs(src)
