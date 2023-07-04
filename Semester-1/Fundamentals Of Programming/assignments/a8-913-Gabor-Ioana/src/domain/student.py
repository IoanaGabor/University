from dataclasses import dataclass

from src.domain.validators.student_validator import StudentValidator


@dataclass
class Student:
    def __init__(self, id, name):
        StudentValidator.validate_id(id)
        StudentValidator.validate_name(name)
        self.__id = id
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        StudentValidator.validate_name(value)
        self.__name = value

    def __eq__(self, other):
        return isinstance(other, Student) and self.id == other.id and self.name == other.name

    def __str__(self):
        return "Student id={0}, name={1}".format(self.id, self.name)
