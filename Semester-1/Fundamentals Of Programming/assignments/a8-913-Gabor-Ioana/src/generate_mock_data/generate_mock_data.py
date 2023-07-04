import random

from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository


class MockDataGenerator:

    def __init__(self):
        self.__generate_disciplines_repo()
        self.__generate_students_repo()
        self.__assign_random_grades()

    def __generate_disciplines_repo(self):
        self.__discipline_repo = GenericRepository()
        self.__discipline_repo.add(Discipline(1, "Calculus"))
        self.__discipline_repo.add(Discipline(2, "DSA"))
        self.__discipline_repo.add(Discipline(3, "Algebra"))
        self.__discipline_repo.add(Discipline(4, "Python"))
        self.__discipline_repo.add(Discipline(5, "Logic"))
        self.__discipline_repo.add(Discipline(6, "Geometry"))

    def __generate_students_repo(self):
        self.__students_repo = GenericRepository()
        self.__students_repo.add(Student(1, "Gigel"))
        self.__students_repo.add(Student(2, "Marcel"))
        self.__students_repo.add(Student(3, "Maricica"))
        self.__students_repo.add(Student(4, "Florica"))
        self.__students_repo.add(Student(5, "Sandu"))
        self.__students_repo.add(Student(6, "Nicolae"))

    def __assign_random_grades(self):
        self.__grades_repo = GradesRepository()
        for i in range(60):
            self.__grades_repo.add(
                Grade(i + 1, random.randrange(1, 7), random.randrange(1, 7), random.randrange(1, 11)))

    @property
    def students_repository(self):
        return self.__students_repo

    @property
    def disciplines_repository(self):
        return self.__discipline_repo

    @property
    def grades_repository(self):
        return self.__grades_repo
