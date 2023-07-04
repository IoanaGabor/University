import functions


def print_menu():
    print("1. Add a flight\n"
          "2. Delete a flight\n"
          "3. Show all flights with a given departure city\n"
          "4. Update the delay of all flights with a certain departure city\n")


def add_flight(flights):
    code = input("Enter the code:")
    try:
        duration = int(input("Enter the duration"))
    except ValueError:
        print("Duration should be an integer")
        return
    departure_city = input("Enter the departure city:")
    destination_city = input("Enter the destination city:")
    try:
        functions.add_flight(code, duration, departure_city, destination_city, flights)
    except Exception as e:
        print(e)


def delete_flight(flights):
    code = input("Enter the code:")
    try:
        functions.delete_flight(code, flights)
    except Exception as e:
        print(e)


def print_flights(flights):
    if len(flights) == 0:
        print("No flights")
    else:
        for fli in flights:
            print("The code is {0}, the dureation is {1}, the departure is {2}, the destionation is {3}".format(
                functions.get_code(fli),
                functions.get_duration(fli),
                functions.get_departure_city(fli),
                functions.get_destination_city(fli),
            ))


def show_all_flights_with_departure_city(flights):
    departure_city = input("Enter the departure city:")
    found_flights = functions.list_given_departure_city(departure_city, flights)
    print_flights(found_flights)


def delay_flights(flights):
    departure_city = input("Enter the departure city:")
    try:
        delay = int(input("Enter the delay:\n"))
    except ValueError:
        print("Delay should be an integer!\n")
        return
    try:
        functions.update_delay(departure_city, delay, flights)
    except Exception as e:
        print(e)


def run_menu(flights):
    commands = {
        "1": add_flight,
        "2": delete_flight,
        "3": show_all_flights_with_departure_city,
        "4": delay_flights
    }
    while True:
        print_menu()
        cmd = input("Please enter a command")
        if cmd == "0":
            return
        if cmd not in commands.keys():
            print("Invalid command\n")
        else:
            commands[cmd](flights)
