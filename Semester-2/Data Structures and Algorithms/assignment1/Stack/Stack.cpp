#include "Stack.h"
#include <exception>

using namespace std;


Stack::Stack() {
    this->dynamicArray = new TElem[1];
    this->capacity = 1;
    this->size = 0;
}

void Stack::push(TElem e) {
    ///time complexity: best case theta(1), worst case theta(n) - when the array needs resizing
    if (this->isResizingNeeded()) {
        resize();
    }
    this->dynamicArray[this->size] = e;
    this->size++;
}

TElem Stack::top() const {
    ///time complexity: theta(1)
    if (this->isEmpty()) {
        throw exception();
    }
    return this->dynamicArray[size - 1];
}

TElem Stack::pop() {
    ///time complexity: theta(1)
    if (this->isEmpty()) {
        throw exception();
    }
    this->size--;
    return this->dynamicArray[size];
}


bool Stack::isEmpty() const {
    ///time complexity: theta(1)
    if (this->size == 0) {
        return true;
    }
    return false;
}

bool Stack::isResizingNeeded() const {
    ///time complexity: theta(1)
    return this->capacity == this->size;
}

void Stack::resize() {
    ///time complexity O(n)
    auto *new_array = new TElem[capacity * 2];
    for (int i = 0; i < size; i++) {
        new_array[i] = dynamicArray[i];
    }
    delete[] dynamicArray;
    dynamicArray = new_array;
    capacity *= 2;
}

Stack::~Stack() {
    delete[] this->dynamicArray;
}