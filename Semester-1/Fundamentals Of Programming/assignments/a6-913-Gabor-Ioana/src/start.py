#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from functions import generate_starting_entities
from ui import run_console_ui
from copy import deepcopy


def start():
    numbers = generate_starting_entities()
    history = [deepcopy(numbers)]
    run_console_ui(history, numbers)


if __name__ == "__main__":
    start()
