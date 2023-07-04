from repository.generic_repo import GenericRepository


class MemoryRepository(GenericRepository):

    def __init__(self):
        super().__init__()

    def load(self):
        pass

    def save(self):
        pass
