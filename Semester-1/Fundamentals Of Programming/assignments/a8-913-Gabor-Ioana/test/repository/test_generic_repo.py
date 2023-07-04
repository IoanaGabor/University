from unittest import TestCase

from src.domain.student import Student
from src.exceptions.repository_exceptions import GenericRepositoryException
from src.repository.generic_repository import GenericRepository


class TestGenericRepo(TestCase):
    def setUp(self):
        self.__generic_repo = GenericRepository()
        self.__generic_repo.add_all([Student(1, "john"), Student(2, "mary")])

    def test_add_ok(self):
        self.__generic_repo.add(Student(3, "isabela"))
        actual_list = self.__generic_repo.find_all()
        expected_list = [Student(1, "john"), Student(2, "mary"), Student(3, "isabela")]
        self.assertEqual(actual_list, expected_list)

    def test_add_error(self):
        self.assertRaises(GenericRepositoryException, self.__generic_repo.add, Student(1, "crina"))

    def test_find_ok(self):
        entity = self.__generic_repo.find_by_entity_id(2)
        self.assertEqual(entity, Student(2, "mary"))

    def test_entity_not_found(self):
        entity = self.__generic_repo.find_by_entity_id(5)
        self.assertEqual(entity, None)

    def test_update_ok(self):
        self.__generic_repo.update(Student(2, "isabela"))
        actual_list = self.__generic_repo.find_all()
        expected_list = [Student(1, "john"), Student(2, "isabela")]
        self.assertEqual(actual_list, expected_list)

    def test_update_error(self):
        self.assertRaises(GenericRepositoryException, self.__generic_repo.update, Student(5, "crina"))

    def test_delete_ok(self):
        self.__generic_repo.delete_by_entity_id(1)
        actual_list = self.__generic_repo.find_all()
        expected_list = [Student(2, "mary")]
        self.assertEqual(actual_list, expected_list)

    def test_delete_exception(self):
        self.assertRaises(GenericRepositoryException, self.__generic_repo.delete_by_entity_id, 10)

    def test_delete_all(self):
        self.__generic_repo.delete_all()
        self.assertEqual(self.__generic_repo.find_all(), [])