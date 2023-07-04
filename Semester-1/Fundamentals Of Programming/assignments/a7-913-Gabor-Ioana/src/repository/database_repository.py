import pathlib
import sqlite3
from sqlite3 import Error

from domain.book import Book


class DataBaseRepository:
    def __init__(self, database_name):
        super().__init__()
        self.__database = pathlib.Path(database_name.absolute())
        self.__connection = self.__create__connection(database_name)
        self.__create_table()

    @staticmethod
    def __create__connection(datab):
        conn = None
        try:
            conn = sqlite3.connect(datab)
        except Error as err:
            print(err)
        return conn

    def __create_table(self):
        command = """ CREATE TABLE IF NOT EXISTS BOOKS (
                                                    isbn text PRIMARY KEY,
                                                    author text NOT NULL,
                                                    title text NOT NULL
                                            ); """
        if self.__connection is not None:
            try:
                c = self.__connection.cursor()
                c.execute(command)
            except Error as err:
                print(err)
        else:
            print("Error! cannot create the database connection.")

    def add(self, book):
        """Adds a book to the repository, throws Value Error if there is duplicate isbn

        :param book: Book
        :return:
        """
        command = '''INSERT INTO BOOKS
                (isbn, author, title) VALUES (?, ?, ?);'''
        try:
            current = self.__connection.cursor()
            current.execute(command, (book.isbn, book.author, book.title))
            self.__connection.commit()
        except Error as err:
            raise ValueError("Duplicate isbn!")

    def add_all(self, list_of_books):
        """Adds all books from a list of books to the repository, or throws an error in case of duplicate isbn

        :param list_of_books:
        :return:
        """
        for book in list_of_books:
            self.add(book)

    def delete_all(self):
        """Deletes all books from the repository.

        :return:
        """
        sql = 'DELETE FROM BOOKS'
        current = self.__connection.cursor()
        current.execute(sql)
        self.__connection.commit()

    def find_all(self):
        """ Returns a list of all the books

        :return: list of books
        """
        current = self.__connection.cursor()
        current.execute("SELECT * FROM BOOKS")
        rows = current.fetchall()
        book_list = []
        for row in rows:
            book_list.append(Book(row[0], row[1], row[2]))
        return book_list

    def delete_by_isbn(self, isbn):
        """Deletes a book with a certain isbn or throws ValueError if the isbn was not found.

        :param isbn: string
        :return:
        """
        if self.find_by_isbn(isbn) is None:
            raise ValueError("Isbn not found")
        sql = 'DELETE FROM BOOKS WHERE isbn = ?'
        current = self.__connection.cursor()
        current.execute(sql, (isbn,))
        self.__connection.commit()

    def find_by_isbn(self, isbn):
        """Finds a book, given an isbn, or returns None if none was found

        :param isbn: string
        :return:
        """
        current = self.__connection.cursor()
        current.execute("SELECT * FROM BOOKS WHERE isbn = ?", (isbn,))
        rows = current.fetchall()
        if len(rows) == 0:
            return None
        row = rows[0]
        return Book(row[0], row[1], row[2])
