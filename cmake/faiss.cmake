set(FAISS_VERSION v1.3.0)
set(FAISS_URL https://github.com/facebookresearch/faiss/archive/${FAISS_VERSION}.tar.gz)

ExternalProject_Add(faiss
    PREFIX faiss
    URL ${FAISS_URL}
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/faiss
)
