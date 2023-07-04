from src.domain.grade import Grade
from src.exceptions.services_exceptions import GradesServiceException
from src.repository.generic_repository import GenericRepository

from src.repository.grades_repository import GradesRepository


class GradesService:
    def __init__(self, grades_repository: GradesRepository, students_repository: GenericRepository,
                 disciplines_repository: GenericRepository):
        self.__grades_repository = grades_repository
        self.__students_repository = students_repository
        self.__disciplines_repository = disciplines_repository

    def __generate_new_grade_id(self):
        """Generates a new different grade id

        :return: new grade id
        """
        all_grades = self.__grades_repository.find_all()
        existing_ids = [grade.id for grade in all_grades]
        existing_ids.sort()
        for i in range(len(existing_ids)):
            if i + 1 < existing_ids[i]:
                return i + 1
        return len(existing_ids) + 1

    def assign_grade_to_student(self, discipline_id, student_id, grade_value):
        """Assigns a grade to student at a certain discipline. Raises GradeServiceException if the student of the discipline doesn't exist

        :param discipline_id: int
        :param student_id: int
        :param grade_value: int
        :return:
        """
        if self.__students_repository.find_by_entity_id(student_id) is None:
            raise GradesServiceException("This student does not exist!")
        if self.__disciplines_repository.find_by_entity_id(discipline_id) is None:
            raise GradesServiceException("This discipline does not exist!")

        self.__grades_repository.add(Grade(self.__generate_new_grade_id(), discipline_id, student_id, grade_value))

    def get_all_grades_of_student(self, student_id):
        """Get all the grades of a student

        :param student_id: int
        :return: list of Grades
        """
        all_grades_of_student = []
        all_grades = self.__grades_repository.find_all()
        for grade in all_grades:
            if grade.student_id == student_id:
                all_grades_of_student.append(grade)
        return all_grades_of_student

    def get_all_grades_of_discipline(self, discipline_id):
        """Get all grades of a discipline

        :param discipline_id: int
        :return: list of Grades
        """
        all_grades_of_discipline = []
        all_grades = self.__grades_repository.find_all()
        for grade in all_grades:
            if grade.discipline_id == discipline_id:
                all_grades_of_discipline.append(grade)
        return all_grades_of_discipline

    def delete_all_grades_of_student(self, student_id):
        """Delete all the grades of a student

        :param student_id: int
        :return:
        """
        all_grades_of_student = self.get_all_grades_of_student(student_id)
        for grade in all_grades_of_student:
            self.__grades_repository.delete_by_entity_id(grade.id)

    def delete_all_grades_of_discipline(self, discipline_id):
        """Delete all the grades of a discipline

        :param discipline_id: int
        :return:
        """
        all_grades_of_discipline = self.get_all_grades_of_discipline(discipline_id)
        for grade in all_grades_of_discipline:
            self.__grades_repository.delete_by_entity_id(grade.id)

    def list_all(self):
        """Get all the grades.

        :return: list of Grades
        """
        return self.__grades_repository.find_all()
