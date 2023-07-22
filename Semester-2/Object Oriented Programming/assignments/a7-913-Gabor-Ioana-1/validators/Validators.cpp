//
// Created by ioana on 30.03.2023.
//

#include <regex>
#include "Validators.h"
#include "domain/AppExceptions.h"

bool Validators::isValidLink(std::string link) {
    if(std::regex_search(link,std::regex("^https?:\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\."
                                         "[a-zA-Z0-9()]{1,6}\\b([-a-zA-Z0-9()@:%_\\+.~#?&//=]*)$"))){
        return true;
    }
    return false;
}

bool Validators::isValidDateAndTime(std::string dateAndTime) {
    if(std::regex_search(dateAndTime,std::regex("^/[0-9]{4}/[0-9]{2}/[0-9]{2}/[0-9]{2}:[0-9]{2}$"))){
        return true;
    }
    return false;
}

bool Validators::isValidMonth(const std::string& month){
    if(std::regex_search(month,std::regex("^[0-9]{2}$"))){
        if(month[0]>'2' || (month[0]=='1' && month[1]>'2')){
            return false;
        }
        return true;
    }
    return false;

}

void Validators::validateEventArguments(const std::string &title, const std::string &description, int numberOfAttendants,
                                        const std::string &dateAndTime, const std::string &link) {
    std::string exceptionMessage;
    if (!Validators::isValidDateAndTime(dateAndTime)) {
        exceptionMessage+="Invalid date and time\n";
    }
    if (!Validators::isValidLink(link)) {
        exceptionMessage+="Invalid link\n";
    }
    if(numberOfAttendants<0){
        exceptionMessage+="Invalid number of attendants\n";
    }
    if(!exceptionMessage.empty()){
        throw EventException(exceptionMessage);
    }
}
