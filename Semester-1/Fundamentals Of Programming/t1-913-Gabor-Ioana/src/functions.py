def create_flight(code, duration, departure_city, destination_city):
    return {
        "code": code,
        "duration": duration,
        "departure_city": departure_city,
        "destination_city": destination_city,
    }


def get_code(flight):
    return flight["code"]


def set_code(flight, new_code):
    flight["code"] = new_code


def get_duration(flight):
    return flight["duration"]


def set_duration(flight, new_duration):
    flight["duration"] = new_duration


def get_departure_city(flight):
    return flight["departure_city"]


def set_departure_city(flight, new_departure_city):
    flight["departure_city"] = new_departure_city


def get_destination_city(flight):
    return flight["destination_city"]


def set_destination_city(flight, new_destination_city):
    flight["destination_city"] = new_destination_city


def add_flight(code, duration, departure_city, destination_city, flights):
    """ Adds a flight to the map of flights, throws exceptions if the parameters of the flight are not valid or
    if a flight with the given code already exists

    :param code: string
    :param duration: integer
    :param departure_city: string
    :param destination_city: string
    :param flights: map of flights
    :return: -
    """
    if len(code) < 3:
        raise Exception("Code should have a length of minimum 3")
    if len(departure_city) < 3:
        raise Exception("Departure city should have a length of minimum 3")
    if len(destination_city) < 3:
        raise Exception("Destination city should have a length of minimum 3")
    if duration < 20:
        raise Exception("Duration can't be less than 20 minutes")
    new_flight = create_flight(code, duration, departure_city, destination_city)
    if find_flight_by_code(get_code(new_flight), flights) is not None:
        raise Exception("Flight with code {0} already exists".format(get_code(new_flight)))
    flights[get_code(new_flight)] = new_flight


def delete_flight(code, flights):
    """Deletes a flight with a given code from the map of flags. Throws an exception if the flight does not exist

    :param code: string
    :param flights: map of flights
    :return:
    """
    if find_flight_by_code(code, flights) is None:
        raise Exception("Flight with code {0} does not exist".format(code))
    del flights[code]


def find_flight_by_code(code, flights):
    """Given a code, finds and returns the corresponding flight, or None if it doesn't exist

    :param code: string
    :param flights: map of flights
    :return: flight (map) or None
    """
    if code in flights.keys():
        return flights[code]
    return None


def list_given_departure_city(departure_city, flights):
    """Returns a list of the flights with a given departure city, sorted increasing by the destination city.

    :param departure_city: string
    :param flights: map of flights (map of maps)
    :return:
    """
    result = []
    for flight in flights.values():
        if departure_city == get_departure_city(flight):
            result.append(flight)
    for i in range(len(result)):
        for j in range(i + 1, len(result)):
            if get_destination_city(result[i]) > get_destination_city(result[j]):
                result[i], result[j] = result[j], result[i]
    return result


def update_delay(departure_city, delay, flights):
    """Updates the duration of all flights with a given departure city, if the delay is in range [10,60],

    :param departure_city: string
    :param delay: integer
    :param flights: map of flights
    :return:
    """
    if delay >= 60 or delay < 10:
        raise Exception("The delay is not in the range [10,60]")
    for flight in flights.values():
        if departure_city == get_departure_city(flight):
            old_duration = get_duration(flight)
            set_duration(flight, old_duration + delay)
