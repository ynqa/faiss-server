from os.path import isfile

import faiss

INDEX_FILE_PATH = 'faiss.index'


def indexing(word2vec_model=None):
    if not isfile(INDEX_FILE_PATH):
        index = faiss.IndexFlatIP(word2vec_model.vector_size)
        index.add(word2vec_model.wv.syn0norm)
        faiss.write_index(index, INDEX_FILE_PATH)
        return index
    else:
        return faiss.read_index(INDEX_FILE_PATH)
