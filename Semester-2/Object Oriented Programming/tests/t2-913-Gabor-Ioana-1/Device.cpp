//
// Created by ioana on 12.05.2023.
//

#include <fstream>
#include <algorithm>
#include "Device.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "SmokeSensor.h"


const std::vector<Sensor *> &Device::getAllSensors() const {
    return allSensors;
}

std::vector<Sensor *> Device::getAlertingSensors() {
    std::vector<Sensor*> alertingSensors;
    for(auto sensor:allSensors){
        if(sensor->sendAlert()){
            alertingSensors.push_back(sensor);
        }
    }
    return alertingSensors;
}

void Device::writeToFile(std::string fileName, std::vector<Sensor*> sensorToBeWritten) {
    std::ofstream fileOutputStream(fileName);
    for(auto sensor: sensorToBeWritten){
        fileOutputStream<<sensor->toString()<<'\n';
    }
}

void Device::addSensor(Sensor *sensor) {
    allSensors.push_back(sensor);
}

Device::Device() {
    allSensors = std::vector<Sensor*>();
    allSensors.push_back(new TemperatureSensor("napoca", std::vector<double>({3,3,23}),2));
    allSensors.push_back(new HumiditySensor("wadas", std::vector<double>({3,3212,23})));
    allSensors.push_back(new SmokeSensor("smoking", std::vector<double>({3,3321,23})));
    allSensors.push_back(new TemperatureSensor("asdfnapoca", std::vector<double>({3,3,23}),2));
    allSensors.push_back(new HumiditySensor("cswadas", std::vector<double>({3,3212,23})));
    allSensors.push_back(new SmokeSensor("bdssmoking", std::vector<double>({3,3321,23})));
}

std::vector<Sensor *> Device::getCheapSensorsSortedByProducer(double maxPrice) {
    std::vector<Sensor*> cheapSensors;
    for(auto sensor:allSensors){
        if(sensor->getPrice() < maxPrice){
            cheapSensors.push_back(sensor);
        }
    }
    std::sort(cheapSensors.begin(), cheapSensors.end(),[](Sensor* first, Sensor* second){
        return first->getProducer() < second->getProducer();
    });
    return cheapSensors;
}

void Device::writeToFileCheapSensors(std::string fileName, double maxPrice) {
    std::vector<Sensor*> cheapSensors = getCheapSensorsSortedByProducer(maxPrice);
    writeToFile(fileName, cheapSensors);
}

