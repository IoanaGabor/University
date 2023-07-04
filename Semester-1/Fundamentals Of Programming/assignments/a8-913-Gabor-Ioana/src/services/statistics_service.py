from src.domain.dto.discipline_average_dto import DisciplineAverageDTO
from src.domain.dto.student_average_dto import StudentAverageDTO
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository


class StatisticsService:
    def __init__(self, students_repository: GenericRepository, grades_repository: GradesRepository,
                 disciplines_repository: GenericRepository):
        self.__students_repository = students_repository
        self.__disciplines_repository = disciplines_repository
        self.__grades_repository = grades_repository

    def get_average_of_student_at_discipline(self, student_id, discipline_id):
        """Computes the average of a student at a discipline, assuming that the student and the discipline exist.

        :param student_id: integer
        :param discipline_id: integer
        :return: float
        """
        all_grades_of_student_at_discipline = self.__grades_repository.get_all_grades_of_student_at_discipline(
            student_id, discipline_id)
        if len(all_grades_of_student_at_discipline) == 0:
            return None
        sum = 0
        for grade in all_grades_of_student_at_discipline:
            sum += grade.value
        average = sum / len(all_grades_of_student_at_discipline)
        return average

    def get_aggregated_average_of_student(self, student_id):
        """Computes the aggregated average of a student at a discipline, assuming that the student and the discipline exist.

        :param student_id: integer
        :return: float
        """
        all_disciplines = self.__disciplines_repository.find_all()
        number_of_disciplines = 0
        sum = 0
        for discipline in all_disciplines:
            average = self.get_average_of_student_at_discipline(student_id, discipline.id)
            if average is not None:
                sum += average
                number_of_disciplines += 1
        if number_of_disciplines == 0:
            return None
        return sum / number_of_disciplines

    def get_average_of_discipline_grades(self, discipline_id):
        """Computes the average of the grades at a discipline, assuming that the student and the discipline exist.

        :param discipline_id: integer
        :return: float
        """
        all_grades_at_discipline = self.__grades_repository.get_all_grades_with_discipline_id(discipline_id)
        if len(all_grades_at_discipline) == 0:
            return None
        sum = 0
        for grade in all_grades_at_discipline:
            sum += grade.value
        return sum / len(all_grades_at_discipline)

    def get_failing_students(self):
        """Returns the students which fail (average<5) at a least one discipline

        :return: list of Students
        """
        all_students = self.__students_repository.find_all()
        all_disciplines = self.__disciplines_repository.find_all()
        failing_students = []
        for student in all_students:
            for discipline in all_disciplines:
                average = self.get_average_of_student_at_discipline(student.id, discipline.id)
                if average is not None and average < 5:
                    failing_students.append(student)
                    break
        return failing_students

    def get_sorted_students(self):
        """Sorts the students after their aggregated average

        :return: list of students
        """
        all_students = self.__students_repository.find_all()
        students_average_dtos = []
        for student in all_students:
            average = self.get_aggregated_average_of_student(student.id)
            if average is not None:
                students_average_dtos.append(StudentAverageDTO(student, average))

        students_average_dtos.sort(key=lambda x: x.average, reverse=True)
        return students_average_dtos

    def get_sorted_disciplines(self):
        """Sorts the disciplines after the average.

        :return: float
        """
        all_disciplines = self.__disciplines_repository.find_all()
        disciplines_average_dtos = []
        for discipline in all_disciplines:
            average = self.get_average_of_discipline_grades(discipline.id)
            if average is not None:
                disciplines_average_dtos.append(DisciplineAverageDTO(discipline, average))

        disciplines_average_dtos.sort(key=lambda x: x.average, reverse=True)
        return disciplines_average_dtos
