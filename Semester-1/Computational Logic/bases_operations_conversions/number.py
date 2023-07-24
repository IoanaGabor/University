"""
@author: Ioana Gabor
"""


from copy import deepcopy


class Number:
    def __init__(self, digits, base):
        self.__digits = digits
        self.__base = base
        self.validate_digits()

    def is_zero(self):
        if len(self.__digits) == 1 and self.__digits[0] == 0:
            return True
        return False

    def validate_digits(self):
        for d in self.__digits:
            if d >= self.__base or d < 0:
                raise ValueError("The digits of the number are not in base " + str(self.__base))

    def __eq__(self, other):
        print("here")
        if self.__base != other.__base:
            return False
        if len(self.__digits) != len(other.__digits):
            return False
        for d in range(len(self.__digits)):
            if self.__digits[d] != other.__digits[d]:
                return False
        return True

    def __str__(self):
        string_representation = ""
        value = {10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'}
        for d in self.__digits:
            if d < 10:
                string_representation += str(d)
            else:
                string_representation += value[d]
        return string_representation

    @classmethod
    def get_number_from_string_representation(cls, string_representation, base):
        if len(string_representation) == 0:
            raise ValueError("The length of the string can't be 0.")
        digits = []
        string_representation = string_representation.upper()
        for ch in string_representation:
            if ch in ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']:
                if int(ch) >= base:
                    raise ValueError(
                        "The number " + string_representation + " contains digits that do not exist in base {0}".format(
                            base))
                digits.append(int(ch))
            elif ch in ['A', 'B', 'C', 'D', 'E', 'F']:
                digits.append(ord(ch) - ord('A') + 10)
                if digits[-1] >= base:
                    raise ValueError(
                        "The number " + string_representation + " contains digits that do not exist in base {0}".format(
                            base))
            else:
                raise ValueError(
                    "The number " + string_representation + " contains digits that do not exist in base {0}".format(
                        base))
        return cls(digits, base)

    def get_digits(self):
        return deepcopy(self.__digits)

    def get_base(self):
        return self.__base
