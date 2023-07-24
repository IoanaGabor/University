from unittest import TestCase

from conversions import Operations
from number import Number


class TestOperations(TestCase):
    def test_addition(self):
        first_number = Number.get_number_from_string_representation("1234", 7)
        second_number = Number.get_number_from_string_representation("4326", 7)
        expected_number = Number.get_number_from_string_representation("5563", 7)
        actual_number = Operations.add(first_number, second_number)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_subtraction(self):
        first_number = Number.get_number_from_string_representation("A43F", 16)
        second_number = Number.get_number_from_string_representation("4326", 16)
        expected_number = Number.get_number_from_string_representation("6119", 16)
        actual_number = Operations.subtract(first_number, second_number)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_multiplication(self):
        first_number = Number.get_number_from_string_representation("543A", 11)
        second_number = Number.get_number_from_string_representation("7", 11)
        expected_number = Number.get_number_from_string_representation("34854", 11)
        actual_number = Operations.multiply(first_number, second_number)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_division(self):
        first_number = Number.get_number_from_string_representation("5235BC", 13)
        second_number = Number.get_number_from_string_representation("9", 13)
        expected_number = Number.get_number_from_string_representation("76214", 13)
        expected_remainder = Number.get_number_from_string_representation("2", 13)
        actual_number, actual_remainder = Operations.divide(first_number, second_number)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())
        self.assertEqual(expected_remainder.get_digits(), actual_remainder.get_digits())
        self.assertEqual(expected_remainder.get_base(), actual_remainder.get_base())

    def test_multiplication_invalid_second_number(self):
        first_number = Number.get_number_from_string_representation("543A", 11)
        second_number = Number.get_number_from_string_representation("78", 11)
        self.assertRaises(ValueError, Operations.multiply, first_number, second_number)

    def test_division_invalid_second_number(self):
        first_number = Number.get_number_from_string_representation("543A", 11)
        second_number = Number.get_number_from_string_representation("78", 11)
        self.assertRaises(ValueError, Operations.divide, first_number, second_number)

    def test_division_by_0(self):
        first_number = Number.get_number_from_string_representation("5235BC", 13)
        second_number = Number.get_number_from_string_representation("0", 13)
        self.assertRaises(ZeroDivisionError, Operations.divide,first_number, second_number)
