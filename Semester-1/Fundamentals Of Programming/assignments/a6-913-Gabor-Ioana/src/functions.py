#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import math
from copy import deepcopy


def create_complex_number(z):
    """Creates a complex number as a list, from a tuple.

    :param z: tuple of two elements
    :return: list
    """
    return [z[0], z[1]]


def get_real_part(z):
    """Gets the real part of a complex number stored as a list.

    :param z: list of 2 integers(complex number)
    :return: integer
    """
    return z[0]


def get_imaginary_part(z):
    """Gets the imaginary part of a complex number stored as a list.

    :param z: list of 2 integers(complex number)
    :return: integer
    """
    return z[1]


def set_real_part(z, real):
    """Sets the real part of a complex number stored as a list

    :param z: list of 2 integers(complex number)
    :param real: integer
    :return:
    """
    z[0] = real


def set_imaginary_part(z, imaginary):
    """Sets the imaginary part of a complex number stored as a list

    :param z: list of 2 integers(complex number)
    :param imaginary: integer
    :return:
    """
    z[1] = imaginary


def parse_complex_number(complex_number_string):
    """Parses a string and returns a complex number

    :param complex_number_string:
    :return:
    """
    real_sign = 1
    if complex_number_string.find('+') == -1 and complex_number_string[1:].find('-') != -1:

        parts = complex_number_string.split('-')
        if len(parts) == 3 and parts[0] == "":
            parts = parts[1:]
            real_sign = -1
        if len(parts) != 2 or parts[1].find('i') == -1:
            raise ValueError
        else:
            parts[0].strip()
            imaginary = - int(parts[1].strip('i'))
            real = int(parts[0])
            real = real * real_sign
            return create_complex_number((real, imaginary))
    else:
        parts = complex_number_string.split('+')
        if len(parts) != 2 or parts[1].find('i') == -1:
            raise ValueError
        else:
            parts[0].strip()
            imaginary = int(parts[1].strip('i'))
            real = int(parts[0])
            return create_complex_number((real, imaginary))


def complex_number_to_string(z):
    """Gets the string representation of a complex number

    :param z: complex number
    :return: string
    """
    return "{0}+{1}i".format(get_real_part(z), get_imaginary_part(z))


def list_of_numbers_to_string(numbers):
    """Gets the string representation of a list of complex numbers.

    :param numbers: list of complex numbers
    :return: string
    """
    list_as_string = ""
    for num in numbers:
        list_as_string += " " + complex_number_to_string(num)
    return list_as_string


def modulus(z):
    """Returns the modulus of a complex numer z

    :param z: list or dict
    :return: integer
    """
    return math.sqrt(get_real_part(z) ** 2 + get_imaginary_part(z) ** 2)


def add_number_to_list(history, numbers, new_number):
    """Adds a complex number to the list.
    :param history: list of lists of complex numbers
    :param numbers: list of complex numbers
    :param new_number:complex number
    :return:
    """
    numbers.append(new_number)
    history.append(deepcopy(numbers))


def insert_number_at_position(history, numbers, new_number, position):
    """Inserts a complex number at a certain position in the list

    :param numbers:list of complex numbers
    :param new_number: complex number
    :param position:integer
    :return:
    """
    if position > len(numbers):
        raise Exception("Position is out of range")
    numbers.insert(position, new_number)
    history.append(deepcopy(numbers))


def select_real_numbers(numbers):
    """Returns the list of numbers who don't have an imaginary part.

    :param numbers: list of complex numbers
    :return: list of complex numbers
    """
    real = []
    for num in numbers:
        if get_imaginary_part(num) == 0:
            real.append(num)
    return real


def select_real_numbers_from_range(numbers, start_pos, end_pos):
    """Returns the list of numbers with positions between start_pos and end_pos, who don't have an imaginary part.

    :param numbers: list of complex numbers
    :param start_pos: integer
    :param end_pos: integer
    :return: list of complex numbers
    """
    if start_pos > end_pos:
        raise Exception("The start position cannot be larger than the end position")
    if 0 > start_pos or len(numbers) <= start_pos:
        raise Exception("The start position is not in range")
    if 0 > end_pos or len(numbers) <= end_pos:
        raise Exception("The end position is not in range")
    real = []
    for num in numbers[start_pos:end_pos]:
        if get_imaginary_part(num) == 0:
            real.append(num)
    return real


