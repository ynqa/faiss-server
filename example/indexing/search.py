import argparse
from os.path import isfile

from get_corpus import get_text8, DATASET_FILE_PATH
from indexing import indexing
from train import train


def main(args):
    word = args.word[0]
    neighbors = args.n + 1

    if not isfile(DATASET_FILE_PATH):
        get_text8()

    # train word2vec
    model = train()
    model.wv.init_sims(replace=True)

    # indexing
    index = indexing(word2vec_model=model)

    idx = model.wv.vocab[word].index
    D, I = index.search(model.wv.syn0norm[idx].reshape(1, -1), neighbors)
    for _D, _I in zip(D, I):
        for n, (d, i) in enumerate(zip(_D.ravel(), _I.ravel())):
            if n > 0:
                print('{} {} = {}'.format(model.wv.index2word[idx],
                                          model.wv.index2word[i], d))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-n', type=int, default=10, help='number of neighbor')
    parser.add_argument(
        'word', type=str, nargs=1, help='a target word to estimate neighbors')
    main(parser.parse_args())
