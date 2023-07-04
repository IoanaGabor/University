from unittest import TestCase

from domain.book import Book


class TestBook(TestCase):
    def setUp(self):
        self.__book = Book("1", "Arghezi", "Flori de mucigai")

    def test_isbn(self):
        self.assertEqual(self.__book.isbn, "1")

    def test_title(self):
        self.assertEqual(self.__book.title, "Flori de mucigai")

    def test_author(self):
        self.assertEqual(self.__book.author, "Arghezi")

