import pathlib
import pickle

from repository.generic_repo import GenericRepository


class BinaryFileRepository(GenericRepository):

    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load(self):
        abspath = pathlib.Path(self.__filename).absolute()
        with open(str(abspath), 'rb') as f:
            try:
                self._all_books = pickle.load(f)
                f.close()
            except EOFError:
                self._all_books = {}

    def save(self):
        abspath = pathlib.Path(self.__filename).absolute()
        with open(str(abspath), 'wb') as f:
            pickle.dump(self._all_books, f)
            f.close()
