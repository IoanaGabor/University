from mpmath import nsum, inf
import numpy as np
import matplotlib.pyplot as plt
import math


def show_numerically_convergence():
    n = 10
    while n < 100000:
        val = aproximate_the_alternating_harmonic_series(n)
        print("The sum of the first n=" + str(
            n) + " elements of the alternating harmonic series is {:.15f}, the absolute value of the"
                 " difference between this and  ln(2) is {:.15f}".format(
            val, (abs(val - math.log(2)).round(5))))
        n *= 10


def show_that_changing_order_changes_value():
    val = aproximate_the_alternating_harmonic_series(1000)
    print("The sum of the first 1000 elements of the original sequence is ", val)
    val = aproximate_the_alternating_harmonic_series(1000, 1, 2)
    print("The sum of the first 1000 elements of the reordered sequence (1 positive number followed by 2 "
          "negatives is ", val)
    val = aproximate_the_alternating_harmonic_series(1000, 2, 3)
    print("The sum of the first 1000 elements of the reordered sequence (2 positive numbers followed by 3 "
          "negatives is ", val)
    val = aproximate_the_alternating_harmonic_series(1000, 5, 2)
    print("The sum of the first 1000 elements of the reordered sequence (5 positive numbers followed by 2 "
          "negatives is ", val)
    plot_the_alternating_harmonic_series(1000, "The original order")
    plot_the_alternating_harmonic_series(1000, "1 positive and 2 negative", 1, 2)
    plot_the_alternating_harmonic_series(1000, "2 positive and 3 negative", 2, 3)
    plot_the_alternating_harmonic_series(1000, "5 positive and 2 negative", 5, 2)


def get_first_n_elements_of_sequence(p, q, n):
    sequence = []
    next_odd = 1
    next_even = 2
    for i in range(n):
        if i % (p + q) < p:
            sequence.append(1 / next_odd)
            next_odd += 2
        else:
            sequence.append(-1 / next_even)
            next_even += 2
    return sequence


def the_value_of_the_alternating_harmonic_series():
    """Displays the value of the alternating harmonic series, with the help of nsum from mpmath

    :return:
    """
    print("The value of the sum computed with nsum, from mpmath", nsum(lambda n: ((-1) ** (n + 1)) / n, [1, inf]))
    print("The value of ln(2)", math.log(2))


def aproximate_the_alternating_harmonic_series(n, a=1, b=1):
    """Computes the sum of the first n elements of the alternating harmonic series, with the option
    of reordering the elements, taking alternatively a positive elements and b negative elements

    :param n: integer
    :param a: integer
    :param b: integer
    :return: floating-point
    """
    y = get_first_n_elements_of_sequence(a, b, n)
    y = np.cumsum(y)
    return y[-1]


def plot_the_alternating_harmonic_series(n, custom_label, a=1, b=1):
    """Plots the alternating harmonic series up to a specified n, with the option
    of reordering the elements, taking alternatively a positive elements and b negative elements
    By default, a and b are both 1 (the series in original order)
    :param n:  integer
    :param a: integer
    :param b: integer
    :param custom_label: string
    :return:
    """
    y = get_first_n_elements_of_sequence(a, b, n)
    y = np.cumsum(y)
    x = np.arange(1, len(y) + 1)
    fig, ax = plt.subplots()
    ax.plot(x, y)
    ax.set_xlabel(custom_label)
    ax.hlines(math.log(2), xmin=x[0], xmax=x[-1], color="black")
    plt.show()


if __name__ == '__main__':
    the_value_of_the_alternating_harmonic_series()
    print("Show numerically convergence:")
    show_numerically_convergence()
    print("Show that changing order changes value:")
    show_that_changing_order_changes_value()
