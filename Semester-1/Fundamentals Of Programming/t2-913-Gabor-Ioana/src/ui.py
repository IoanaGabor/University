from src.services import PlayersService


class ConsoleUI:
    def __init__(self, players_service: PlayersService):
        self.__players_service = players_service

    def display_all_players_sorted(self):
        all_players = self.__players_service.list_all_players_descending_by_strength()
        for player in all_players:
            print(player)

    def play_round(self, pair):
        print("player 1", pair[0])
        print("player 2", pair[1])
        winner = int(input("Choose the winner\n"))
        self.__players_service.handle_winner(pair, winner)

    def qualifying_round(self):
        pairs = self.__players_service.get_pairs_for_qualifying_round()
        for pair in pairs:
            self.play_round(pair)

    def play_tournament(self):
        while self.__players_service.get_number_of_players() > 1:
            print("Last ", self.__players_service.get_number_of_players())
            self.display_all_players_sorted()
            pairs = self.__players_service.get_pairs_for_normal_round()
            for pair in pairs:
                self.play_round(pair)
        print("winner is")
        self.display_all_players_sorted()

    def run(self):
        self.display_all_players_sorted()
        # qualifying round
        self.qualifying_round()
        self.play_tournament()