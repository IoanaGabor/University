from src.domain.student import Student
from src.exceptions.repository_exceptions import GenericRepositoryException
from src.exceptions.services_exceptions import StudentsServiceException
from src.exceptions.validation_exceptions import StudentValidationException
from src.repository.generic_repository import GenericRepository
from src.services.grades_service import GradesService


class StudentsService:
    def __init__(self, students_repository: GenericRepository, grades_service: GradesService):
        self.__students_repository = students_repository
        self.__grades_service = grades_service

    def add(self, student_id, name):
        """Creates and adds a student, given a student_id and a name. Could raise StudentsServiceException.

        :param student_id: integer
        :param name:string
        :return:
        """
        try:
            self.__students_repository.add(Student(student_id, name))
        except GenericRepositoryException or StudentValidationException as exception:
            raise StudentsServiceException(exception)

    def find(self, student_id):
        """Returns the student with student_id or raise StudentsServiceException if it's not found.

        :param student_id: integer
        :return:
        """
        student = self.__students_repository.find_by_entity_id(student_id)
        if student is None:
            raise StudentsServiceException("The student doesn't exist!")
        return student

    def delete(self, student_id):
        """Deletes a student and its corresponding grades, as given by a student id, raises StudentsServiceExeption if it doesn't exist

        :param student_id: integer
        :return:
        """
        try:
            self.__students_repository.delete_by_entity_id(student_id)
            self.__grades_service.delete_all_grades_of_student(student_id)
        except GenericRepositoryException as exception:
            raise StudentsServiceException(exception)

    def update(self, student_id, name):
        """Updates a student, given a student_id and a name. Could raise StudentsServiceException.

        :param student_id: integer
        :param name:string
        :return:
        """
        try:
            self.__students_repository.update(Student(student_id, name))
        except GenericRepositoryException as exception:
            raise StudentsServiceException(exception)

    def search(self, search_token):
        """Searches for all student which have the search_token as a subsequence in their name

        :param search_token:string
        :return:list of Students
        """
        all_students = self.__students_repository.find_all()
        matching_students = []
        for student in all_students:
            if student.name.lower().find(search_token.lower()) != -1:
                matching_students.append(student)
        return matching_students

    def list_all(self):
        """Returns a list containing all students

        :return: list of Students
        """
        return self.__students_repository.find_all()
