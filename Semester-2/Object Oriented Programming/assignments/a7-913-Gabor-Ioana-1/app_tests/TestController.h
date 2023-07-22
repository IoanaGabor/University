//
// Created by ioana on 31.03.2023.
//

#ifndef A45_913_GABOR_IOANA_TESTCONTROLLER_H
#define A45_913_GABOR_IOANA_TESTCONTROLLER_H


#include "domain/Event.h"
#include "repository/AbstractRepository.h"
#include "repository/AbstractUserEventList.h"

class TestController {
public:
    static void testAllController(
            AbstractRepository<Event> &eventsRepository,
            AbstractUserEventList &userEventListRepository
    );

private:
    static void testAddEventAdministrator(AbstractRepository<Event> &eventsRepository,
                                          AbstractUserEventList &userEventListRepository);

    static void testUpdateEventAdministrator(AbstractRepository<Event> &eventsRepository,
                                             AbstractUserEventList &userEventListRepository);

    static void testRemoveEventAdministrator(AbstractRepository<Event> &eventsRepository,
                                             AbstractUserEventList &userEventListRepository);

    static void testListEventsAdministrator(AbstractRepository<Event> &eventsRepository,
                                            AbstractUserEventList &userEventListRepository);

    static void testSelectEventsByMonthAdministrator(AbstractRepository<Event> &eventsRepository,
                                                     AbstractUserEventList &userEventListRepository);

    static void testAddEventUser(AbstractRepository<Event> &eventsRepository,
                                 AbstractUserEventList &userEventListRepository);

    static void testRemoveEventUser(AbstractRepository<Event> &eventsRepository,
                                    AbstractUserEventList &userEventListRepository);
};


#endif //A45_913_GABOR_IOANA_TESTCONTROLLER_H
