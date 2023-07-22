//
// Created by ioana on 16.06.2023.
//

#include <fstream>
#include <sstream>
#include "PatientRepository.h"
#include "GenericException.h"

const std::vector<Patient> &PatientRepository::getAllPatients() const {
    return allPatients;
}

void PatientRepository::readFromFile() {
    std::ifstream inputStream(fileName);
    std::string line;
    std::string name;
    std::string diagnosis;
    std::string specialisation;
    std::string current_doctor;
    int admission_date;
    allPatients= std::vector<Patient>();
    while (getline(inputStream, line)) {
        std::istringstream parser(line);
        getline(parser, name, '|');
        getline(parser, diagnosis, '|');
        getline(parser, specialisation, '|');
        getline(parser, current_doctor, '|');
        parser >> admission_date;
        allPatients.emplace_back(name, diagnosis, specialisation, current_doctor, admission_date);
    }
    inputStream.close();
}

PatientRepository::PatientRepository(const std::string &fileName) : fileName(fileName) {
    readFromFile();
}

void PatientRepository::addPatient(Patient patient) {
    allPatients.push_back(patient);
}

void PatientRepository::updatePatientWithName(std::string name, Patient updatedPatient) {
    for(int i=0;i<allPatients.size();i++){
        if(allPatients[i].getName() == updatedPatient.getName()){
            allPatients[i] = updatedPatient;
        }
    }

}

Patient PatientRepository::getPatientByName(std::string name) {
    for(int i=0;i<allPatients.size();i++){
        if(allPatients[i].getName() == name){
            return allPatients[i];
        }
    }
    throw GenericException("dne");
}

void PatientRepository::writeToFile() {
    std::ofstream outputStream(fileName);
    for(auto patient: allPatients){
        outputStream<<patient.getName()<<'|'<<patient.getDiagnosis()<<'|'<<patient.getSpecialisation()<<'|'<<patient.getCurrentDoctor()<<'|'
                <<patient.getAdmissionDate()<<'\n';
    }
    outputStream.close();
}

PatientRepository::~PatientRepository() {
    writeToFile();
}

