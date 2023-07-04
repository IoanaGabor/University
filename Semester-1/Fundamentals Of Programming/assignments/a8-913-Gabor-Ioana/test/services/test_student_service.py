from unittest import TestCase

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.exceptions.services_exceptions import StudentsServiceException
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository
from src.services.grades_service import GradesService
from src.services.students_service import StudentsService


class TestStudentsService(TestCase):
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
        self.__students_service = StudentsService(self.__students_repository, self.__grades_service)

    def test_add_student_ok(self):
        self.__students_service.add(4, "caro")
        actual_students = self.__students_service.list_all()
        expected_students = [Student(1, "john"), Student(2, "isabela"), Student(3, "mary"), Student(4, "caro")]
        self.assertEqual(actual_students, expected_students)

    def test_add_student_error(self):
        self.assertRaises(StudentsServiceException, self.__students_service.add, 2, "caro")

    def test_update_student_ok(self):
        self.__students_service.update(3, "ioana")
        actual_students = self.__students_service.list_all()
        expected_students = [Student(1, "john"), Student(2, "isabela"), Student(3, "ioana")]
        self.assertEqual(actual_students, expected_students)

    def test_update_student_error(self):
        self.assertRaises(StudentsServiceException, self.__students_service.update, 7, "ioana")

    def test_delete_student(self):
        self.__students_service.delete(2)
        actual_students = self.__students_service.list_all()
        actual_grades = self.__grades_service.list_all()
        expected_students = [Student(1, "john"), Student(3, "mary")]
        expected_grades = [Grade(1, 1, 1, 7), Grade(2, 1, 3, 9),
                           Grade(6, 1, 1, 4), Grade(8, 2, 3, 9)]
        self.assertEqual(actual_students, expected_students)
        self.assertEqual(actual_grades, expected_grades)

    def test_delete_student_exception(self):
        self.assertRaises(StudentsServiceException, self.__students_service.delete, 4)

    def test_find_student(self):
        self.assertEqual(self.__students_service.find(1), Student(1, "john"))
        self.assertRaises(StudentsServiceException, self.__students_service.find, 7)

    def test_search(self):
        expected_students = [Student(2, "isabela"), Student(3, "mary")]
        actual_students = self.__students_service.search("A")
        self.assertEqual(expected_students, actual_students)
