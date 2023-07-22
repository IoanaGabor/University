//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_DEVICE_H
#define T2_913_GABOR_IOANA_1_DEVICE_H


#include "Sensor.h"

class Device {
public:
    Device();
    void addSensor(Sensor *sensor);
    const std::vector<Sensor *> &getAllSensors() const;
    std::vector<Sensor *> getAlertingSensors();
    void writeToFile(std::string fileName, std::vector<Sensor*> sensorToBeWritten);
    void writeToFileCheapSensors(std::string fileName, double maxPrice);
    std::vector<Sensor *> getCheapSensorsSortedByProducer(double maxPrice);
private:
    std::vector<Sensor*> allSensors;
};


#endif //T2_913_GABOR_IOANA_1_DEVICE_H
