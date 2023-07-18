from console_ui import ConsoleUI
from graph import Graph

if __name__ == '__main__':
    graph = Graph()
    console_ui = ConsoleUI(graph)
    console_ui.run_console_menu()
