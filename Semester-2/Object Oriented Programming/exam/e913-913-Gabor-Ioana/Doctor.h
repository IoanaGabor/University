//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_DOCTOR_H
#define E913_913_GABOR_IOANA_DOCTOR_H


#include <string>

class Doctor {
public:
    Doctor(const std::string &name, const std::string &specialisation);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getSpecialisation() const;

    void setSpecialisation(const std::string &specialisation);

private:
    std::string name;
    std::string specialisation;
};

#endif //E913_913_GABOR_IOANA_DOCTOR_H
