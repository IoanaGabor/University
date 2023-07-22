//
// Created by ioana on 30.03.2023.
//
#include "app_tests/TestAll.h"
#include "domain/DynamicVector.h"
#include "domain/Event.h"
#include "ui/ConsoleUI.h"
#include "controller/EventsController.h"
#include "repository/Repository.h"

int main(){
    TestAll::runAllTests();
    Repository<Event> eventsRepository = Repository<Event>();
    Repository<Event> userEventListRepository = Repository<Event>();
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    ConsoleUI consoleUI = ConsoleUI(eventsController);
    consoleUI.runConsoleMenu();
}