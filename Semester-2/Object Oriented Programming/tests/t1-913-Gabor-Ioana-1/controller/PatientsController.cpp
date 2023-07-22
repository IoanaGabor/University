//
// Created by ioana on 28.04.2023.
//

#include "PatientsController.h"
#include "GenericAppException.h"

PatientsController::PatientsController() {
    this->patientsRepository = Repository();
}

void PatientsController::addPatient(std::string name, int age, bool infected, int roomNumber) {
    ///adds a patient, given by name, age, infection status and room number
    ///throws GenericAppException if a patient with the same name already exists
    ///parameters: name (string), age(int), infected(bool), roomNumber(int)
    ///returns: -
    try {
        this->patientsRepository.addPatient(Patient(name, age, infected, roomNumber));
    } catch (std::exception &exception) {
        throw GenericAppException("Patient already exists");
    }
}

std::vector<Patient> PatientsController::getAllPatients() {
    return this->patientsRepository.getAllPatients();
}

void PatientsController::healPatient(std::string name) {
    ///Given a patient name, sets the infected status to false. If the patient does not exist, throws exception.
    ///parameters: name (string)
    ///returns: -
    try {
        Patient foundPatient = this->patientsRepository.getPatientByID(name);
        this->patientsRepository.updatePatient(
                Patient(foundPatient.getName(), foundPatient.getAge(), false, foundPatient.getRoomNumber()));
    } catch (std::exception &exception) {
        throw GenericAppException("Patient does not exist");
    }

}

void PatientsController::updateInfectionStatus(std::string name) {
    try {
        Patient foundPatient = this->patientsRepository.getPatientByID(name);
        this->patientsRepository.updatePatient(
                Patient(foundPatient.getName(), foundPatient.getAge(), true, foundPatient.getRoomNumber()));
        std::vector<Patient> allPatients = this->patientsRepository.getAllPatients();
        for (int i = 0; i < allPatients.size(); i++) {
            if (allPatients[i].getRoomNumber() == foundPatient.getRoomNumber() &&
                allPatients[i].getRoomNumber() == foundPatient.getRoomNumber() - 1 &&
                allPatients[i].getRoomNumber() == foundPatient.getRoomNumber() + 1) {
                this->patientsRepository.updatePatient(Patient(allPatients[i].getName(), allPatients[i].getAge(), true,
                                                               allPatients[i].getRoomNumber()));
            }
        }
    } catch (std::exception &exception) {
        throw GenericAppException("Patient does not exist");
    }

}
