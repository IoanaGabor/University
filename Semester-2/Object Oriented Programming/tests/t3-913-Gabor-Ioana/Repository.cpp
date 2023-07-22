
//
// Created by ioana on 26.05.2023.
//

#include <fstream>
#include <sstream>
#include "Repository.h"

Repository::Repository(const std::string &fileName) : fileName(fileName) {
    readFromFile();
}

void Repository::readFromFile() {
    std::ifstream inputStream(fileName);
    std::string line;
    double a,b,c;
    allEquations = std::vector<Equation>();
    while(getline(inputStream, line)){
        std::istringstream parser(line);
        parser>>a;
        parser.get();
        parser>>b;
        parser.get();
        parser>>c;
        allEquations.push_back(Equation(a,b,c));
    }
}

std::vector<Equation> Repository::getAllEquations(){
    return allEquations;
}

void Repository::updateEquation(Equation oldEquation, Equation newEquation) {
    for(int i=0;i<allEquations.size();i++){
        if(allEquations[i] == oldEquation){
            allEquations[i] = newEquation;
        }
    }
}
