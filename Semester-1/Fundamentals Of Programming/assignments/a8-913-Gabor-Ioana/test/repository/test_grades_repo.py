from unittest import TestCase

from src.domain.grade import Grade
from src.repository.grades_repository import GradesRepository


class TestGradesRepo(TestCase):
    def setUp(self):
        self.__grades_repository = GradesRepository()
        self.__grades_repository.add_all(
            [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9), Grade(3, 2, 2, 6), Grade(4, 2, 2, 7), Grade(5, 2, 2, 5),
             Grade(6, 1, 1, 4), Grade(7, 1, 2, 6), Grade(8, 2, 3, 9), Grade(9, 2, 2, 7)])

    def test_get_all_grades_with_discipline_id(self):
        actual_grades = self.__grades_repository.get_all_grades_with_discipline_id(1)
        expected_grades = [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9),
                           Grade(6, 1, 1, 4), Grade(7, 1, 2, 6)]
        self.assertEqual(actual_grades, expected_grades)

    def test_get_all_grades_with_student_id(self):
        actual_grades = self.__grades_repository.get_all_grades_with_student_id(2)
        expected_grades = [Grade(3, 2, 2, 6), Grade(4, 2, 2, 7), Grade(5, 2, 2, 5),
                           Grade(7, 1, 2, 6), Grade(9, 2, 2, 7)]
        self.assertEqual(actual_grades, expected_grades)

    def test_get_all_grades_of_student_at_discipline(self):
        actual_grades = self.__grades_repository.get_all_grades_of_student_at_discipline(2, 1)
        expected_grades = [Grade(7, 1, 2, 6)]
        self.assertEqual(actual_grades, expected_grades)

    def test_delete_all_grades_with_student_id(self):
        self.__grades_repository.delete_all_grades_with_student_id(3)
        actual_grades = self.__grades_repository.find_all()
        expected_grades = [Grade(1, 1, 1, 7), Grade(3, 2, 2, 6), Grade(4, 2, 2, 7), Grade(5, 2, 2, 5),
                           Grade(6, 1, 1, 4), Grade(7, 1, 2, 6), Grade(9, 2, 2, 7)]
        self.assertEqual(actual_grades, expected_grades)

    def test_delete_all_grades_with_discipline_id(self):
        self.__grades_repository.delete_all_grades_of_discipline(2)
        actual_grades = self.__grades_repository.find_all()
        expected_grades = [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9), Grade(6, 1, 1, 4), Grade(7, 1, 2, 6)]
        self.assertEqual(actual_grades, expected_grades)
