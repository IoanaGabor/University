from src.domain.discipline import Discipline
from src.exceptions.repository_exceptions import GenericRepositoryException
from src.exceptions.services_exceptions import DisciplinesServiceException
from src.exceptions.validation_exceptions import DisciplineValidationException
from src.repository.generic_repository import GenericRepository
from src.services.grades_service import GradesService


class DisciplinesService:
    def __init__(self, discipline_repository: GenericRepository, grades_service: GradesService):
        self.__disciplines_repository = discipline_repository
        self.__grades_service = grades_service

    def add(self, discipline_id, name):
        """Creates and adds a discipline, given a discipline_id and a name. Could raise DisciplinesServiceException.

        :param discipline_id: integer
        :param name:string
        :return:
        """
        try:
            self.__disciplines_repository.add(Discipline(discipline_id, name))
        except GenericRepositoryException or DisciplineValidationException as ex:
            raise DisciplinesServiceException(ex)

    def find(self, discipline_id):
        """Returns the discipline with discipline_id or raise DisciplinesServiceException if it's not found.

        :param discipline_id: integer
        :return:
        """
        discipline = self.__disciplines_repository.find_by_entity_id(discipline_id)
        if discipline is None:
            raise DisciplinesServiceException("The discipline doesn't exist!")
        return discipline

    def delete(self, discipline_id):
        """Deletes a discipline and its corresponding grades, as given by a discipline id, raises DisciplinesServiceExeption if it doesn't exist

        :param discipline_id: integer
        :return:
        """
        try:
            self.__disciplines_repository.delete_by_entity_id(discipline_id)
            self.__grades_service.delete_all_grades_of_discipline(discipline_id)
        except GenericRepositoryException as ex:
            raise DisciplinesServiceException("This discipline does not exist")

    def update(self, discipline_id, name):
        """Updates a discipline, given a discipline_id and a name. Could raise DisciplinesServiceException.

        :param discipline_id: integer
        :param name:string
        :return:
        """
        try:
            self.__disciplines_repository.update(Discipline(discipline_id, name))
        except GenericRepositoryException or DisciplineValidationException as ex:
            raise DisciplinesServiceException(ex)

    def search(self, search_token):
        """Searches for all discipline which have the search_token as a subsequence in their name

        :param search_token:string
        :return:list of Disciplines
        """
        all_disciplines = self.__disciplines_repository.find_all()
        matching_disciplines = []
        for discipline in all_disciplines:
            if discipline.name.lower().find(search_token.lower()) != -1:
                matching_disciplines.append(discipline)
        return matching_disciplines

    def list_all(self):
        """Returns a list containing all disciplines

        :return: list of Disciplines
        """
        return self.__disciplines_repository.find_all()
