from ui import run_menu
from functions import create_flight

if __name__ == "__main__":
    flights = {
        "083342": create_flight("083342", 45, "Cluj-Napoca", "London"),
        "083345": create_flight("083345", 10, "Bucuresti", "London"),
        "083347": create_flight("083347", 70, "Cluj-Napoca", "Cairo"),
        "083349": create_flight("083345", 50, "Iasi", "London"),
        "083313": create_flight("083347", 48, "Cluj-Napoca", "Viena"),
    }
    run_menu(flights)
