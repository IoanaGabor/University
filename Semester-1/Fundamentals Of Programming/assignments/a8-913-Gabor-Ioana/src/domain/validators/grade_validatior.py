from src.exceptions.validation_exceptions import GradeValidationException


class GradeValidator:
    @staticmethod
    def validate_id(id):
        if type(id) is not int:
            raise GradeValidationException("The id should be an integer!")

    @staticmethod
    def validate_discipline_id(discipline_id):
        if type(discipline_id) is not int:
            raise GradeValidationException("The discipline id should be an integer!")

    @staticmethod
    def validate_student_id(student_id):
        if type(student_id) is not int:
            raise GradeValidationException("The student id should be an integer!")

    @staticmethod
    def validate_value(value):
        if type(value) is not int:
            raise GradeValidationException("The value of the grade should be an integer!")
        if value < 1 or value > 10:
            raise GradeValidationException("The value should be between 1 and 10")
