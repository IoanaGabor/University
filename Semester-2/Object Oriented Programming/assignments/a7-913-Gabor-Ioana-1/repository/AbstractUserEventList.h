//
// Created by ioana on 04.05.2023.
//

#ifndef A7_913_GABOR_IOANA_1_ABSTRACTUSEREVENTLIST_H
#define A7_913_GABOR_IOANA_1_ABSTRACTUSEREVENTLIST_H


#include "domain/Event.h"
#include "repository/AbstractFileRepository.h"

class AbstractUserEventList : public AbstractFileRepository<Event> {
    void load() override;

public:
    explicit AbstractUserEventList(const std::string &fileName) : AbstractFileRepository<Event>(fileName) {}

    virtual void displayEventList() = 0;
};


#endif //A7_913_GABOR_IOANA_1_ABSTRACTUSEREVENTLIST_H
