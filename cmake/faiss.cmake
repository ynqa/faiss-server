set(FAISS_VERSION v1.3.0)
set(FAISS_URL https://github.com/facebookresearch/faiss/archive/${FAISS_VERSION}.tar.gz)

set(FAISS_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/faiss/src/faiss)
set(FAISS_MAKEFILEINC_SRC ${FAISS_SOURCE}/example_makefiles/makefile.inc.Mac.brew)
set(FAISS_MAKEFILEINC_DEST ${FAISS_SOURCE}/makefile.inc)

ExternalProject_Add(faiss
    PREFIX faiss
    URL ${FAISS_URL}
    CONFIGURE_COMMAND cp ${FAISS_MAKEFILEINC_SRC} ${FAISS_MAKEFILEINC_DEST}
    BUILD_COMMAND cd ${FAISS_SOURCE} && make
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/faiss
)

set(FAISS_INCLUDE_DIR ${FAISS_SOURCE}/include)
add_custom_target(install_header ALL COMMAND cmake -E copy ${FAISS_SOURCE}/*.h ${FAISS_INCLUDE_DIR})
set_target_properties(faiss PROPERTIES IMPORTED_LOCATION 
                      ${FAISS_SOURCE}/*.a)
