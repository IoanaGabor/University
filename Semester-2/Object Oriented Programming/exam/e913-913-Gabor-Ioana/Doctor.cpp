//
// Created by ioana on 16.06.2023.
//

#include "Doctor.h"

Doctor::Doctor(const std::string &name, const std::string &specialisation) : name(name),
                                                                             specialisation(specialisation) {}

const std::string &Doctor::getName() const {
    return name;
}

void Doctor::setName(const std::string &name) {
    Doctor::name = name;
}

const std::string &Doctor::getSpecialisation() const {
    return specialisation;
}

void Doctor::setSpecialisation(const std::string &specialisation) {
    Doctor::specialisation = specialisation;
}
