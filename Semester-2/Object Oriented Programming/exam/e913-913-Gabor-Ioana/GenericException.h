//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_GENERICEXCEPTION_H
#define E913_913_GABOR_IOANA_GENERICEXCEPTION_H


#include <exception>
#include <string>

class GenericException : std::exception{
private:
    std::string message;
public:
    const std::string &getMessage() const;

public:
    explicit GenericException(const std::string &message);
};


#endif //E913_913_GABOR_IOANA_GENERICEXCEPTION_H
