from math import inf

from graph import Graph


class SchedulingProblem:
    """
    Static methods used for solving the Scheduling problem.
    """
    @staticmethod
    def solve(graph: Graph):
        """Given a graph of activities, solves the scheduling problem. 
        :param graph:
        :return: tuple: the total duration of the project, the earliest starting times, the latest starting times,
        the critical vertices
        :raises Exception: if the graph is not a DAG
        """
        sorted_vertices = graph.topological_sort()  # topological sort
        earliest_starting_time = {}
        latest_starting_time = {}
        for vertex in sorted_vertices:
            earliest_starting_time[vertex] = 0
            latest_starting_time[vertex] = inf
        # computing the earliest starting times, in the order of the topological sort
        earliest_starting_time[("start", 0)] = 0
        for vertex in sorted_vertices:
            for neigh in graph.get_outbound_neighbours(vertex):
                earliest_starting_time[neigh] = max(earliest_starting_time[neigh],
                                                    earliest_starting_time[vertex] + vertex[1])
        # computing the latest starting times, in reverse order of the topological sort
        latest_starting_time[("finish", 0)] = earliest_starting_time[("finish", 0)]
        for vertex in reversed(sorted_vertices):
            for neigh in graph.get_inbound_neighbours(vertex):
                latest_starting_time[neigh] = min(latest_starting_time[neigh],
                                                  latest_starting_time[vertex] - neigh[1])
        # the critical vertices are those which have the earliest starting time equal to the latest starting time
        critical_vertices = []
        for vertex in sorted_vertices:
            if earliest_starting_time[vertex] == latest_starting_time[vertex]:
                critical_vertices.append(vertex)
        return earliest_starting_time[("finish", 0)], earliest_starting_time, latest_starting_time, critical_vertices

    @staticmethod
    def read_activities_from_file(filename):
        """Reads the activities from the file and builds the corresponding graph, adding 2 additional activities, of
        cost 0: start and finish

        :param filename: string
        :return: graph
        """
        with open(filename, "r") as file_descriptor:
            lines = (file_descriptor.readlines())
        file_descriptor.close()
        vertices_with_activities = {}
        edges = []
        for line in lines:
            line = line[:-1]
            args = line.split(" ")
            if len(args) < 2:
                raise Exception("invalid format")
            vertices_with_activities[args[0]] = int(args[1])
            previous_activities = args[2:]
            for prev in previous_activities:
                edges.append((prev, args[0]))

        edges_with_activity_costs = []
        for edge in edges:
            edges_with_activity_costs.append(
                ((edge[0], vertices_with_activities[edge[0]]), (edge[1], vertices_with_activities[edge[1]])))
        vertices_with_activity_costs = []
        for vertex in vertices_with_activities.keys():
            vertices_with_activity_costs.append((vertex, vertices_with_activities[vertex]))
        graph = Graph.build_graph_from_given_vertices_and_edges(vertices_with_activity_costs, edges_with_activity_costs)
        without_predecessors = graph.get_vertices_without_predecessors()
        without_successors = graph.get_vertices_without_successors()
        extra_start = ("start", 0)  # add 2 extra activities: start and finish
        extra_finish = ("finish", 0)
        graph.add_vertex(extra_start)
        graph.add_vertex(extra_finish)
        for vertex in without_predecessors:
            graph.add_edge((extra_start, vertex))
        for vertex in without_successors:
            graph.add_edge((vertex, extra_finish))
        return graph
