from unittest import TestCase

from src.domain.student import Student
from src.domain.validators.student_validator import StudentValidator
from src.exceptions.validation_exceptions import StudentValidationException


class TestStudent(TestCase):
    def setUp(self):
        self.__student = Student(1, "Marcel")

    def test_name(self):
        self.assertEqual(self.__student.name, "Marcel")

    def test_name_error(self):
        self.assertRaises(StudentValidationException, Student, 4, 3)
        with self.assertRaises(StudentValidationException):
            self.__student.name = 12345

    def test_id(self):
        self.assertEqual(self.__student.id, 1)

    def test_validator(self):
        self.assertRaises(StudentValidationException, StudentValidator.validate_id, "342")
        self.assertRaises(StudentValidationException, StudentValidator.validate_name, list)
        self.assertRaises(StudentValidationException, StudentValidator.validate_name, "")

    def test_str(self):
        self.assertEqual("Student id=1, name=Marcel", str(self.__student))
