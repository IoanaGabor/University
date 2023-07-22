//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_PATIENT_H
#define E913_913_GABOR_IOANA_PATIENT_H


#include <string>

class Patient {
    std::string name;
    std::string diagnosis;
    std::string specialisation;
    std::string current_doctor;
    int admission_date;
public:
    Patient(const std::string &name, const std::string &diagnosis, const std::string &specialisation,
            const std::string &currentDoctor, int admissionDate);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getDiagnosis() const;

    void setDiagnosis(const std::string &diagnosis);

    const std::string &getSpecialisation() const;

    void setSpecialisation(const std::string &specialisation);

    const std::string &getCurrentDoctor() const;

    void setCurrentDoctor(const std::string &currentDoctor);

    int getAdmissionDate() const;

    void setAdmissionDate(int admissionDate);
};


#endif //E913_913_GABOR_IOANA_PATIENT_H
