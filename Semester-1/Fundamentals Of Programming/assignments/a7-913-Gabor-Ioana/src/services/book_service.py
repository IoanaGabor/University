from copy import deepcopy

from domain.book import Book


class BookService:
    def __init__(self, book_repository):
        self.__book_repository = book_repository

        self.__history = [deepcopy(self.__book_repository.find_all())]

    def add_book(self, isbn, author, title):
        """Creates and adds a book with given isbn, author and title, or throws ValueError in case of duplicate isbn.

        :param isbn: string
        :param author: string
        :param title: string
        :return:
        """
        book = Book(isbn, author, title)
        try:
            self.__book_repository.add(book)
        except ValueError as ve:
            raise ValueError(ve)
        self.__history.append(deepcopy(self.__book_repository.find_all()))

    def list_all_books(self):
        """Returns a list with all the books

        :return: list of books
        """
        return self.__book_repository.find_all()

    def filter_out(self, starting_word):
        """Filters out all books whose title starts with a certain word

        :param starting_word: string
        :return:
        """
        all_books = self.list_all_books()
        for book in all_books:
            if book.title.startswith(starting_word):
                self.__book_repository.delete_by_isbn(book.isbn)
        self.__history.append(deepcopy(self.__book_repository.find_all()))

    def undo(self):
        """Performs the undo operation, or raises an Exception if the previous operation does not exist

        :return:
        """
        if len(self.__history) < 2:
            raise Exception("Previous operation does not exist")
        previous_version = self.__history[-2]
        self.__history.pop(-1)
        self.__book_repository.delete_all()
        self.__book_repository.add_all(previous_version)
