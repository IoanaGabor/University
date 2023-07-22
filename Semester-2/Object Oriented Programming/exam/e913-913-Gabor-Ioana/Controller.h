//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_CONTROLLER_H
#define E913_913_GABOR_IOANA_CONTROLLER_H


#include <map>
#include "AbstractSubject.h"
#include "PatientRepository.h"
#include "Doctor.h"

class Controller : public AbstractSubject{
    PatientRepository *patientRepository;
public:
    explicit Controller(PatientRepository *patientRepository);
    std::vector<Patient> getPatientsWithSpecialisationOrUndiagnosed(std::string specialisation);
    std::vector<Patient> getPatientsWithCurrentDoctor(std::string doctorName);
    void addPatient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
                    const std::string &currentDoctor, int admissionDate);
    void updatePatient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
                       Doctor doctor);
    std::map<std::string, int> getStatisticsMap();
};


#endif //E913_913_GABOR_IOANA_CONTROLLER_H
