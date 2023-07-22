//
// Created by ioana on 26.05.2023.
//

#ifndef T3_913_GABOR_IOANA_CONTROLLER_H
#define T3_913_GABOR_IOANA_CONTROLLER_H


#include "Repository.h"

class Controller {
private:
    Repository &repository;
public:
    explicit Controller(Repository &repository);
    std::vector<Equation> getAllSortedEquations();
    void updateEquationGivenByItsPosition(Equation equation, double a, double b, double c);
};


#endif //T3_913_GABOR_IOANA_CONTROLLER_H
