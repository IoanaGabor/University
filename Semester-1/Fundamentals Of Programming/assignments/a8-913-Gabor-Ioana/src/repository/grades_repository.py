from src.repository.generic_repository import GenericRepository


class GradesRepository(GenericRepository):
    def __init__(self):
        super().__init__()

    def get_all_grades_with_student_id(self, student_id):
        """Gets all grades which correspond to a given student id

        :param student_id: integer
        :return: list of Grades
        """
        all_grades_of_student = []
        for grade in self._all_entities.values():
            if grade.student_id == student_id:
                all_grades_of_student.append(grade)
        return all_grades_of_student

    def get_all_grades_with_discipline_id(self, discipline_id):
        """Gets all grades which correspond to a given discipline_id

        :param discipline_id: integer
        :return: list of Grades
        """
        all_grades_of_discipline = []
        for grade in self._all_entities.values():
            if grade.discipline_id == discipline_id:
                all_grades_of_discipline.append(grade)
        return all_grades_of_discipline

    def get_all_grades_of_student_at_discipline(self, student_id, discipline_id):
        """Gets all grades which correspond to a given student_id and discipline_id

        :param student_id: integer
        :param discipline_id: integer
        :return: list of Grades
        """
        all_grades_of_student_at_discipline = []
        for grade in self._all_entities.values():
            if grade.discipline_id == discipline_id and grade.student_id == student_id:
                all_grades_of_student_at_discipline.append(grade)
        return all_grades_of_student_at_discipline

    def delete_all_grades_with_student_id(self, student_id):
        """Deletes all grades which correspond to a student_id from the repository

        :param student_id: integer
        :return:
        """
        all_grades_of_student = self.get_all_grades_with_student_id(student_id)
        for grade in all_grades_of_student:
            self.delete_by_entity_id(grade.id)

    def delete_all_grades_of_discipline(self, discipline_id):
        """Deletes all grades which correspond to a discipline_id from the repository

        :param discipline_id: integer
        :return:
        """
        all_grades_of_discipline = self.get_all_grades_with_discipline_id(discipline_id)
        for grade in all_grades_of_discipline:
            self.delete_by_entity_id(grade.id)
