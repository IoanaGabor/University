def snake_sequences_dynamic_programming(matrix):
    """Given a matrix, computes the maximum length of a snake sequence and its list of coordinates,
     using dynamic programming.

    :param matrix: list of lists of integers
    :return: tuple (integer, list of tuples of integers) - the maximum length of the sequence and its coordinates
    """
    n = len(matrix)
    dp_matrix = [[(1, (-1, -1)) for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i - 1 >= 0 and matrix[i - 1][j] + 1 == matrix[i][j]:
                dp_matrix[i][j] = max(dp_matrix[i][j][0], dp_matrix[i - 1][j][0] + 1), (i - 1, j)
            if j - 1 >= 0 and matrix[i][j - 1] + 1 == matrix[i][j]:
                dp_matrix[i][j] = max(dp_matrix[i][j][0], dp_matrix[i][j - 1][0] + 1), (i, j - 1)
    sol = 1, (-1, -1)
    for i in range(n):
        for j in range(n):
            sol = max(sol, (dp_matrix[i][j][0], (i, j)))
    print(*dp_matrix, sep="\n")
    coord = sol[1]
    path = []
    while coord != (-1, -1):
        path = path + [coord]
        coord = dp_matrix[coord[0]][coord[1]][1]
    path.reverse()
    return sol[0], path


def depth_first_search(matrix, x, y):
    """Given a matrix and the starting coordinates, computes the maximum length of a snake
    sequence and its list of coordinates, using a naive implementation
    that searches through the entire solution space.

    :param x: integer - the starting row coordinate
    :param y: integer - the starting column coordinate
    :param matrix: list of lists of integers
    :return: tuple (integer, list of tuples of integers) - the maximum length of the sequence and its coordinates
    """
    if x + 1 < len(matrix) and matrix[x + 1][y] == matrix[x][y] + 1:
        partial_solution = depth_first_search(matrix, x + 1, y)
        return partial_solution[0] + 1, [(x, y)] + partial_solution[1]
    if y + 1 < len(matrix) and matrix[x][y + 1] == matrix[x][y] + 1:
        partial_solution = depth_first_search(matrix, x, y + 1)
        return partial_solution[0] + 1, [(x, y)] + partial_solution[1]
    return 1, [(x, y)]


def snake_sequence_naive(matrix):
    """Given a matrix, computes the maximum length of a snake sequence and its list of coordinates,
    using a naive implementation that searches through the entire solution space.

    :param matrix: list of lists of integers
    :return: tuple (integer, list of tuples of integers) - the maximum length of the sequence and its coordinates
    """

    n = len(matrix)
    sol = (1, [0, 0])
    for i in range(n):
        for j in range(n):
            partial_solution = depth_first_search(matrix, i, j)
            sol = max(sol, partial_solution)
    return sol


if __name__ == "__main__":
    test_matrix = [[1, 2, 3], [8, 6, 4], [7, 2, 5]]
    solution = snake_sequences_dynamic_programming(test_matrix)
    solution2 = snake_sequence_naive(test_matrix)
    print(solution)
    print(solution2)
    assert solution == solution2
