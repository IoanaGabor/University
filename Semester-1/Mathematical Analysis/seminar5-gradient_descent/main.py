def f(x):
    """x^2 - 4x + 4, a convex function with a global minimum at 2
    """
    return (x ** 2) - 4 * x + 4


def g(x):
    """x^4 - 30x^3 + 308x^2 - 1266x + 1755, a non-convex function, with a local minimum at x=3.8516
    and a global minimum at x=11.507
    """
    return (x ** 4) - 30 * (x ** 3) + 308 * (x ** 2) - 1266 * x + 1755


def diff_f(x):
    return 2 * x - 4


def diff_g(x):
    return 4 * (x ** 3) - 90 * (x ** 2) + 616 * x - 1266


def gradient_descent(starting_point, eta, function, differential_function, max_iterations=100, step=5):
    print("The value of x1 is {0}, eta is {1}, the function is {2}".format(starting_point, eta, function.__doc__))
    x = [starting_point]
    for i in range(max_iterations):
        x.append(x[-1] - eta * differential_function(x[-1]))
        if (i + 1) % step == 0:
            print("After iteration {0}, x{1} ={2}".format(i + 1, i+2, x[-1]))
        if differential_function(x[-2]) == 0:
            print("The algorithm converges to {0} after {1} iterations".format(x[-1], i+1))
            break

    return x


if __name__ == '__main__':
    print("a) the algorithm converges to the global minimum of the convex function")
    gradient_descent(10, 0.35, f, diff_f, 50, 2)
    print("b) by increasing eta, the algorithm can converge faster")
    gradient_descent(10, 0.45, f, diff_f, 50, 1)
    print("c) taking eta too large can lead to divergence")
    gradient_descent(10, 2, f, diff_f, 100, 10)
    print("d) for a nonconvex function, the algorithm can get stuck at a local minimum")
    gradient_descent(2, 0.0004,g, diff_g, 100, 10)
    print("starting from a different point, we get to the global minimum")
    gradient_descent(9, 0.0004, g, diff_g, 100, 10)
