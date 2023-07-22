//
// Created by ioana on 28.04.2023.
//

#include "Repository.h"
#include "GenericAppException.h"

int Repository::getPositionOfPatient(std::string id) {
    for (int i=0;i<allPatients.size();i++){
        if(allPatients[i].getID() == id){
            return i;
        }
    }
    return -1;
}

void Repository::addPatient(Patient patient) {
    ///adds a patient
    ///throws GenericAppException if a patient with the same id already exists
    int position = getPositionOfPatient(patient.getID());
    if(position!=-1){
        throw std::exception();
    }else{
        allPatients.push_back(patient);
    }
}

void Repository::updatePatient(Patient patient){
    int position = getPositionOfPatient(patient.getID());
    if(position==-1){
        throw GenericAppException("this patient does not exist");
    }else{
        allPatients[position] = patient;
    }
}

std::vector<Patient> Repository::getAllPatients() {
    return this->allPatients;
}

Patient Repository::getPatientByID(std::string id) {
    int position = this->getPositionOfPatient(id);
    if(position==-1){
        throw std::exception();
    }
    return allPatients[position];
}

