include_directories(${FAISS_SOURCE})

add_executable(faiss-example faiss-example.cpp)
target_link_libraries(faiss-example faiss)
