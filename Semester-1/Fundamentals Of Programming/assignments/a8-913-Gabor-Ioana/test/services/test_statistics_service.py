from unittest import TestCase

from src.domain.discipline import Discipline
from src.domain.dto.discipline_average_dto import DisciplineAverageDTO
from src.domain.dto.student_average_dto import StudentAverageDTO
from src.domain.grade import Grade
from src.domain.student import Student
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository
from src.services.statistics_service import StatisticsService


class TestStatisticsService(TestCase):
    def setUp(self):
        self.__disciplines_repository = GenericRepository()
        self.__students_repository = GenericRepository()
        self.__grades_repository = GradesRepository()
        self.__disciplines_repository.add_all(
            [Discipline(1, "Logic"), Discipline(2, "Math"), Discipline(13, "Algebra"), Discipline(77, "nothing")])
        self.__students_repository.add_all(
            [Student(1, "john"), Student(2, "isabela"), Student(3, "mary"), Student(5, "nobody")])
        self.__grades_repository.add_all(
            [
                Grade(1, 1, 1, 8),
                Grade(2, 1, 1, 10),
                Grade(3, 1, 1, 10),
                Grade(4, 2, 1, 9),
                Grade(5, 2, 1, 10),
                Grade(6, 13, 1, 10),
                Grade(7, 13, 1, 10),
                Grade(8, 1, 2, 3),
                Grade(9, 1, 2, 4),
                Grade(10, 2, 2, 10),
                Grade(11, 2, 2, 3),
                Grade(12, 13, 2, 6),
                Grade(13, 13, 2, 5),
                Grade(14, 1, 3, 5),
                Grade(15, 1, 3, 5),
                Grade(16, 2, 3, 5),
                Grade(17, 2, 3, 5),
                Grade(18, 13, 3, 5),
                Grade(19, 13, 3, 5),
            ])
        self.__statistics_service = StatisticsService(self.__students_repository, self.__grades_repository,
                                                      self.__disciplines_repository)

    def test_get_failing_students(self):
        actual_failing_students = self.__statistics_service.get_failing_students()
        expected_failing_students = [Student(2, "isabela")]
        self.assertEqual(actual_failing_students, expected_failing_students)

    def test_aggregated_average(self):
        self.assertEqual(self.__statistics_service.get_aggregated_average_of_student(1),
                         ((8 + 10 + 10) / 3 + (9 + 10) / 2 + (10 + 10) / 2) / 3)

    def test_get_sorted_students(self):
        actual_sorted_students = self.__statistics_service.get_sorted_students()
        expected_sorted_students = [
            StudentAverageDTO(Student(1, "john"), ((8 + 10 + 10) / 3 + (9 + 10) / 2 + (10 + 10) / 2) / 3),
            StudentAverageDTO(Student(2, "isabela"), ((3 + 4) / 2 + (3 + 10) / 2 + (6 + 5) / 2) / 3),
            StudentAverageDTO(Student(3, "mary"), ((5 + 5) / 2 + (5 + 5) / 2 + (5 + 5) / 2) / 3)]
        self.assertEqual(actual_sorted_students, expected_sorted_students)

    def test_get_sorted_disciplines(self):
        actual_sorted_disciplines = self.__statistics_service.get_sorted_disciplines()
        expected_sorted_disciplines = [
            DisciplineAverageDTO(Discipline(2, "Math"), (10 + 9 + 10 + 3 + 5 + 5) / 6),
            DisciplineAverageDTO(Discipline(13, "Algebra"), (10 + 10 + 5 + 6 + 5 + 5) / 6),
            DisciplineAverageDTO(Discipline(1, "Logic"), (8 + 10 + 10 + 3 + 4 + 5 + 5) / 7),
        ]
        self.assertEqual(actual_sorted_disciplines, expected_sorted_disciplines)

    def test_aggregated_average_no_grades(self):
        self.assertEqual(None, self.__statistics_service.get_aggregated_average_of_student(5))

    def test_discipline_average_no_grades(self):
        self.assertEqual(None, self.__statistics_service.get_average_of_discipline_grades(77))
