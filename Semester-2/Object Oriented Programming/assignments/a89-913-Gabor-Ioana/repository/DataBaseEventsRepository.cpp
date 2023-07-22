//
// Created by ioana on 04.05.2023.
//

#include "DataBaseEventsRepository.h"
#include "domain/AppExceptions.h"
#include <sqlite3.h>


DataBaseEventsRepository::DataBaseEventsRepository(const std::string &fileName) {
    this->fileName = fileName;
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "CREATE TABLE IF NOT EXISTS EVENTS("  \
      "ID CHAR(50) PRIMARY KEY     NOT NULL," \
      "TITLE CHAR(50)    NOT NULL," \
      "DESCRIPTION   TEXT            NOT NULL," \
      "DATE_AND_TIME CHAR(20) NOT NULL," \
      "NUMBER_OF_ATTENDANTS INT,"
                      "LINK CHAR(100));";
    char *errorMessage = 0;
    returnCode = sqlite3_exec(dataBase, sql.c_str(), nullptr, 0, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
}

void DataBaseEventsRepository::add(Event event) {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "INSERT INTO EVENTS (ID,TITLE,DESCRIPTION,DATE_AND_TIME,NUMBER_OF_ATTENDANTS,"
                      "LINK) "  \
         "VALUES (\"" + event.getId() + "\",\""
                      + event.getTitle() + "\",\""
                      + event.getDescription() + "\",\""
                      + event.getDateAndTime() + "\",\""
                      + std::to_string(event.getNumberOfAttendants()) + "\",\""
                      + event.getLink() + "\");";
    char *errorMessage = 0;
    returnCode = sqlite3_exec(dataBase, sql.c_str(), nullptr, 0, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
}

void DataBaseEventsRepository::remove(std::string element_id) {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "DELETE from EVENTS where ID=\"" + element_id + "\"; ";
    char *errorMessage = 0;
    returnCode = sqlite3_exec(dataBase, sql.c_str(), nullptr, nullptr, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
}

void DataBaseEventsRepository::update(Event event) {
    if (!isPresent(event.getId())) {
        throw RepositoryException("element does not exist");
    }
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "UPDATE EVENTS set "
                      "TITLE = \'" + event.getTitle() + "\',"
                      + "DESCRIPTION = \'" + event.getDescription() + "\',"
                      + "DATE_AND_TIME= \'" + event.getDateAndTime() + "\',"
                      + "NUMBER_OF_ATTENDANTS= \'" + std::to_string(event.getNumberOfAttendants()) + "\',"
                      + "LINK= \'" + event.getLink() + "\' "
                      + "where ID=\'" + event.getId() + "\'; ";
    char *errorMessage = 0;
    returnCode = sqlite3_exec(dataBase, sql.c_str(), nullptr, nullptr, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
}

std::vector<Event> DataBaseEventsRepository::getAllEntities() {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    const char *sql = "SELECT * from EVENTS";
    char *errorMessage;
    std::vector<Event> selectedEvents = std::vector<Event>();
    returnCode = sqlite3_exec(dataBase, sql,
                              [](void *ptr, int argc, char **argv, char **azColName) {
                                  auto *list = reinterpret_cast<std::vector<Event> *>(ptr);
                                  Event event(argv[1], argv[2], atoi(argv[4]), argv[3], argv[5]);
                                  list->push_back(event);
                                  return 0;
                              }, &selectedEvents, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
    return selectedEvents;
}

Event DataBaseEventsRepository::getElementById(const std::string &elementId) {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "SELECT * from EVENTS where ID=\"" + elementId + "\"";

    char *errorMessage;
    std::vector<Event> selectedEvents = std::vector<Event>();
    returnCode = sqlite3_exec(dataBase, sql.c_str(),
                              [](void *ptr, int argc, char **argv, char **azColName) {
                                  auto *list = reinterpret_cast<std::vector<Event> *>(ptr);
                                  Event event(argv[1], argv[2], atoi(argv[4]), argv[3], argv[5]);
                                  list->push_back(event);
                                  return 0;
                              }, &selectedEvents, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
    if (selectedEvents.empty()) {
        throw RepositoryException("event not found!");
    }
    return selectedEvents[0];
}

bool DataBaseEventsRepository::isPresent(const std::string &elementId) {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "SELECT * from EVENTS where ID=\"" + elementId + "\"";

    char *errorMessage;
    std::vector<Event> selectedEvents = std::vector<Event>();
    returnCode = sqlite3_exec(dataBase, sql.c_str(),
                              [](void *ptr, int argc, char **argv, char **azColName) {
                                  auto *list = reinterpret_cast<std::vector<Event> *>(ptr);
                                  Event event(argv[1], argv[2], atoi(argv[4]), argv[3], argv[5]);
                                  list->push_back(event);
                                  return 0;
                              }, &selectedEvents, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }
    return !selectedEvents.empty();
}

DataBaseEventsRepository::~DataBaseEventsRepository() = default;

void DataBaseEventsRepository::removeAll() {
    int returnCode = sqlite3_open(fileName.c_str(), &dataBase);
    if (returnCode) {
        throw RepositoryException("the database could not be opened!");
    }
    std::string sql = "DELETE from EVENTS ; ";
    char *errorMessage = 0;
    returnCode = sqlite3_exec(dataBase, sql.c_str(), nullptr, nullptr, &errorMessage);
    sqlite3_close(dataBase);
    if (returnCode != SQLITE_OK) {
        std::string errorAsString(errorMessage);
        sqlite3_free(errorMessage);
        throw RepositoryException(errorAsString);
    }

}
