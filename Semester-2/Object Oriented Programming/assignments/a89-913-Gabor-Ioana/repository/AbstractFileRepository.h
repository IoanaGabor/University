//
// Created by ioana on 30.04.2023.
//

#ifndef A7_913_GABOR_IOANA_1_ABSTRACTFILEREPOSITORY_H
#define A7_913_GABOR_IOANA_1_ABSTRACTFILEREPOSITORY_H


#include <algorithm>
#include <fstream>
#include "AbstractRepository.h"
#include "domain/AppExceptions.h"

template<class T>
class AbstractFileRepository : public AbstractRepository<T> {
protected:
    std::vector<T> entities;
    std::string fileName;
public:
    explicit AbstractFileRepository(const std::string &fileName);

    ~AbstractFileRepository() = default;

    void add(T element) override;

    void remove(std::string element_id) override;

    void update(T element) override;

    std::vector<T> getAllEntities() override;

    T getElementById(const std::string &elementId) override;

    void removeAll() override;

    bool isPresent(const std::string &elementId) override;

    virtual void load() = 0;

    virtual void save() = 0;

private:
    int findPosition(const std::string &elementId);

};

template<class T>
void AbstractFileRepository<T>::removeAll() {
    this->load();
    this->entities.clear();
    this->save();
}

template<class T>
AbstractFileRepository<T>::AbstractFileRepository(const std::string &fileName) {
    this->fileName = fileName;
    this->entities = std::vector<T>();
}

template<class T>
T AbstractFileRepository<T>::getElementById(const std::string &elementId) {
    this->load();
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    if (iteratorToFoundElement == entities.end()) {
        throw RepositoryException("element was not found!");
    }
    return *iteratorToFoundElement;
}


template<class T>
bool AbstractFileRepository<T>::isPresent(const std::string &elementId) {
    this->load();
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    return iteratorToFoundElement != entities.end();
}

template<class T>
std::vector<T> AbstractFileRepository<T>::getAllEntities() {
    this->load();
    return this->entities;
}

template<class T>
int AbstractFileRepository<T>::findPosition(const std::string &elementId) {
    this->load();
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    if (iteratorToFoundElement == entities.end()) {
        return -1;
    }
    return iteratorToFoundElement - entities.begin();
}

template<class T>
void AbstractFileRepository<T>::update(T element) {
    this->load();
    int position = this->findPosition(element.getId());
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    this->entities[position] = element;
    this->save();
}

template<class T>
void AbstractFileRepository<T>::remove(std::string element_id) {
    this->load();
    int position = this->findPosition(element_id);
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    std::swap(this->entities[position], this->entities[this->entities.size() - 1]);
    this->entities.pop_back();
    this->save();
}

template<class T>
void AbstractFileRepository<T>::add(T element) {
    this->load();
    int position = this->findPosition(element.getId());
    if (position != -1) {
        throw RepositoryException("the element already exists");
    }
    this->entities.push_back(element);
    this->save();
}


#endif //A7_913_GABOR_IOANA_1_ABSTRACTFILEREPOSITORY_H
