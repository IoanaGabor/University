//
// Created by ioana on 30.03.2023.
//

#include <iostream>
#include "EventsController.h"
#include "validators/Validators.h"

EventsController::EventsController(const Repository<Event> &eventsRepository,
                                   const Repository<Event> &userEventListRepository) {
    this->eventsRepository = eventsRepository;
    this->userEventListRepository = userEventListRepository;
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
    if(!isPresentAdministrator) {
        throw EventsControllerException("the event does not exist in the database");
    }
    if(isPresentUser){
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
    if(!isPresentAdministrator) {
        throw EventsControllerException("the event does not exist in the database");
    }
    if(!isPresentUser){
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

DynamicVector<Event> EventsController::selectAllEventsByMonth(const std::string& month) {
    DynamicVector<Event> allEvents = this->eventsRepository.getAllEntities();
    DynamicVector<Event> selectedEvents = DynamicVector<Event>();
    if (!month.empty() && !Validators::isValidMonth(month)) {
        throw EventsControllerException("invalid month");
    }
    if(month.empty()){
        return this->getAllEventsSortedByDate();
    }
    for (int i = 0; i < allEvents.getSize(); i++) {
        if (allEvents[i].getMonth() == month) {
            selectedEvents.add(allEvents[i]);
        }
    }
    return selectedEvents;
}

DynamicVector<Event> EventsController::getAllEventsSortedByDate(){
    DynamicVector<Event> allEvents = this->eventsRepository.getAllEntities();
    Event temporaryEventUsedForSwapping;
    for(int i=0;i<allEvents.getSize();i++){
        for(int j=i+1;j<allEvents.getSize();j++){
            if(allEvents[i].getDateAndTime() > allEvents[j].getDateAndTime()){
                temporaryEventUsedForSwapping = allEvents[i];
                allEvents[i] = allEvents[j];
                allEvents[j] = temporaryEventUsedForSwapping;
            }
        }
    }
    return allEvents;
}

EventsController::EventsController() = default;

DynamicVector<Event> EventsController::listEventsAdministrator() {
    return this->eventsRepository.getAllEntities();
}

DynamicVector<Event> EventsController::listEventsUser() {
    return this->userEventListRepository.getAllEntities();
}
