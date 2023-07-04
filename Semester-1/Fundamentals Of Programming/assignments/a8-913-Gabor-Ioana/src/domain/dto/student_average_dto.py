from dataclasses import dataclass

from src.domain.student import Student


@dataclass
class StudentAverageDTO:
    student: Student
    average: float

    def __str__(self):
        return str(self.student) + " average: " + str(self.average)
