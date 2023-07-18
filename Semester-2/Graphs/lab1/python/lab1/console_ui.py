from graph import Graph
from graph_utils import GraphUtils


class ConsoleUI:

    def __init__(self, graph):
        self.__graph = graph

    @staticmethod
    def __print_list_of_vertices(vertices):
        print("The vertices are: ")
        for vertex in vertices:
            print(vertex, end=" ")

    @staticmethod
    def __print_list_of_edges(edges):
        print("The edges are: ")
        for edge in edges:
            print(edge, end=" ")

    @staticmethod
    def __print_menu():
        print("Options:\n")
        print("1. Print the number of vertices")
        print("2. Print the set of vertices")
        print("3. Check if this edge exists")
        print("4. Print the in degree and the out degree of an vertex")
        print("5. Print the set of outbound edges of an vertex")
        print("6. Print the set of inbound edges of an vertex")
        print("7. Print the cost of an edge")
        print("8. Modify the cost of an edge")
        print("9. Add edge")
        print("10. Remove edge")
        print("11. Add vertex")
        print("12. Remove vertex")
        print("13. Display all edges")
        print("14. Generate random graph")
        print("15. Read graph with normal format ")
        print("16. Write graph with normal format")
        print("17. Read graph with altered format")
        print("18. Write graph with altered format")
        print("19. Check if a vertex exists")
        print("exit")

    @staticmethod
    def __read_a_vertex():
        vertex = input("Enter the vertex:\n")
        return vertex

    @staticmethod
    def __read_an_edge_without_cost():
        x = input("First vertex:\n")
        y = input("Second vertex:\n")
        return x, y

    @staticmethod
    def __read_an_edge_with_cost():
        x = input("First vertex:\n")
        y = input("Second vertex:\n")
        try:
            c = int(input("Cost: \n"))
        except ValueError as ve:
            raise Exception("The cost should be an integer")

        return x, y, c

    def __handle_print_the_number_of_vertices(self):
        print("The number of vertices is {0}".format(self.__graph.get_number_of_vertices()))

    def __handle_print_list_of_vertices(self):
        ConsoleUI.__print_list_of_vertices(self.__graph.get_all_vertices())

    def __handle_print_list_of_edges(self):
        ConsoleUI.__print_list_of_edges(self.__graph.get_all_edges())

    def __handle_checking_if_an_edge_exists(self):
        edge = self.__read_an_edge_without_cost()
        if self.__graph.is_edge(edge):
            print("The edge exists")
        else:
            print("The edge doesn't exist")

    def __handle_checking_if_a_vertex_exists(self):
        vertex = self.__read_a_vertex()
        if self.__graph.is_vertex(vertex):
            print("The vertex exists")
        else:
            print("The vertex doesn't exist")


    def __handle_reading_graph_with_normal_format(self):
        filename = input("Enter the filename")
        try:
            self.__graph = GraphUtils.read_graph_normal_format(filename)
        except Exception as exc:
            print(exc)

    def __handle_writing_graph_with_normal_format(self):
        filename = input("Enter the filename")
        try:
            GraphUtils.write_graph_normal_format(filename, self.__graph)
        except Exception as exc:
            print(exc)

    def __handle_reading_graph_with_modified_format(self):
        filename = input("Enter the filename")
        try:
            self.__graph = GraphUtils.read_graph_modified_format(filename)
        except Exception as exc:
            print(exc)

    def __handle_writing_graph_with_modified_format(self):
        filename = input("Enter the filename")
        try:
            GraphUtils.write_graph_modified_format(filename, self.__graph)
        except Exception as exc:
            print(exc)

    def __handle_printing_the_degrees_of_a_vertex(self):
        try:
            vertex = ConsoleUI.__read_a_vertex()
            in_degree = self.__graph.get_in_degree_of_vertex(vertex)
            out_degree = self.__graph.get_out_degree_of_vertex(vertex)
            print("The in degree is {0} and the out degree is {1}".format(in_degree, out_degree))
        except Exception as e:
            print(e)

    def __handle_printing_the_set_of_outbound_vertices(self):
        try:
            vertex = ConsoleUI.__read_a_vertex()
            outbound_vertices = self.__graph.get_outbound_neighbours(vertex)
            ConsoleUI.__print_list_of_vertices(outbound_vertices)
        except Exception as e:
            print(e)

    def __handle_printing_the_set_of_inbound_vertices(self):
        try:
            vertex = ConsoleUI.__read_a_vertex()
            inbound_vertices = self.__graph.get_inbound_neighbours(vertex)
            ConsoleUI.__print_list_of_vertices(inbound_vertices)
        except Exception as e:
            print(e)

    def __handle_printing_the_cost_of_an_edge(self):
        try:
            edge = ConsoleUI.__read_an_edge_without_cost()
            print("The cost is {0} ", self.__graph.get_cost_of_edge(edge))
        except Exception as e:
            print(e)

    def __handle_modifying_the_cost_of_an_edge(self):
        try:
            edge = ConsoleUI.__read_an_edge_with_cost()
            self.__graph.set_cost_of_edge((edge[0], edge[1]), edge[2])
        except Exception as e:
            print(e)

    def __handle_adding_an_edge(self):
        try:
            edge_with_cost = self.__read_an_edge_with_cost()
            edge, cost = (edge_with_cost[0], edge_with_cost[1]), edge_with_cost[2]
            self.__graph.add_edge(edge, cost)
        except Exception as exc:
            print(exc)

    def __handle_removing_an_edge(self):
        try:
            edge = self.__read_an_edge_without_cost()
            self.__graph.remove_edge(edge)
        except Exception as exc:
            print(exc)

    def __handle_adding_a_vertex(self):
        try:
            vertex = self.__read_a_vertex()
            self.__graph.add_vertex(vertex)
        except Exception as exc:
            print(exc)

    def __handle_removing_a_vertex(self):
        try:
            vertex = self.__read_a_vertex()
            self.__graph.remove_vertex(vertex)
        except Exception as exc:
            print(exc)

    def __handle_generating_random_graph(self):
        try:
            number_of_vertices = int(input("The number of vertices:"))
            number_of_edges = int(input("The number of edges:"))
        except ValueError:
            print("The number of vertices and the number of edges should be positive integers")
            return
        if number_of_vertices < 0 or number_of_edges < 0:
            print("The number of vertices and the number of edges should be positive integers")
            return
        try:
            self.__graph = Graph.build_random_graph(number_of_vertices, number_of_edges)
        except Exception as exc:
            self.__graph = Graph()
            print(exc)

    def run_console_menu(self):
        while True:
            ConsoleUI.__print_menu()
            command = input()
            if command == "1":
                self.__handle_print_the_number_of_vertices()
            elif command == "2":
                self.__handle_print_list_of_vertices()
            elif command == "3":
                self.__handle_checking_if_an_edge_exists()
            elif command == "4":
                self.__handle_printing_the_degrees_of_a_vertex()
            elif command == "5":
                self.__handle_printing_the_set_of_outbound_vertices()
            elif command == "6":
                self.__handle_printing_the_set_of_inbound_vertices()
            elif command == "7":
                self.__handle_printing_the_cost_of_an_edge()
            elif command == "8":
                self.__handle_modifying_the_cost_of_an_edge()
            elif command == "9":
                self.__handle_adding_an_edge()
            elif command == "10":
                self.__handle_removing_an_edge()
            elif command == "11":
                self.__handle_adding_a_vertex()
            elif command == "12":
                self.__handle_removing_a_vertex()
            elif command == "13":
                self.__handle_print_list_of_edges()
            elif command == "14":
                self.__handle_generating_random_graph()
            elif command == "15":
                self.__handle_reading_graph_with_normal_format()
            elif command == "16":
                self.__handle_writing_graph_with_normal_format()
            elif command == "17":
                self.__handle_reading_graph_with_modified_format()
            elif command == "18":
                self.__handle_writing_graph_with_modified_format()
            elif command == "19":
                self.__handle_checking_if_a_vertex_exists()
            elif command == "exit":
                break
            else:
                print("Invalid command")
