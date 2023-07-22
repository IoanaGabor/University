//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_TEMPERATURESENSOR_H
#define T2_913_GABOR_IOANA_1_TEMPERATURESENSOR_H


#include "Sensor.h"

class TemperatureSensor : public Sensor{
private:
    double diamenter;
public:
    TemperatureSensor(const std::string &producer, const std::vector<double> &recordings, double diamenter);

    bool sendAlert() override;

    double getPrice() override;
    std::string toString() override;
};


#endif //T2_913_GABOR_IOANA_1_TEMPERATURESENSOR_H
