from functions import *


def test_add_flight_good():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Cluj-Napoca", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    add_flight("083349", 45, "Cluj-Napoca", "London", flights)
    expected_flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Cluj-Napoca", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
        "083349": create_flight("083349", 45, "Cluj-Napoca", "London")
    }
    assert expected_flights == flights


def test_add_flight_duplicate_code():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Cluj-Napoca", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    try:
        add_flight("083349", 45, "Cluj-Napoca", "London", flights)
        assert False
    except Exception as e:
        assert True


def test_update_delay():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    expected_flights = {
        "083342": create_flight("083342", 60, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 60, "Cluj-Napoca", "London"),
    }
    update_delay("Cluj-Napoca", 15, flights)
    assert flights == expected_flights


def test_update_delay_invalid_delay():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    try:
        update_delay("Cluj-Napoca", 200, flights)
        assert False
    except Exception as e:
        assert True


def test_delete_flight_that_does_not_exist():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    try:
        delete_flight("asadf", flights)
        assert False
    except Exception as e:
        assert True


def test_delete_flight_good():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    delete_flight("083347", flights)
    expected_flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
    }
    assert expected_flights == flights


def test_select_flights_with_departure_city():
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 45, "Bucuresti", "London"),
        "083347": create_flight("083347", 45, "Cluj-Napoca", "London"),
    }
    actual_flights = list_given_departure_city("Cluj-Napoca", flights)
    expected_flights = [
        create_flight("083342", 45, "Cluj-Napoca", "London"),
        create_flight("083347", 45, "Cluj-Napoca", "London"),
    ]
    assert actual_flights == expected_flights


def run_tests():
    test_add_flight_good()
    test_add_flight_duplicate_code()
    test_update_delay()
    test_update_delay_invalid_delay()
    test_delete_flight_good()
    test_delete_flight_that_does_not_exist()
    test_select_flights_with_departure_city()


if __name__ == "__main__":
    run_tests()
