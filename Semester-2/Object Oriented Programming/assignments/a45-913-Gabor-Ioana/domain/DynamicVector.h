//
// Created by ioana on 30.03.2023.
//
#pragma once

#include <algorithm>
#include "AppExceptions.h"

const int RESIZING_FACTOR = 2;
const int DEFAULT_INITIAL_CAPACITY = 1;

template<class T>
class DynamicVector {
private:
    int capacity, size;
    T *elements;
public:
    DynamicVector();

    DynamicVector(int capacity);

    ~DynamicVector();

    DynamicVector(const DynamicVector &other);

    DynamicVector &operator=(const DynamicVector &other);

    T &operator[](unsigned int position);

    void add(T new_element);

    void pop_back();

    int getSize();

private:
    void resize(int new_capacity);
};

template<class T>
void DynamicVector<T>::pop_back() {
    if (this->size == 0) {
        throw DynamicVectorException("cannot pop from empty vector");
    }
    this->size--;
}

template<class T>
T &DynamicVector<T>::operator[](unsigned int position) {
    if (position >= this->size) {
        throw DynamicVectorException("index out of bounds");
    }
    return this->elements[position];
}

template<class T>
DynamicVector<T>::DynamicVector() {
    this->size = 0;
    this->capacity = DEFAULT_INITIAL_CAPACITY;
    this->elements = new T[DEFAULT_INITIAL_CAPACITY];
}

template<class T>
DynamicVector<T>::~DynamicVector() {
    delete[] this->elements;
}

template<class T>
DynamicVector<T>::DynamicVector(const DynamicVector &other) {
    this->size = other.size;
    this->capacity = other.capacity;
    this->elements = new T[other.capacity];
    for (int i = 0; i < this->size; i++) {
        this->elements[i] = other.elements[i];
    }
}

template<class T>
DynamicVector<T>::DynamicVector(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->elements = new T[capacity];
}

template<class T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector &other) {
    this->capacity = other.capacity;
    this->size = other.size;
    delete[] this->elements;
    this->elements = new T[other.capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->elements[i] = other.elements[i];
    }
    return *this;
}

template<class T>
void DynamicVector<T>::resize(int new_capacity) {
    if (new_capacity < 0) {
        new_capacity = 0;
    }
    this->capacity = new_capacity;
    T *new_elements = new T[new_capacity];
    for (int i = 0; i < std::min(new_capacity, this->size); i++) {
        new_elements[i] = this->elements[i];
    }
    this->size = std::min(this->size, new_capacity);
    delete[] this->elements;
    this->elements = new_elements;
}

template<class T>
void DynamicVector<T>::add(T new_element) {
    if (this->capacity == this->size) {
        this->resize(this->capacity * RESIZING_FACTOR);
    }
    this->elements[this->size] = new_element;
    this->size++;
}

template<class T>
int DynamicVector<T>::getSize() {
    return this->size;
}