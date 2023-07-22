//
// Created by ioana on 30.03.2023.
//

#include "TestEvent.h"
#include <cassert>
#include "domain/Event.h"
#include "domain/AppExceptions.h"

void TestEvent::testAllEvent() {
    TestEvent::testCreateGettersAndSettersEvent();
    TestEvent::testCopyAndEqualOperatorEvent();
    TestEvent::testToString();
}

void TestEvent::testCreateGettersAndSettersEvent() {
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    Event event = Event(title, description, numberOfAttendants, dateAndTime, link);
    assert(event.getTitle() == title);
    assert(event.getDescription() == description);
    assert(event.getDateAndTime() == dateAndTime);
    assert(event.getNumberOfAttendants() == numberOfAttendants);
    assert(event.getLink() == link);
    std::string newTitle = "movie nightfdas";
    std::string newDescription = "moviefdas night";
    std::string newDateAndTime = "/2022/10/23/10:25";
    int newNumberOfAttendants = 43;
    event.setTitle(newTitle);
    assert(event.getTitle() == newTitle);
    event.setDescription(newDescription);
    assert(event.getDescription() == newDescription);
    event.setDateAndTime(newDateAndTime);
    assert(event.getDateAndTime() == newDateAndTime);
    event.setNumberOfAttendants(newNumberOfAttendants);
    assert(event.getNumberOfAttendants() == newNumberOfAttendants);
    std::string newLink = "https://youtube.com";
    event.setLink(newLink);
    assert(event.getLink() == newLink);
    try {
        event.setLink("    ");
        assert(false);
    } catch (EventException &eventException) {
        assert(true);
    }
    try {
        event.setDateAndTime("");
        assert(false);
    } catch (EventException &eventException) {
        assert(true);
    }
}

void TestEvent::testCopyAndEqualOperatorEvent() {
    std::string title = "movie night";
    std::string description = "movie night";
    std::string dateAndTime = "/2022/10/23/10:24";
    int numberOfAttendants = 39;
    std::string link = "https://stackoverflow.com/questions/3385229";
    Event event = Event(title, description, numberOfAttendants, dateAndTime, link);
    Event copyOfEvent = Event(event);
    assert(copyOfEvent.getTitle() == title);
    assert(copyOfEvent.getDescription() == description);
    assert(copyOfEvent.getDateAndTime() == dateAndTime);
    assert(copyOfEvent.getLink() == link);
    assert(event == copyOfEvent);
    copyOfEvent.setTitle("fdas");
    assert(event != copyOfEvent);
}

void TestEvent::testToString() {
    std::string expectedString = "Title fdasfdas Description fda Date and timeDate and time /2022/06/23/10:25Link https://www.infoarena.ro/ Number of participants 3";
    Event event = Event("fdasfdas", "fda", 3, "/2022/06/23/10:25", "https://www.infoarena.ro/");
    assert(event.toString() == expectedString);
}
