//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_EVENTSCONTROLLER_H
#define A45_913_GABOR_IOANA_EVENTSCONTROLLER_H

#include "repository/Repository.h"
#include "domain/Event.h"

class EventsController {
private:
    Repository<Event> eventsRepository;
    Repository<Event> userEventListRepository;
public:
    EventsController();
    explicit EventsController(const Repository<Event>& eventsRepository, const Repository<Event>& userEventListRepository);

    void addEventAdministrator(const std::string &title, const std::string &description, const std::string &dateAndTime,
                               int numberOfAttendants, const std::string &link);

    void
    updateEventAdministrator(const std::string &title, const std::string &description, const std::string &dateAndTime,
                             int numberOfAttendants, const std::string &link);

    void removeEventAdministrator(const std::string &title, const std::string &dateAndTime);
    std::vector<Event> listEventsAdministrator();

    void addEventUser(const std::string &id);

    void removeEventUser(const std::string &title, const std::string &dateAndTime);

    std::vector<Event> selectAllEventsByMonth(const std::string& month);

    std::vector<Event> listEventsUser();

    std::vector<Event> getAllEventsSortedByDate();
};


#endif //A45_913_GABOR_IOANA_EVENTSCONTROLLER_H
