//
// Created by ioana on 30.03.2023.
//
#include "app_tests/TestAll.h"
#include "domain/Event.h"
#include "ui/ConsoleUI.h"
#include "controller/EventsController.h"
#include "repository/CSVEventList.h"
#include "repository/DataBaseEventsRepository.h"
#include "repository/TextFileRepository.h"
#include "repository/HTMLEventList.h"

const std::string TEXT_FILE_REPOSITORY = "1";
const std::string CSV_EVENT_LIST = "1";

int main() {
    TestAll::runAllTests();
    std::string adminOption = ConsoleUI::getAdminStorageMode();
    std::string userOption = ConsoleUI::getUserStorageMode();
    AbstractRepository<Event> *eventsRepository;
    AbstractUserEventList *userEventListRepository;
    if (adminOption == TEXT_FILE_REPOSITORY) {
        eventsRepository = new TextFileRepository<Event>("../events.txt");
    } else {
        eventsRepository = new DataBaseEventsRepository("../events.db");
    }
    if (userOption == CSV_EVENT_LIST) {
        userEventListRepository = new CSVEventList("../events.csv");
    } else {
        userEventListRepository = new HTMLEventList("../events.html");
    }
    EventsController eventsController(*eventsRepository, *userEventListRepository);
    ConsoleUI consoleUI = ConsoleUI(eventsController);
    consoleUI.runConsoleMenu();
    delete eventsRepository;
    delete userEventListRepository;
}
