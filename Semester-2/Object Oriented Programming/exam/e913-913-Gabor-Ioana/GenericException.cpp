//
// Created by ioana on 16.06.2023.
//

#include "GenericException.h"

GenericException::GenericException(const std::string &message) : message(message) {}

const std::string &GenericException::getMessage() const {
    return message;
}
