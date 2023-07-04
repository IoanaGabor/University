class ValidationException(Exception):
    pass


class DisciplineValidationException(ValidationException):
    pass


class GradeValidationException(ValidationException):
    pass


class StudentValidationException(ValidationException):
    pass
