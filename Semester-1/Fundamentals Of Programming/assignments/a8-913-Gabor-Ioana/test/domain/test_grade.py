from unittest import TestCase

from src.domain.grade import Grade
from src.domain.validators.grade_validatior import GradeValidator
from src.exceptions.validation_exceptions import GradeValidationException


class TestGrade(TestCase):
    def setUp(self):
        self.__grade = Grade(1, 2, 3, 10)

    def test_discipline_id(self):
        self.assertEqual(self.__grade.discipline_id, 2)

    def test_student_id(self):
        self.assertEqual(self.__grade.student_id, 3)

    def test_value(self):
        self.assertEqual(self.__grade.value, 10)

    def test_value_error(self):
        self.assertRaises(GradeValidationException, Grade, 1, 2, 3, 11)
        with self.assertRaises(GradeValidationException):
            self.__grade.value = 12345

    def test_id(self):
        self.assertEqual(self.__grade.id, 1)

    def test_validator(self):
        self.assertRaises(GradeValidationException, GradeValidator.validate_id, "dfsa")
        self.assertRaises(GradeValidationException, GradeValidator.validate_value, "dfsa")
        self.assertRaises(GradeValidationException, GradeValidator.validate_discipline_id, "dfsa")
        self.assertRaises(GradeValidationException, GradeValidator.validate_student_id, "dfsa")
        self.assertRaises(GradeValidationException, GradeValidator.validate_value, 432)
