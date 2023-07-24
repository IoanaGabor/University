"""
author: Gabor Ioana, 913

The 2x2 matrices A from the statement are defined as
d1 0
0 d2
(diagonal matrix)

And only the values d1 and d2 are passed as parameters to the functions.

"""

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import FancyArrowPatch


def f(x, y, d1, d2):
    return d1 * x ** 2 + d2 * y ** 2


def grad_f(x, y, d1, d2):
    return [2 * x * d1, 2 * y * d2]


def plot_contour_lines_and_gradient(d1, d2):
    xlist = np.linspace(-15.0, 15.0, 100)
    ylist = np.linspace(-15.0, 15.0, 100)
    fig, ax = plt.subplots()
    ax.set_title("Plot for d1 = {0} and d2 = {1}".format(d1, d2))
    X, Y = np.meshgrid(xlist, ylist)
    Z = f(X, Y, d1, d2)
    # levels
    nlevels = 3
    levels = np.zeros(nlevels)
    levels[0] = f(1, 1, d1, d2)
    levels[1] = f(5, 7, d1, d2)
    levels[2] = f(10, 5, d1, d2)
    levels = np.sort(levels)
    print(levels)
    # plot the contour lines
    contours = plt.contour(X, Y, Z, levels, colors='black')
    plt.clabel(contours, inline=True, fontsize=8)

    # gradient
    points = [[1, 1], [5, 7], [10, 3]]
    for point in points:
        x = point[0]
        y = point[1]
        [gx, gy] = grad_f(x, y, d1, d2)
        arrow1 = FancyArrowPatch((x, y), (x + gx, y + gy),
                                 arrowstyle='simple', color='b', mutation_scale=10)
        ax.add_patch(arrow1)

    plt.show()


if __name__ == '__main__':
    # minimum
    plot_contour_lines_and_gradient(0.5, 0.5)
    plot_contour_lines_and_gradient(0.5, 1)
    # maximum
    plot_contour_lines_and_gradient(-1.5, -1.5)
    plot_contour_lines_and_gradient(-0.5, -1)
    # saddle
    plot_contour_lines_and_gradient(-0.5, 0.5)
    plot_contour_lines_and_gradient(-0.7, 0.5)
