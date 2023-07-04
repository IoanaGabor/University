import json
import pathlib

from domain.book import BookDecoder, BookEncoder
from repository.generic_repo import GenericRepository


class JsonRepository(GenericRepository):

    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name

    def load(self):
        abspath = pathlib.Path(self.__file_name).absolute()
        with open(self.__file_name, 'r') as f:
            try:
                data = json.load(f)
                for d in data:
                    book = json.loads(d, cls=BookDecoder)
                    self._all_books[book.isbn] = book
            except Exception as e:
                print(e)
        f.close()

    def save(self):
        abspath = pathlib.Path(self.__file_name).absolute()
        with open(self.__file_name, 'w') as f:
            all_books_json = []
            for book in self._all_books.values():
                all_books_json.append(json.dumps(book, cls=BookEncoder))
            json.dump(all_books_json, f)
        f.close()
