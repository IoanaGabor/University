//
// Created by ioana on 16.06.2023.
//

#include "Patient.h"

Patient::Patient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
                 const std::string &currentDoctor, int admissionDate) : name(name), diagnosis(diagnosis),
                                                                        specialisation(specialisation),
                                                                        current_doctor(currentDoctor),
                                                                        admission_date(admissionDate) {}

const std::string &Patient::getName() const {
    return name;
}

void Patient::setName(const std::string &name) {
    Patient::name = name;
}

const std::string &Patient::getDiagnosis() const {
    return diagnosis;
}

void Patient::setDiagnosis(const std::string &diagnosis) {
    Patient::diagnosis = diagnosis;
}

const std::string &Patient::getSpecialisation() const {
    return specialisation;
}

void Patient::setSpecialisation(const std::string &specialisation) {
    Patient::specialisation = specialisation;
}

const std::string &Patient::getCurrentDoctor() const {
    return current_doctor;
}

void Patient::setCurrentDoctor(const std::string &currentDoctor) {
    current_doctor = currentDoctor;
}

int Patient::getAdmissionDate() const {
    return admission_date;
}

void Patient::setAdmissionDate(int admissionDate) {
    admission_date = admissionDate;
}
