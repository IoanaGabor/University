//
// Created by ioana on 26.05.2023.
//

#include "Controller.h"

Controller::Controller(Repository &repository) : repository(repository) {}

std::vector<Equation> Controller::getAllSortedEquations() {
    std::vector<Equation> allEq = repository.getAllEquations();
    sort(allEq.begin(), allEq.end(), [](Equation a, Equation b){
        if(a.degree() == b.degree()){
            return a < b;
        }
        return a.degree() > b.degree();
    });
    return allEq;
}

void Controller::updateEquationGivenByItsPosition(Equation equation, double a, double b, double c) {
    repository.updateEquation(equation, Equation(a,b,c));
}
