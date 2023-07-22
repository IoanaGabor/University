//
// Created by ioana on 26.05.2023.
//

#ifndef T3_913_GABOR_IOANA_REPOSITORY_H
#define T3_913_GABOR_IOANA_REPOSITORY_H
#include <string>
#include <vector>
#include "Equation.h"

class Repository {
private:
    std::string fileName;
    std::vector<Equation> allEquations;
public:
    explicit Repository(const std::string &fileName);
    void readFromFile();
    std::vector<Equation> getAllEquations();
    void updateEquation(Equation oldEquation, Equation newEquation);
};


#endif //T3_913_GABOR_IOANA_REPOSITORY_H
