"""
author: Gabor Ioana, 913

What do you notice as b gets smaller?
As b gets, smaller, the algorithm converges slower to (0,0) (starting from the same initial point)



"""

import matplotlib.pyplot as plt
import numpy as np


def f(x, y, b):
    return 1 / 2 * (x ** 2 + b * (y ** 2))


def step(x, y, b):
    """The step chosen for the gradient descent algorithm (exact line search), when the current coordinates are (x,y)
    """
    return (x ** 2 + (b ** 2) * (y ** 2)) / (x ** 2 + (b ** 3) * (y ** 2))


def next_iteration(x, y, s, b):
    """The coordinates obtained after this iteration.
    """
    return [(1 - s) * x, (1 - b * s) * y]


def gradient(x, y, b):
    """The gradient of the function f
    """
    return [x, b * y]


def gradient_descent(b):
    """Performs 15 iterations of the gradient descent algorithm for the function f
    (which depends on the value of b) and plots contour levels.
    """
    iterations = 15
    x = np.zeros(iterations + 2)
    y = np.zeros(iterations + 2)

    # initial value
    x[0] = 1
    y[0] = 6
    # gradient descent
    k = 0
    print("Gradient descent for b = {0}".format(b))
    print("Starting position {0}, {1}, function value {2}".format(x[k], y[k], f(x[k], y[k], b)))

    while k < iterations and gradient(x[k], y[k], b) != [0, 0]:
        # if the gradient is 0 or all the iterations are complete, we stop
        s = step(x[k], y[k], b)
        [x[k + 1], y[k + 1]] = next_iteration(x[k], y[k], s, b)
        k += 1
        print("After iteration {0}, the position is {1}, {2}, the function is {3} and the gradient is {4}"
              .format(k, x[k], y[k], f(x[k], y[k], b), gradient(x[k], y[k], b)))
    if k < iterations:
        iterations = k + 1

    # create meshgrid for contour plot
    xlist = np.linspace(-5.0, 5.0, 100)
    ylist = np.linspace(-5.0, 5.0, 100)
    X, Y = np.meshgrid(xlist, ylist)
    Z = f(X, Y, b)

    # define the contour levels
    nlevels = min(5, iterations)
    levels = np.zeros(nlevels)
    for k in range(nlevels):
        levels[k] = f(x[k], y[k], b)
    levels = np.sort(levels)

    # plot the contour lines
    contours = plt.contour(X, Y, Z, levels, colors='black')
    plt.clabel(contours, inline=True, fontsize=8)

    # plot the gradient descent iterations
    plt.plot(x[:iterations], y[:iterations], 'r--o')
    plt.title("Gradient descent for b = {0}".format(b))
    plt.show()


if __name__ == '__main__':
    gradient_descent(1)
    gradient_descent(1 / 2)
    gradient_descent(1 / 5)
    gradient_descent(1 / 10)
