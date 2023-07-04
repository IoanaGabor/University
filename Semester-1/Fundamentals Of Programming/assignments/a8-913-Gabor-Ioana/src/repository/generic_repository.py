from src.exceptions.repository_exceptions import GenericRepositoryException


class GenericRepository:
    def __init__(self):
        self._all_entities = {}

    def add(self, entity):
        """Adds an entity to the repository, throws Value Error if there is duplicate isbn

        :param entity: object with property id
        :return:
        """
        if self.find_by_entity_id(entity.id) is not None:
            raise GenericRepositoryException("Duplicate id!")
        self._all_entities[entity.id] = entity

    def add_all(self, list_of_entities):
        """Adds all entities from a list of entities to the repository, or throws an error in case of duplicate entity_id

        :param list_of_entities:
        :return:
        """
        for entity in list_of_entities:
            if self.find_by_entity_id(entity.id) is not None:
                raise GenericRepositoryException("Duplicate id!")
            self._all_entities[entity.id] = entity

    def delete_all(self):
        """Deletes all entities from the repository.

        :return:
        """
        self._all_entities = {}

    def find_all(self):
        """ Returns a list of all the entities, sorted by id

        :return: list of books
        """
        return sorted(list(self._all_entities.values()),key=lambda x:x.id)

    def update(self, entity):
        """Updates an entity with a certain entity_id or throws GenericRepositoryException if the id was not found.

        :param entity: object with property entity_id
        :return:
        """
        if self.find_by_entity_id(entity.id) is None:
            raise GenericRepositoryException("id was not found!")
        self._all_entities[entity.id] = entity

    def delete_by_entity_id(self, entity_id):
        """Deletes an entity with a certain entity_id or throws GenericRepositoryException if the id was not found.

        :param entity_id: string
        :return:
        """
        if self.find_by_entity_id(entity_id) is None:
            raise GenericRepositoryException("id was not found!")
        del self._all_entities[entity_id]

    def find_by_entity_id(self, entity_id):
        """Finds an entity, given an entity_id, or returns None if none was found

        :param entity_id: string
        :return:
        """
        if entity_id in self._all_entities.keys():
            return self._all_entities[entity_id]
        return None
