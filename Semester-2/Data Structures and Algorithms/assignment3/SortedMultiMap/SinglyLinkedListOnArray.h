//
// Created by ioana on 09.05.2023.
//

#ifndef SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAY_H
#define SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAY_H

#include <exception>
#include <iostream>
#include "SortedMultiMap.h"
#include "SinglyLinkedListOnArrayIterator.h"

template<class T>
class SinglyLinkedListOnArray {
    T *elements;
    int *next;
    int capacity;
    int head;
    int firstEmpty;
    int size;
public:
    friend class SinglyLinkedListOnArrayIterator<T>;

    explicit SinglyLinkedListOnArray(int initialCapacity);

    SinglyLinkedListOnArray(const SinglyLinkedListOnArray<T> &other);
    SinglyLinkedListOnArray<T>& operator=(const SinglyLinkedListOnArray<T>& other);
    void insertPosition(T element, int position);

    void addFirst(T element);

    SinglyLinkedListOnArrayIterator<T> iterator() const;

    bool isEmpty() const;

    bool deleteElement(T elem);

    int getSize();

    SinglyLinkedListOnArray();

    ~SinglyLinkedListOnArray();
};

template<class T>
SinglyLinkedListOnArray<T> &SinglyLinkedListOnArray<T>::operator=(const SinglyLinkedListOnArray<T> &other) {
    this->capacity = other.capacity;
    this->elements = new T[other.capacity];
    this->next = new int[other.capacity];
    this->head = other.head;
    this->firstEmpty = other.firstEmpty;
    for (int i = 0; i < this->capacity; i++) {
        this->next[i] = other.next[i];
        this->elements[i] = other.elements[i];
    }
    this->size = other.size;
    return *this;
}


template<class T>
int SinglyLinkedListOnArray<T>::getSize() {
    return this->size;
}

template<class T>
SinglyLinkedListOnArray<T>::~SinglyLinkedListOnArray() {
    delete[] elements;
    delete[] next;
}

template<class T>
bool SinglyLinkedListOnArray<T>::deleteElement(T elem) {
    ///best theta(1), average, worst theta(n), total O(n)
    int currentPosition = this->head;
    int previous = -1;
    while (currentPosition != -1 && this->elements[currentPosition] != elem) {
        previous = currentPosition;
        currentPosition = this->next[currentPosition];
    }
    if (currentPosition != -1) {
        if (currentPosition == this->head) {
            this->head = this->next[this->head];
        } else {
            this->next[previous] = this->next[currentPosition];
        }
        this->next[currentPosition] = this->firstEmpty;
        this->firstEmpty = currentPosition;
        this->size--;
        return true;
    } else {
        return false;
    }
}

template<class T>
bool SinglyLinkedListOnArray<T>::isEmpty() const {
    return this->head == -1;
}

template<class T>
void SinglyLinkedListOnArray<T>::addFirst(T element) {
    ///best theta(1), average, worst: theta(n), total: O(n)
    if (this->firstEmpty == -1) {
        T *newElements = new T[this->capacity * 2];
        int *newNext = new int[this->capacity * 2];
        for (int i = 0; i < this->capacity; i++) {
            newElements[i] = this->elements[i];
            newNext[i] = this->next[i];
        }
        for (int i = this->capacity; i < 2 * this->capacity - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[2 * this->capacity - 1] = -1;
        delete[] this->elements;
        delete[] this->next;
        this->elements = newElements;
        this->next = newNext;
        this->firstEmpty = this->capacity + 1;
        this->capacity = this->capacity * 2;
    }
    int newPosition = this->firstEmpty;
    this->elements[newPosition] = element;
    this->firstEmpty = this->next[this->firstEmpty];
    this->next[newPosition] = this->head;
    this->head = newPosition;
    this->size++;
}

template<class T>
SinglyLinkedListOnArrayIterator<T> SinglyLinkedListOnArray<T>::iterator() const {
    return SinglyLinkedListOnArrayIterator<T>(*this);
}

template<class T>
SinglyLinkedListOnArray<T>::SinglyLinkedListOnArray(const SinglyLinkedListOnArray<T> &other) {
    this->capacity = other.capacity;
    this->elements = new T[other.capacity];
    this->next = new int[other.capacity];
    this->head = other.head;
    this->firstEmpty = other.firstEmpty;
    for (int i = 0; i < this->capacity; i++) {
        this->next[i] = other.next[i];
        this->elements[i] = other.elements[i];
    }
    this->size = other.size;
}

template<class T>
SinglyLinkedListOnArray<T>::SinglyLinkedListOnArray() {
    this->capacity = 1;
    this->elements = new T[1];
    this->next = new int[1];
    this->head = -1;
    for (int i = 0; i < this->capacity - 2; i++) {
        this->next[i] = i + 1;
    }
    this->next[this->capacity - 1] = -1;
    this->firstEmpty = 0;
    this->size = 0;
}

template<class T>
void SinglyLinkedListOnArray<T>::insertPosition(T element, int position) {
    ///best case: theta(1), average case, worst case: theta(n), total complexity: O(n)
    if (position < 0) {
        throw std::exception();
    }
    if (this->firstEmpty == -1) {
        T *newElements = new T[this->capacity * 2];
        int *newNext = new int[this->capacity * 2];
        for (int i = 0; i < this->capacity; i++) {
            newElements[i] = this->elements[i];
            newNext[i] = this->next[i];
        }
        for (int i = this->capacity; i < 2 * this->capacity - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[2 * this->capacity - 1] = -1;
        delete[] this->elements;
        delete[] this->next;
        this->elements = newElements;
        this->next = newNext;
        this->firstEmpty = this->capacity + 1;
        this->capacity = this->capacity * 2;
    }
    if (position == 0) {
        int newPosition = this->firstEmpty;
        this->elements[newPosition] = element;
        this->firstEmpty = this->next[this->firstEmpty];
        this->next[newPosition] = this->head;
        this->head = newPosition;
    } else {
        int currentPosition = 0;
        int currentNode = this->head;
        while (currentNode != -1 && currentPosition < position - 1) {
            currentPosition++;
            currentNode = this->next[currentNode];
        }
        if (currentNode != -1) {
            int newPosition = this->firstEmpty;
            this->firstEmpty = this->next[this->firstEmpty];
            this->elements[newPosition] = element;
            this->next[newPosition] = this->next[currentNode];
            this->next[currentNode] = newPosition;
        } else {
            throw std::exception();
        }
    }
    this->size++;
}

template<class T>
SinglyLinkedListOnArray<T>::SinglyLinkedListOnArray(int initialCapacity) {
    ///theta(n)
    this->capacity = initialCapacity;
    this->elements = new T[initialCapacity];
    this->next = new int[initialCapacity];
    this->head = -1;
    for (int i = 0; i < this->capacity - 1; i++) {
        this->next[i] = i + 1;
    }
    this->next[this->capacity - 1] = -1;
    this->firstEmpty = 0;
    this->size = 0;
}


#endif //SORTEDMULTIMAP_SINGLYLINKEDLISTONARRAY_H
