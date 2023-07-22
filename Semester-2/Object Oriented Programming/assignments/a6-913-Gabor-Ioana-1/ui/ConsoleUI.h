//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_CONSOLEUI_H
#define A45_913_GABOR_IOANA_CONSOLEUI_H


#include "controller/EventsController.h"

class ConsoleUI {
private:
    EventsController eventsController;
    std::string usageMode;
public:
    explicit ConsoleUI(const EventsController &eventsController);
    void runConsoleMenu();
private:
    static void printAdministratorMenu();
    void executeAdministratorCommand(const std::string& command);
    void handleAdministratorAddEventCommand();
    void handleAdministratorUpdateEventCommand();
    void handleAdministratorRemoveEventCommand();
    static void printEvents(std::vector<Event> someEvents);

    static void printUserMenu();

    void executeUserCommand(const std::string &command);

    void handleUserDisplayEventsMenuCommand();

    void handleUserRemoveEventCommand();
};


#endif //A45_913_GABOR_IOANA_CONSOLEUI_H
