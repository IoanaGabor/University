from domain.book import Book
from repository.binary_file_repository import BinaryFileRepository
from repository.database_repository import DataBaseRepository
from repository.json_repository import JsonRepository
from repository.memory_repository import MemoryRepository
from repository.text_file_repository import TextFileRepository
from services.book_service import BookService
from settings.settings import SettingsLoader
from ui.console import ConsoleUI


def get_starting_entities():
    return [Book("1", "C.S.Lewis", "Chronicles of Narnia"),
            Book("2", "Edwin A. Abbott", "Flatland"),
            Book("3", "Fyodor Dostoevsky", "Crime and Punishment"),
            Book("4", "Albert Camus", "The Stranger"),
            Book("5", "Charlotte Bronte", "Jane Eyre"),
            Book("6", "Jane Austen", "Sense and Sensibility"),
            Book("7", "Honore de Balzac", "Pierre Gorriot"),
            Book("8", "Daniel Keys", "Flowers for Algernon"),
            Book("9", "Franz Kafka", "The Trial"),
            Book("10", "Jose Saramago", "Blindness"),
            ]


def run_application():
    try:
        settings_loader = SettingsLoader()
        repository = settings_loader.getRepository
    except ValueError as ve:
        print(ve)
        print("Using in memory repository")
        repository = MemoryRepository()

    if len(repository.find_all()) == 0:
        repository.add_all(get_starting_entities())
    service = BookService(repository)
    console_ui = ConsoleUI(service)
    console_ui.run()


if __name__ == "__main__":
    run_application()
