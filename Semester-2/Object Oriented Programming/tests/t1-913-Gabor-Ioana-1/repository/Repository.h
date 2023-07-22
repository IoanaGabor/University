//
// Created by ioana on 28.04.2023.
//

#ifndef T1_913_GABOR_IOANA_1_REPOSITORY_H
#define T1_913_GABOR_IOANA_1_REPOSITORY_H

#include <vector>
#include "Patient.h"

class Repository {
public:
    void addPatient(Patient patient);
    void updatePatient(Patient patient);
    Patient getPatientByID(std::string id);
    std::vector<Patient> getAllPatients();
private:
    int getPositionOfPatient(std::string id);
    std::vector<Patient> allPatients;
};


#endif //T1_913_GABOR_IOANA_1_REPOSITORY_H
