//
// Created by ioana on 02.05.2023.
//

#include "CSVEventList.h"

void CSVEventList::displayEventList() {
    system(("open " + fileName).c_str());
}

void CSVEventList::save() {
    std::ofstream fileWriter(fileName);
    for (const auto & entity : entities) {
        fileWriter << CSVEventList::eventToCSVString(entity) << '\n';
    }
}

std::string CSVEventList::eventToCSVString(const Event& event){
    std::string eventAsCSVString;
    eventAsCSVString += event.getTitle() + ", " + event.getDescription() + ", "
            + event.getDateAndTime() + ", " + std::to_string(event.getNumberOfAttendants()) + ", "
            + event.getLink();
    return eventAsCSVString;
}
