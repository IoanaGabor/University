//
// Created by ioana on 30.03.2023.
//

#include <string>
#include <iostream>
#include <regex.h>
#include <string>
#include <regex>
#include "validators/Validators.h"
#include "ConsoleUI.h"
#include "domain/AppExceptions.h"

const std::string ADMIN_USAGE_MOD = "1";
const std::string USER_USAGE_MOD = "2";

void ConsoleUI::runConsoleMenu() {
    std::string commandAsLine;

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
    eventsController.addEventAdministrator("other", "generic description", "/2022/06/23/10:25", 6, "https://www.infoarena.ro/");    usageMode = "";
    while (true) {
        std::cout << "Options:\n";
        std::cout << "1. Admin mode\n";
        std::cout << "2. User mode\n";
        getline(std::cin, usageMode);
        if (usageMode == ADMIN_USAGE_MOD || usageMode == USER_USAGE_MOD) {
            break;
        } else if (usageMode == "exit") {
            return;
        } else {
            std::cout << "invalid command\n";
        }
    }

    while (true) {
        if (usageMode == ADMIN_USAGE_MOD) {
            printAdministratorMenu();
        } else if (usageMode == USER_USAGE_MOD) {
            printUserMenu();
        }
        getline(std::cin, commandAsLine);
        if (commandAsLine == "exit") {
            break;
        }
        if (usageMode == ADMIN_USAGE_MOD) {
            executeAdministratorCommand(commandAsLine);
        } else if (usageMode == USER_USAGE_MOD) {
            executeUserCommand(commandAsLine);
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
    std::cout << "exit\n";
}

void ConsoleUI::executeAdministratorCommand(const std::string &command) {
    if (std::regex_search(command, std::regex("^add event$"))) {
        this->handleAdministratorAddEventCommand();
    } else if (std::regex_search(command, std::regex("^update event$"))) {
        this->handleAdministratorUpdateEventCommand();
    } else if (std::regex_search(command, std::regex("^remove event$"))) {
        this->handleAdministratorRemoveEventCommand();
    } else if (std::regex_search(command, std::regex("^list event$"))) {
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
    } else {
        std::cout << "Invalid command\n";
    }
}

void ConsoleUI::handleAdministratorAddEventCommand() {
    std::string title, description, attendants, link, dateAndTime;
    std::cout << "Please enter the event title:\n";
    getline(std::cin, title);
    std::cout << "Please enter the event date and time:\n";
    getline(std::cin, dateAndTime);
    std::cout << "Please enter the event description:\n";
    getline(std::cin, description);
    std::cout << "Please enter the number of attendants:\n";
    getline(std::cin, attendants);
    std::cout << "Please enter the event link:\n";
    getline(std::cin, link);
    int attendantsAsInteger;
    try {
        attendantsAsInteger = stoi(attendants);
    } catch (std::invalid_argument &invalid_argument) {
        std::cout << "The number of attendants should be an integer!\n";
        return;
    }
    try {
        this->eventsController.addEventAdministrator(
                title,
                description, dateAndTime,
                attendantsAsInteger,
                link
        );
    } catch (EventsControllerException &eventsControllerException) {
        std::cout << eventsControllerException.get_message() << '\n';
    }
}

void ConsoleUI::handleAdministratorUpdateEventCommand() {
    std::string title, description, attendants, link, dateAndTime;
    std::cout << "Please enter title of the event which you want to update:\n";
    getline(std::cin, title);
    std::cout << "Please enter the date and time of the event which you want to update:\n";
    getline(std::cin, dateAndTime);
    std::cout << "Please enter the new event description:\n";
    getline(std::cin, description);
    std::cout << "Please enter the new number of attendants:\n";
    getline(std::cin, attendants);
    std::cout << "Please enter the new event link:\n";
    getline(std::cin, link);
    int attendantsAsInteger;
    try {
        attendantsAsInteger = stoi(attendants);
    } catch (std::invalid_argument &invalid_argument) {
        std::cout << "The number of attendants should be an integer!\n";
        return;
    }
    try {
        this->eventsController.updateEventAdministrator(
                title,
                description, dateAndTime,
                attendantsAsInteger,
                link
        );
    } catch (EventsControllerException &eventsControllerException) {
        std::cout << eventsControllerException.get_message() << '\n';
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
    for (auto & someEvent : someEvents) {
        std::cout << someEvent.toString() << '\n';
    }
}

ConsoleUI::ConsoleUI(const EventsController &eventsController) {
    this->eventsController = eventsController;
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
        system(("open " + selectedEvents[currentIndex].getLink()).c_str());
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
