from unittest import TestCase

from number import Number


class TestNumber(TestCase):
    def test_validate_digits_ok(self):
        Number([3, 4, 3], 5)

    def test_validate_digits_raises_error(self):
        self.assertRaises(ValueError, Number, [1, 3, -3, 14], 5)

    def test_get_number_from_string_rep_ok(self):
        self.assertEqual(Number.get_number_from_string_representation("22A3", 13), Number([2, 2, 10, 3], 13))

    def test_get_number_from_string_rep_error(self):
        self.assertRaises(ValueError, Number.get_number_from_string_representation,"22A", 5)

    def test_is_zero_true(self):
        self.assertTrue(Number.is_zero(Number([0], 15)))

    def test_is_zero_false(self):
        self.assertFalse(Number.is_zero(Number([10], 15)))