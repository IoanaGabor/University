//
// Created by ioana on 28.04.2023.
//

#ifndef T1_913_GABOR_IOANA_1_CONSOLEUI_H
#define T1_913_GABOR_IOANA_1_CONSOLEUI_H
#include "PatientsController.h"

class ConsoleUI {
public:
    explicit ConsoleUI(const PatientsController& patientsController);
    void run();
private:
    PatientsController patientsController;
    static void printMenu();
    void handleAddPatient();
    void handleListAllPatients();
    void handleHealingPatient();
    void handleUpdateInfectionStatus();

};


#endif //T1_913_GABOR_IOANA_1_CONSOLEUI_H
