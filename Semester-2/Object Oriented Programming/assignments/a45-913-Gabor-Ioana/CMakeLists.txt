cmake_minimum_required(VERSION 3.24)
project(a45_913_Gabor_Ioana)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a45_913_Gabor_Ioana
        domain/DynamicVector.cpp
        domain/DynamicVector.h main.cpp domain/Event.h domain/Event.cpp repository/Repository.h repository/Repository.cpp controller/EventsController.h controller/EventsController.cpp ui/ConsoleUI.h ui/ConsoleUI.cpp validators/Validators.h validators/Validators.cpp domain/AppExceptions.h domain/AppExceptions.cpp app_tests/TestDynamicVector.h app_tests/TestEvent.cpp app_tests/TestRepository.cpp app_tests/TestDynamicVector.cpp app_tests/TestAll.h app_tests/TestAll.cpp app_tests/TestController.h app_tests/TestController.cpp)
