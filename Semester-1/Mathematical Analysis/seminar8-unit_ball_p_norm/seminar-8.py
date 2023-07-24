"""
@author: ioana gabor
"""
import matplotlib.pyplot as plt
from numpy import random


def get_p_norm(number, p):
    """Computes the p-norm of a real number with 2 dimensions

    :param number: tuple of 2 real numbers
    :param p:rational number
    :return: rational number
    """
    return (abs(number[0]) ** p + abs(number[1]) ** p) ** (1 / p)


def plotUnitCircle(p, subplot, title):
    """Plots the unit ball for the p-norm, with a given p

    :param p: rational number
    :param subplot:subplot
    :param title: string (title for the subplot)
    :return:
    """
    for i in range(5000):
        x = (random.rand() * 2 - 1, random.rand() * 2 - 1)
        if get_p_norm(x, p) <= 1:
            subplot.plot(x[0], x[1], "b.")
    subplot.axis([-2, 2, -2, 2])
    subplot.set_title(title)


def plot_all_4_subplots():
    fig, subplots = plt.subplots(2, 2)
    plotUnitCircle(1.25, subplots[0, 0], "p = 1.25")
    plotUnitCircle(1.5, subplots[0, 1], "p = 1.5")
    plotUnitCircle(3, subplots[1, 0], "p = 3")
    plotUnitCircle(8, subplots[1, 1], "p = 8")
    plt.show()


if __name__ == '__main__':
    plot_all_4_subplots()
