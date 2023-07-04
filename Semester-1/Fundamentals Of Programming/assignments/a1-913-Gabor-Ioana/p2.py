def compute_product_of_proper_factors(n):
    """Computes the product of all the proper factors of a given natural number n.
    A proper factor is any positive number that divides n, except n.

    :param n: natural number
    :return: Product of proper factors (natural number)
    """

    product = 1
    for fact in range(2, n):
        if n % fact == 0:
            product *= fact

    return product


if __name__ == "__main__":
    number = int(input("Enter a number:\n"))
    print("The product of proper factors is: " + str(compute_product_of_proper_factors(number)))
