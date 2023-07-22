//
// Created by ioana on 28.04.2023.
//

#ifndef T1_913_GABOR_IOANA_1_GENERICAPPEXCEPTION_H
#define T1_913_GABOR_IOANA_1_GENERICAPPEXCEPTION_H


#include <exception>
#include <string>

class GenericAppException : std::exception{
public:
    GenericAppException(std::string message);
    std::string getMessage();
private:
    std::string message;
};


#endif //T1_913_GABOR_IOANA_1_GENERICAPPEXCEPTION_H
