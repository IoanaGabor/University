from src.repository import PlayersRepository
from src.services import PlayersService
from src.ui import ConsoleUI


def run():
    players_repo = PlayersRepository("data.csv")
    players_service = PlayersService(players_repo)
    console_ui = ConsoleUI(players_service)
    console_ui.run()


if __name__ == "__main__":
    run()
