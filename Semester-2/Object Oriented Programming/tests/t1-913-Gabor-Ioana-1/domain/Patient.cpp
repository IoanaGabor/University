//
// Created by ioana on 28.04.2023.
//

#include "Patient.h"

Patient::Patient(std::string name, int age, bool infected, int roomNumber) {
    this->name = name;
    this->age = age;
    this->infected = infected;
    this->roomNumber = roomNumber;
}

std::string Patient::getName() {
    return this->name;
}

int Patient::getAge() {
    return this->age;
}

bool Patient::isInfected() {
    return this->infected;
}

int Patient::getRoomNumber() {
    return this->roomNumber;
}

std::string Patient::getID() {
    return this->getName();
}

std::string Patient::toString() {
    return name + " | " + std::to_string(age) + " | " +
           std::to_string(infected) + " | " + std::to_string(roomNumber);
}
