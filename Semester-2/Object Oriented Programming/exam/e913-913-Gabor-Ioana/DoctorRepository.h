//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_DOCTORREPOSITORY_H
#define E913_913_GABOR_IOANA_DOCTORREPOSITORY_H


#include "Doctor.h"
#include <vector>

class DoctorRepository {
public:
    const std::vector<Doctor> &getAllDoctors() const;

    explicit DoctorRepository(const std::string &fileName);

private:
    std::string fileName;
    std::vector<Doctor> allDoctors;
public:

    void readFromFile();
};


#endif //E913_913_GABOR_IOANA_DOCTORREPOSITORY_H
