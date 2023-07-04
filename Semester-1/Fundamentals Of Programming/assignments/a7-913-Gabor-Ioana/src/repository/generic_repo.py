class GenericRepository:
    def __init__(self):
        self._all_books = {}

    def load(self):
        """Not implemented here, used for polymorphism

        :return:
        """
        raise NotImplementedError("Not implemented here")

    def save(self):
        """Not implemented here, used for polymorphism

        :return:
        """
        raise NotImplementedError("Not implemented here")

    def add(self, book):
        """Adds a book to the repository, throws Value Error if there is duplicate isbn

        :param book: Book
        :return:
        """
        self.load()
        if self.find_by_isbn(book.isbn) is not None:
            raise ValueError("Duplicate isbn!")
        self._all_books[book.isbn] = book
        self.save()

    def add_all(self, list_of_books):
        """Adds all books from a list of books to the repository, or throws an error in case of duplicate isbn

        :param list_of_books:
        :return:
        """
        self.load()
        for book in list_of_books:
            if self.find_by_isbn(book.isbn) is not None:
                raise ValueError("Duplicate isbn!")
            self._all_books[book.isbn] = book
        self.save()

    def delete_all(self):
        """Deletes all books from the repository.

        :return:
        """
        self._all_books = {}
        self.save()

    def find_all(self):
        """ Returns a list of all the books

        :return: list of books
        """
        self.load()
        return list(self._all_books.values())

    def update(self, book):
        """Updates a book with a certain isbn or throws ValueError if the isbn was not found.

        :param book: Book
        :return:
        """
        self.load()
        if self.find_by_isbn(book.isbn) is None:
            raise ValueError("Isbn was not found!")
        self._all_books[book.isbn] = book
        self.save()

    def delete_by_isbn(self, isbn):
        """Deletes a book with a certain isbn or throws ValueError if the isbn was not found.

        :param isbn: string
        :return:
        """
        self.load()
        if self.find_by_isbn(isbn) is None:
            raise ValueError("Isbn was not found!")
        del self._all_books[isbn]
        self.save()

    def find_by_isbn(self, isbn):
        """Finds a book, given an isbn, or returns None if none was found

        :param isbn: string
        :return:
        """
        if isbn in self._all_books.keys():
            return self._all_books[isbn]
        return None
