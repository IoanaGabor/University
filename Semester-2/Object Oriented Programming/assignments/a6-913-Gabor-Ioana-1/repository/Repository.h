//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_REPOSITORY_H
#define A45_913_GABOR_IOANA_REPOSITORY_H


#include <string>
#include <vector>
#include <algorithm>
#include "domain/AppExceptions.h"

template<class T>
class Repository {
private:
    std::vector<T> entities;
public:
    Repository();

    void add(T element);

    void remove(std::string element_id);

    void update(T element);

    std::vector<T> getAllEntities();

    T getElementById(const std::string &elementId);

    bool isPresent(const std::string &elementId);

private:
    int findPosition(const std::string &element_id);

};

template<class T>
T Repository<T>::getElementById(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin()
                 , entities.end(),
                 [&elementId](T element) { return element.getId() == elementId; });
    if(iteratorToFoundElement==entities.end()){
        throw RepositoryException("element was not found!");
    }
    return *iteratorToFoundElement;
}


template<class T>
bool Repository<T>::isPresent(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin()
            , entities.end(),
            [&elementId](T element) { return element.getId() == elementId; });
    return iteratorToFoundElement != entities.end();
}

template<class T>
std::vector<T> Repository<T>::getAllEntities() {
    return this->entities;
}

template<class T>
Repository<T>::Repository() {
    this->entities = std::vector<T>();
}

template<class T>
int Repository<T>::findPosition(const std::string &elementId) {
    auto iteratorToFoundElement = std::find_if(entities.begin()
            , entities.end(),
            [&elementId](T element) { return element.getId() == elementId; });
    if(iteratorToFoundElement==entities.end()){
        return -1;
    }
    return iteratorToFoundElement - entities.begin();
}

template<class T>
void Repository<T>::update(T element) {
    int position = this->findPosition(element.getId());
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    this->entities[position] = element;

}

template<class T>
void Repository<T>::remove(std::string element_id) {
    int position = this->findPosition(element_id);
    if (position == -1) {
        throw RepositoryException("the element does not exist");
    }
    std::swap(this->entities[position], this->entities[this->entities.size() - 1]);
    this->entities.pop_back();
}

template<class T>
void Repository<T>::add(T element) {
    int position = this->findPosition(element.getId());
    if (position != -1) {
        throw RepositoryException("the element already exists");
    }
    this->entities.push_back(element);
}


#endif //A45_913_GABOR_IOANA_REPOSITORY_H
