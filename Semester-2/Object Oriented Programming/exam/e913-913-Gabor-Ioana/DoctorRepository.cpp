//
// Created by ioana on 16.06.2023.
//

#include <sstream>
#include <fstream>
#include "DoctorRepository.h"

void DoctorRepository::readFromFile() {
    std::ifstream inputStream(fileName);
    std::string line;
    std::string name;
    std::string specialisation;
    allDoctors= std::vector<Doctor>();
    while (getline(inputStream, line)) {
        std::istringstream parser(line);
        getline(parser, name, '|');
        getline(parser, specialisation, '|');
        allDoctors.push_back(Doctor(name, specialisation));
    }

}

DoctorRepository::DoctorRepository(const std::string &fileName) : fileName(fileName) {
    readFromFile();
}

const std::vector<Doctor> &DoctorRepository::getAllDoctors() const {
    return allDoctors;
}
