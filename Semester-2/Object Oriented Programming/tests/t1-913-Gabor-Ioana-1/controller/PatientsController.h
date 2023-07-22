//
// Created by ioana on 28.04.2023.
//

#ifndef T1_913_GABOR_IOANA_1_PATIENTSCONTROLLER_H
#define T1_913_GABOR_IOANA_1_PATIENTSCONTROLLER_H


#include "Repository.h"

class PatientsController {
public:
    PatientsController();
    ~PatientsController()=default;
    void addPatient(std::string name,int age,bool infected,int roomNumber);
    void healPatient(std::string name);
    void updateInfectionStatus(std::string name);
    std::vector<Patient> getAllPatients();
private:
    Repository patientsRepository;
};


#endif //T1_913_GABOR_IOANA_1_PATIENTSCONTROLLER_H
