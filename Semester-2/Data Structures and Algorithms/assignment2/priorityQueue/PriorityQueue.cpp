
#include "PriorityQueue.h"
#include <exception>

struct PriorityQueue::DLLNode {
    Element element;
    PNode next;
    PNode previous;

    DLLNode(TElem e, TPriority p, PNode n, PNode prev);
};

PriorityQueue::DLLNode::DLLNode(TElem e, TPriority p, PNode n, PNode prev) {
    element.first = e;
    element.second = p;
    next = n;
    previous = prev;
}


PriorityQueue::PriorityQueue(Relation r) {
    this->relation = r;
    head = tail = nullptr;
}


void PriorityQueue::push(TElem e, TPriority p) {
    ///best case: theta(1), average case, worst case: theta(n), overall O(n)
    PNode newNode = new DLLNode(e, p, nullptr, nullptr);
    if (this->isEmpty()) {
        head = tail = newNode;
    } else {
        if (this->relation(newNode->element.second, head->element.second)) {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        } else if (this->relation(tail->element.second, newNode->element.second)) {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        } else {
            PNode currentNode = head;
            while (currentNode != nullptr && this->relation(currentNode->element.second, newNode->element.second)) {
                currentNode = currentNode->next;
            }
            currentNode->previous->next = newNode;
            newNode->previous = currentNode->previous;
            newNode->next = currentNode;
            currentNode->previous = newNode;
        }
    }
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
    ///best case, average case, worst case, overall: theta(1)
    if (isEmpty()) {
        throw exception();
    }
    return head->element;
}

Element PriorityQueue::pop() {
    ///best case, average case, worst case, overall: theta(1)
    if (isEmpty()) {
        throw exception();
    }
    Element value = head->element;
    if (head->next == nullptr) {
        delete head;
        head = tail = nullptr;
    } else {
        PNode newHead = head->next;
        delete head;
        head = newHead;
    }
    return value;
}

bool PriorityQueue::isEmpty() const {
    ///best case, average case, worst case, overall: theta(1)
    if (head == nullptr) {
        return true;
    }
    return false;
}


PriorityQueue::~PriorityQueue() {
    ///best case, average case, worst case, overall: theta(n)
    PNode currentNode = head;
    PNode nextNode;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = tail = nullptr;
}

TPriority PriorityQueue::increasePriority(TElem elem, TPriority newPriority) {
    ///best case: theta(1), average case: theta(n), worst case: theta(n), total complexity: O(n)
    ///search for the node
    PNode currentNode = tail;
    while (currentNode != nullptr) {
        if (currentNode->element.first == elem) {
            break;
        }
        currentNode = currentNode->previous;
    }
    ///if not found
    if (currentNode == nullptr) {
        return -1;
    }
    ///if its priority is greater than the new one
    if (this->relation(currentNode->element.second, newPriority)) {
        throw exception();
    }
    PNode foundNode = currentNode;
    int oldPriority = foundNode->element.second;
    foundNode->element.second=newPriority;
    ///if it is head, we dont change its position, else
    if(foundNode->previous!= nullptr){
        if (foundNode->next == nullptr){
            ///if it is tail, we change the tail
            tail = tail->previous;
            tail->next = nullptr;
        }else{
            foundNode->previous->next = foundNode->next;
            foundNode->next->previous = foundNode->previous;
        }
        currentNode = foundNode->previous; ///we search for the position in which to be inserted
        while (currentNode != nullptr) {
            if (!this->relation(newPriority, currentNode->element.second)) {
                break;
            }
            currentNode = currentNode->previous;
        }
        if (currentNode == nullptr) {
            ///if the element will be the new head, we need to update the head
            foundNode->next = head;
            head->previous = foundNode;
            head = foundNode;
            foundNode->previous = nullptr;
        } else {
            foundNode->next = currentNode->next;
            currentNode->next->previous = foundNode;
            currentNode->next = foundNode;
            foundNode->previous = currentNode;
        }
    }
    return oldPriority;
}

