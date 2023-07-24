"""
@author : Gabor Ioana
"""

from math import sin, cos


def f(x):
    return sin(x)


def f_diff(x):
    return cos(x)


def first_order_approximation():
    print("First order aproximation")
    x = 0.7
    h_list = [0.01, 0.008, 0.005, 0.003]
    for h in h_list:
        print("f diff for h= {0}is {1}".format(h, f_diff(x)))
        err = f_diff(x) - ((f(x + h) - f(x)) / h)
        print("error with h = {0} is {1}".format(h, err))
        print("Proportion err/h is {0}".format(err / h))
        print("\n")


def second_order_approximation():
    print("Second order aproximation")
    x = 0.7
    h_list = [0.01, 0.008, 0.005, 0.003]
    for h in h_list:
        print("f diff for h= {0}is {1}".format(h, f_diff(x)))
        err = f_diff(x) - ((f(x + h) - f(x - h)) / (2 * h))
        print("error with h = {0} is {1}".format(h, err))
        print("Proportion err/h^2 is {0}".format(err / (h ** 2)))
        print("\n")


if __name__ == '__main__':
    first_order_approximation()
    second_order_approximation()
