from unittest import TestCase

from conversions import Conversions
from number import Number


class TestConversions(TestCase):
    def test_successive_divisions(self):
        initial_number = Number.get_number_from_string_representation("1234", 7)
        target_base = 4
        expected_number = Number.get_number_from_string_representation("13102", 4)
        actual_number = Conversions.successive_divisions(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_successive_divisions_invalid_parameters(self):
        initial_number = Number.get_number_from_string_representation("1234", 7)
        target_base = 9
        self.assertRaises(ValueError, Conversions.successive_divisions, initial_number, target_base)

    def test_substitution_method(self):
        initial_number = Number.get_number_from_string_representation("1234", 6)
        target_base = 16
        expected_number = Number.get_number_from_string_representation("136", 16)
        actual_number = Conversions.substitution_method(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_substitution_method_invalid_parameters(self):
        initial_number = Number.get_number_from_string_representation("1234", 9)
        target_base = 5
        self.assertRaises(ValueError, Conversions.substitution_method, initial_number, target_base)

    def test_using_base_10_as_intermediary1(self):
        initial_number = Number.get_number_from_string_representation("1234", 7)
        target_base = 4
        expected_number = Number.get_number_from_string_representation("13102", 4)
        actual_number = Conversions.using_base_10_as_intermediary_base(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_using_base_10_as_intermediary2(self):
        initial_number = Number.get_number_from_string_representation("13102", 4)
        expected_number = Number.get_number_from_string_representation("1234", 7)
        target_base = 7

        actual_number = Conversions.using_base_10_as_intermediary_base(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_rapid_conversions1(self):
        initial_number = Number.get_number_from_string_representation("1234", 8)
        target_base = 16
        expected_number = Number.get_number_from_string_representation("29C", 16)
        actual_number = Conversions.rapid_conversions(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_rapid_conversions2(self):
        initial_number = Number.get_number_from_string_representation("1234", 16)
        target_base = 2
        expected_number = Number.get_number_from_string_representation("1001000110100", 2)
        actual_number = Conversions.rapid_conversions(initial_number, target_base)
        self.assertEqual(expected_number.get_digits(), actual_number.get_digits())
        self.assertEqual(expected_number.get_base(), actual_number.get_base())

    def test_rapid_conversions_invalid_parameters(self):
        initial_number = Number.get_number_from_string_representation("1234", 16)
        target_base = 3
        self.assertRaises(ValueError, Conversions.rapid_conversions, initial_number, target_base)
