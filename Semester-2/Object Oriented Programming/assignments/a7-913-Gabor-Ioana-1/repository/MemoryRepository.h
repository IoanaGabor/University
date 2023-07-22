//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_REPOSITORY_H
#define A45_913_GABOR_IOANA_REPOSITORY_H


#include <string>
#include <vector>
#include <algorithm>
#include "domain/AppExceptions.h"
#include "AbstractRepository.h"

template<class T>
class MemoryRepository : public AbstractRepository<T> {
private:
    std::vector<T> entities;
public:
    MemoryRepository();

    void add(T element) override;

    void remove(std::string element_id) override;

    void update(T element) override;

    std::vector<T> getAllEntities() override;

    T getElementById(const std::string &elementId) override;

    bool isPresent(const std::string &elementId) override;

    void removeAll() override;

private:
    int findPosition(const std::string &elementId);

};

template<class T>
T MemoryRepository<T>::getElementById(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    if (iteratorToFoundElement == entities.end()) {
        throw RepositoryException("element was not found!");
    }
    return *iteratorToFoundElement;
}


template<class T>
bool MemoryRepository<T>::isPresent(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    return iteratorToFoundElement != entities.end();
}

template<class T>
std::vector<T> MemoryRepository<T>::getAllEntities() {
    return this->entities;
}

template<class T>
MemoryRepository<T>::MemoryRepository() {
    this->entities = std::vector<T>();
}

template<class T>
int MemoryRepository<T>::findPosition(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin(), entities.end(),
                                               [&elementId](T element) { return element.getId() == elementId; });
    if (iteratorToFoundElement == entities.end()) {
        return -1;
    }
    return iteratorToFoundElement - entities.begin();
}

template<class T>
void MemoryRepository<T>::update(T element) {
    int position = this->findPosition(element.getId());
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    this->entities[position] = element;

}

template<class T>
void MemoryRepository<T>::remove(std::string element_id) {
    int position = this->findPosition(element_id);
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    std::swap(this->entities[position], this->entities[this->entities.size() - 1]);
    this->entities.pop_back();
}

template<class T>
void MemoryRepository<T>::add(T element) {
    int position = this->findPosition(element.getId());
    if (position != -1) {
        throw RepositoryException("the element already exists");
    }
    this->entities.push_back(element);
}


template<class T>
void MemoryRepository<T>::removeAll() {
    this->entities.clear();
}


#endif //A45_913_GABOR_IOANA_REPOSITORY_H
