import heapq
import random
from copy import deepcopy
from math import inf
from queue import Queue


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
            graph.add_edge(edge, random.randrange(0, 100))
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

    def get_all_pairs_shortest_paths(self):
        """Gets all the shortest paths, using the matrix multiplication algorithm. Enables the user to enter pairs
        of vertices and to obtain their shortest path

        :raises Exception: if the graph contains a negative cycle
        """

        def extend(old_dist, weights, old_next_vertex):
            """This method is used only in the get_shortest_path_between_vertices method, for "multiplying" two
            matrices, with the meaning of "extending"/"relaxing" the old distances, using the weights given as the second
             matrix. It also returns the new_next_vertex matrix, in which new_next_vertex[i][j] represents the vertex that
             comes after i on the walk from i to j

            :param old_dist: list[list[int]]
            :param weights: list[list[int]]
            :param old_next_vertex: list[list[int]]
            :return: list[list[int]], list[list[int]]
            """
            new_dist = [[0 for _ in range(number_of_vertices)] for _ in range(number_of_vertices)]
            new_next_vertex = [[-1 for _ in range(number_of_vertices)] for _ in range(number_of_vertices)]
            for i in range(number_of_vertices):
                for j in range(number_of_vertices):
                    new_dist[i][j] = old_dist[i][j]
                    new_next_vertex[i][j] = old_next_vertex[i][j]
                    for k in range(number_of_vertices):
                        if new_dist[i][j] > old_dist[i][k] + weights[k][j]:
                            new_dist[i][j] = old_dist[i][k] + weights[k][j]
                            new_next_vertex[i][j] = old_next_vertex[i][k]
            return new_dist, new_next_vertex

        def all_paths_slow(weights, old_next_vertex):
            """This method is used only in the get_shortest_path_between_vertices method, for computing all pairs
            shortest paths, by the matrix multiplication method. This is done by a linear "raise to the power n-1" of
            the weights matrix. The method returns the list of intermediate matrices and also computes new_next_vertex,
            with the meaning that new_next_vertex[i][j] indicates the vertex that comes after i on the walk from i to j

            :param weights: list[list[int]]
            :param old_next_vertex: list[list[int]]
            :return: list[list[list[int]]], list[list[int]]
            """
            intermediate_matrices = [weights]
            new_next_vertex = old_next_vertex
            for i in range(number_of_vertices - 2):
                new_dist, new_next_vertex = extend(intermediate_matrices[-1], weights, new_next_vertex)
                intermediate_matrices.append(new_dist)
            return intermediate_matrices, new_next_vertex

        def all_paths_faster(weights, old_next_vertex):
            """This method is used only in the get_shortest_path_between_vertices method, for computing all pairs
            shortest paths, by the matrix multiplication method. This is done by an exponential "raise to the power
            2^[log(n-1)]" of the weights matrix. This could often be greater than the power of n-1, but this is ok,
            because all the distance matrices stay the same after the power n-1, if there are no negative cycles.
            The method returns the list of intermediate matrices and also computes new_next_vertex, with the
            meaning that new_next_vertex[i][j] indicates the vertex that comes after i on the walk from i to j

            :param weights: list[list[int]]
            :param old_next_vertex: list[list[int]]
            :return: list[list[list[int]]], list[list[int]]
            """

            intermediate_matrices = [weights]
            new_next_vertex = old_next_vertex
            m = 1
            while m < number_of_vertices - 1:
                new_dist, new_next_vertex = extend(intermediate_matrices[-1], intermediate_matrices[-1],
                                                   new_next_vertex)
                intermediate_matrices.append(new_dist)
                m = 2 * m
            return intermediate_matrices, new_next_vertex

        number_of_vertices = self.get_number_of_vertices()
        from_integer_to_vertex = sorted(self.get_all_vertices())
        from_vertex_to_integer = {}
        for i in range(len(from_integer_to_vertex)):
            from_vertex_to_integer[from_integer_to_vertex[i]] = i

        # computing the adjacency_matrix and next_vertex
        adjacency_matrix = [[0 for _ in range(number_of_vertices)] for _ in range(number_of_vertices)]
        next_vertex = [[-1 for _ in range(number_of_vertices)] for _ in range(number_of_vertices)]
        for i in range(number_of_vertices):
            for j in range(number_of_vertices):
                first_vertex = from_integer_to_vertex[i]
                second_vertex = from_integer_to_vertex[j]
                if i == j:
                    adjacency_matrix[i][j] = 0
                    next_vertex[i][j] = i
                else:
                    current_edge = (first_vertex, second_vertex)
                    if self.is_edge(current_edge):
                        adjacency_matrix[i][j] = self.get_cost_of_edge(current_edge)
                        next_vertex[i][j] = j
                    else:
                        # if there is no edge
                        adjacency_matrix[i][j] = inf

        intermediate_matrices, next_vertex = all_paths_faster(adjacency_matrix, next_vertex)
        distance = intermediate_matrices[-1]
        if distance != extend(distance, distance, next_vertex)[0]:
            # if by "squaring" the matrix we get a different one, the graph has negative cycles
            raise Exception("the graph has negative cycles!")
        for i in range(len(intermediate_matrices)):
            print("Intermediate matrix: ", 2 ** i, intermediate_matrices[i])

        while True:
            command = input("Enter a pair of vertices? y/n")
            if command == "n":
                break
            elif command == "y":
                start_vertex = input("First vertex:\n")
                end_vertex = input("Second vertex:\n")
                if not self.is_vertex(start_vertex) or not self.is_vertex(end_vertex):
                    print("at least one of the vertices doesn't exist")
                start_vertex_as_int = from_vertex_to_integer[start_vertex]
                end_vertex_as_int = from_vertex_to_integer[end_vertex]
                if distance[start_vertex_as_int][end_vertex_as_int] == inf:
                    print("path does not exist")
                else:
                    # retrieving the path, from the next_vertex matrix
                    path = []
                    current_vertex = start_vertex_as_int
                    path.append(from_integer_to_vertex[current_vertex])
                    while current_vertex != end_vertex_as_int:
                        current_vertex = next_vertex[current_vertex][end_vertex_as_int]
                        path.append(from_integer_to_vertex[current_vertex])
                    print("The cost is", distance[start_vertex_as_int][end_vertex_as_int])
                    print("The path is", path)
            else:
                print("invalid command")

    def get_number_of_minimum_paths_between_vertices(self, start_vertex, end_vertex):
        """Bonus 1

        """
        if not self.is_vertex(start_vertex):
            raise Exception("start vertex does not exist")

        if not self.is_vertex(end_vertex):
            raise Exception("end vertex does not exist")

        distance = {}
        number_of_paths = {}
        visited = {}
        for vertex in self.get_all_vertices():
            distance[vertex] = inf
            number_of_paths[vertex] = 0
            visited[vertex] = 0
        distance[start_vertex] = 0
        number_of_paths[start_vertex] = 1
        priority_queue = []
        heapq.heappush(priority_queue, (0, start_vertex))
        while len(priority_queue) > 0:
            dist, current_vertex = heapq.heappop(priority_queue)
            visited[current_vertex] += 1
            if dist != distance[current_vertex]:
                continue
            if visited[current_vertex] > self.get_number_of_vertices():
                raise Exception("This graph has a negative cycle!")
            for neighbour in self.get_outbound_neighbours(current_vertex):
                edge_cost = self.get_cost_of_edge((current_vertex, neighbour))
                if distance[neighbour] > distance[current_vertex] + edge_cost:
                    distance[neighbour] = distance[current_vertex] + edge_cost
                    number_of_paths[neighbour] = number_of_paths[current_vertex]
                    heapq.heappush(priority_queue, (distance[neighbour], neighbour))
                elif distance[neighbour] == distance[current_vertex] + edge_cost:
                    number_of_paths[neighbour] += number_of_paths[current_vertex]
        return number_of_paths[end_vertex]

    def topological_sort(self):
        in_degree = {}
        queue = Queue()
        for vertex in self.get_all_vertices():
            in_degree[vertex] = self.get_in_degree_of_vertex(vertex)
            if in_degree[vertex] == 0:
                queue.put(vertex)
        topologically_sorted_vertices = []
        while not queue.empty():
            current_element = queue.get()
            topologically_sorted_vertices.append(current_element)
            for neigh in self.get_outbound_neighbours(current_element):
                in_degree[neigh] -= 1
                if in_degree[neigh] == 0:
                    queue.put(neigh)
        if len(topologically_sorted_vertices) < self.get_number_of_vertices():
            raise Exception("This graph is not a Directed Acyclic Graph!")
        return topologically_sorted_vertices

    def get_number_of_walks_between_vertices_in_dag(self, start_vertex, end_vertex):
        """Bonus 2

        """
        if not self.is_vertex(start_vertex):
            raise Exception("start vertex does not exist")

        if not self.is_vertex(end_vertex):
            raise Exception("end vertex does not exist")

        topologically_sorted_vertices = self.topological_sort()
        number_of_walks = {}
        for vertex in self.get_all_vertices():
            number_of_walks[vertex] = 0
        number_of_walks[start_vertex] = 1
        for vertex in topologically_sorted_vertices:
            for neigh in self.get_outbound_neighbours(vertex):
                number_of_walks[neigh] += number_of_walks[vertex]
        return number_of_walks[end_vertex]
