from repository.binary_file_repository import BinaryFileRepository
from repository.json_repository import JsonRepository
from repository.memory_repository import MemoryRepository
from repository.text_file_repository import TextFileRepository


class SettingsLoader:
    def __init__(self):
        with open("settings.properties", 'r') as f:
            lines = f.readlines()
            if len(lines) < 1:
                f.close()
                raise ValueError("Invalid settings file")
            self.__type = lines[0].split('=')[1].strip()
            if self.__type != "memory":
                self.__file = lines[1].split('=')[1].strip()
            f.close()

    @property
    def getRepository(self):
        if self.__type == "memory":
            return MemoryRepository()
        elif self.__type == "binary":
            return BinaryFileRepository(self.__file)
        elif self.__type == "text":
            return TextFileRepository(self.__file)
        elif self.__type == "json":
            return JsonRepository(self.__file)
        elif self.__type == "database":
            return JsonRepository(self.__file)
        else:
            raise ValueError("Invalid settings file")
