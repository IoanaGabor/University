//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_APPEXCEPTIONS_H
#define A45_913_GABOR_IOANA_APPEXCEPTIONS_H


#include <exception>
#include <string>

class GenericAppException : public std::exception {

    std::string message;
public:
    explicit GenericAppException(const std::string &message);

    std::string get_message() const;
};

class EventException : public GenericAppException {

    std::string message;
public:
    EventException(const std::string &message);

};

class RepositoryException : public GenericAppException {

    std::string message;
public:
    RepositoryException(const std::string &message);

};

class EventsControllerException : public GenericAppException {

    std::string message;
public:
    EventsControllerException(const std::string &message);

};


#endif //A45_913_GABOR_IOANA_APPEXCEPTIONS_H
