include_directories(${GRPC_INCLUDE_DIR})
include_directories(${FAISS_INCLUDE_DIR})

add_executable(server main.cpp)
