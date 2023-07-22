//
// Created by ioana on 12.05.2023.
//

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const std::string &producer, const std::vector<double> &recordings,
                                     double diamenter) : Sensor(producer, recordings), diamenter(diamenter) {}

bool TemperatureSensor::sendAlert() {
    int count = 0;
    for(auto &record:recordings){
        if(record > 35){
            count ++;
        }
    }
    return count>=2;
}

double TemperatureSensor::getPrice() {
    double initial_price = 9;
    if(diamenter < 3){
        initial_price += 8;
    }
    return initial_price;
}

std::string TemperatureSensor::toString() {
    return "Temperature: diameter" + std::to_string(diamenter)+ Sensor::toString();
}
