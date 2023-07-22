//
// Created by ioana on 12.05.2023.
//

#include "Sensor.h"

Sensor::Sensor(const std::string &producer, const std::vector<double> &recordings) : producer(producer),
                                                                                     recordings(recordings) {}

std::string Sensor::toString() {
    std::string stringRepresentation;
    stringRepresentation = "Producer: " + producer+ "Price: " + std::to_string(this->getPrice()) + " Recordings: ";
    for (auto record:recordings){
        stringRepresentation += std::to_string(record) + " ";
    }
    stringRepresentation += "Alerting: " + std::to_string(sendAlert());
    return stringRepresentation;
}

const std::string &Sensor::getProducer() const {
    return producer;
}
