//
// Created by ioana on 02.05.2023.
//

#ifndef A7_913_GABOR_IOANA_1_CSVEVENTLIST_H
#define A7_913_GABOR_IOANA_1_CSVEVENTLIST_H

#include "AbstractRepository.h"
#include "domain/Event.h"
#include "AbstractFileRepository.h"
#include "AbstractUserEventList.h"

class CSVEventList : public AbstractUserEventList {
public:
    explicit CSVEventList(const std::string &fileName) : AbstractUserEventList(fileName) {}

    void save() override;

    void displayEventList() override;

    static std::string eventToCSVString(const Event &event);
};


#endif //A7_913_GABOR_IOANA_1_CSVEVENTLIST_H
