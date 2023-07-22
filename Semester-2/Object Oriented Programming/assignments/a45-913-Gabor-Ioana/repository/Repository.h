//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_REPOSITORY_H
#define A45_913_GABOR_IOANA_REPOSITORY_H


#include <string>
#include "domain/DynamicVector.h"
#include "domain/AppExceptions.h"
template<class T>
class Repository {
private:
    DynamicVector<T> entities;
public:
    Repository();
    void add(T element);
    void remove(std::string element_id);
    void update(T element);
    DynamicVector<T> getAllEntities();
    T getElementById(const std:: string& elementId);
    bool isPresent(const std::string &elementId);
private:
    int findPosition(const std::string& element_id);

};

template<class T>
T Repository<T>::getElementById(const std::string& elementId) {
    for(int i=0;i<entities.getSize();i++){
        if(entities[i].getId() == elementId){
            return entities[i];
        }
    }
    throw RepositoryException("element was not found!");
}


template<class T>
bool Repository<T>::isPresent(const std::string& elementId) {
    for(int i=0;i<entities.getSize();i++){
        if(entities[i].getId() == elementId){
            return true;
        }
    }
    return false;
}

template<class T>
DynamicVector<T> Repository<T>::getAllEntities() {
    return this->entities;
}

template<class T>
Repository<T>::Repository() {
    this->entities = DynamicVector<T>(1);
}

template<class T>
int Repository<T>::findPosition(const std::string& element_id) {
    for(int i=0;i< this->entities.getSize();i++){
        if(this->entities[i].getId()==element_id){
            return i;
        }
    }
    return -1;
}

template<class T>
void Repository<T>::update(T element) {
    int position = this->findPosition(element.getId());
    if(position == -1){
        throw RepositoryException("the element does not exist");
    }
    this->entities[position] = element;

}

template<class T>
void Repository<T>::remove(std::string element_id) {
    int position = this->findPosition(element_id);
    if(position == -1){
        throw RepositoryException("the element does not exist");
    }
    std::swap(this->entities[position], this->entities[this->entities.getSize()-1]);
    this->entities.pop_back();
}

template<class T>
void Repository<T>::add(T element) {
    int position = this->findPosition(element.getId());
    if(position != -1){
        throw RepositoryException("the element already exists");
    }
    this->entities.add(element);
}


#endif //A45_913_GABOR_IOANA_REPOSITORY_H
