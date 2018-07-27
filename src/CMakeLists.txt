set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find 3rd parties
find_package(gflags REQUIRED)
find_package(spdlog REQUIRED)

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Proto file
get_filename_component(fproto "../protobuf/faiss.proto" ABSOLUTE)
get_filename_component(fproto_path "${fproto}" PATH)

# Generated sources
set(fproto_srcs "${CMAKE_CURRENT_BINARY_DIR}/faiss.pb.cc")
set(fproto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/faiss.pb.h")
set(fgrpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/faiss.grpc.pb.cc")
set(fgrpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/faiss.grpc.pb.h")
add_custom_command(
      OUTPUT "${fproto_srcs}" "${fproto_hdrs}" "${fgrpc_srcs}" "${fgrpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${fproto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${fproto}"
      DEPENDS "${fproto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Faiss Server
add_executable(faiss_server
    main.cpp service_impl.cpp search.cpp
    ${fproto_srcs}
    ${fgrpc_srcs})

target_link_libraries(faiss_server
    faiss gflags spdlog::spdlog
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF})
