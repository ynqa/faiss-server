import zipfile
from urllib.request import urlretrieve

from tqdm import tqdm

DATASET_FILE_PATH = 'text8'
DATASET_ZIP_PATH = '{}.zip'.format(DATASET_FILE_PATH)


class DLProgress(tqdm):
    last_block = 0

    def hook(self, block_num=1, block_size=1, total_size=None):
        self.total = total_size
        self.update((block_num - self.last_block) * block_size)
        self.last_block = block_num


def get_text8():
    with DLProgress(
            unit='B', unit_scale=True, miniters=1,
            desc=DATASET_FILE_PATH) as pbar:
        urlretrieve('http://mattmahoney.net/dc/text8.zip', DATASET_ZIP_PATH,
                    pbar.hook)

    with zipfile.ZipFile(DATASET_ZIP_PATH) as zip_ref:
        zip_ref.extractall()

    with open(DATASET_FILE_PATH) as fread:
        text = fread.read()

    return text
