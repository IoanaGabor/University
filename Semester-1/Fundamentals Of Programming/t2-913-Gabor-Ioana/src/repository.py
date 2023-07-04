import pathlib

from src.domain import PlayerRepositoryConverter


class PlayersRepository:
    def __init__(self, file_name):
        self.__all_players = {}
        self.__file_name = file_name
        self.__load()

    def __load(self):
        abspath = pathlib.Path(self.__file_name).absolute()
        with open(abspath, 'r') as f:
            lines = f.readlines()
            for line in lines:
                new_player = PlayerRepositoryConverter.from_string(line)
                self.__all_players[new_player.id] = new_player
            f.close()

    def __save(self):
        abspath = pathlib.Path(self.__file_name).absolute()
        with open(abspath, 'w') as f:
            for player in self.__all_players.values():
                f.write(PlayerRepositoryConverter.to_string(player)+"\n")
            f.close()

    def add_player(self):
        pass

    def update_player(self, updated_player):
        self.__load()
        if updated_player.id not in self.__all_players:
            raise KeyError("player not found")
        self.__all_players[updated_player.id] = updated_player
        self.__save()

    def delete_player(self, player):
        self.__load()
        if player.id not in self.__all_players:
            raise KeyError("player not found")
        del self.__all_players[player.id]
        self.__save()

    def list_all(self):
        return list(self.__all_players.values())

    def __len__(self):
        return len(self.__all_players)
