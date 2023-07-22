//
// Created by ioana on 28.04.2023.
//

#include "GenericAppException.h"

GenericAppException::GenericAppException(std::string message) {
    this->message = message;
}

std::string GenericAppException::getMessage() {
    return this->message;
}
