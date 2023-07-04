import re

from src.exceptions.services_exceptions import ServiceException
from src.services.disciplines_service import DisciplinesService
from src.services.grades_service import GradesService
from src.services.statistics_service import StatisticsService
from src.services.students_service import StudentsService


class ConsoleUI:
    def __init__(self, disciplines_service: DisciplinesService, students_service: StudentsService,
                 grades_service: GradesService, statistics_service: StatisticsService):
        self.__disciplines_service = disciplines_service
        self.__students_service = students_service
        self.__grades_service = grades_service
        self.__statistics_service = statistics_service
        self.__commands = self.__get_commands()

    def __get_commands(self):
        commands = {"^add student [0-9]* [a-zA-Z_]*$": self.__add_student,
                    "^update student [0-9]* [a-zA-Z_]*$": self.__update_student,
                    "^delete student [0-9]*$": self.__delete_student,
                    "^print student [0-9]*$": self.__print_student,
                    "^search student [a-zA-Z]*$": self.__search_student,
                    "^add discipline [0-9]* [a-zA-Z_]*$": self.__add_discipline,
                    "^update discipline [0-9]* [a-zA-Z_]*$": self.__update_discipline,
                    "^delete discipline [0-9]*$": self.__delete_discipline,
                    "^print discipline [0-9]*$": self.__print_discipline,
                    "^search discipline [a-zA-Z]*$": self.__search_discipline,
                    "^grade [0-9]* [0-9]* [0-9]*$": self.__grade_student_at_discipline,
                    "^list failing students$": self.__list_failing_students,
                    "^list sorted students$": self.__list_sorted_students,
                    "^list sorted disciplines$": self.__list_sorted_disciplines,
                    "^list all students$": self.__list_all_students,
                    "^list all disciplines$": self.__list_all_disciplines,
                    "^list all grades at discipline [0-9]*$": self.__list_all_grades_of_discipline,
                    "^list all grades of student [0-9]*$": self.__list_all_grades_of_student,
                    "^list all grades$": self.__list_all_grades}

        return commands

    def __search_for_corresponding_command(self, command_text):
        command_text = " ".join(command_text.split())
        for exp in self.__commands.keys():
            if re.match(exp, command_text):
                return exp, command_text
        return None, command_text

    @staticmethod
    def __print_list_of_entities(entities):
        for entity in entities:
            print(entity)

    def __add_student(self, args):
        student_id = int(args[2])
        name = args[3]
        self.__students_service.add(student_id, name)

    def __update_student(self, args):
        student_id = int(args[2])
        name = args[3]
        self.__students_service.update(student_id, name)

    def __delete_student(self, args):
        student_id = int(args[2])
        self.__students_service.delete(student_id)

    def __print_student(self, args):
        student_id = int(args[2])
        print(self.__students_service.find(student_id))

    def __search_student(self, args):
        search_token = args[2]
        ConsoleUI.__print_list_of_entities(self.__students_service.search(search_token))

    def __add_discipline(self, args):
        discipline_id = int(args[2])
        name = args[3]
        self.__disciplines_service.add(discipline_id, name)

    def __update_discipline(self, args):
        discipline_id = int(args[2])
        name = args[3]
        self.__disciplines_service.update(discipline_id, name)

    def __delete_discipline(self, args):
        discipline_id = int(args[2])
        self.__disciplines_service.delete(discipline_id)

    def __print_discipline(self, args):
        discipline_id = int(args[2])
        print(self.__disciplines_service.find(discipline_id))

    def __search_discipline(self, args):
        search_token = args[2]
        ConsoleUI.__print_list_of_entities(self.__disciplines_service.search(search_token))

    def __grade_student_at_discipline(self, args):
        student_id = int(args[1])
        discipline_id = int(args[2])
        grade_value = int(args[3])
        self.__grades_service.assign_grade_to_student(discipline_id, student_id, grade_value)

    def __list_failing_students(self, args):
        ConsoleUI.__print_list_of_entities(self.__statistics_service.get_failing_students())

    def __list_sorted_students(self, args):
        ConsoleUI.__print_list_of_entities(self.__statistics_service.get_sorted_students())

    def __list_sorted_disciplines(self, args):
        ConsoleUI.__print_list_of_entities(self.__statistics_service.get_sorted_disciplines())

    def __list_all_students(self, args):
        ConsoleUI.__print_list_of_entities(self.__students_service.list_all())

    def __list_all_disciplines(self, args):
        ConsoleUI.__print_list_of_entities(self.__disciplines_service.list_all())

    def __list_all_grades(self, args):
        ConsoleUI.__print_list_of_entities(self.__grades_service.list_all())

    def __list_all_grades_of_student(self, args):
        student_id = int(args[5])
        ConsoleUI.__print_list_of_entities(self.__grades_service.get_all_grades_of_student(student_id))

    def __list_all_grades_of_discipline(self, args):
        discipline_id = int(args[5])
        ConsoleUI.__print_list_of_entities(self.__grades_service.get_all_grades_of_discipline(discipline_id))

    @staticmethod
    def print_menu():
        print("Options:")
        print("add student <id> <name>")
        print("update student <id> <name>")
        print("delete student <id> ")
        print("print student <id> ")
        print("search student <prefix> ")
        print("add discipline <id> <name>")
        print("update discipline <id> <name>")
        print("delete discipline <id> ")
        print("print discipline <id> ")
        print("search discipline <prefix> ")
        print("grade <student_id> <discipline_id> <grade_value>")
        print("list failing students ")
        print("list sorted students ")
        print("list sorted disciplines ")
        print("list all students ")
        print("list all disciplines ")
        print("list all grades at discipline <id>")
        print("list all grades of student <id>")
        print("list all grades")

        print("exit \n")
        print("For ids, only numbers are allowed. For names, you can use letters and _")

    def __process_command(self, expression, command_text):
        try:
            args = command_text.split(" ")
            self.__commands[expression](args)
        except Exception as exception:
            print(exception)

    def run_menu(self):
        while True:
            ConsoleUI.print_menu()
            command_text = input("Please enter the command:\n")
            expression, command_text = self.__search_for_corresponding_command(command_text)
            if command_text == "exit":
                break
            if expression is None:
                print("Invalid command!")
            else:
                self.__process_command(expression, command_text)
