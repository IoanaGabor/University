cmake_minimum_required(VERSION 3.24)
project(t1_913_Gabor_Ioana_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(controller)
include_directories(domain)
include_directories(repository)
include_directories(ui)
include_directories(exceptions)

add_executable(t1_913_Gabor_Ioana_1
        controller/PatientsController.cpp
        controller/PatientsController.h
        domain/Patient.cpp
        domain/Patient.h
        repository/Repository.cpp
        repository/Repository.h
        ui/ConsoleUI.cpp
        ui/ConsoleUI.h
        main.cpp exceptions/GenericAppException.h exceptions/GenericAppException.cpp)
