//
// Created by ioana on 12.05.2023.
//

#include <iostream>
#include "ConsoleUI.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "SmokeSensor.h"

ConsoleUI::ConsoleUI() {
    device = Device();
}

void ConsoleUI::run() {
    std::string command;
    while (true){
        std::cout<<"commands\n";
        std::cout<<"1. add\n";
        std::cout<<"2. show all\n";
        std::cout<<"3. show alerting\n";
        std::cout<<"4. save to file\n";
        getline(std::cin, command);
        if(command == ADD_COMMAND){
            this->handleAddSensor();
        }else if(command == SHOW_ALL_COMMAND){
            this->handleShowAllSensors();
        }else if(command == "3"){
            this->handleShowAlertingSensors();
        }else if(command == "4"){
            this->handleSaveToFile();
        }else if(command == "0"){
            break;
        }else{
            std::cout<<"invalid";
        }
    }
}

void ConsoleUI::handleAddSensor() {
    std::string producer;
    int countRecordings;
    std::vector<double> recordings;
    double recording;
    std::string type;
    std::cout<<"Type:\n";
    getline(std::cin, type);
    std::cout<<"nb of rec\n";
    std::cin>>countRecordings;
    if(countRecordings <=0){
        std::cin.get();
        std::cout<<"invalid" <<'\n';
        return;
    }
    for(int i=0;i<countRecordings;i++){
        std::cout<<"Recording nr "<<i<<" :\n";
        std::cin>>recording;
        recordings.push_back(recording);
    }
    Sensor* sensor;
    if(type == "t"){
        double diameter;
        std::cout<<"Diameter:\n";
        std::cin>>diameter;
        sensor = new TemperatureSensor(producer, recordings, diameter);
    }else if(type == "h"){
        sensor = new HumiditySensor(producer, recordings);
    }else if(type=="s"){
        sensor = new SmokeSensor(producer, recordings);
    }else{
        std::cout<<"invalid type";
        return;
    }
    std::cin.get();
    this->device.addSensor(sensor);
    std::cout<<"added";
}

void ConsoleUI::handleShowAllSensors() {
    std::cout<<"all sensors"<<'\n';
    std::vector<Sensor*> allSensors = this->device.getAllSensors();
    for(auto sensor: allSensors){
        std::cout<<sensor->toString()<<'\n';
    }
}

void ConsoleUI::handleShowAlertingSensors() {
    std::cout<<"alerting"<<'\n';
    std::vector<Sensor*> allSensors = this->device.getAlertingSensors();
    for(auto sensor: allSensors){
        std::cout<<sensor->toString()<<'\n';
    }
}

void ConsoleUI::handleSaveToFile() {
    std::string fileName;
    std::cout<<"file name:\n";
    getline(std::cin, fileName);
    double price;
    std::cout<<"price:\n";
    std::cin>>price;
    std::cin.get();
    device.writeToFileCheapSensors(fileName, price);
}
