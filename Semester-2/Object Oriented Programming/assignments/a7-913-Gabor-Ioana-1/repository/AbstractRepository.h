//
// Created by ioana on 30.04.2023.
//

#ifndef A7_913_GABOR_IOANA_1_ABSTRACTREPOSITORY_H
#define A7_913_GABOR_IOANA_1_ABSTRACTREPOSITORY_H

#include <vector>
#include <string>

template<class T>
class AbstractRepository {
public:
    virtual void add(T element) = 0;

    virtual void remove(std::string element_id) = 0;

    virtual void update(T element) = 0;

    virtual std::vector<T> getAllEntities() = 0;

    virtual T getElementById(const std::string &elementId) = 0;

    virtual bool isPresent(const std::string &elementId) = 0;
    virtual void removeAll() = 0;
};

#endif //A7_913_GABOR_IOANA_1_ABSTRACTREPOSITORY_H
