from os.path import isfile

from get_corpus import get_text8, DATASET_FILE_PATH
from indexing import indexing
from train import train


def main():
    if not isfile(DATASET_FILE_PATH):
        get_text8()

    # train word2vec
    model = train()
    model.wv.init_sims(replace=True)

    # indexing
    indexing(word2vec_model=model)


if __name__ == '__main__':
    main()
