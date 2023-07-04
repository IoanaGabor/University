#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

SortedMultiMap::SortedMultiMap(const SortedMultiMap &map) {
    this->relation = map.relation;
    this->elements = map.elements;
}

SortedMultiMap::SortedMultiMap(Relation r) {
    this->relation = r;
    this->elements = new SinglyLinkedListOnArray<pair<TKey, SinglyLinkedListOnArray<TValue> *>>(5);
    this->count = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
    ///best case theta(1), average, worst: theta(n), total: O(n)
    auto iterator = this->elements->iterator();
    bool foundKey = false;
    int position = 0;
    while (iterator.valid()) {
        auto keyValues = iterator.getCurrent();
        auto key = keyValues.first;
        auto values = keyValues.second;
        if (key == c) {
            keyValues.second->addFirst(v);
            this->count++;
            foundKey = true;
            break;
        }
        if (!this->relation(key, c)) {
            break;
        }
        iterator.next();
        position++;
    }
    if (!foundKey) {
        auto newValues = new SinglyLinkedListOnArray<TValue>(3);
        newValues->addFirst(v);
        this->elements->insertPosition(make_pair(c, newValues), position);
        this->count++;
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    ///best case: theta(1), average, worst: theta(n), total: O(n)
    //TODO - Implementation
    auto iterator = this->elements->iterator();
    vector<TValue> foundValues;
    while (iterator.valid()) {
        auto keyValues = iterator.getCurrent();
        auto key = keyValues.first;
        auto values = keyValues.second;
        if (key == c) {
            auto valuesIterator = values->iterator();
            while (valuesIterator.valid()) {
                auto currentValue = valuesIterator.getCurrent();
                foundValues.push_back(currentValue);
                valuesIterator.next();
            }
        }
        if (!this->relation(key, c)) {
            break;
        }
        iterator.next();
    }

    return foundValues;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    ///best case: theta(1), average, worst: theta(n), total: O(n)
    //TODO - Implementation
    auto iterator = this->elements->iterator();
    bool foundKey = false;
    pair<TKey, SinglyLinkedListOnArray<TValue> *> keyValues;
    TKey key;
    SinglyLinkedListOnArray<TValue> *values;
    while (iterator.valid()) {
        keyValues = iterator.getCurrent();
        key = keyValues.first;
        values = keyValues.second;
        if (key == c) {
            foundKey = true;
            break;
        }
        if (!this->relation(key, c)) {
            break;
        }
        iterator.next();
    }
    if (foundKey){
        bool deletedValue = values->deleteElement(v);
        if(deletedValue){
            if(values->isEmpty()){
                this->elements->deleteElement({key, values});
                delete values;
            }
            this->count--;
            return true;
        }
    }
    return false;
}


int SortedMultiMap::size() const {
    ///theta(1)
    //TODO - Implementation
    return this->count;
}

bool SortedMultiMap::isEmpty() const {
    ///theta(1)
    return this->elements->isEmpty();
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    ///theta(n)
    //TODO - Implementation
    auto iterator = this->elements->iterator();
    while (iterator.valid()) {
        auto keyValues = iterator.getCurrent();
        auto key = keyValues.first;
        auto values = keyValues.second;
        iterator.next();
        delete values;
    }
    delete this->elements;
}

int SortedMultiMap::keysComparator(pair<TKey, SinglyLinkedListOnArray<TValue>*> alpha, pair<TKey, SinglyLinkedListOnArray<TValue>*> beta) {
    if (alpha.first == beta.first){
        return 0;
    }
    if (alpha.first < beta.first){
        return -1;
    }else{
        return 1;
    }
}
