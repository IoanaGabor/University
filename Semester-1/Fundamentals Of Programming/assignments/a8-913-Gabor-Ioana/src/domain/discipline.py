from dataclasses import dataclass

from src.domain.validators.discipline_validator import DisciplineValidator


class Discipline:
    def __init__(self, id, name):
        DisciplineValidator.validate_id(id)
        DisciplineValidator.validate_name(name)
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
        DisciplineValidator.validate_name(value)
        self.__name = value

    def __eq__(self, other):
        return isinstance(other, Discipline) and self.name == other.name and self.id == other.id

    def __str__(self):
        return "Discipline id={0}, name={1}".format(self.id, self.name)
