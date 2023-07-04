import csv
import pathlib

from domain.book import Book
from repository.generic_repo import GenericRepository


class TextFileRepository(GenericRepository):

    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load(self):
        abspath = pathlib.Path(self.__filename).absolute()
        with open(abspath, 'r') as f:
            lines = f.readlines()
            for line in lines:
                book = Book.from_text_line_to_book(line)
                self._all_books[book.isbn] = book
            f.close()

    def save(self):
        abspath = pathlib.Path(self.__filename).absolute()
        with open(abspath, 'w') as f:
            for book in self._all_books.values():
                f.write(book.from_book_to_text_line() + '\n')
            f.close()
