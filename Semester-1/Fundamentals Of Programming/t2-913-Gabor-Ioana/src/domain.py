class Player:
    def __init__(self, id, name, playing_strength):
        self.__id = id
        self.__name = name
        self.__playing_strength = playing_strength

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @property
    def playing_strength(self):
        return self.__playing_strength

    @playing_strength.setter
    def playing_strength(self, value):
        self.__playing_strength = value

    def __str__(self):
        return str(self.id) + "," + str(self.name) + "," + str(self.playing_strength)

    def __eq__(self, other):
        return isinstance(other,
                          Player) and self.id == other.id and self.name == other.name and self.playing_strength == other.playing_strength


class PlayerRepositoryConverter:
    @staticmethod
    def to_string(player):
        return str(player.id) + "," + str(player.name) + "," + str(player.playing_strength)

    @staticmethod
    def from_string(string: str):
        string.strip()
        tokens = string.split(",")
        return Player(int(tokens[0]), tokens[1], int(tokens[2]))
