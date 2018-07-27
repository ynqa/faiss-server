import os
import zipfile
from urllib.request import urlretrieve

import faiss
from gensim.models import KeyedVectors, word2vec
from tqdm import tqdm

SRC_PATH = os.path.dirname(os.path.abspath(__file__))
DATASET_FILE_PATH = os.path.join(SRC_PATH, 'text8')
DATASET_ZIP_PATH = os.path.join(SRC_PATH, '{}.zip'.format(DATASET_FILE_PATH))
INDEX_FILE_PATH = os.path.join(SRC_PATH, 'faiss.index')
MODEL_FILE_PATH = os.path.join(SRC_PATH, 'word2vec.model')


class DLProgress(tqdm):
    last_block = 0

    def hook(self, block_num=1, block_size=1, total_size=None):
        self.total = total_size
        self.update((block_num - self.last_block) * block_size)
        self.last_block = block_num


def get_text8():

    if not os.path.isfile(DATASET_ZIP_PATH):
        with DLProgress(
                unit='B', unit_scale=True, miniters=1,
                desc=DATASET_FILE_PATH) as pbar:
            urlretrieve('http://mattmahoney.net/dc/text8.zip',
                        DATASET_ZIP_PATH, pbar.hook)

    if not os.path.isfile(DATASET_FILE_PATH):
        with zipfile.ZipFile(DATASET_ZIP_PATH) as zip_ref:
            zip_ref.extractall(path=SRC_PATH)


def train():
    if not os.path.isfile(MODEL_FILE_PATH):
        sentences = word2vec.Text8Corpus(fname=DATASET_FILE_PATH)
        model = word2vec.Word2Vec(sentences=sentences)
        model.wv.save_word2vec_format(fname=MODEL_FILE_PATH)
        return model
    else:
        return KeyedVectors.load_word2vec_format(
            fname=MODEL_FILE_PATH, binary=False)


def indexing(word2vec_model=None):
    if not os.path.isfile(INDEX_FILE_PATH):
        index = faiss.IndexFlatIP(word2vec_model.vector_size)
        index.add(word2vec_model.wv.syn0norm)
        faiss.write_index(index, INDEX_FILE_PATH)
        return index
    else:
        return faiss.read_index(INDEX_FILE_PATH)


def main():
    # fetch dataset
    get_text8()

    # train word2vec
    model = train()
    model.wv.init_sims(replace=True)

    # indexing
    indexing(word2vec_model=model)


if __name__ == '__main__':
    main()
