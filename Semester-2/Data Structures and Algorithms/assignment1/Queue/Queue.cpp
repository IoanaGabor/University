#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
    this->dynamicArray = new TElem[1];
    this->capacity = 1;
    this->size = 0;
    this->front = 0;
    this->back = 0;
}


void Queue::push(TElem elem) {
    /// time complexity: best case theta(1), worst case theta(n) (if the queue needs resizing)
    if (this->isResizingNeeded()) {
        this->resize();
    }
    this->dynamicArray[this->back] = elem;
    this->back = (this->back + 1) % this->capacity;
    this->size++;
}


TElem Queue::top() const {
    ///time complexity: theta(1)
    if (this->isEmpty()) {
        throw exception();
    }
    return this->dynamicArray[this->front];
}

TElem Queue::pop() {
    ///time complexity: theta(1)
    if (this->isEmpty()) {
        throw exception();
    }
    TElem popped_element = this->dynamicArray[this->front];
    this->front = (this->front + 1) % this->capacity;
    this->size--;
    return popped_element;
}

bool Queue::isEmpty() const {
    ///time complexity: theta(1)
    if (this->size == 0) {
        return true;
    }
    return false;
}

void Queue::resize() {
    ///time complexity: O(n), since the elements must be copied
    auto *newDynamicArray = new TElem[2 * this->capacity];
    int numberOfElementsInSecondPart = this->capacity - this->front;
    //cout<<"resize"<<this->front<<' '<<this->back<<'\n';
    for (int i = this->front; i < this->capacity; i++) {
        newDynamicArray[i - this->front] = this->dynamicArray[i];
      //  cout<<this->dynamicArray[i]<<' ';
    }
    for (int i = 0; i < this->back; i++) {
        newDynamicArray[numberOfElementsInSecondPart + i] = this->dynamicArray[i];
        //cout<<this->dynamicArray[i]<<' ';
    }
    //cout<<'\n';
    delete[] this->dynamicArray;
    this->dynamicArray = newDynamicArray;
    this->front = 0;
    this->back = this->size;
    this->capacity *= 2;
}

bool Queue::isResizingNeeded() const {
    ///time complexity: theta(1)
    if (this->capacity == this->size) {
        return true;
    }
    return false;
}

TElem Queue::popMiddle() {
    ///time complexity: theta(n)
    if (this->isEmpty()) {
        throw exception();
    }
    TElem middleElement;
    int indexOfTheMiddleElement;
    if(this->front<this->back){
        indexOfTheMiddleElement = (this->front + this->size / 2 ) % this->capacity;
        middleElement = this->dynamicArray[indexOfTheMiddleElement];
        for(int i=indexOfTheMiddleElement; i < this->back - 1; i++){
            this->dynamicArray[i] = this->dynamicArray[i+1];
        }
    }else {
        indexOfTheMiddleElement = (this->front + this->size / 2) % this->capacity;
        middleElement = this->dynamicArray[indexOfTheMiddleElement];
        if(indexOfTheMiddleElement < this->back) {
            for(int i=indexOfTheMiddleElement; i < this->back - 1; i++){
                this->dynamicArray[i] = this->dynamicArray[i+1];
            }
        }else{
            for(int i=indexOfTheMiddleElement; i < this->capacity - 1; i++){
                this->dynamicArray[i] = this->dynamicArray[i+1];
            }
            this->dynamicArray[this->capacity-1] = this->dynamicArray[0];
            for(int i=0;i<this->back-1;i++){
                this->dynamicArray[i] = this->dynamicArray[i+1];
            }
        }
    }
    this->size--;
    this->back = (this->back + this->capacity -1 )%this->capacity;
    return middleElement;
}


Queue::~Queue() {
    delete[] this->dynamicArray;
}


