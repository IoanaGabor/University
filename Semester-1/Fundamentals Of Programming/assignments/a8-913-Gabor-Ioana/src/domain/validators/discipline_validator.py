from src.exceptions.validation_exceptions import DisciplineValidationException


class DisciplineValidator:
    @staticmethod
    def validate_id(id):
        if type(id) is not int:
            raise DisciplineValidationException("The id should be an integer!")

    @staticmethod
    def validate_name(name):
        if type(name) is not str:
            raise DisciplineValidationException("The name should be a string!")

        if name == "":
            raise DisciplineValidationException("The discipline name of should not be empty")
