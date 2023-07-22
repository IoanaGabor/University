//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_HUMIDITYSENSOR_H
#define T2_913_GABOR_IOANA_1_HUMIDITYSENSOR_H


#include "Sensor.h"

class HumiditySensor: public Sensor{
public:
    HumiditySensor(const std::string &producer, const std::vector<double> &recordings);

private:
    bool sendAlert() override;

    double getPrice() override;

    std::string toString() override;

};


#endif //T2_913_GABOR_IOANA_1_HUMIDITYSENSOR_H
