from dataclasses import dataclass

from src.domain.validators.grade_validatior import GradeValidator


class Grade:
    def __init__(self, id, discipline_id, student_id, value):
        GradeValidator.validate_id(id)
        GradeValidator.validate_discipline_id(discipline_id)
        GradeValidator.validate_student_id(student_id)
        GradeValidator.validate_value(value)
        self.__id = id
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__value = value

    @property
    def id(self):
        return self.__id

    @property
    def discipline_id(self):
        return self.__discipline_id

    @property
    def student_id(self):
        return self.__student_id

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, value):
        GradeValidator.validate_value(value)
        self.__value = value

    def __eq__(self, other):
        return isinstance(other, Grade) and self.id == other.id and self.discipline_id == other.discipline_id and \
            self.student_id == other.student_id and self.value == other.value

    def __str__(self):
        return "Grade id={0}, discipline_id={1}, student_id={2}, value={3}".format(self.id, self.discipline_id,
                                                                                   self.student_id, self.value)
