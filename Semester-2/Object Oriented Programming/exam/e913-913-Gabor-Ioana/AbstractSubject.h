//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_ABSTRACTSUBJECT_H
#define E913_913_GABOR_IOANA_ABSTRACTSUBJECT_H


#include <vector>
#include "AbstractObserver.h"

class AbstractSubject {
private:
    std::vector<AbstractObserver*> allObservers;
public:
    void notify();
    void addObserver(AbstractObserver *newObserver);
};


#endif //E913_913_GABOR_IOANA_ABSTRACTSUBJECT_H
