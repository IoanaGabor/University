cmake_minimum_required(VERSION 3.24)
project(t2_913_Gabor_Ioana_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t2_913_Gabor_Ioana_1
        main.cpp Device.cpp Device.h HumiditySensor.cpp HumiditySensor.h Sensor.cpp Sensor.h SmokeSensor.cpp SmokeSensor.h TemperatureSensor.cpp TemperatureSensor.h ConsoleUI.cpp ConsoleUI.h)
