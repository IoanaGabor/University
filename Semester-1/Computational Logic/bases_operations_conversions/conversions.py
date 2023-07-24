"""
@author: Ioana Gabor
"""

from math import log2

from number import Number
from operations import Operations


class Conversions:
    @staticmethod
    def successive_divisions(number, target_base):
        """Converts a number to target_base using successive divisions, throws ValueError if start_base < target_base

        :param number: Number
        :param target_base: integer
        :return:
        """
        start_base = number.get_base()
        if start_base <= target_base:
            raise ValueError(
                "The start base should be larger than the target base, in the case of successive divisions")
        rem = []
        quotient, remainder = Operations.divide(number, Number([target_base], start_base))
        rem += remainder.get_digits()
        while not quotient.is_zero():
            quotient, remainder = Operations.divide(quotient, Number([target_base], start_base))
            rem += remainder.get_digits()

        rem.reverse()
        return Number(rem, target_base)

    @staticmethod
    def substitution_method(number, target_base):
        """Converts a number to target_base using the substitution method, throws ValueError if start_base > target_base

        :param number: Number
        :param target_base: integer
        :return:
        """
        start_base = number.get_base()
        if start_base >= target_base:
            raise ValueError(
                "The start base should be smaller than the target base, in the case of the substitution method")
        prod = []
        digits = number.get_digits()
        digits.reverse()
        power = Number([1], target_base)
        for d in digits:
            prod.append(Operations.multiply(power, Number([d], target_base)))
            power = Operations.multiply(power, Number([start_base], target_base))
        result = Number([0], target_base)
        for p in prod:
            result = Operations.add(result, p)
        return result

    @staticmethod
    def convert_from_base_10(number, target_base):
        string_number = str(number)
        integer_number = int(string_number)
        rem = []
        quotient, remainder = integer_number // target_base, integer_number % target_base
        rem.append(remainder)
        while quotient != 0:
            quotient, remainder = quotient // target_base, quotient % target_base
            rem.append(remainder)
        rem.reverse()
        return Number(rem, target_base)

    @staticmethod
    def convert_to_base_10(number):
        result = 0
        digits = number.get_digits()
        digits.reverse()
        start_base = number.get_base()
        prod = 1
        for d in digits:
            result += d * prod
            prod *= start_base
        string_result = str(result)
        return Number.get_number_from_string_representation(string_result, 10)

    @staticmethod
    def using_base_10_as_intermediary_base(number, target_base):
        """Converts a number to target_base using base 10 as intermediary base

        :param number: Number
        :param target_base: integer
        :return:
        """
        return Conversions.convert_from_base_10(Conversions.convert_to_base_10(number), target_base)

    @staticmethod
    def convert_digit_to_binary_list(digit, size):
        binary_list = []
        for i in range(size):
            binary_list.append(digit % 2)
            digit //= 2
        binary_list.reverse()
        return binary_list

    @staticmethod
    def convert_binary_list_to_digit(binary_list):
        digit = 0
        binary_list.reverse()
        power = 1
        for b in binary_list:
            digit += b * power
            power *= 2
        return digit

    @staticmethod
    def rapid_conversions(number, target_base):
        """Converts a number to target_base using rapid conversions. Throws ValueError if the start base and the target base are not both from
        the set {2,4,8, 16}

        :param number: Number
        :param target_base: integer
        :return:
        """
        start_base = number.get_base()
        if start_base not in [2, 4, 8, 16] or target_base not in [2, 4, 8, 16]:
            raise ValueError(
                "For rapid conversions the start base and the target base should both be from the set {2,4,8,16}")
        if start_base == 2:
            all_digits = number.get_digits()
            length_group = int(log2(target_base))
            result_digits = []
            all_digits.reverse()
            size = len(all_digits)
            if size % length_group != 0:
                all_digits += [0 for _ in range(size % length_group)]
            for d in range(len(all_digits) // length_group):
                binary_sublist = all_digits[d * length_group:(d + 1) * length_group]
                binary_sublist.reverse()
                result_digits.append(Conversions.convert_binary_list_to_digit(binary_sublist))
            result_digits.reverse()
            return Number(result_digits, target_base)
        elif target_base == 2:
            all_digits = number.get_digits()
            result_digits = []
            length_group = int(log2(start_base))
            for d in all_digits:
                result_digits += Conversions.convert_digit_to_binary_list(d, length_group)
            while len(result_digits) > 0 and result_digits[0] == 0:
                result_digits.pop(0)
            return Number(result_digits, target_base)
        else:
            return Conversions.rapid_conversions(Conversions.rapid_conversions(number, 2), target_base)

