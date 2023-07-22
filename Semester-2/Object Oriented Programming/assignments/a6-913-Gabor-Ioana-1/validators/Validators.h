//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_VALIDATORS_H
#define A45_913_GABOR_IOANA_VALIDATORS_H


#include <string>

class Validators {
public:
    static bool isValidLink(std::string link);
    static bool isValidDateAndTime(std::string dateAndTime);

    static bool isValidMonth(const std::string& month);
};


#endif //A45_913_GABOR_IOANA_VALIDATORS_H
