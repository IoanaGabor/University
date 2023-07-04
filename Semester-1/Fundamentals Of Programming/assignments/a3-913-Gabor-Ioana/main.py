"""
@author: ioana g.
"""
import timeit
from random import randrange


def display_menu_prompt():
    """Displays the menu prompt

    :return:
    """
    print(
        "For visualising complexities, the first list has 1024 elements, and the other 4 lists have each double the number of elements of the previous one.")
    print("Options:\n"
          "1. Generate a list of n elements\n"
          "2. Display the last generated list of numbers\n"
          "3. Sort the last generated list with the selection sort algorithm\n"
          "4. Sort the last generated list with the shell sort algorithm\n"
          "5. Best case\n"
          "6. Average case\n"
          "7. Worst case\n"
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


def generate_five_lists(n):
    """Generates five lists, the first list containing n numbers,
     and the following containing each the double of the previous list's length.
    :param n: positive integer
    :return: list of lists
    """
    lists = []
    for _ in range(5):
        lists.append(generate_list(n))
        n *= 2
    return lists


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
    """Sorts and returns a list of numbers using the selection sort algorithm and prints the list once every x steps.
    If step is 0, then the function doesn't print anything

    :param numbers: list of integers
    :param step: positive integer
    :return: sorted numbers
    """
    if not numbers and step:
        print("The list hasn't been generated yet.")
        return

    count = 0
    for i in range(len(numbers)):
        for j in range(i + 1, len(numbers)):
            if numbers[i] > numbers[j]:
                numbers[i], numbers[j] = numbers[j], numbers[i]
                count += 1
                if step and count % step == 0:
                    display_list(numbers, "The list after " + str(count) + " steps: ")
    return numbers


def shell_sort(numbers, step):
    """Sorts and returns a list of numbers using the Shell sort algorithm and prints the list once every x steps.
    If step is 0, then the function doesn't print anything
    This Shell sort implementation uses Shell's original sequence. A step is considered to be an iteration with the same
    gap value.

    :param numbers: list of integers
    :param step: integer
    :return: -
    """
    if not numbers and not step:
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
            if step and count % step == 0:
                display_list(numbers, "The list after " + str(count) + " steps, with the gap being " + str(gap) + ": ")
        gap = gap // 2
    return numbers


def best_case(lists):
    """
    Calculates and prints the time it takes to sort more lists with selection sort and Shell sort, in the best case scenario.
    :param lists: lists of lists of integers
    :return:
    """
    print("Best case")
    for numbers in lists:
        numbers.sort()
    for numbers in lists:
        start_selection = timeit.default_timer()
        selection_sort(numbers.copy(), 0)
        end_selection = timeit.default_timer()
        start_shell = timeit.default_timer()
        shell_sort(numbers.copy(), 0)
        end_shell = timeit.default_timer()
        print(str(len(numbers)) + " elements -   " +
              "Selection sort: " + str(end_selection - start_selection) +
              "  Shell sort: " + str(end_shell - start_shell))


def average_case(lists):
    """
    Calculates and prints the time it takes to sort more lists with selection sort and Shell sort, in the average case scenario.
    :param lists: lists of lists of integers
    :return:
    """
    print("Average case")
    for numbers in lists:
        start_selection = timeit.default_timer()
        selection_sort(numbers, 0)
        end_selection = timeit.default_timer()
        start_shell = timeit.default_timer()
        shell_sort(numbers, 0)
        end_shell = timeit.default_timer()
        print(str(len(numbers)) + " elements -   " +
              "Selection sort: " + str(end_selection - start_selection) +
              "  Shell sort: " + str(end_shell - start_shell))


def worst_case(lists):
    """
    Calculates and prints the time it takes to sort more lists with selection sort and Shell sort, in the worst case scenario.
    :param lists: lists of lists of integers
    :return:
    """
    print("Worst case")

    for numbers in lists:
        numbers.sort()
        numbers.reverse()
        start_selection = timeit.default_timer()
        selection_sort(numbers.copy(), 0)
        end_selection = timeit.default_timer()

        numbers.sort()
        numbers.reverse()
        aux = [None] * len(numbers)
        size = len(numbers)
        for i in range(size // 2):
            aux[2 * i] = numbers[i]
            aux[2 * i + 1] = numbers[size // 2 + i]
        numbers = aux

        start_shell = timeit.default_timer()
        shell_sort(numbers.copy(), 0)
        end_shell = timeit.default_timer()
        print(str(len(numbers)) + " elements -   " +
              "Selection sort: " + str(end_selection - start_selection) +
              "  Shell sort: " + str(end_shell - start_shell))


def run_menu():
    invalid_command_text = "The command you entered is invalid"
    enter_instruction_text = "Enter an option: "
    size_of_list_text = "Please enter the size of the list."
    generate_list_text = "The generated list is: "
    step_text = "Enter the number of steps:"
    last_generated_list_text = "The last generated list is:"
    lists = generate_five_lists(1024)
    numbers = []
    sorting_algorithms = {3: selection_sort, 4: shell_sort}
    complexity_cases = {5: best_case, 6: average_case, 7: worst_case}
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
            sorted_list = sorting_algorithms[instruction](numbers.copy(), step)
            display_list(sorted_list, "The sorted list: ")
        elif 5 <= instruction <= 7:
            if not lists:
                print("The lists haven't been generated yet.")
            else:
                complexity_cases[instruction](lists.copy())
        else:
            print(invalid_command_text)


if __name__ == "__main__":
    run_menu()
