//
// Created by ioana on 31.03.2023.
//

#include <iostream>
#include "TestAll.h"
#include "TestEvent.h"
#include "TestRepository.h"
#include "TestController.h"
//#include "repository/DataBaseEventsRepository.h"
#include "repository/CSVEventList.h"
#include "repository/TextFileRepository.h"
#include "repository/HTMLEventList.h"

void TestAll::runAllTests() {
    TestController::testsWithFakeRepository();
    TestEvent::testAllEvent();
    TestRepository::testAllRepository();
    AbstractRepository<Event> *eventsRepository = new TextFileRepository<Event>("../test_text.txt");
    AbstractUserEventList *userEventListRepository = new CSVEventList("../testeventlist.csv");
    try {
        TestController::testAllController(
                *eventsRepository,
                *userEventListRepository
        );
        remove("../test_text.txt");
        remove("../testeventlist.csv");
    } catch (GenericAppException &genericAppException) {
        std::cout << genericAppException.get_message();
    }
    eventsRepository = new TextFileRepository<Event>("../test_text.txt");
    userEventListRepository = new HTMLEventList("../testeventlist.html");
    try {
        TestController::testAllController(
                *eventsRepository,
                *userEventListRepository
        );
        remove("../test_text.txt");
        remove("../testeventlist.html");
    } catch (GenericAppException &genericAppException) {
        std::cout << genericAppException.get_message();
    }

}
