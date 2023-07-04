def strictly_increasing_subsequences_recursive(numbers, solution_candidate, current_index):
    """Generates the strictly increasing subsequences of a list with recursive backtracking

    :param numbers: list of integers
    :param solution_candidate: list of integers
    :param current_index: integer
    :return: list of lists of integers
    """
    subsequences = []
    if len(solution_candidate):
        subsequences = [solution_candidate]
    if current_index == len(numbers):
        return subsequences

    for i in range(current_index + 1, len(numbers)):
        if current_index == -1 or solution_candidate[-1] < numbers[i]:
            partial_solutions = strictly_increasing_subsequences_recursive(numbers, solution_candidate + [numbers[i]],
                                                                           i)
            for partial_solution in partial_solutions:
                subsequences += [partial_solution]

    return subsequences


def next_element(solution_candidate, numbers):
    """Generates the next element, given a solution candidate and the numbers list, or returns None
    if the next element does not exist

    :param solution_candidate: list of integers
    :param numbers: list of integers
    :return: integer or None
    """
    if len(solution_candidate) == 1:
        el = solution_candidate[0] + 1
    elif solution_candidate[-1] == -1:
        el = solution_candidate[-2] + 1
    else:
        el = solution_candidate[-1] + 1
    if el >= len(numbers):
        return None
    return el


def is_consistent(solution_candidate, numbers):
    """Checks if a solution candidate is consistent.
    A solution candidate is consistent if it has strictly increasing elements.

    :param solution_candidate: list of integers
    :param numbers: list of integers
    :return: boolean (true if the solution candidate is consistent)
    """
    if len(solution_candidate) == 1:
        return True
    if numbers[solution_candidate[-1]] > numbers[solution_candidate[-2]]:
        return True
    return False


def strictly_increasing_subsequences_iterative(numbers):
    """Genereates the strictly increasing subsequences with iterative backtracking.

    :param numbers: list of integers
    :return: list of lists of integers
    """
    subsequences = []
    solution_candidate = [-1]
    while len(solution_candidate) > 0:
        el = next_element(solution_candidate, numbers)
        while el is not None:
            solution_candidate[-1] = el
            if is_consistent(solution_candidate, numbers):
                subsequences += [[numbers[i] for i in solution_candidate]]
                solution_candidate.append(-1)
                break
            el = next_element(solution_candidate, numbers)
        if el is None:
            solution_candidate = solution_candidate[:-1]

    return subsequences


if __name__ == "__main__":
    solutions = strictly_increasing_subsequences_recursive([1, 2, 3, 43, 5, 3], [], -1)
    solutions2 = strictly_increasing_subsequences_iterative([1, 2, 3, 43, 5, 3])
    print(solutions)
    print(solutions2)
    solutions.sort()
    solutions2.sort()
    assert solutions == solutions2
