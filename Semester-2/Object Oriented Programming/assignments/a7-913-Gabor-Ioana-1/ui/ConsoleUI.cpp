//
// Created by ioana on 30.03.2023.
//

#include <string>
#include <iostream>
#include <regex>
#include "ConsoleUI.h"

const std::string ADMIN_USAGE_MOD = "1";
const std::string USER_USAGE_MOD = "2";
const std::string ADD_EVENT_ADMIN = "add event";
const std::string UPDATE_EVENT_ADMIN = "update event";
const std::string REMOVE_EVENT_ADMIN = "remove event";
const std::string LIST_EVENT_ADMIN = "list event";
const std::string EXIT_COMMAND = "exit";
const std::string TEXT_FILE_REPOSITORY = "1";
const std::string CSV_EVENT_LIST = "1";

const std::string DATABASE_REPOSITORY = "2";
const std::string HTML_EVENT_LIST = "2";

void ConsoleUI::runConsoleMenu() {
    std::string commandAsLine;
    if (eventsController.listEventsAdministrator().empty()) {
        eventsController.addEventAdministrator("movie", "generic description", "/2022/09/23/10:25", 3, "https://www.google.com/");
        eventsController.addEventAdministrator("concert", "generic description", "/2022/10/23/10:25", 4, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("abc", "generic description", "/2022/04/23/10:25", 5, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("contest", "generic description", "/2022/10/21/10:25", 43, "https://www.youtube.com/");
        eventsController.addEventAdministrator("party", "generic description", "/2022/11/23/10:25", 42, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("something", "generic description", "/2022/12/23/10:25", 65, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("nothing", "generic description", "/2022/01/23/10:25", 54, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("haha", "generic description", "/2022/03/23/10:25", 65, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("well", "generic description", "/2022/04/23/10:25", 2, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("another", "generic description", "/2022/05/23/10:25", 3, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("other", "generic description", "/2022/06/23/10:25", 6, "https://www.infoarena.ro/");    }
    usageMode = "";
    while (true) {
        std::cout << "Options:\n";
        std::cout << "1. Admin mode\n";
        std::cout << "2. User mode\n";
        getline(std::cin, usageMode);
        if (usageMode == ADMIN_USAGE_MOD || usageMode == USER_USAGE_MOD) {
            while (true) {
                if (usageMode == ADMIN_USAGE_MOD) {
                    printAdministratorMenu();
                } else if (usageMode == USER_USAGE_MOD) {
                    printUserMenu();
                }
                getline(std::cin, commandAsLine);
                if (commandAsLine == EXIT_COMMAND) {
                    break;
                }
                if (usageMode == ADMIN_USAGE_MOD) {
                    executeAdministratorCommand(commandAsLine);
                } else if (usageMode == USER_USAGE_MOD) {
                    executeUserCommand(commandAsLine);
                }
            }

        } else if (usageMode == EXIT_COMMAND) {
            return;
        } else {
            std::cout << "invalid command\n";
        }
    }

}

void ConsoleUI::printAdministratorMenu() {
    std::cout << "Options:\n";
    std::cout << "add event\n";
    std::cout << "update event\n";
    std::cout << "remove event\n";
    std::cout << "list event\n";
    std::cout << "exit\n";
}

void ConsoleUI::printUserMenu() {
    std::cout << "Options:\n";
    std::cout << "display\n";
    std::cout << "my list\n";
    std::cout << "remove event\n";
    std::cout << "open\n";
    std::cout << "exit\n";
}

void ConsoleUI::executeAdministratorCommand(const std::string &command) {
    if (command == ADD_EVENT_ADMIN) {
        this->handleAdministratorAddEventCommand();
    } else if (command == UPDATE_EVENT_ADMIN) {
        this->handleAdministratorUpdateEventCommand();
    } else if (command == REMOVE_EVENT_ADMIN) {
        this->handleAdministratorRemoveEventCommand();
    } else if (command == LIST_EVENT_ADMIN) {
        printEvents(this->eventsController.listEventsAdministrator());
    } else {
        std::cout << "Invalid command\n";
    }
}

void ConsoleUI::executeUserCommand(const std::string &command) {
    if (std::regex_search(command, std::regex("^display$"))) {
        this->handleUserDisplayEventsMenuCommand();
    } else if (std::regex_search(command, std::regex("^remove event$"))) {
        this->handleUserRemoveEventCommand();
    } else if (std::regex_search(command, std::regex("^my list$"))) {
        printEvents(this->eventsController.listEventsUser());
    } else if (std::regex_search(command, std::regex("^open$"))) {
        this->handleUserOpenCommand();
    } else {
        std::cout << "Invalid command\n";
    }
}

void ConsoleUI::handleAdministratorAddEventCommand() {
    std::cout << "Please enter the event which you want to add:\n";
    Event toBeAdded;
    try {
        std::cin >> toBeAdded;
        this->eventsController.addEventAdministrator(
                toBeAdded.getTitle(),
                toBeAdded.getDescription(),
                toBeAdded.getDateAndTime(),
                toBeAdded.getNumberOfAttendants(),
                toBeAdded.getLink()
        );
    } catch (GenericAppException &genericAppException) {
        std::cout << genericAppException.get_message() << '\n';
    }
}

void ConsoleUI::handleAdministratorUpdateEventCommand() {
    std::cout << "Please enter the event which you want to update:\n";
    Event toBeUpdated;
    try {
        std::cin >> toBeUpdated;
        this->eventsController.updateEventAdministrator(
                toBeUpdated.getTitle(),
                toBeUpdated.getDescription(),
                toBeUpdated.getDateAndTime(),
                toBeUpdated.getNumberOfAttendants(),
                toBeUpdated.getLink()
        );
    } catch (GenericAppException &genericAppException) {
        std::cout << genericAppException.get_message() << '\n';
    }
}

void ConsoleUI::handleAdministratorRemoveEventCommand() {
    std::string title, dateAndTime;
    std::cout << "Please enter title of the event which you want to remove:\n";
    getline(std::cin, title);
    std::cout << "Please enter the date and time of the event which you want to remove:\n";
    getline(std::cin, dateAndTime);
    try {
        this->eventsController.removeEventAdministrator(
                title,
                dateAndTime
        );
    } catch (EventsControllerException &eventsControllerException) {
        std::cout << eventsControllerException.get_message() << '\n';
    }
}

void ConsoleUI::handleUserRemoveEventCommand() {
    std::string title, dateAndTime;
    std::cout << "Please enter title of the event which you want to remove:\n";
    getline(std::cin, title);
    std::cout << "Please enter the date and time of the event which you want to remove:\n";
    getline(std::cin, dateAndTime);
    try {
        this->eventsController.removeEventUser(
                title,
                dateAndTime
        );
    } catch (EventsControllerException &eventsControllerException) {
        std::cout << eventsControllerException.get_message() << '\n';
    }
}

void ConsoleUI::printEvents(std::vector<Event> someEvents) {
    for (auto &someEvent: someEvents) {
        std::cout << someEvent << '\n';
    }
}

ConsoleUI::ConsoleUI(const EventsController &eventsController) : eventsController(eventsController) {

}

void ConsoleUI::handleUserDisplayEventsMenuCommand() {
    std::string month;
    std::cout << "Please enter the month, or leave blank";
    getline(std::cin, month);
    int currentIndex = 0;
    std::string commandAsLine;
    std::vector<Event> selectedEvents;
    try {
        selectedEvents = this->eventsController.selectAllEventsByMonth(month);
    } catch (EventsControllerException &eventsControllerException) {
        std::cout << eventsControllerException.get_message() << '\n';
        return;
    }
    if (selectedEvents.empty()) {
        std::cout << "no selected events";
        return;
    }
    while (true) {
        //this->printUserMenu();
        this->eventsController.openEventLinkInBrowser(selectedEvents[currentIndex].getLink());
        std::cout << selectedEvents[currentIndex].toString() << '\n';
        getline(std::cin, commandAsLine);
        if (std::regex_search(commandAsLine, std::regex("^next$"))) {
            currentIndex++;
            currentIndex %= selectedEvents.size();
        } else if (std::regex_search(commandAsLine, std::regex("^add$"))) {
            try {
                this->eventsController.addEventUser(selectedEvents[currentIndex].getId());
            } catch (GenericAppException &genericAppException) {
                std::cout << genericAppException.get_message() << '\n';
            }

        } else if (std::regex_search(commandAsLine, std::regex("^exit$"))) {
            break;
        } else {
            std::cout << "invalid command\n";
        }
    }
}

void ConsoleUI::handleUserOpenCommand() {
    try {
        this->eventsController.openUserEventList();
    } catch (GenericAppException &genericAppException) {
        std::cout << genericAppException.get_message() << '\n';
    }

}


std::string ConsoleUI::getAdminStorageMode() {
    std::string option;
    while (true) {
        std::cout << "Choose admin storage: 1. Text file 2. Database" << '\n';
        getline(std::cin, option);
        if (option == TEXT_FILE_REPOSITORY || option == DATABASE_REPOSITORY) {
            break;
        }
    }
    return option;
}


std::string ConsoleUI::getUserStorageMode() {
    std::string option;
    while (true) {
        std::cout << "Choose user storage: 1. CSV file 2. HTML file" << '\n';
        getline(std::cin, option);
        if (option == CSV_EVENT_LIST || option == HTML_EVENT_LIST) {
            break;
        }
    }
    return option;
}
