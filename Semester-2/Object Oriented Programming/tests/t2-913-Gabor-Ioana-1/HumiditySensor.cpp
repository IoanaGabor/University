//
// Created by ioana on 12.05.2023.
//

#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(const std::string &producer, const std::vector<double> &recordings) : Sensor(producer,
                                                                                                            recordings) {}

bool HumiditySensor::sendAlert() {
    int count = 0;
    for(auto &record:recordings){
        if(record < 30){
            count ++;
        }
    }
    return count>=2;
}

double HumiditySensor::getPrice() {
    return 4;
}

std::string HumiditySensor::toString() {
    return "hum " + Sensor::toString();
}
