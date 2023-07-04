from unittest import TestCase

from src.domain.discipline import Discipline
from src.domain.validators.discipline_validator import DisciplineValidator
from src.exceptions.validation_exceptions import DisciplineValidationException


class TestDiscipline(TestCase):
    def setUp(self):
        self.__discipline = Discipline(1, "Logic")

    def test_name(self):
        self.assertEqual(self.__discipline.name, "Logic")

    def test_name_error(self):
        self.assertRaises(DisciplineValidationException, Discipline, 4, 3)
        with self.assertRaises(DisciplineValidationException):
            self.__discipline.name = 12345

    def test_id(self):
        self.assertEqual(self.__discipline.id, 1)

    def test_validator(self):
        self.assertRaises(DisciplineValidationException, DisciplineValidator.validate_id, "342")
        self.assertRaises(DisciplineValidationException, DisciplineValidator.validate_name, list)
        self.assertRaises(DisciplineValidationException, DisciplineValidator.validate_name, "")

    def test_str(self):
        self.assertEqual("Discipline id=1, name=Logic", str(self.__discipline))
