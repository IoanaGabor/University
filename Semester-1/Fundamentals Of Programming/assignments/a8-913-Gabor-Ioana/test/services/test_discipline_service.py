from unittest import TestCase

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.exceptions.services_exceptions import DisciplinesServiceException
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository
from src.services.disciplines_service import DisciplinesService
from src.services.grades_service import GradesService


class TestDisciplinesService(TestCase):
    def setUp(self):
        self.__disciplines_repository = GenericRepository()
        self.__students_repository = GenericRepository()
        self.__grades_repository = GradesRepository()
        self.__disciplines_repository.add_all(
            [Discipline(1, "Logic"), Discipline(2, "Math"), Discipline(13, "Algebra")])
        self.__students_repository.add_all([Student(1, "john"), Student(2, "isabela"), Student(3, "mary")])
        self.__grades_repository.add_all(
            [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9), Grade(3, 2, 2, 6), Grade(4, 2, 2, 7), Grade(5, 2, 2, 5),
             Grade(6, 1, 1, 4), Grade(7, 1, 2, 6), Grade(8, 2, 3, 9), Grade(9, 2, 2, 7)])

        self.__grades_service = GradesService(self.__grades_repository, self.__students_repository,
                                              self.__disciplines_repository)
        self.__disciplines_service = DisciplinesService(self.__disciplines_repository, self.__grades_service)

    def test_add_discipline_ok(self):
        self.__disciplines_service.add(3, "DSA")
        actual_disciplines = self.__disciplines_service.list_all()
        expected_disciplines = [Discipline(1, "Logic"), Discipline(2, "Math"), Discipline(3, "DSA"), Discipline(13, "Algebra")]
        self.assertEqual(actual_disciplines, expected_disciplines)

    def test_add_discipline_error(self):
        self.assertRaises(DisciplinesServiceException, self.__disciplines_service.add, 2, "dsa")

    def test_update_discipline_ok(self):
        self.__disciplines_service.update(2, "DSA")
        actual_disciplines = self.__disciplines_service.list_all()
        expected_disciplines = [Discipline(1, "Logic"), Discipline(2, "DSA"), Discipline(13, "Algebra")]
        self.assertEqual(actual_disciplines, expected_disciplines)

    def test_update_discipline_error(self):
        self.assertRaises(DisciplinesServiceException, self.__disciplines_service.update, 7, "dsa")

    def test_delete_discipline(self):
        self.__disciplines_service.delete(2)
        actual_disciplines = self.__disciplines_service.list_all()
        actual_grades = self.__grades_service.list_all()
        expected_disciplines = [Discipline(1, "Logic"), Discipline(13, "Algebra")]
        expected_grades = [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9),
                           Grade(6, 1, 1, 4), Grade(7, 1, 2, 6)]
        self.assertEqual(actual_disciplines, expected_disciplines)
        self.assertEqual(actual_grades, expected_grades)

    def test_delete_discipline_exception(self):
        self.assertRaises(DisciplinesServiceException, self.__disciplines_service.delete, 4)

    def test_find_discipline(self):
        self.assertEqual(self.__disciplines_service.find(1), Discipline(1, "Logic"))
        self.assertRaises(DisciplinesServiceException, self.__disciplines_service.find, 7)

    def test_search(self):
        expected_disciplines = [Discipline(2, "Math"), Discipline(13, "Algebra")]
        actual_disciplines = self.__disciplines_service.search("A")
        self.assertEqual(expected_disciplines, actual_disciplines)
