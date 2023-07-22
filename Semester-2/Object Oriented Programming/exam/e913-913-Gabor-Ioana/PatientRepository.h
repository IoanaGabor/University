//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_PATIENTREPOSITORY_H
#define E913_913_GABOR_IOANA_PATIENTREPOSITORY_H


#include <vector>
#include "Patient.h"

class PatientRepository {
public:
    explicit PatientRepository(const std::string &fileName);

private:
    std::string fileName;
    std::vector<Patient> allPatients;
public:
    const std::vector<Patient> &getAllPatients() const;
    void addPatient(Patient patient);
    void updatePatientWithName(std::string name, Patient updatedPatient);
    Patient getPatientByName(std::string name);
    void readFromFile();
    void writeToFile();

    virtual ~PatientRepository();

};


#endif //E913_913_GABOR_IOANA_PATIENTREPOSITORY_H
