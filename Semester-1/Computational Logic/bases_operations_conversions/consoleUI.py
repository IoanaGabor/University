"""
@author: Ioana Gabor
"""

from number import Number


class ConsoleUI:

    @staticmethod
    def print_menu():
        print("Welcome to the Operations&Conversions app! ")
        print("Operations:")
        print("1. Add two numbers ")
        print("2. Subtract two numbers with a > b")
        print("3. Multiply two numbers ")
        print("4. Divide two numbers\n")
        print("Conversions:")
        print("5. Successive divisions")
        print("6. Substitution method")
        print("7. Using base 10 as an intermediary base")
        print("8. Rapid conversions\n")
        print("0. Exit\n")

    def __init__(self, operations, conversions):
        self.__operations = operations
        self.__conversions = conversions

    @staticmethod
    def get_operations_arguments():
        try:
            base = int(input("The base is:\n"))
        except ValueError as ve:
            raise ValueError("Base should be an integer")
        if base > 16:
            raise ValueError("Base should be <= 16")

        try:
            first_string = input("First number is: \n")
            first_number = Number.get_number_from_string_representation(first_string, base)
        except ValueError as ve:
            raise ve
        try:
            second_string = input("Second number is: \n")
            second_number = Number.get_number_from_string_representation(second_string, base)
        except ValueError as ve:
            raise ve

        return first_number, second_number

    @staticmethod
    def get_conversion_arguments():
        try:
            source_base = int(input("The source base is: \n"))
        except ValueError as ve:
            raise ValueError("Base should be an integer")
        if source_base > 16:
            raise ValueError("Base should be <= 16")

        try:
            first_string = input("The number is: \n")
            first_number = Number.get_number_from_string_representation(first_string, source_base)
        except ValueError as ve:
            raise ve
        try:
            target_base = int(input("The target base is:\n"))
        except ValueError as ve:
            raise ValueError("Base should be an integer")
        if source_base > 16:
            raise ValueError("Base should be <= 16")

        return first_number, target_base

    def run_menu(self):
        operations_commands = {
            '1': self.__operations.add,
            '2': self.__operations.subtract,
            '3': self.__operations.multiply,
            '4': self.__operations.divide
        }
        conversions_commands = {
            '5': self.__conversions.successive_divisions,
            '6': self.__conversions.substitution_method,
            '7': self.__conversions.using_base_10_as_intermediary_base,
            '8': self.__conversions.rapid_conversions,

        }
        while True:
            ConsoleUI.print_menu()
            option = input("Please enter a command (the number in front of it, for instance '1' for addition): \n")
            if option == '0':
                break
            if option not in operations_commands.keys() and option not in conversions_commands.keys():
                print("Option is invalid!")
            else:
                try:
                    if '1' <= option <= '4':
                        first_arg, second_arg = ConsoleUI.get_operations_arguments()
                        result = operations_commands[option](first_arg, second_arg)
                        print("The result is: ")
                        if option == '4':
                            print(result[0])
                        else:
                            print(result)
                    elif '5' <= option <= '8':
                        first_arg, second_arg = ConsoleUI.get_conversion_arguments()
                        result = conversions_commands[option](first_arg, second_arg)
                        print("The result is: ")
                        print(result)
                except Exception as er:
                    print(er)