def select_numbers_with_modulus(numbers, mod, comparator):
    """Returns a list of numbers with respect a certain property regarding the modulus (less than, greater than, equal to).

    :param numbers: list of complex numbers
    :param mod: integer
    :param comparator: character (<, >, =)
    :return:list of selected complex numbers
    """
    comparing_condition = {
        "<": lambda x, m: modulus(x) < m,
        "=": lambda x, m: modulus(x) == m,
        ">": lambda x, m: modulus(x) > m
    }
    selected_numbers = []
    for num in numbers:
        if comparing_condition[comparator](num, mod):
            selected_numbers.append(num)
    return selected_numbers


def keep_only_real_numbers(history, numbers):
    """Filters the list and keeps only the real numbers.

    :param history: list of lists of complex numbers (the history of operations)
    :param numbers: list of complex numbers
    :return:
    """
    numbers[:] = select_real_numbers(numbers)
    history.append(deepcopy(numbers))


def keep_only_numbers_with_modulus_constraint(history, numbers, mod, comparator):
    """Changes the initial list so that only numbers which respect a certain modulus constraint are kept.

    :param history: list of lists of complex numbers
    :param numbers: list of complex numbers
    :param comparator: character (<, >, =)
    :return:
    """
    selected = select_numbers_with_modulus(numbers, mod, comparator)
    numbers[:] = deepcopy(selected)
    history.append(deepcopy(numbers))


def replace_old_number_with_new_number(history, numbers, old_number, new_number):
    """Replaces all the occurrences of the old number with the new number, changing the initial list.

    :param numbers: list of complex numbers
    :param old_number: complex number
    :param new_number: complex number
    :return:
    """
    for i in range(len(numbers)):
        if numbers[i] == old_number:
            set_real_part(numbers[i], get_real_part(new_number))
            set_imaginary_part(numbers[i], get_imaginary_part(new_number))
    history.append(deepcopy(numbers))


def remove_position_from_list(history, numbers, position):
    """Removes the number from a given position, changing the initial list.
    Throws an exception if the position is not in range

    :param numbers: list of complex numbers
    :param position: integer
    :return:
    """
    if position >= len(numbers):
        raise Exception("Position is out of range")
    numbers.pop(position)
    history.append(deepcopy(numbers))


def remove_range_of_numbers_from_list(history, numbers, start_position, end_position):
    """Removes the number from a given position, changing the initial list.
    Throws an exception if the position is not in range

    :param numbers: list of complex numbers
    :param start_position: integer
    :param end_position: integer
    :return:
    """
    if start_position > end_position:
        raise Exception("The start position cannot be larger than the end position")
    if 0 > start_position or len(numbers) <= start_position:
        raise Exception("The start position is not in range")
    if 0 > end_position or len(numbers) <= end_position:
        raise Exception("The end position is not in range")
    numbers[:] = numbers[:start_position] + numbers[end_position:]
    history.append(deepcopy(numbers))


def generate_starting_entities():
    """Generates and returns a list of 10 starting entities (complex numbers)

    :return: list of complex numbers
    """
    return [create_complex_number((5, 0)), create_complex_number((4, 5)), create_complex_number((3, 0)),
            create_complex_number((5, 4)), create_complex_number((3, 5)), create_complex_number((3, 9)),
            create_complex_number((5, 90)), create_complex_number((4, 5)), create_complex_number((6, 8)),
            create_complex_number((5, 0)), create_complex_number((41, 5)), create_complex_number((3, 0))]


def undo(history, numbers):
    """Performs the undo operation on the numbers list, modifying it to the last version.

    :param history: list of lists of complex numbers (the previous versions)
    :param numbers: list of complex numbers
    :return:
    """
    if len(history) < 2:
        raise Exception("Previous operation does not exist")
    numbers[:] = deepcopy(history[-2])
    history[:] = history[:-1]
