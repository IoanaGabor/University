//
// Created by ioana on 16.06.2023.
//

#include "AbstractSubject.h"

void AbstractSubject::addObserver(AbstractObserver *newObserver) {
    allObservers.push_back(newObserver);
}

void AbstractSubject::notify() {
    for(auto observer: allObservers){
        observer->update();
    }
}
