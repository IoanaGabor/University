import copy
import random

from src.domain import Player
from src.repository import PlayersRepository


class PlayersService:
    def __init__(self, players_repository: PlayersRepository):
        self.__players_repository = players_repository

    def list_all_players_descending_by_strength(self):
        all_players = self.__players_repository.list_all()
        return sorted(all_players, key=lambda x: -x.playing_strength)

    def get_number_of_players(self):
        return len(self.__players_repository)

    def get_number_of_players_for_qualifying_round(self):
        nb_of_players = self.get_number_of_players()
        power_of_2 = 1
        while power_of_2 < nb_of_players:
            power_of_2 *= 2
        if power_of_2 > nb_of_players:
            power_of_2 //= 2
            return nb_of_players - power_of_2
        return 0

    def get_pairs_for_qualifying_round(self):
        """Selects the pairs of players that will compete in the qualifying round

        :return: list of pairs
        """
        players = self.select_players_for_qualifying_round()
        return self.pair_players(players)

    def select_players_for_qualifying_round(self):
        """Selects the weakest players that will compete in the qualifying round

        :return: list of players
        """
        nb_of_players = self.get_number_of_players()
        all_players = self.list_all_players_descending_by_strength()
        k = self.get_number_of_players_for_qualifying_round()
        weakest_players = all_players[nb_of_players - 2 * k:nb_of_players]
        return weakest_players

    def handle_winner(self, pair, winner_index):
        # increase strength
        # delete loser
        winner = pair[winner_index - 1]
        loser = pair[1 - (winner_index - 1)]
        self.__players_repository.update_player(Player(winner.id, winner.name, winner.playing_strength + 1))
        self.__players_repository.delete_player(loser)

    def get_pairs_for_normal_round(self):
        """Makes random paris of all players

        :return: list of pairs of players
        """
        return self.pair_players(self.list_all_players_descending_by_strength())

    def pair_players(self, players_to_be_paired: list):
        """Makes random pairs of players. The length of players to be paired must be even

        :param players_to_be_paired:
        :return:
        """
        nr_pairs = len(players_to_be_paired) // 2
        pairs = []
        for pair in range(nr_pairs):
            first_player = copy.deepcopy(players_to_be_paired[0])
            players_to_be_paired = players_to_be_paired[1:]
            second_player_index = random.randrange(0, len(players_to_be_paired))
            second_player = copy.deepcopy(players_to_be_paired[second_player_index])
            players_to_be_paired.remove(second_player)
            pairs.append((first_player, second_player))
        return pairs
