//
// Created by ioana on 28.04.2023.
//
#include <iostream>
#include "PatientsController.h"
#include "ConsoleUI.h"

int main() {
    PatientsController patientsController = PatientsController();
    ConsoleUI consoleUi = ConsoleUI(patientsController);
    consoleUi.run();
}