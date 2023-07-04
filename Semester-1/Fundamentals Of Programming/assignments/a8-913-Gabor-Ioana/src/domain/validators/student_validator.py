from src.exceptions.validation_exceptions import StudentValidationException


class StudentValidator:
    @staticmethod
    def validate_id(id):
        if type(id) is not int:
            raise StudentValidationException("The id should be an integer!")

    @staticmethod
    def validate_name(name):
        if type(name) is not str:
            raise StudentValidationException("The name should be a string!")

        if name == "":
            raise StudentValidationException("The student name of should not be empty")
