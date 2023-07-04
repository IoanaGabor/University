from math import sqrt


def check_if_prime(n):
    """
    Checks if a natural numer is prime. Returns True or False, if it's a prime or not.

    :param n: natural number
    :return: boolean
    """
    if n == 2:
        return True

    if n < 2 or n % 2 == 0:
        return False

    for fact in range(3, int(sqrt(n)) + 1, 2):
        if n % fact == 0:
            return False

    return True


def next_smaller_prime(n):
    """
    Generates the largest prime number smaller than a given natural number n.
    If such a number does not exist, "does not exist" is returned.

    :param n: natural number
    :return: natural number or string ("does not exist")
    """
    if n < 3:
        return "does not exist"

    n -= 1
    while not check_if_prime(n):
        n -= 1

    return n


if __name__ == "__main__":
    number = int(input("Enter a number:\n"))
    print("The next smaller prime is: " + str(next_smaller_prime(number)))
