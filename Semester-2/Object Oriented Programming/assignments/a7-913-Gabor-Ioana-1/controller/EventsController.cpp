//
// Created by ioana on 30.03.2023.
//

#include <iostream>
#include <algorithm>
#include "EventsController.h"
#include "validators/Validators.h"

EventsController::EventsController(AbstractRepository<Event> &eventsRepository,
                                   AbstractUserEventList &userEventListRepository) : eventsRepository(
        eventsRepository), userEventListRepository(userEventListRepository) {
}

void EventsController::addEventAdministrator(const std::string &title, const std::string &description,
                                             const std::string &dateAndTime, int numberOfAttendants,
                                             const std::string &link) {
    try {
        Event eventToBeAdded = Event(title, description, numberOfAttendants, dateAndTime, link);
        this->eventsRepository.add(eventToBeAdded);
    } catch (GenericAppException &genericAppException) {
        throw EventsControllerException(genericAppException.get_message());
    }

}

void EventsController::updateEventAdministrator(const std::string &title, const std::string &description,
                                                const std::string &dateAndTime, int numberOfAttendants,
                                                const std::string &link) {
    try {
        Event eventToBeUpdated = Event(title, description, numberOfAttendants, dateAndTime, link);
        this->eventsRepository.update(eventToBeUpdated);
    } catch (GenericAppException &genericAppException) {
        throw EventsControllerException(genericAppException.get_message());
    }
}

void EventsController::removeEventAdministrator(const std::string &title, const std::string &dateAndTime) {
    try {
        this->eventsRepository.remove(Event::getIdFromTitleAndDate(title, dateAndTime));
    } catch (GenericAppException &genericAppException) {
        throw EventsControllerException(genericAppException.get_message());
    }
}

void EventsController::addEventUser(const std::string &id) {
    bool isPresentAdministrator = this->eventsRepository.isPresent(id);
    bool isPresentUser = this->userEventListRepository.isPresent(id);
    if (!isPresentAdministrator) {
        throw EventsControllerException("the event does not exist in the database");
    }
    if (isPresentUser) {
        throw EventsControllerException("the event is already in user's list");
    }
    Event eventToBeUpdated = this->eventsRepository.getElementById(id);
    this->eventsRepository.update(
            Event(
                    eventToBeUpdated.getTitle(),
                    eventToBeUpdated.getDescription(),
                    eventToBeUpdated.getNumberOfAttendants() + 1,
                    eventToBeUpdated.getDateAndTime(),
                    eventToBeUpdated.getLink()
            ));
    Event eventToBeAddedToUserList = this->eventsRepository.getElementById(id);
    this->userEventListRepository.add(eventToBeAddedToUserList);
}

void EventsController::removeEventUser(const std::string &title, const std::string &dateAndTime) {
    bool isPresentAdministrator = this->eventsRepository.isPresent(Event::getIdFromTitleAndDate(title, dateAndTime));
    bool isPresentUser = this->userEventListRepository.isPresent(Event::getIdFromTitleAndDate(title, dateAndTime));
    if (!isPresentAdministrator) {
        throw EventsControllerException("the event does not exist in the database");
    }
    if (!isPresentUser) {
        throw EventsControllerException("the event is not in user's list");
    }
    Event eventToBeUpdated = this->eventsRepository.getElementById(
            Event::getIdFromTitleAndDate(title, dateAndTime));
    this->eventsRepository.update(
            Event(
                    eventToBeUpdated.getTitle(),
                    eventToBeUpdated.getDescription(),
                    eventToBeUpdated.getNumberOfAttendants() - 1,
                    eventToBeUpdated.getDateAndTime(),
                    eventToBeUpdated.getLink()
            ));
    this->userEventListRepository.remove(Event::getIdFromTitleAndDate(title, dateAndTime));
}

std::vector<Event> EventsController::selectAllEventsByMonth(const std::string &month) {
    std::vector<Event> allEvents = this->eventsRepository.getAllEntities();
    std::vector<Event> selectedEvents = std::vector<Event>();
    if (!month.empty() && !Validators::isValidMonth(month)) {
        throw EventsControllerException("invalid month");
    }
    if (month.empty()) {
        return this->getAllEventsSortedByDate();
    }
    std::copy_if(allEvents.begin(), allEvents.end(),
                 std::back_inserter(selectedEvents),
                 [&month](const Event &event) { return event.getMonth() == month; });

    return selectedEvents;
}

std::vector<Event> EventsController::getAllEventsSortedByDate() {
    std::vector<Event> allEvents = this->eventsRepository.getAllEntities();
    Event temporaryEventUsedForSwapping;
    std::sort(allEvents.begin(), allEvents.end(),
              [](const Event &a, const Event &b) -> bool {
                  return a.getDateAndTime() > b.getDateAndTime();
              });
    return allEvents;
}


std::vector<Event> EventsController::listEventsAdministrator() {
    return this->eventsRepository.getAllEntities();
}

std::vector<Event> EventsController::listEventsUser() {
    return this->userEventListRepository.getAllEntities();
}

void EventsController::openUserEventList() {
    try {
        this->userEventListRepository.displayEventList();
    } catch (std::exception &exception) {
        throw EventsControllerException("the event list could not be opened");
    }
}

void EventsController::openEventLinkInBrowser(std::string eventLink) {
    system(("open " + eventLink).c_str());
}
