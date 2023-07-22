//
// Created by ioana on 03.05.2023.
//

#ifndef A7_913_GABOR_IOANA_1_HTMLEVENTLIST_H
#define A7_913_GABOR_IOANA_1_HTMLEVENTLIST_H


#include "AbstractFileRepository.h"
#include "domain/Event.h"
#include "AbstractUserEventList.h"

class HTMLEventList : public AbstractUserEventList {
public:
    explicit HTMLEventList(const std::string &fileName) : AbstractUserEventList(fileName) {}

    void save() override;

    void displayEventList() override;

    static std::string eventToHTMLString(const Event &event);

};


#endif //A7_913_GABOR_IOANA_1_HTMLEVENTLIST_H
