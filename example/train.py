from os.path import isfile

from gensim.models import KeyedVectors, word2vec

from get_corpus import DATASET_FILE_PATH

MODEL_FILE_PATH = 'word2vec.model'


def train():
    if not isfile(MODEL_FILE_PATH):
        sentences = word2vec.Text8Corpus(fname=DATASET_FILE_PATH)
        model = word2vec.Word2Vec(sentences=sentences)
        model.wv.save_word2vec_format(fname=MODEL_FILE_PATH)
        return model
    else:
        return KeyedVectors.load_word2vec_format(
            fname=MODEL_FILE_PATH, binary=False)
