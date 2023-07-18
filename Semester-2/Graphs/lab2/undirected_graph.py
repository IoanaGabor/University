import random
from copy import deepcopy
from queue import Queue


class UndirectedGraph:
    """
    Represents an undirected graph.

    """

    def __init__(self):
        """Constructor for graph. Builds an empty graph.

        """
        self.__neighbours = {}
        self.__cost = {}

    def is_vertex(self, vertex: str):
        """Checks if a vertex is part of this graph.

        :param vertex: given vertex
        :return: boolean
        """
        if vertex in self.__neighbours:
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

        self.__neighbours[vertex] = []

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
        self.__neighbours[edge[1]].append(edge[0])
        self.__neighbours[edge[0]].append(edge[1])
        self.__cost[edge] = cost
        self.__cost[(edge[1], edge[0])] = cost

    def get_degree_of_vertex(self, vertex: str):
        """Gets the degree of a vertex. The degree is the number of vertices that directly reach (and are reached by)
         this vertex.

        :param vertex: given vertex
        :return: integer - the in degree
        :raises Exception: if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist")
        return len(self.__neighbours[vertex])

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
        self.__cost[(edge[1], edge[0])] = cost

    def get_neighbours(self, vertex):
        """Gets the neighbours of a vertex.

        :param vertex: given vertex
        :return: list of outbound neighbours
        :raises Exception: if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist!")
        return deepcopy(self.__neighbours[vertex])

    def remove_edge(self, edge: tuple):
        """Removes an edge.

        :param edge: tuple of 2 vertices
        :return: nothing
        :raises Exception: if the edge doesn't exist
        """
        if not self.is_edge(edge):
            raise Exception("This edge does not exist!")
        self.__neighbours[edge[1]].remove(edge[0])
        self.__neighbours[edge[0]].remove(edge[1])
        del self.__cost[edge]
        del self.__cost[(edge[1], edge[0])]

    def remove_vertex(self, vertex: str):
        """Removes a vertex.

        :param vertex: given vertex
        :return: nothing
        :raises Exception: if the vertex doesn't exist
        """
        if not self.is_vertex(vertex):
            raise Exception("This vertex does not exist!")
        for neigh in self.__neighbours[vertex]:
            del self.__cost[(neigh, vertex)]
            del self.__cost[(vertex, neigh)]
            self.__neighbours[neigh].remove(vertex)
        del self.__neighbours[vertex]

    @classmethod
    def build_graph_from_given_vertices_and_edges(cls, vertices, edges_with_costs):
        """Builds a graph from a list of vertices and a list of edges with costs.

        :param vertices: list of vertices
        :param edges_with_costs: list of tuples of 3 parameters - (first vertex, second vertex, cost)
        :return: created graph
        :raises Exception: if the list of received edges is invalid or if the vertices are not all strings
        """
        graph = UndirectedGraph()
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
        graph = UndirectedGraph()
        for v in range(number_of_vertices):
            graph.add_vertex(str(v))
        edges = []
        for v in range(number_of_vertices):
            for w in range(v + 1, number_of_vertices):
                edges.append((str(v), str(w)))
        random.shuffle(edges)
        edges = edges[:number_of_edges]
        for edge in edges:
            graph.add_edge(edge, random.randrange(0, 10000))
        return graph

    def get_number_of_vertices(self):
        """Gets the number of vertices in this graph.

        :return: integer
        """
        return len(self.__neighbours)

    def get_all_vertices(self):
        """Gets the list of all the vertices in this graph.

        :return: list of vertices
        """
        return list(self.__neighbours)

    def get_all_edges(self):
        """Gets the list of all the edges in this graph.

        :return: list of tuple of 2 elements: a tuple for the edge (another tuple of 2 vertices) and an integer
        """
        return [(x, self.__cost[x]) for x in self.__cost]

    def get_edges_without_duplicates(self):
        """Gets the list of all the undirected edges in this graph without duplicates.
        This means that (a,b) is the same as (b,a)

        :return: list of tuple of 2 elements: a tuple for the edge (another tuple of 2 vertices) and an integer
        """
        return [(x, self.__cost[x]) for x in self.__cost if x[0] < x[1]]

    def get_isolated_vertices(self):
        """Gets the list of all the isolated vertices

        :return: list of vertices
        """
        isolated_vertices = []
        for vertex in self.__neighbours.keys():
            if not self.__neighbours[vertex]:
                isolated_vertices.append(vertex)
        return isolated_vertices

    def __str__(self):
        """String representation of a graph

        :return: string
        """
        graph_as_string = "List of vertices: "
        for vertex in self.get_all_vertices():
            graph_as_string += str(vertex) + ", "
        graph_as_string += "\n"
        graph_as_string += "List of edges: "
        for edge in self.get_edges_without_duplicates():
            graph_as_string += str(edge) + ", "
        return graph_as_string

    def __get_connected_component_of(self, vertex_of_start):
        """Gets the connected component that contains the vertex_of_start, with a
        breadth-first traversal of the graph.

        :param vertex_of_start:
        :return: UndirectedGraph
        """
        queue = Queue(0)
        queue.put(vertex_of_start)
        accessible_vertices = set(vertex_of_start)
        component_edges = set()
        while not queue.empty():
            current_vertex = queue.get()  # the current vertex is popped from the queue
            for neighbour in self.get_neighbours(current_vertex):
                if neighbour not in accessible_vertices:
                    # the unvisited neighbours are marked as visited and added to the queue
                    accessible_vertices.add(neighbour)
                    queue.put(neighbour)
                if (neighbour, current_vertex) not in component_edges:
                    # the not added edges are added to the list of edges of the current component
                    component_edges.add((current_vertex, neighbour))
        component_edges_with_costs = set()
        for edge in component_edges:
            edge_with_cost = (edge[0], edge[1], self.get_cost_of_edge((edge[0], edge[1])))
            component_edges_with_costs.add(edge_with_cost)
        return UndirectedGraph.build_graph_from_given_vertices_and_edges(list(accessible_vertices),
                                                                         list(component_edges_with_costs))

    def get_connected_components(self):
        """Gets the connected components of the undirected graph.

        :return: list of UndirectedGraph
        """
        visited_vertices = set()
        connected_components = []
        for vertex in self.get_all_vertices():
            if vertex not in visited_vertices:
                # the connected component which contains the current unvisited vertex is obtained
                current_connected_component = self.__get_connected_component_of(vertex)
                accessible_vertices = current_connected_component.get_all_vertices()
                # the visited vertices are marked as such
                for visited_vertex in accessible_vertices:
                    visited_vertices.add(visited_vertex)
                connected_components.append(current_connected_component)
        return connected_components
