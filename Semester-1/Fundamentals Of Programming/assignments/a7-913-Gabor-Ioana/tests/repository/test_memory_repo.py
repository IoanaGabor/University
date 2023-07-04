from unittest import TestCase

from domain.book import Book
from repository.memory_repository import MemoryRepository


class TestMemoryRepo(TestCase):
    def setUp(self):
        self.__mem_repo = MemoryRepository()

    def test_add_ok(self):
        self.__mem_repo.add_all([Book(1, "Herman Hesse", "Steppenwolf"), Book(2, "lala", "lala")])

        self.__mem_repo.add(Book(3, "Liviu Rebreanu", "Ion"))
        expected_books = [Book(1, "Herman Hesse", "Steppenwolf"), Book(2, "lala", "lala"),
                          Book(3, "Liviu Rebreanu", "Ion")]
        actual_books = self.__mem_repo.find_all()
        self.assertEqual(expected_books, actual_books)

    def test_add_book_invalid_id(self):
        self.__mem_repo.add_all([Book(1, "Herman Hesse", "Steppenwolf"), Book(2, "lala", "lala")])
        self.assertRaises(ValueError, self.__mem_repo.add, Book(1, "Liviu Rebreanu", "Ion"))

    def tearDown(self):
        pass
