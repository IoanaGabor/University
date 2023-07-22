cmake_minimum_required(VERSION 3.24)
project(a7_913_Gabor_Ioana_1)

SET(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(.)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} CMakeFiles/a7_913_Gabor_Ioana_1.dir/main.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/domain/Event.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/MemoryRepository.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/controller/EventsController.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/ui/ConsoleUI.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/validators/Validators.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/domain/AppExceptions.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/app_tests/TestEvent.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/app_tests/TestRepository.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/app_tests/TestAll.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/app_tests/TestController.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/AbstractFileRepository.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/CSVEventList.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/HTMLEventList.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/TextFileRepository.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/AbstractUserEventList.cpp.o CMakeFiles/a7_913_Gabor_Ioana_1.dir/repository/DataBaseEventsRepository.cpp.o -o a7_913_Gabor_Ioana_1 -l sqlite3 #")

add_executable(a7_913_Gabor_Ioana_1
        main.cpp domain/Event.h domain/Event.cpp repository/MemoryRepository.h repository/MemoryRepository.cpp controller/EventsController.h controller/EventsController.cpp ui/ConsoleUI.h ui/ConsoleUI.cpp validators/Validators.h validators/Validators.cpp domain/AppExceptions.h domain/AppExceptions.cpp app_tests/TestEvent.cpp app_tests/TestRepository.cpp app_tests/TestAll.h app_tests/TestAll.cpp app_tests/TestController.h app_tests/TestController.cpp repository/AbstractRepository.h repository/AbstractFileRepository.h repository/AbstractFileRepository.cpp repository/CSVEventList.h repository/CSVEventList.cpp repository/HTMLEventList.h repository/HTMLEventList.cpp repository/TextFileRepository.h repository/TextFileRepository.cpp repository/AbstractUserEventList.h repository/AbstractUserEventList.cpp repository/DataBaseEventsRepository.h repository/DataBaseEventsRepository.cpp)

