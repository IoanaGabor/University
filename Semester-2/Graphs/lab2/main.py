from console_ui import ConsoleUI
from undirected_graph import UndirectedGraph

if __name__ == '__main__':
    graph = UndirectedGraph()
    console_ui = ConsoleUI(graph)
    console_ui.run_console_menu()