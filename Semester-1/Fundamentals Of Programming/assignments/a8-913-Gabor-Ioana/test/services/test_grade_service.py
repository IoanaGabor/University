from unittest import TestCase

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.exceptions.services_exceptions import GradesServiceException
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository
from src.services.grades_service import GradesService


class TestGradesService(TestCase):
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

    def test_assign_grade_ok(self):
        self.__grades_service.assign_grade_to_student(2, 3, 7)
        actual_grades = self.__grades_service.list_all()
        expected_grades = [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9), Grade(3, 2, 2, 6), Grade(4, 2, 2, 7),
                           Grade(5, 2, 2, 5),
                           Grade(6, 1, 1, 4), Grade(7, 1, 2, 6), Grade(8, 2, 3, 9), Grade(9, 2, 2, 7),
                           Grade(10, 2, 3, 7)]
        self.assertEqual(actual_grades, expected_grades)

    def test_assign_grade_inexisting_student(self):
        self.assertRaises(GradesServiceException, self.__grades_service.assign_grade_to_student, 2, 21, 7)

    def test_assign_grade_inexisting_discipline(self):
        self.assertRaises(GradesServiceException, self.__grades_service.assign_grade_to_student, 14, 2, 7)