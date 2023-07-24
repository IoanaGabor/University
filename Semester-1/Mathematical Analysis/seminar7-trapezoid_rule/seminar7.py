"""
@author: ioana gabor
"""
from math import e, pi


def function(x):
    return e ** (- (x ** 2))


def trapezium_rule(a, b, func, n=10000):
    """Approximates the integral from a to b of a given function, with the trapezium rule.

    :param a: integer
    :param b: integer
    :param func: function
    :param n: integer, 10000 by default
    :return:
    """
    delta = (b - a) / n
    sum = 0.5 * delta * (func(b) - func(a))
    for i in range(n):
        sum += delta * func(a + (i + 1) * delta)
    return sum


def approximate():
    values = [10, 100, 200, 500]
    for val in values:
        app = trapezium_rule(-val, val, function)
        print("For a = {0}, the approximation with trapezoid rule is {1}".format(val, app))
        print("sqrt(pi) is {0}".format(pi ** (1 / 2)))
        print("the difference is {0}".format(abs(app - (pi ** (1 / 2)))))


if __name__ == '__main__':
    approximate()
