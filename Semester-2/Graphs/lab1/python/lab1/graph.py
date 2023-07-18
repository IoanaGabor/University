import random
from copy import deepcopy


class Graph:
    """
    Represents a directed graph.

    """

    def __init__(self):
        """Constructor for graph. Builds an empty graph.

        """
        self.__in_neighbours = {}
        self.__out_neighbours = {}
        self.__cost = {}

    def is_vertex(self, vertex: str):
        """Checks if a vertex is part of this graph.

        :param vertex: given vertex
        :return: boolean
        """
        if vertex in self.__in_neighbours and vertex in self.__out_neighbours:
            return True
        return False

    def is_edge(self, edge: tuple):
        """Checks if an edge is part of this graph. Preconditions: the edge must be a tuple of 2 vertices.

        :param edge: tuple of 2 edges
        :return: boolean
        :raises Exception: if the edge is not a tuple of 2 vertices
        """
        if not isinstance(edge, tuple) or len(edge) != 2 or type(edge[0]) != str or type(edge[1]) != str:
            raise Exception("The edge doesn't have the required format")
        if edge in self.__cost:
            return True
        return False

    def add_vertex(self, vertex: str):
        """Adds a vertex to the graph. Preconditions: the vertex must not exist in the current graph.

        :param vertex: given vertex
        :return:
        :raises Exception:  if the vertex already exists
        """
        if self.is_vertex(vertex):
            raise Exception("Cannot add vertex, this vertex already exists!")

        self.__in_neighbours[vertex] = []
        self.__out_neighbours[vertex] = []

    def add_edge(self, edge: tuple, cost: int):
        """Adds an edge to the graph. Preconditions: both of its vertices must exist, but the edge must not be present
        in the current graph.

        :param cost:the cost of the added edge
        :param edge:tuple of 2 vertices, the added edge
        :return: nothing
        :raises Exception: if one of its vertices doesn't exist, if the edge already exists or if the cost is not integer
        """
        if type(cost) != int:
            raise Exception("The cost should be an integer")
        if self.is_edge(edge):
            raise Exception("This edge already exists")
        if not self.is_vertex(edge[0]):
            raise Exception("The first vertex of this edge doesn't exist in this graph")
        if not self.is_vertex(edge[1]):
            raise Exception("The second vertex of this edge doesn't exist in this graph")
        self.__in_neighbours[edge[1]].append(edge[0])
        self.__out_neighbours[edge[0]].append(edge[1])
        self.__cost[edge] = cost

    def get_in_degree_of_vertex(self, vertex: str):
        """Gets the in-degree of a vertex. The in-degree is the number of vertices that directly reach
         this vertex.

        :param vertex: given vertex
        :return: integer - the in degree
        :raises Exception: if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist")
        return len(self.__in_neighbours[vertex])

    def get_out_degree_of_vertex(self, vertex):
        """Gets the out-degree of a vertex. The out-degree is the number of vertices that are directly reachable
        from this vertex.

        :param vertex: given vertex
        :return: integer - the out degree
        :raises Exception:  if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist")
        return len(self.__out_neighbours[vertex])

    def get_cost_of_edge(self, edge: tuple):
        """Gets the cost of an edge.

        :param edge: tuple of vertices
        :return: integer - the cost of the given edge
        :raises Exception: if the edge does not exist
        """
        if not self.is_edge(edge):
            raise Exception("This edge does not exist!")
        return self.__cost[edge]

    def set_cost_of_edge(self, edge: tuple, cost: int):
        """Sets the cost of an edge.

        :param edge: tuple of vertices
        :param cost: integer
        :return: integer - the cost of the given edge
        :raises Exception: if the edge doesn't exist or if the cost is not an integer
        """
        if not type(cost) == int:
            raise Exception("The cost should be an integer!")
        if not self.is_edge(edge):
            raise Exception("This edge does not exist!")
        self.__cost[edge] = cost

    def get_inbound_neighbours(self, vertex):
        """Gets the inbound neighbours of a vertex.

        :param vertex: given vertex
        :return: list of outbound neighbours
        :raises Exception: if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist!")
        return deepcopy(self.__in_neighbours[vertex])

    def get_outbound_neighbours(self, vertex):
        """Gets the outbound neighbours of a vertex.

        :param vertex: given vertex
        :return: list of outbound neighbours
        :raises Exception: if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist!")
        return deepcopy(self.__out_neighbours[vertex])

    def remove_edge(self, edge: tuple):
        """Removes an edge.

        :param edge: tuple of 2 vertices
        :return: nothing
        :raises Exception: if the edge doesn't exist
        """
        if not self.is_edge(edge):
            raise Exception("This edge does not exist!")
        self.__in_neighbours[edge[1]].remove(edge[0])
        self.__out_neighbours[edge[0]].remove(edge[1])
        del self.__cost[edge]

    def remove_vertex(self, vertex: str):
        """Removes a vertex.

        :param vertex: given vertex
        :return: nothing
        :raises Exception: if the vertex doesn't exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist!")
        for in_neigh in self.__in_neighbours[vertex]:
            self.__out_neighbours[in_neigh].remove(vertex)
            del self.__cost[(in_neigh, vertex)]
        for out_neigh in self.__out_neighbours[vertex]:
            self.__in_neighbours[out_neigh].remove(vertex)
            del self.__cost[(vertex, out_neigh)]
        del self.__in_neighbours[vertex]
        del self.__out_neighbours[vertex]

    @classmethod
    def build_graph_from_given_vertices_and_edges(cls, vertices, edges_with_costs):
        """Builds a graph from a list of vertices and a list of edges with costs.

        :param vertices: list of vertices
        :param edges_with_costs: list of tuples of 3 parameters - (first vertex, second vertex, cost)
        :return: created graph
        :raises Exception: if the list of received edges is invalid or if the vertices are not all strings
        """
        graph = Graph()
        for vertex in vertices:
            if not type(vertex) == str:
                raise Exception("A vertex should be a string")
            graph.add_vertex(vertex)
        for edge in edges_with_costs:
            if not isinstance(edge, tuple) and len(edge) != 3:
                raise Exception("Invalid edge list!")
            graph.add_edge((edge[0], edge[1]), edge[2])
        return graph

    @classmethod
    def create_copy(cls, graph):
        """Creates a deepcopy of a graph

        :param graph:
        :return: created graph
        """
        return deepcopy(graph)

    @classmethod
    def build_random_graph(cls, number_of_vertices: int, number_of_edges: int):
        """Builds a random graph with a specified number of vertices and number of edges. Preconditions:
        the number of edges should be smaller than or equal to the square of the number of vertices.

        :param number_of_vertices: integer
        :param number_of_edges:integer
        :return: created graph
        :raises Exception: if the number of edges is too large for a graph with distinct edges
        """
        if number_of_edges > number_of_vertices * number_of_vertices:
            raise Exception("Too many edges!")
        graph = Graph()
        for v in range(number_of_vertices):
            graph.add_vertex(str(v))
        edges = set()
        number_of_added_edges = 0
        while number_of_added_edges < number_of_edges:
            edge = (str(random.randrange(0, number_of_vertices)), str(random.randrange(0, number_of_vertices)))
            if edge not in edges:
                edges.add(edge)
                number_of_added_edges += 1
        for edge in edges:
            graph.add_edge(edge, random.randrange(0, 10000))
        return graph

    def get_number_of_vertices(self):
        """Gets the number of vertices in this graph.

        :return: integer
        """
        return len(self.__in_neighbours)

    def get_all_vertices(self):
        """Gets the list of all the vertices in this graph.

        :return: list of vertices
        """
        return list(self.__in_neighbours)

    def get_all_edges(self):
        """Gets the list of all the edges in this graph.

        :return: list of tuple of 2 elements: a tuple for the edge (another tuple of 2 vertices) and an integer
        """
        return [(x, self.__cost[x]) for x in self.__cost]

    def get_isolated_vertices(self):
        """Gets the list of all the isolated vertices

        :return: list of vertices
        """
        isolated_vertices = []
        for vertex in self.__in_neighbours.keys():
            if not self.__in_neighbours[vertex] and not self.__out_neighbours[vertex]:
                isolated_vertices.append(vertex)
        return isolated_vertices
