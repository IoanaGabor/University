"""
@author: ioana g.
"""
from random import randrange


def display_menu_prompt():
    """Displays the menu prompt

    :return:
    """
    print("Options:\n"
          "1. Generate a list of n elements\n"
          "2. Display the last generated list of numbers\n"
          "3. Sort the last generated list with the selection sort algorithm\n"
          "4. Sort the last generated list with the shell sort algorithm\n"
          "0. Exit\n")


def read_integer(input_message):
    """Displays a given message, then reads a string. If the string doesn't represent an integer, the function warns
    the user, then tries to read again,until an integer is inputted.

    :param input_message: string
    :return: integer
    """
    while True:
        try:
            return int(input(input_message))
        except ValueError:
            print("Not an integer!")


def generate_list(n):
    """Generates a list containing n random natural numbers between 1 and 100.

    :param n: positive integer
    :return: list of integers between 1 and 100
    """
    numbers = []
    for _ in range(n):
        numbers.append(randrange(0, 101))
    return numbers


def display_list(numbers, message=""):
    """Displays the list of numbers and an optional message.

    :param numbers: list of integers
    :param message: string (empty by default)
    :return:
    """
    print(message)
    if not numbers:
        print("Empty list")
    print(numbers)


def selection_sort(numbers, step):
    """Sorts a list of numbers using the selection sort algorithm and prints the list once every x steps.

    :param numbers: list of integers
    :param step: positive integer
    :return: -
    """
    if not numbers:
        print("The list hasn't been generated yet.")
        return

    count = 0
    for i in range(len(numbers)):
        for j in range(i + 1, len(numbers)):
            if numbers[i] > numbers[j]:
                numbers[i], numbers[j] = numbers[j], numbers[i]
                count += 1
                if count % step == 0:
                    display_list(numbers, "The list after " + str(count) + " steps: ")

    display_list(numbers, "The sorted list: ")


def shell_sort(numbers, step):
    """Sorts a list of numbers using the Shell sort algorithm and prints the list once every x steps.

    This Shell sort implementation uses Shell's original sequence. A step is considered to be an iteration with the same
    gap value.

    :param numbers: list of integers
    :param step: integer
    :return: -
    """
    if not numbers:
        print("The list hasn't been generated yet.")
        return
    count = 0
    n = len(numbers)
    gap = n // 2
    while gap > 0:
        for i in range(0, n, gap):
            temp = numbers[i]
            j = i - gap
            while j >= 0 and numbers[j] > temp:
                numbers[j + gap] = numbers[j]
                j = j - gap
            numbers[j + gap] = temp
            count += 1
            if count % step == 0:
                display_list(numbers, "The list after " + str(count) + " steps, with the gap being " + str(gap) + ": ")
        gap = gap // 2
    display_list(numbers, "The sorted list: ")


def run_menu():
    size_of_list_text = "Please enter the size of the list."
    generate_list_text = "The generated list is: "
    step_text = "Enter the number of steps:"
    last_generated_list_text = "The last generated list is:"
    invalid_command_text = "The command you entered is invalid"
    enter_instruction_text = "Enter an option: "
    numbers = []
    sorting_algorithms = {3: selection_sort, 4: shell_sort}
    while True:
        display_menu_prompt()
        instruction = read_integer(enter_instruction_text)
        if instruction == 0:
            break
        elif instruction == 1:
            size = read_integer(size_of_list_text)
            numbers = generate_list(size)
            display_list(numbers, generate_list_text)
        elif instruction == 2:
            display_list(numbers, last_generated_list_text)
        elif 3 <= instruction <= 4:
            step = read_integer(step_text)
            sorting_algorithms[instruction](numbers.copy(), step)
        else:
            print(invalid_command_text)


if __name__ == "__main__":
    run_menu()
