//
// Created by ioana on 30.03.2023.
//

#include "AppExceptions.h"

EventException::EventException(const std::string &message) : GenericAppException(message) {

}

std::string GenericAppException::get_message() const {
    return this->message;
}

GenericAppException::GenericAppException(const std::string &message) {
    this->message = message;
}

RepositoryException::RepositoryException(const std::string &message) : GenericAppException(message) {

}

EventsControllerException::EventsControllerException(const std::string &message) : GenericAppException(message) {

}

EventsControllerUserException::EventsControllerUserException(const std::string &message) : EventsControllerException(
        message) {

}

EventsControllerAdminException::EventsControllerAdminException(const std::string &message) : EventsControllerException(
        message) {

}
