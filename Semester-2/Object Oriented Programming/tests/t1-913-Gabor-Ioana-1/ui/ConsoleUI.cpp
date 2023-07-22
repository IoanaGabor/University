//
// Created by ioana on 28.04.2023.
//

#include "ConsoleUI.h"
#include "GenericAppException.h"
#include <iostream>

ConsoleUI::ConsoleUI(const PatientsController& patientsController) {
    this->patientsController = patientsController;
}



void ConsoleUI::run() {
    std::string command;

    this->patientsController.addPatient("Ioana", 19, false, 4);
    this->patientsController.addPatient("Ioan", 19, true, 5);
    this->patientsController.addPatient("Ioanrewqa", 19, false, 3);
    this->patientsController.addPatient("Io43an", 19, true, 2);
    this->patientsController.addPatient("Io43ana", 19, false, 1);


    while(true){
        this->printMenu();
        getline(std::cin, command);
        if(command == "add"){
            this->handleAddPatient();
        }if(command=="list"){
            this->handleListAllPatients();
        }if(command=="heal"){
            this->handleHealingPatient();
        }if(command=="infect"){
            this->handleUpdateInfectionStatus();
        }else{
            std::cout<<"Invalid command\n";
        }
    }
}

void ConsoleUI::handleAddPatient() {
    std::cout<<"Please enter the name of the patient:\n";
    std::string name;
    getline(std::cin, name);
    std::cout<<"Please enter the age of the patient:\n";
    std::string ageAsString;
    getline(std::cin, ageAsString);
    int age = std::stoi(ageAsString);
    std::cout<<"Please enter the infection status(0 or 1) of the patient:\n";
    std::string infectedAsString;
    getline(std::cin, infectedAsString);
    bool infected = std::stoi(infectedAsString);
    std::cout<<"Please enter the room of the patient:\n";
    std::string roomAsString;
    getline(std::cin, roomAsString);
    int room = std::stoi(roomAsString);
    try{
        this->patientsController.addPatient(name, age, infected, room);
        std::cout<<"successfully added\n";
    }catch (GenericAppException &genericAppException){
        std::cout<<genericAppException.getMessage();
    }
}

void ConsoleUI::printMenu() {
    std::cout<<"Options:"<<'\n';
    std::cout<<"add"<<'\n';
    std::cout<<"list"<<'\n';
    std::cout<<"heal"<<'\n';
    std::cout<<"infect"<<'\n';
}

void ConsoleUI::handleListAllPatients() {
    std::vector<Patient> allPatients = this->patientsController.getAllPatients();
    for(auto & allPatient : allPatients){
        std::cout<<allPatient.toString()<<'\n';
    }
}

void ConsoleUI::handleHealingPatient() {
    std::cout<<"Please enter the name of the patient which you want to heal:\n";
    std::string name;
    getline(std::cin, name);
    try{
        this->patientsController.healPatient(name);
    }catch (GenericAppException &genericAppException){
        std::cout<<genericAppException.getMessage()<<'\n';
    }
}

void ConsoleUI::handleUpdateInfectionStatus() {
    std::cout<<"Please enter the name of the patient which you want to infect:\n";
    std::string name;
    getline(std::cin, name);
    try{
        this->patientsController.updateInfectionStatus(name);
    }catch (GenericAppException &genericAppException){
        std::cout<<genericAppException.getMessage()<<'\n';
    }
}
