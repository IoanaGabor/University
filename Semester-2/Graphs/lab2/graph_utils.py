from undirected_graph import UndirectedGraph


class GraphUtils:
    """Helper methods used for reading and writing graphs to files, in normal or modified format.

    """

    @staticmethod
    def read_graph_normal_format(filename):
        """Reads a graph in "normal format" from a given filename.

        Preconditions: the file must exist, the graph must
        be in the valid format.

        The "normal" format must obey the following rules: on
        the first line of the file, there are 2 integers, separated by space: the number of vertices (n) and the number
        of edges (m). On the next m lines, there are three numbers that describe each of the m edges: the starting
        vertex, the ending vertex and the cost of the edge.


        :param filename: string
        :return: Graph
        :raises Exception: if the graph is invalid, if the file doesn't exist or if other file-related errors occured.

        """
        try:
            with open(filename, "r") as file_descriptor:
                lines = (file_descriptor.readlines())
                arguments = lines[0].split(" ")
            file_descriptor.close()
        except FileNotFoundError:
            raise Exception("The file was not found\n")
        except Exception:
            raise Exception("An error occurred while reading the file\n")

        number_of_vertices = int(arguments[0])
        number_of_edges = int(arguments[1])
        total_vertices = []
        total_edges_with_costs = []
        for i in range(number_of_edges):
            arguments = lines[i + 1].split(" ")
            vertex_from = arguments[0]
            vertex_to_which = arguments[1]
            cost_of_vertex = int(arguments[2])
            total_vertices.append(vertex_from)
            total_vertices.append(vertex_to_which)
            total_edges_with_costs.append((vertex_from, vertex_to_which, cost_of_vertex))
        total_vertices = list(set(total_vertices))
        if len(total_vertices) > number_of_vertices:
            raise Exception("Invalid graph format")
        total_vertices = [str(i) for i in range(number_of_vertices)]
        if len(total_edges_with_costs) != number_of_edges:
            raise Exception("Invalid graph format")
        return UndirectedGraph.build_graph_from_given_vertices_and_edges(total_vertices, total_edges_with_costs)

    @staticmethod
    def write_graph_normal_format(filename, graph):
        """Writes a graph in "normal format" to a given file.

        :param filename: string
        :param graph: Graph
        :raises Exception: if output-related errors occurred
        """
        edges = graph.get_edges_without_duplicates()
        number_of_edges = len(edges)
        number_of_vertices = graph.get_number_of_vertices()
        lines = [str(number_of_vertices) + " " + str(number_of_edges) + "\n"]
        for edge in edges:
            lines.append(str(edge[0][0]) + " " + str(edge[0][1]) + " " + str(edge[1]) + "\n")
        try:
            with open(filename, "w") as file_descriptor:
                file_descriptor.writelines(lines)
            file_descriptor.close()
        except Exception:
            raise Exception("An error occurred while writing into the file\n")

    @staticmethod
    def read_graph_modified_format(filename):
        """Reads a graph in "modified format" from a given filename.

        Preconditions: the file must exist, the filename
        must end with "modified.txt" and the graph should be in the valid format.

        The "modified" format must obey the following rules: on the first line of the file, there are two numbers,
        separated by space: the number of vertices(n) and the number of edges(m). On the second line, there is the
        list of isolated vertices. On the following m lines, there are three numbers that describe each of the m edges:
        the starting vertex, the ending vertex and the cost of the edge.

        :param filename: string
        :return: Graph
        :raises Exception: if the graph is invalid, if the file doesn't exist, if the filename doesn't end with
        "modified.txt" or if other file-related errors occurred

        """
        if not filename.endswith("modified.txt"):
            raise Exception("Filename should start with modified")
        try:
            with open(filename, "r") as file_descriptor:
                lines = (file_descriptor.readlines())
            file_descriptor.close()
        except FileNotFoundError:
            raise Exception("The file was not found\n")
        except Exception:
            raise Exception("An error occurred while reading the file\n")
        arguments = lines[0].split(" ")
        number_of_vertices = int(arguments[0])
        number_of_edges = int(arguments[1])
        isolated_vertices = lines[1].split(" ")
        isolated_vertices.pop(-1)
        total_vertices = []
        total_edges_with_costs = []
        for vertex in isolated_vertices:
            total_vertices.append(vertex)
        for i in range(number_of_edges):
            arguments = lines[i + 2].split(" ")
            vertex_from = arguments[0]
            vertex_to_which = arguments[1]
            cost_of_vertex = int(arguments[2])
            total_vertices.append(vertex_from)
            total_vertices.append(vertex_to_which)
            total_edges_with_costs.append((vertex_from, vertex_to_which, cost_of_vertex))
        total_vertices = list(set(total_vertices))
        if len(total_vertices) != number_of_vertices:
            raise Exception("Invalid graph format")
        if len(total_edges_with_costs) != number_of_edges:
            raise Exception("Invalid graph format")
        return UndirectedGraph.build_graph_from_given_vertices_and_edges(total_vertices, total_edges_with_costs)

    @staticmethod
    def write_graph_modified_format(filename: str, graph):
        """Writes a graph in "modified format" to a given file.

        :param filename: string
        :param graph: Graph
        :raises Exception: if the filename doesn't end with "modified.txt" or if other file-related errors occurred.

        """
        if not filename.endswith("modified.txt"):
            raise Exception("Filename should start with modified")
        edges = graph.get_edges_without_duplicates()
        isolated_vertices = graph.get_isolated_vertices()
        number_of_edges = len(edges)
        number_of_vertices = graph.get_number_of_vertices()
        lines = [str(number_of_vertices) + " " + str(number_of_edges) + "\n", ""]
        for vertex in isolated_vertices:
            lines[1] += str(vertex) + " "
        lines[1] += "\n"
        for edge in edges:
            lines.append(str(edge[0][0]) + " " + str(edge[0][1]) + " " + str(edge[1]) + "\n")
        try:
            with open(filename, "w") as file_descriptor:
                file_descriptor.writelines(lines)
            file_descriptor.close()
        except Exception:
            raise Exception("An error occurred while writing into the file\n")
