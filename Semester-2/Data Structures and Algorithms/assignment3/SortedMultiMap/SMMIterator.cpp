#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap &d) :
        map(d),
        iterator(SinglyLinkedListOnArrayIterator<pair<TKey, SinglyLinkedListOnArray<TValue> *> >(*map.elements)) {
    ///theta(1)
    iterator.first();
    if(iterator.valid()){
        currentKey = iterator.getCurrent().first;
        currentValues = new SinglyLinkedListOnArrayIterator<int>(*iterator.getCurrent().second);
        currentValues->first();
        invalid = false;
    }else{
        invalid = true;
    }

}

void SMMIterator::first() {
    ///theta(1)
    //TODO - Implementation
    iterator.first();
    if(iterator.valid()){
        currentKey = iterator.getCurrent().first;
        currentValues = new SinglyLinkedListOnArrayIterator<int>(*iterator.getCurrent().second);
        currentValues->first();
        invalid = false;
    }else{
        invalid = true;
    }
}

void SMMIterator::next() {
    ///theta(1)
    //TODO - Implementation
    if (!iterator.valid()) {
        throw std::exception();
    }
    currentValues->next();
    if (!currentValues->valid()){
        iterator.next();
        if(iterator.valid()) {
            currentKey = iterator.getCurrent().first;
            delete currentValues;
            currentValues = new SinglyLinkedListOnArrayIterator<int>(*iterator.getCurrent().second);
            currentValues->first();
        }else{
            delete currentValues;
            invalid =true;
        }
    }
}

bool SMMIterator::valid() const {
    ///theta(1)
    //TODO - Implementation
    if (!invalid ) {
        return true;
    }
    return false;
}

TElem SMMIterator::getCurrent() const {
    ///theta(1)
    if(!this->valid()){
        throw std::exception();
    }
    //TODO - Implementation
    return {currentKey,currentValues->getCurrent()};
}


