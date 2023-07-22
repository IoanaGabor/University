//
// Created by ioana on 31.03.2023.
//

#ifndef A45_913_GABOR_IOANA_TESTCONTROLLER_H
#define A45_913_GABOR_IOANA_TESTCONTROLLER_H


class TestController {
public:
    static void testAllController();
private:
    static void testAddEventAdministrator();
    static void testUpdateEventAdministrator();
    static void testRemoveEventAdministrator();
    static void testListEventsAdministrator();

    static void testSelectEventsByMonthAdministrator();

    static void testAddEventUser();

    static void testRemoveEventUser();
};


#endif //A45_913_GABOR_IOANA_TESTCONTROLLER_H
