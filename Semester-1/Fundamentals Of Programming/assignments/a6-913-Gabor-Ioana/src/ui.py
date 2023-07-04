#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import re
from functions import create_complex_number
from functions import add_number_to_list
from functions import insert_number_at_position, remove_position_from_list, remove_range_of_numbers_from_list
from functions import replace_old_number_with_new_number, list_of_numbers_to_string, \
    select_real_numbers_from_range, select_numbers_with_modulus, keep_only_real_numbers, \
    keep_only_numbers_with_modulus_constraint, undo, parse_complex_number


def add_element(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        add_number_to_list(history, numbers, parse_complex_number(args[1]))
        print("A new element was added")
    except ValueError:
        print("Invalid complex number format.")


def insert_element(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        cmplx_nb = parse_complex_number(args[1])
        pos = int(args[4])
    except ValueError:
        print("Invalid complex number format.")
        return
    try:
        insert_number_at_position(history, numbers, cmplx_nb, pos)
    except Exception as ex:
        print(ex)


def remove_element(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        pos = int(args[1])
    except ValueError:
        print("Invalid complex number format.")
        return
    try:
        remove_position_from_list(history, numbers, pos)
    except Exception as ex:
        print(ex)


def remove_range(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        start_pos = int(args[1])
    except ValueError:
        print("The start position should be a natural number.")
        return
    try:
        end_pos = int(args[3])
    except ValueError:
        print("The end position should be a natural number.")
        return
    try:
        remove_range_of_numbers_from_list(history, numbers, start_pos, end_pos)
    except Exception as ex:
        print(ex)


def replace(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        old_cmplx_nb = parse_complex_number(args[1])
    except ValueError:
        print("First number has invalid complex number format.")
        return
    try:
        new_cmplx_nb = parse_complex_number(args[3])
    except ValueError:
        print("Second number has invalid complex number format.")
        return
    try:
        replace_old_number_with_new_number(history, numbers, old_cmplx_nb, new_cmplx_nb)
    except Exception as ex:
        print(ex)


def list_numbers(history, numbers, command_string):
    print(list_of_numbers_to_string(numbers))


def list_real_numbers_from_range(history, numbers, command_string):
    args = command_string.split(" ")
    try:
        start_pos = int(args[2])
    except ValueError as ve:
        print("The start position should be a natural number.")
        return
    try:
        end_pos = int(args[4])
    except ValueError as ve:
        print("The end position should be a natural number.")
        return
    try:
        print(list_of_numbers_to_string(select_real_numbers_from_range(numbers, start_pos, end_pos)))
    except Exception as ex:
        print(ex)


def list_numbers_with_modulus_constraint(history, numbers, command_string):
    args = command_string.split(" ")
    cmp = args[2]
    try:
        mod = int(args[3])
    except ValueError:
        print("The modulus should be a natural number.")
        return
    try:
        print(list_of_numbers_to_string(select_numbers_with_modulus(numbers, mod, cmp)))
    except Exception as ex:
        print(ex)


def filter_real_numbers(history, numbers, command_string):
    try:
        keep_only_real_numbers(history, numbers)
    except Exception as ex:
        print(ex)


def filter_modulo_constraint(history, numbers, command_string):
    args = command_string.split(" ")
    cmp = args[2]
    try:
        mod = int(args[3])
    except ValueError as ve:
        print("Mod should be a natural number")
        return
    try:
        keep_only_numbers_with_modulus_constraint(history, numbers, mod, cmp)
    except Exception as ex:
        print(ex)


def undo_last_operation(history, numbers, command_string):
    try:
        undo(history, numbers)
        print("The list is now: ")
        print(list_of_numbers_to_string(numbers))
    except Exception as ex:
        print(ex)


def search_for_corresponding_command(expressions, command):
    command = command.lower()
    command = " ".join(command.split())
    for exp in expressions:
        if re.match(exp["structure"], command):
            return exp, command
    return None, command


def print_menu():
    print("Commands: \n"
          "add <number>\n"
          "insert <number> at <position>\n"
          "remove < position >\n"
          "remove < startposition > to < endposition >\n"
          "replace < oldnumber > with < new number >\n"
          "list\n"
          "list real < startposition > to < endposition >\n"
          "list modulo[ < | = | >] < number >\n"
          "filter real\n"
          "filter modulo[ < | = | >] < number >\n"
          "undo \n"
          "exit \n"
          )


def run_console_ui(history, numbers):
    expressions = [
        {
            "structure": "^add [+\-0-9i]*$",
            "function": add_element
        },
        {
            "structure": "^insert [+\-0-9i]* at position [0-9a-z]*$",
            "function": insert_element
        },
        {
            "structure": "^remove [0-9a-z]*$",
            "function": remove_element
        },
        {
            "structure": "^remove [0-9a-z]* to [0-9a-z]*$",
            "function": remove_range
        },
        {
            "structure": "^replace [+\-0-9i]* with [+\-0-9i]*",
            "function": replace
        },
        {
            "structure": "^list$",
            "function": list_numbers,
        },
        {
            "structure": "^list real [0-9a-z]* to [0-9a-z]*",
            "function": list_real_numbers_from_range,
        },
        {
            "structure": "^list modulo [<=>] [0-9a-z]*",
            "function": list_numbers_with_modulus_constraint
        },
        {
            "structure": "^filter real$",
            "function": filter_real_numbers
        },
        {
            "structure": "^filter modulo [<=>] [0-9a-z]*",
            "function": filter_modulo_constraint
        },
        {
            "structure": "^undo$",
            "function": undo_last_operation,
        }
    ]

    while True:
        print_menu()
        command = input("Please enter the command:\n")
        exp, command = search_for_corresponding_command(expressions, command)
        if command == "exit":
            break
        if exp is None:
            print("Invalid expression")
        else:
            exp["function"](history, numbers, command)
