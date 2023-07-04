#pragma once

#include <vector>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue {
private:
    TElem *dynamicArray;
    int capacity;
    int size;
    int front;
    int back;

public:
    Queue();

    //pushes an element to the end of the queue
    void push(TElem e);

    //returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem top() const;

    //removes and returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem pop();

    //checks if the queue is empty
    bool isEmpty() const;

    //removes and returns the middle element of the queue (if the queue has an even number of elements
    // , either of the “two middle elements” can be removed.
    // throws an exception if the queue is empty

    TElem popMiddle();

    // destructor
    ~Queue();

private:
    void resize();

    bool isResizingNeeded() const;
};
