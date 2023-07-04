#
# Write the implementation for A5 in this file
#
import math


#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

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


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex_number(z):
    """Creates a complex number as a dict, from a tuple.

    :param z: tuple of two elements
    :return: dict
    """
    return {
        "real": z[0],
        "img": z[1]
    }


def get_real_part(z):
    """Gets the real part of a complex number stored as a dict.

    :param z: dict(complex number)
    :return: integer
    """
    return z["real"]


def get_imaginary_part(z):
    """Gets the imaginary part of a complex number stored as a dict.

    :param z: dict(complex number)
    :return: integer
    """
    return z["img"]


def set_real_part(z, real):
    """Sets the real part of a complex number stored as a dict

    :param z: dict(complex number)
    :param real: integer
    :return:
    """
    z["real"] = real


def set_imaginary_part(z, imaginary):
    """Sets the imaginary part of a complex number stored as a dict

    :param z: dict(complex number)
    :param imaginary: integer
    :return:
    """
    z["img"] = imaginary


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def modulus(z):
    """Returns the modulus of a complex numer z

    :param z: list or dict
    :return: integer
    """
    return math.sqrt(get_real_part(z) ** 2 + get_imaginary_part(z) ** 2)


def get_longest_subarray_with_increasing_modulus(numbers):
    """Returns the longest subarray with elements which have an increasing modulus.

    :param numbers: list of complex numbers (list or dict)
    :return: list of complex numbers (list or dict)
    """
    solution = []
    solution_candidate = []
    for number in numbers:
        if len(solution_candidate) == 0 or modulus(solution_candidate[-1]) < modulus(number):
            solution_candidate.append(number)
        else:
            if len(solution_candidate) > len(solution):
                solution = solution_candidate.copy()
            solution_candidate = [number]
    if len(solution_candidate) > len(solution):
        solution = solution_candidate.copy()
    return solution


def get_length_of_longest_alternating_subsequence_with_modulus(numbers):
    """The longest alternating subsequence, when considering each number's modulus
    (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10] is an alternating subsequence, because 1 < 3 > 2 < 10)

    :param numbers: list of complex numbers (list or dict)
    :return: list (the longest alternating subsequence)
    """
    dp = []
    for i in range(len(numbers)):
        dp.append([[1, -1], [1, -1]])
    maxi = [0, -1, 0]
    for i in range(len(numbers)):
        for j in range(i):
            if modulus(numbers[j]) < modulus(numbers[i]):
                dp[i][1] = max(dp[i][1], [dp[j][0][0] + 1, j])
            elif modulus(numbers[j]) > modulus(numbers[i]):
                dp[i][0] = max(dp[i][0], [dp[j][1][0] + 1, j])
        maxi = max(maxi, [dp[i][0][0], i, 0])
        maxi = max(maxi, [dp[i][1][0], i, 1])
    num = maxi[1]
    direction = maxi[2]
    sol = []
    while num != -1:
        sol.append(numbers[num])
        num = dp[num][direction][1]
        direction = 1 - direction
    sol.reverse()
    return sol


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_menu():
    """Prints the menu

    :return:
    """
    print("Options:\n"
          "1. Read a list of complex numbers\n"
          "2. Display the list of complex numbers\n"
          "3a. Display the length and elements of a longest subarray of numbers having increasing modulus.\n"
          "3b. Display the length of a longest alternating subsequence, when considering each number's modulus.\n"
          "4. Exit\n")


def read_complex_number():
    """Reads a complex number and returns the complex number stored as a list or dict, depending on the implementation

    :return: list or dict
    """
    while True:
        complex_number_string = input("Enter a complex number, in the form a+bi: ")
        parts = complex_number_string.split('+')
        if len(parts) != 2 or parts[1].find('i') == -1:
            print("Invalid complex number format.")
        else:
            parts[0].strip()
            try:
                imaginary = int(parts[1].strip('i'))
                real = int(parts[0])
                return create_complex_number((real, imaginary))
            except ValueError:
                print("Invalid complex number format.")


def display_complex_number(z):
    """Writes a complex number, in the form a+bi

    :param z: tuple of 2 elements
    :return:
    """
    print("{0}+{1}i".format(get_real_part(z), get_imaginary_part(z)))


def read_list_of_complex_numbers():
    """Reads and returns a list of complex numbers.

    :return: list of tuples
    """
    while True:
        try:
            n = int(input("Enter the length of the list:"))
            break
        except ValueError:
            print("The length is not a natural number")

    list_of_complex_numbers = []
    for i in range(n):
        complex_number = read_complex_number()
        list_of_complex_numbers.append(complex_number)
    return list_of_complex_numbers


def display_list_of_complex_numbers(numbers):
    """Displays a list of complex numbers

    :param numbers:
    :return:
    """
    print("{0} elements".format(len(numbers)))
    for number in numbers:
        display_complex_number(number)


def run_console_menu():
    """Runs the console menu.

    :return:
    """
    numbers = [create_complex_number((1, 0)), create_complex_number((2, 3)), create_complex_number((0, 1)),
               create_complex_number((3, 1)), create_complex_number((4, 5)), create_complex_number((2, 2)),
               create_complex_number((6, 1)), create_complex_number((1, 7)), create_complex_number((6, 6)),
               create_complex_number((4, 3))]
    while True:
        print_menu()
        command = input("Please enter the command:\n")
        if command == "1":
            numbers = read_list_of_complex_numbers()
        elif command == "2":
            display_list_of_complex_numbers(numbers)
        elif command == "3a":
            longest_subarray = get_longest_subarray_with_increasing_modulus(numbers)
            print("The size of the longest subarray is {0}, and the elements are: ".format(len(longest_subarray)))
            display_list_of_complex_numbers(longest_subarray)
        elif command == "3b":
            longest_subsequence = get_length_of_longest_alternating_subsequence_with_modulus(numbers)
            print("The length of the longest alternating subsequence is {0}, and the elements are "
                  .format(len(longest_subsequence)))
            display_list_of_complex_numbers(longest_subsequence)
        elif command == "4":
            break
        else:
            print("Invalid command")


if __name__ == "__main__":
    run_console_menu()
