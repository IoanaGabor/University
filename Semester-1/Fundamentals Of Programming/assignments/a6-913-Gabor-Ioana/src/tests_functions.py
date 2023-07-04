from functions import *


def test_modulus():
    nb = create_complex_number((3, 4))
    assert (5 == modulus(nb))


def test_parse_complex_number():
    assert (create_complex_number((2, 3)) == parse_complex_number("2+3i"))
    assert (create_complex_number((2, -3)) == parse_complex_number("2-3i"))
    assert (create_complex_number((-2, -3)) == parse_complex_number("-2-3i"))
    assert (create_complex_number((-2, 3)) == parse_complex_number("-2+3i"))
    try:
        parse_complex_number("-2+++3i")
        assert False
    except ValueError as ve:
        assert True


def test_add_number():
    nb = create_complex_number((3, 4))
    numbers = [create_complex_number((5, 6)), create_complex_number((4, 5))]
    history = []
    add_number_to_list(history, numbers, nb)
    expected_numbers = [create_complex_number((5, 6)), create_complex_number((4, 5)), create_complex_number((3, 4))]
    assert (expected_numbers == numbers)
    assert (history == [expected_numbers])


def test_insert_number():
    nb = create_complex_number((3, 4))
    numbers = [create_complex_number((5, 6)), create_complex_number((4, 5))]
    history = []
    insert_number_at_position(history, numbers, nb, 1)
    expected_numbers = [create_complex_number((5, 6)), create_complex_number((3, 4)), create_complex_number((4, 5))]
    assert (expected_numbers == numbers)
    assert (history == [expected_numbers])
    try:
        insert_number_at_position(history, numbers, nb, 100)
        assert False
    except Exception as ex:
        assert True


def test_select_real():
    numbers = [create_complex_number((5, 0)), create_complex_number((4, 5)), create_complex_number((3, 0))]
    expected_numbers = [create_complex_number((5, 0)), create_complex_number((3, 0))]
    actual_numbers = select_real_numbers(numbers)
    assert (expected_numbers == actual_numbers)


def test_select_real_from_range():
    numbers = [create_complex_number((5, 0)), create_complex_number((4, 5)), create_complex_number((3, 0)),
               create_complex_number((5, 2)), create_complex_number((7, 0)), create_complex_number((90, 0)),
               create_complex_number((11, 0)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((3, 0)), create_complex_number((7, 0)), create_complex_number((90, 0)),
                        create_complex_number((11, 0))]
    actual_numbers = select_real_numbers_from_range(numbers, 1, 8)
    assert (expected_numbers == actual_numbers)


def test_select_numbers_with_modulus_equal():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
                        create_complex_number((0, 5))]
    actual_numbers = select_numbers_with_modulus(numbers, 5, "=")
    assert (expected_numbers == actual_numbers)


def test_select_numbers_with_modulus_lower():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0))]
    actual_numbers = select_numbers_with_modulus(numbers, 5, "<")
    assert (expected_numbers == actual_numbers)


def test_select_numbers_with_modulus_greater():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((4, 9)), create_complex_number((3, 5))]
    actual_numbers = select_numbers_with_modulus(numbers, 5, ">")
    assert (expected_numbers == actual_numbers)


def test_keep_only_real_numbers():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [
        create_complex_number((2, 0)), create_complex_number((3, 0)), create_complex_number((5, 0))]
    keep_only_real_numbers([], numbers)
    assert (expected_numbers == numbers)


def test_keep_only_numbers_with_modulus_equal():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
                        create_complex_number((0, 5))]
    keep_only_numbers_with_modulus_constraint([], numbers, 5, "=")

    assert (expected_numbers == numbers)


def test_keep_only_numbers_with_modulus_lower():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0))]
    keep_only_numbers_with_modulus_constraint([], numbers, 5, "<")
    assert (expected_numbers == numbers)


def test_keep_only_numbers_with_modulus_greater():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((3, 4)),
               create_complex_number((0, 5)), create_complex_number((4, 9)), create_complex_number((3, 5))]
    expected_numbers = [
        create_complex_number((4, 9)), create_complex_number((3, 5))]
    keep_only_numbers_with_modulus_constraint([], numbers, 5, ">")
    assert (expected_numbers == numbers)


def test_replace_number():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((4, 2)),
               create_complex_number((0, 5)), create_complex_number((4, 2)), create_complex_number((3, 5))]
    old_number = create_complex_number((4, 2))
    new_number = create_complex_number((4, 13))
    expected_numbers = [create_complex_number((2, 0)), create_complex_number((4, 13)), create_complex_number((3, 0)),
                        create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((4, 13)),
                        create_complex_number((0, 5)), create_complex_number((4, 13)), create_complex_number((3, 5))]
    replace_old_number_with_new_number([], numbers, old_number, new_number)
    assert (expected_numbers == numbers)


def test_remove_position():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((4, 2)),
               create_complex_number((0, 5)), create_complex_number((4, 2)), create_complex_number((3, 5))]
    expected_numbers = [create_complex_number((2, 0)), create_complex_number((3, 0)),
                        create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((4, 2)),
                        create_complex_number((0, 5)), create_complex_number((4, 2)), create_complex_number((3, 5))]
    remove_position_from_list([], numbers, 1)
    assert (numbers == expected_numbers)


def test_remove_range():
    numbers = [create_complex_number((2, 0)), create_complex_number((4, 2)), create_complex_number((3, 0)),
               create_complex_number((5, 0)), create_complex_number((4, 3)), create_complex_number((4, 2)),
               create_complex_number((0, 5)), create_complex_number((4, 2)), create_complex_number((3, 5))]

    expected_numbers = [create_complex_number((2, 0)), create_complex_number((4, 3)), create_complex_number((4, 2)),
                        create_complex_number((0, 5)), create_complex_number((4, 2)), create_complex_number((3, 5))]
    remove_range_of_numbers_from_list([], numbers, 1, 4)
    assert (numbers == expected_numbers)
    try:
        remove_range_of_numbers_from_list([], numbers, 9, 3)
        assert False
    except Exception as ex:
        assert True
    try:
        remove_range_of_numbers_from_list([], numbers, 30, 45)
        assert False
    except Exception as ex:
        assert True

def run_tests():
    test_parse_complex_number()
    test_modulus()
    test_add_number()
    test_insert_number()
    test_select_real_from_range()
    test_select_numbers_with_modulus_equal()
    test_select_numbers_with_modulus_lower()
    test_select_numbers_with_modulus_greater()
    test_keep_only_real_numbers()
    test_keep_only_numbers_with_modulus_equal()
    test_keep_only_numbers_with_modulus_greater()
    test_keep_only_numbers_with_modulus_lower()
    test_replace_number()
    test_remove_position()
    test_remove_range()


if __name__ == "__main__":
    run_tests()
