//
// Created by ioana on 09.05.2023.
//

#ifndef SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAYITERATOR_H
#define SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAYITERATOR_H

#include "SinglyLinkedListOnArray.h"

template<class T>
class SinglyLinkedListOnArray;

template<class T>
class SinglyLinkedListOnArrayIterator {
    private:
        const SinglyLinkedListOnArray<T>& slla;
        int current;
        int size;
        int count;

public:
        SinglyLinkedListOnArrayIterator() = delete;
        explicit SinglyLinkedListOnArrayIterator(const SinglyLinkedListOnArray<T>& singlyLinkedListOnArray);
        friend class SinglyLinkedListOnArray<T>;
        void first();
        void next();
        bool valid() const;
        T getCurrent() const;
        int getCount() const;
        int getSize() const;
};

template<class T>
int SinglyLinkedListOnArrayIterator<T>::getSize() const {
    return size;
}

template<class T>
int SinglyLinkedListOnArrayIterator<T>::getCount() const {
    return count;
}

template<class T>
SinglyLinkedListOnArrayIterator<T>::SinglyLinkedListOnArrayIterator(const SinglyLinkedListOnArray<T>& singlyLinkedListOnArray) : slla(singlyLinkedListOnArray){
    current = singlyLinkedListOnArray.head;
    size = singlyLinkedListOnArray.size;
    count = 0;
}

template<class T>
T SinglyLinkedListOnArrayIterator<T>::getCurrent() const {
    if (current == -1){
        throw std::exception();
    }
    return slla.elements[current];
}

template<class T>
void SinglyLinkedListOnArrayIterator<T>::first() {
    current = slla.head;
    count = 0;
}

template<class T>
bool SinglyLinkedListOnArrayIterator<T>::valid() const {
    return count < size;
}

template<class T>
void SinglyLinkedListOnArrayIterator<T>::next() {
    if (!this->valid()){
        throw std::exception();
    }
    current = slla.next[current];
    count ++;
}


#endif //SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAYITERATOR_H
