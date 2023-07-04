from dataclasses import dataclass
from src.domain.discipline import Discipline


@dataclass
class DisciplineAverageDTO:
    discipline: Discipline
    average: float

    def __str__(self):
        return str(self.discipline) + " average: " + str(self.average)
