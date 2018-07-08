add_compile_options(-std=c++11)

# add_executable(faiss-example faiss-example.cpp)
# target_link_libraries(faiss-example faiss)

include_directories(${GRPC_INCLUDE_DIR})

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/../protobuf/helloworld.proto
)
set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

add_executable(greeter_server
    ${CMAKE_CURRENT_SOURCE_DIR}/greeter_server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(greeter_server
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)
