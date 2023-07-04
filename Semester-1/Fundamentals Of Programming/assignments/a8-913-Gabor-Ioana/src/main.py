from src.generate_mock_data.generate_mock_data import MockDataGenerator
from src.repository.generic_repository import GenericRepository
from src.repository.grades_repository import GradesRepository
from src.services.disciplines_service import DisciplinesService
from src.services.grades_service import GradesService
from src.services.statistics_service import StatisticsService
from src.services.students_service import StudentsService
from src.ui.console_ui import ConsoleUI


def start():
    # students_repository = GenericRepository()
    # disciplines_repository = GenericRepository()
    # grades_repository = GradesRepository()
    mock_data_generator = MockDataGenerator()
    students_repository = mock_data_generator.students_repository
    disciplines_repository = mock_data_generator.disciplines_repository
    grades_repository = mock_data_generator.grades_repository
    grades_service = GradesService(grades_repository, students_repository, disciplines_repository)
    students_service = StudentsService(students_repository, grades_service)
    disciplines_service = DisciplinesService(disciplines_repository, grades_service)
    statistics_service = StatisticsService(students_repository, grades_repository, disciplines_repository)
    console_ui = ConsoleUI(disciplines_service, students_service, grades_service, statistics_service)
    console_ui.run_menu()


if __name__ == "__main__":
    start()
