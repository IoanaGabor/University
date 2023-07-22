//
// Created by ioana on 30.03.2023.
//

#include "Event.h"
#include "validators/Validators.h"
#include "AppExceptions.h"
#include <sstream>
#include <string>
#include <vector>

Event::Event() {
    this->title = "";
    this->description = "";
    this->link = "";
    this->numberOfAttendants = 0;
    this->dateAndTime = "";
}


Event::Event(const Event &other) {
    this->title = other.title;
    this->numberOfAttendants = other.numberOfAttendants;
    this->link = other.link;
    this->description = other.description;
    this->dateAndTime = other.dateAndTime;
}

Event::Event(const std::string &title, const std::string &description, int numberOfAttendants,
             const std::string &dateAndTime, const std::string &link) {
    Validators::validateEventArguments(title, description, numberOfAttendants, dateAndTime, link);
    this->title = title;
    this->description = description;
    this->link = link;
    this->numberOfAttendants = numberOfAttendants;
    this->dateAndTime = dateAndTime;
}

std::string Event::getTitle() const {
    return this->title;
}

std::string Event::getDescription() const {
    return this->description;
}

std::string Event::getDateAndTime() const {
    return this->dateAndTime;
}


int Event::getNumberOfAttendants() const {
    return this->numberOfAttendants;
}

std::string Event::getMonth() const {
    std::string month;
    int howManySlashes = 0;
    for (char currentCharacter: this->dateAndTime) {
        if (currentCharacter == '/') {
            howManySlashes++;
        } else if (howManySlashes == 2) {
            month += currentCharacter;
        }
    }
    return month;
}

std::string Event::getLink() const {
    return this->link;
}

void Event::setTitle(const std::string &newTitle) {
    this->title = newTitle;
}

void Event::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Event::setDateAndTime(const std::string &newDateAndTime) {
    if (!Validators::isValidDateAndTime(newDateAndTime)) {
        throw EventException("Invalid date and time\n");
    }
    this->dateAndTime = newDateAndTime;
}

void Event::setLink(const std::string &newLink) {
    if (!Validators::isValidLink(newLink)) {
        throw EventException("Invalid link\n");
    }
    this->link = newLink;
}

void Event::setNumberOfAttendants(int newNumberOfAttendants) {
    this->numberOfAttendants = newNumberOfAttendants;
}

std::string Event::getId() {
    return this->title + " | " + this->dateAndTime;
}

std::string Event::getIdFromTitleAndDate(const std::string &title, const std::string &date) {
    return title + " | " + date;
}

std::pair<std::string, std::string> Event::getTitleAndDateFromId(const std::string &id) {
    std::size_t found = id.find(" | ");
    std::string title = id.substr(0, found);
    std::string date = id.substr(found, std::string::npos);
    return {title, date};
}


bool Event::operator==(const Event &other) const {
    return this->title == other.title && this->description == other.description &&
           this->numberOfAttendants == other.numberOfAttendants && this->link == other.link
           && this->dateAndTime == other.dateAndTime;
}

bool Event::operator!=(const Event &other) const {
    return !(this->title == other.title && this->description == other.description &&
             this->numberOfAttendants == other.numberOfAttendants && this->link == other.link
             && this->dateAndTime == other.dateAndTime);
}

std::string Event::toString() const {
    return "Title " + this->title + " Description " + this->description + " Date and time"
    + this->dateAndTime + "Link " + this->link + " Number of participants "
           + std::to_string(this->numberOfAttendants);
}

std::ostream &operator<<(std::ostream &out, const Event &c) {
    out << c.title << "|" << c.description << "|" << c.dateAndTime << "|" << c.link << "|" << c.numberOfAttendants;
    return out;
}

std::istream &operator>>(std::istream &in, Event &c) {
    std::string eventAsString;
    getline(in, eventAsString);
    if (eventAsString.empty()) {
        c = Event();
        return in;
    }
    std::stringstream parser(eventAsString);
    std::string intermediate;
    std::vector<std::string> tokens = std::vector<std::string>();
    while (getline(parser, intermediate, '|')) {
        tokens.push_back(intermediate);
    }
    if (tokens.size() != 5) {
        throw EventException("invalid number of arguments");
    }
    c.title = tokens[0];
    c.description = tokens[1];
    c.dateAndTime = tokens[2];
    c.link = tokens[3];
    try {
        c.numberOfAttendants = stoi(tokens[4]);
    } catch (std::invalid_argument &invalid_argument) {
        throw EventException("The number of attendants should be an integer!\n");
    }
    Validators::validateEventArguments(c.title, c.description, c.numberOfAttendants, c.dateAndTime, c.link);
    return in;
}

Event &Event::operator=(const Event &other) = default;
