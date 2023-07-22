//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_SMOKESENSOR_H
#define T2_913_GABOR_IOANA_1_SMOKESENSOR_H


#include "Sensor.h"

class SmokeSensor : public Sensor{
public:
    bool sendAlert() override;

    double getPrice() override;

    std::string toString() override;

    SmokeSensor(const std::string &producer, const std::vector<double> &recordings);
};


#endif //T2_913_GABOR_IOANA_1_SMOKESENSOR_H
