//
// Created by ioana on 30.03.2023.
//

#include "Event.h"
#include "validators/Validators.h"
#include "AppExceptions.h"

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
    this->title = title;
    this->description = description;
    this->link = link;
    this->numberOfAttendants = numberOfAttendants;
    this->dateAndTime = dateAndTime;
    if (!Validators::isValidDateAndTime(dateAndTime)) {
        throw EventException("Invalid date and time\n");
    }
    if (!Validators::isValidLink(link)) {
        throw EventException("Invalid link\n");
    }

}

std::string Event::getTitle() {
    return this->title;
}

std::string Event::getDescription() {
    return this->description;
}

std::string Event::getDateAndTime() const{
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
        }else if (howManySlashes == 2) {
            month += currentCharacter;
        }
    }
    return month;
}

std::string Event::getLink() {
    return this->link;
}

void Event::setTitle(const std::string &newTitle) {
    this->title = newTitle;
}

void Event::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Event::setDateAndTime(const std::string &dateAndTime) {
    if (!Validators::isValidDateAndTime(dateAndTime)) {
        throw EventException("Invalid date and time\n");
    }
    this->dateAndTime = dateAndTime;
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
    return this->title + this->dateAndTime;
}

std::string Event::getIdFromTitleAndDate(const std::string &title, const std::string &date) {
    return title + date;
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

std::string Event::toString() {
    return "Title " + this->title + " Description " + this->description + " Date and time"
           + "Date and time " + this->dateAndTime + "Link " + this->link + " Number of participants "
           + std::to_string(this->numberOfAttendants);
}

Event &Event::operator=(const Event &other) = default;
