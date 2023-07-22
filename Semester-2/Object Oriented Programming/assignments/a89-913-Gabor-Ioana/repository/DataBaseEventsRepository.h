//
// Created by ioana on 04.05.2023.
//

#ifndef A7_913_GABOR_IOANA_1_DATABASEEVENTSREPOSITORY_H
#define A7_913_GABOR_IOANA_1_DATABASEEVENTSREPOSITORY_H


#include <sqlite3.h>
#include "domain/Event.h"
#include "AbstractRepository.h"

class DataBaseEventsRepository : public AbstractRepository<Event> {
public:
    explicit DataBaseEventsRepository(const std::string &fileName);

    ~DataBaseEventsRepository();

    void add(Event event) override;

    void remove(std::string element_id) override;

    void update(Event event) override;

    std::vector<Event> getAllEntities() override;

    Event getElementById(const std::string &elementId) override;

    bool isPresent(const std::string &elementId) override;

    void removeAll() override;

private:
    std::string fileName;
    sqlite3 *dataBase;
};


#endif //A7_913_GABOR_IOANA_1_DATABASEEVENTSREPOSITORY_H
