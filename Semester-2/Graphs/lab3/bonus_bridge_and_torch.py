"""
Bonus 3 (the other 2 are in graph.py)
Approach: each configuration is encoded as a bitmask where the ith bit is 0 if the i person is on the left side
Additionally, we store on which side is the torch
For a configuration, its neighbours are those configurations in which 1 or two people are moved to the other side.
"""
import heapq
from math import inf


class BridgeAndTorchGraph:

    def __init__(self, walking_speeds):
        self.__number_of_people = len(walking_speeds)
        self.__walking_speeds = walking_speeds

    def get_outbound_neighbours(self, configuration, torch):
        movable_people = []
        for i in range(self.__number_of_people):
            if configuration & (2 ** i) == 0 and torch == 0:
                movable_people.append(i)
            elif configuration & (2 ** i) != 0 and torch == 1:
                movable_people.append(i)
        neighbouring_configurations = []
        for person in movable_people:
            neighbouring_configurations.append((configuration ^ (2 ** person), self.__walking_speeds[person]))
            for another_person in movable_people:
                if person < another_person:
                    neighbouring_configurations.append(
                        (configuration ^ ((2 ** person) + (2 ** another_person)),
                         max(self.__walking_speeds[person], self.__walking_speeds[another_person])))
        return neighbouring_configurations


def solve(walking_speeds):
    graph = BridgeAndTorchGraph(walking_speeds)
    number_of_people = len(walking_speeds)
    distance = {}
    for configuration in range(1, 2 ** number_of_people):
        distance[(configuration, 0)] = inf
        distance[(configuration, 1)] = inf
    distance[(0, 0)] = 0
    priority_queue = []
    heapq.heappush(priority_queue, (0, 0, 0))
    while len(priority_queue) > 0:
        dist, current_configuration, current_torch = heapq.heappop(priority_queue)
        if dist != distance[(current_configuration,current_torch)]:
            continue
        for neighbour in graph.get_outbound_neighbours(current_configuration, current_torch):
            configuration, edge_cost = neighbour
            if distance[(configuration, 1 - current_torch)] > distance[
                (current_configuration, current_torch)] + edge_cost:
                distance[(configuration, 1 - current_torch)] = distance[
                                                                   (current_configuration, current_torch)] + edge_cost
                heapq.heappush(priority_queue,
                               (distance[(configuration, 1 - current_torch)], configuration, 1 - current_torch))

    return distance[((2 ** number_of_people) - 1, 1)]


if __name__ == "__main__":
    print(solve([1, 2, 5, 8]))
"""
1 and 2 pass, 1 comes back
5 and 8 pass, 2 comes back
1 and 2 pass

2 + 1 + 8 + 2 + 2 = 15
"""
