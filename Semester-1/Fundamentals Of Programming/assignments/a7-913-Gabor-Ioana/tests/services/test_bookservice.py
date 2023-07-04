from unittest import TestCase

from domain.book import Book
from repository.memory_repository import MemoryRepository
from services.book_service import BookService


class TestBookService(TestCase):
    def setUp(self):
        mem_repo = MemoryRepository()
        mem_repo.add_all([Book(1, "Herman Hesse", "Steppenwolf"), Book(2, "lala", "lala")])
        self.__service = BookService(mem_repo)

    def test_add_ok(self):
        self.__service.add_book(3, "Liviu Rebreanu", "Ion")
        expected_books = [Book(1, "Herman Hesse", "Steppenwolf"), Book(2, "lala", "lala"),
                          Book(3, "Liviu Rebreanu", "Ion")]
        actual_books = self.__service.list_all_books()
        self.assertEqual(expected_books, actual_books)

    def test_add_book_invalid_id(self):
        self.assertRaises(ValueError, self.__service.add_book, 1, "Liviu Rebreanu", "Ion")

    def tearDown(self):
        pass
