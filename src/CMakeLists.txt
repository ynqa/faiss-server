set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find 3rd parties
find_package(gflags REQUIRED)
find_package(spdlog REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Faiss Server
add_executable(faiss_server
    main.cpp faiss_server.cpp search.cpp add.cpp
    protobuf/faiss.grpc.pb.cc
    protobuf/faiss.pb.cc)

target_link_libraries(faiss_server
    faiss gflags spdlog::spdlog
    protobuf::libprotobuf
    gRPC::grpc++_unsecure)
