//
// Created by ioana on 28.04.2023.
//

#ifndef T1_913_GABOR_IOANA_1_PATIENT_H
#define T1_913_GABOR_IOANA_1_PATIENT_H


#include <string>

class Patient {
public:
    Patient(std::string name,int age,bool infected,int roomNumber);
    ~Patient() = default;
    std::string getName();
    std::string getID();
    int getAge();
    bool isInfected();
    int getRoomNumber();
    std::string toString();
private:
    std::string name;
    int age;
    bool infected;
    int roomNumber;
};


#endif //T1_913_GABOR_IOANA_1_PATIENT_H
