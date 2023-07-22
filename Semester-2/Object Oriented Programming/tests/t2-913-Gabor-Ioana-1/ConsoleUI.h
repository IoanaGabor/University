//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_CONSOLEUI_H
#define T2_913_GABOR_IOANA_1_CONSOLEUI_H


#include "Device.h"

static const char *const ADD_COMMAND = "1";

static const char *const SHOW_ALL_COMMAND = "2";

class ConsoleUI {
public:
    ConsoleUI();
    void run();
private:
    Device device;
    void handleAddSensor();
    void handleShowAllSensors();
    void handleShowAlertingSensors();
    void handleSaveToFile();
};


#endif //T2_913_GABOR_IOANA_1_CONSOLEUI_H
