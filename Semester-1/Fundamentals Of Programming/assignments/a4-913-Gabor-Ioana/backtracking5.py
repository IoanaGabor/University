def check_valid_solution(solution_candidate, k):
    """Checks if a solution candidate is a valid solution. A valid solution is a list of numbers which
    have the sum divisible by k.

    :param solution_candidate: list of integers
    :param k: integer
    :return: boolean (true if the solution candidate is a valid solution)
    """
    sum = 0
    for value in solution_candidate:
        sum += value
    return sum % k == 0


def generate_subsets_with_sum_divisible_by_k_recursive(numbers, k, solution_candidate, current_index):
    """Generates all the subsets which have the sum divisible by k, using recursive backtracking.
    :param current_index: integer
    :param solution_candidate: list of integers
    :param numbers: list of integers
    :param k: integer
    :return: list of lists of integers
    """

    if current_index == len(numbers):
        if check_valid_solution(solution_candidate, k):
            return [solution_candidate]
        return []

    subsets = []
    subsets += generate_subsets_with_sum_divisible_by_k_recursive(numbers, k,
                                                                  solution_candidate + [numbers[current_index]]
                                                                  , current_index + 1)
    subsets += generate_subsets_with_sum_divisible_by_k_recursive(numbers, k, solution_candidate,
                                                                  current_index + 1)
    return subsets


def generate_subsets_with_sum_divisible_by_k_iterative(numbers, k):
    """Generates all the subsets which have the sum divisible by k, by using iterative backtracking
    and by simulating a stack.

    :param numbers: list of integers
    :param k: integer
    :return: list of lists of integers
    """
    subsets = []
    current_index = 0
    solution_candidate = []
    state_of_subset = [0] * len(numbers)
    while current_index >= 0:
        if current_index < len(numbers):
            if state_of_subset[current_index] < 2:
                if state_of_subset[current_index] == 1:
                    solution_candidate += [numbers[current_index]]
                state_of_subset[current_index] += 1
                current_index += 1
            else:
                solution_candidate = solution_candidate[:-1]
                state_of_subset[current_index] = 0
                current_index -= 1
        else:
            if check_valid_solution(solution_candidate, k):
                subsets += [solution_candidate.copy()]
            current_index -= 1

    return subsets


def generate_subsets_with_sum_divisible_by_k_iterative_v2(numbers, k):
    subsets = [[]]
    for number in numbers:
        added_subsets = []
        for subset in subsets:
            added_subsets += [subset + [number]]
        subsets += added_subsets
    return [subset for subset in subsets if check_valid_solution(subset, k)]


if __name__ == "__main__":
    solutions = generate_subsets_with_sum_divisible_by_k_recursive([1, 2, 3, 43, 5, 3], 2, [], 0)
    solutions2 = generate_subsets_with_sum_divisible_by_k_iterative([1, 2, 3, 43, 5, 3], 2)
    solutions3 = generate_subsets_with_sum_divisible_by_k_iterative_v2([1, 2, 3, 43, 5, 3], 2)
    print(solutions)
    print(solutions2)
    print(solutions3)
    solutions.sort()
    solutions3.sort()
    solutions2.sort()
    assert solutions == solutions3
    assert solutions == solutions2
