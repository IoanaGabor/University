//
// Created by ioana on 12.05.2023.
//

#include "SmokeSensor.h"

SmokeSensor::SmokeSensor(const std::string &producer, const std::vector<double> &recordings) : Sensor(producer,
                                                                                                      recordings) {}

bool SmokeSensor::sendAlert() {
    for(auto &record:recordings){
        if(record > 1600){
            return true;
        }
    }
    return false;
}

double SmokeSensor::getPrice() {
    return 25;
}

std::string SmokeSensor::toString() {
    return "smoke " + Sensor::toString();
}
