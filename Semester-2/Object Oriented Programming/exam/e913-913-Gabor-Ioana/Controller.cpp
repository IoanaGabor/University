//
// Created by ioana on 16.06.2023.
//

#include <ctime>
#include "Controller.h"
#include "GenericException.h"
#include "Doctor.h"

Controller::Controller(PatientRepository *patientRepository) : patientRepository(patientRepository) {}

std::vector<Patient> Controller::getPatientsWithSpecialisationOrUndiagnosed(std::string specialisation) {
    std::vector<Patient> returnedPatients = std::vector<Patient>();
    for(auto patient: patientRepository->getAllPatients()){
        if(patient.getSpecialisation() == specialisation || patient.getDiagnosis() == "undiagnosed"){
            returnedPatients.push_back(patient);
        }
    }
    sort(returnedPatients.begin(),returnedPatients.end(),[](Patient a, Patient b){
        return a.getAdmissionDate() < b.getAdmissionDate();
    });
    return returnedPatients;
}

std::vector<Patient> Controller::getPatientsWithCurrentDoctor(std::string doctorName) {
    std::vector<Patient> returnedPatients = std::vector<Patient>();
    for(auto patient: patientRepository->getAllPatients()){
        if(patient.getCurrentDoctor() == doctorName){
            returnedPatients.push_back(patient);
        }
    }
    sort(returnedPatients.begin(),returnedPatients.end(),[](Patient a, Patient b){
        return a.getAdmissionDate() < b.getAdmissionDate();
    });
    return returnedPatients;
}

void Controller::addPatient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
                            const std::string &currentDoctor, int admissionDate) {
    if(name.empty()){
        throw GenericException("name is empty");
    }
    auto t = std::time(0);
    auto now = std::localtime(&t);
    if(admissionDate < now->tm_mday){
        throw GenericException("admission in the past");
    }
    patientRepository->addPatient(Patient(
            name,
            diagnosis,
            specialisation,
            currentDoctor,
            admissionDate
            ));
}

void Controller::updatePatient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
                               Doctor doctor) {
    Patient p = patientRepository->getPatientByName(name);
    Patient newp = p;
    if(p.getDiagnosis()=="undiagnosed" || p.getCurrentDoctor() == doctor.getName()){
        if(diagnosis == "undiagnosed"){
            throw GenericException("not allowed to update to undiag");
        }
        if(specialisation != doctor.getSpecialisation()){
            newp.setCurrentDoctor(doctor.getName());
        }
        newp.setSpecialisation(specialisation);
        newp.setDiagnosis(diagnosis);
        patientRepository->updatePatientWithName(p.getName(), newp);
    }else{
        throw GenericException("not allowed to update this patient");
    }
}

std::map<std::string, int> Controller::getStatisticsMap(){
    std::map<std::string, int> mp;
    for(auto &patient :patientRepository->getAllPatients()){
        mp[patient.getSpecialisation()]++;
    }
    return mp;
}