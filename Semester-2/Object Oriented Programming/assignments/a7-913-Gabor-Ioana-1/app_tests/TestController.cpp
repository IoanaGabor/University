//
// Created by ioana on 31.03.2023.
//

#include <cassert>
#include "TestController.h"
#include "domain/Event.h"
#include "repository/MemoryRepository.h"
#include "controller/EventsController.h"
#include "repository/CSVEventList.h"
#include "repository/DataBaseEventsRepository.h"

void TestController::testAllController(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {

    TestController::testAddEventAdministrator(eventsRepository, userEventListRepository);
    TestController::testUpdateEventAdministrator(eventsRepository, userEventListRepository);
    TestController::testRemoveEventAdministrator(eventsRepository, userEventListRepository);
    TestController::testListEventsAdministrator(eventsRepository, userEventListRepository);
    TestController::testSelectEventsByMonthAdministrator(eventsRepository, userEventListRepository);
    TestController::testAddEventUser(eventsRepository, userEventListRepository);
    TestController::testRemoveEventUser(eventsRepository, userEventListRepository);
}

void TestController::testAddEventAdministrator(AbstractRepository<Event> &eventsRepository,
                                               AbstractUserEventList &userEventListRepository) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    try {
        eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, "fdsa");
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }

    try {
        eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testUpdateEventAdministrator(AbstractRepository<Event> &eventsRepository,
                                                  AbstractUserEventList &userEventListRepository) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    std::string updatedDescription = "movie night asdf";
    eventsController.updateEventAdministrator(title, updatedDescription, dateAndTime, numberOfAttendants, link);
    try {
        eventsController.updateEventAdministrator(title, description, dateAndTime, numberOfAttendants, "fdsa");
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }

    try {
        eventsController.updateEventAdministrator("fdasd", description, dateAndTime, numberOfAttendants, link);
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testRemoveEventAdministrator(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    eventsController.addEventAdministrator("fdasdas", description, dateAndTime, numberOfAttendants, link);
    eventsController.removeEventAdministrator(title, dateAndTime);
    assert(eventsController.listEventsAdministrator().size() == 1);
    /*try {
        eventsController.removeEventAdministrator("fdasd", dateAndTime);
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }*/
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testListEventsAdministrator(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    assert(eventsController.listEventsAdministrator().size() == 1);
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testSelectEventsByMonthAdministrator(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    eventsController.addEventAdministrator("movie night", "movie night", "/2022/10/23/10:24", 39,
                                           "https://stackoverflow.com/questions/3385229");
    eventsController.addEventAdministrator("movie night 2", "movie night", "/2022/09/23/10:24", 39,
                                           "https://stackoverflow.com/questions/3385229");
    eventsController.addEventAdministrator("movie nigjk;lht 3", "movie night", "/2022/10/23/10:24", 39,
                                           "https://stackoverflow.com/questions/3385229");
    eventsController.addEventAdministrator("movie night 4", "movie night", "/2022/12/23/10:24", 39,
                                           "https://stackoverflow.com/questions/3385229");
    assert(eventsController.selectAllEventsByMonth("10").size() == 2);
    assert(eventsController.selectAllEventsByMonth("").size() == 4);
    try {
        eventsController.selectAllEventsByMonth("13").size();
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    try {
        eventsController.selectAllEventsByMonth("13fdas").size();
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testAddEventUser(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    eventsController.addEventUser(Event::getIdFromTitleAndDate(title, dateAndTime));
    assert(eventsController.listEventsUser().size() == 1);
    try {
        eventsController.addEventUser(Event::getIdFromTitleAndDate(title, dateAndTime));
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}

void TestController::testRemoveEventUser(
        AbstractRepository<Event> &eventsRepository,
        AbstractUserEventList &userEventListRepository
) {
    EventsController eventsController = EventsController(eventsRepository, userEventListRepository);
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    eventsController.addEventAdministrator(title, description, dateAndTime, numberOfAttendants, link);
    eventsController.addEventUser(Event::getIdFromTitleAndDate(title, dateAndTime));
    assert(eventsController.listEventsUser().size() == 1);
    eventsController.removeEventUser(title, dateAndTime);
    try {
        eventsController.removeEventUser(title, dateAndTime);
        assert(false);
    } catch (EventsControllerException &eventsControllerException) {
        assert(true);
    }
    eventsRepository.removeAll();
    userEventListRepository.removeAll();
}
