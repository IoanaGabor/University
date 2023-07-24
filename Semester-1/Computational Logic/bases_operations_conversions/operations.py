"""
@author: Ioana Gabor
"""

from number import Number


class Operations:
    @staticmethod
    def add(first_number, second_number):
        """Adds two Numbers or raises ValueError if the Numbers have different bases

        :param first_number: Number
        :param second_number: Number
        :return: Number
        """
        if first_number.get_base() != second_number.get_base():
            raise ValueError("The numbers have different bases!\n")
        digits1 = first_number.get_digits()
        digits2 = second_number.get_digits()
        base = first_number.get_base()
        result = []
        carry = 0
        digits1.reverse()
        digits2.reverse()
        if len(digits1) < len(digits2):
            digits1 += [0 for _ in range(len(digits2) - len(digits1))]
        elif len(digits1) > len(digits2):
            digits2 += [0 for _ in range(len(digits1) - len(digits2))]

        for d in range(len(digits2)):
            sum = (digits2[d] + digits1[d] + carry)
            carry = sum // base
            result.append(sum % base)
        if carry:
            result.append(carry)
        result.reverse()
        return Number(result, base)

    @staticmethod
    def compare(first_number, second_number):
        """Compares two numbers

        :param first_number: Number
        :param second_number:Number
        :return: -1  if first < second, 0  if first == second, 1  if first > second
        """
        digits1 = first_number.get_digits()
        digits2 = second_number.get_digits()
        if len(digits1) < len(digits2):
            return -1
        if len(digits1) > len(digits2):
            return 1
        for d in range(len(digits1)):
            if digits1[d] < digits2[d]:
                return -1
            elif digits1[d] > digits2[d]:
                return 1
        return 0

    @staticmethod
    def subtract(first_number, second_number):
        """Subtracts two Numbers or raises ValueError if the Numbers have different bases or if the first one is smaller

        :param first_number: Number
        :param second_number: Number
        :return: Number
        """
        if first_number.get_base() != second_number.get_base():
            raise ValueError("The numbers have different bases!\n")
        if Operations.compare(first_number, second_number) < 0:
            raise ValueError("The first number can't be larger than the second number!\n")
        digits1 = first_number.get_digits()
        digits2 = second_number.get_digits()
        base = first_number.get_base()
        result = []
        borrow = 0
        digits1.reverse()
        digits2.reverse()
        if len(digits1) > len(digits2):
            digits2 += [0 for _ in range(len(digits1) - len(digits2))]

        for d in range(len(digits1)):
            if digits1[d] + borrow >= digits2[d]:
                current_digit = (digits1[d] + borrow - digits2[d]) % base
                borrow = 0
            else:
                current_digit = (digits1[d] + borrow + base - digits2[d]) % base
                borrow = -1
            result.append(current_digit)
        while len(result) > 1 and result[-1] == 0:
            result.pop(len(result) - 1)
        result.reverse()
        return Number(result, base)

    @staticmethod
    def multiply(first_number, second_number):
        """Multiplies two Numbers or raises ValueError if the Numbers have different bases or if the second one has more than one digit

        :param first_number: Number
        :param second_number: Number
        :return: Number
        """

        if first_number.get_base() != second_number.get_base():
            raise ValueError("The numbers have different bases!\n")
        digits1 = first_number.get_digits()
        digits2 = second_number.get_digits()
        base = first_number.get_base()
        if len(digits2) > 1:
            raise ValueError("The second number should have only one digit!\n")
        digit2 = digits2[0]
        digits1.reverse()
        result = []
        carry = 0
        for d in range(len(digits1)):
            prod = digits1[d] * digit2 + carry
            carry = prod // base
            result.append(prod % base)
        if carry:
            result.append(carry)
        while len(result) > 1 and result[-1] == 0:
            result = result[:-1]
        result.reverse()
        return Number(result, base)

    @staticmethod
    def divide(first_number, second_number):
        """Divides two Numbers or raises ValueError if the Numbers have different bases or if the second one has more than one digit
        or if the second one is 0.

        :param first_number: Number
        :param second_number: Number
        :return: Number
        """
        if first_number.get_base() != second_number.get_base():
            raise ValueError("The numbers have different bases!\n")
        if second_number.is_zero():
            raise ZeroDivisionError("Cannot divide by 0!")
        digits1 = first_number.get_digits()
        digits2 = second_number.get_digits()
        base = first_number.get_base()
        if len(digits2) > 1:
            raise ValueError("The second number should have only one digit!\n")
        digit2 = digits2[0]
        result = []
        remainder = 0
        for d in range(len(digits1)):
            current_digit = (remainder * base + digits1[d]) // digit2
            remainder = (remainder * base + digits1[d]) % digit2
            result.append(current_digit)
        while result[0] == 0 and len(result) > 1:
            result.pop(0)
        return Number(result, base), Number([remainder], base)

#
# if __name__ == "__main__":
#     print(Operations.divide(Number.get_number_from_string_representation("123", 4),
#                             Number.get_number_from_string_representation("3", 4))[0])
