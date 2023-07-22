cmake_minimum_required(VERSION 3.24)
project(a89-913-Gabor-Ioana)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/home/ioana/Qt/6.5.0/gcc_64/lib/cmake")

include_directories(.)
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} CMakeFiles/a89-913-Gabor-Ioana.dir/a89-913-Gabor-Ioana_autogen/mocs_compilation.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/main.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/domain/Event.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/MemoryRepository.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/controller/EventsController.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/ui/ConsoleUI.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/validators/Validators.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/domain/AppExceptions.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/app_tests/TestEvent.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/app_tests/TestRepository.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/app_tests/TestAll.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/app_tests/TestController.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/AbstractFileRepository.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/CSVEventList.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/HTMLEventList.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/TextFileRepository.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/AbstractUserEventList.cpp.o CMakeFiles/a89-913-Gabor-Ioana.dir/repository/DataBaseEventsRepository.cpp.o -o a89-913-Gabor-Ioana  -Wl,-rpath,/home/ioana/Qt/6.5.0/gcc_64/lib  /home/ioana/Qt/6.5.0/gcc_64/lib/libQt6Widgets.so.6.5.0  /home/ioana/Qt/6.5.0/gcc_64/lib/libQt6Gui.so.6.5.0  /home/ioana/Qt/6.5.0/gcc_64/lib/libQt6Core.so.6.5.0  /usr/lib/x86_64-linux-gnu/libGL.so -l sqlite3 #")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} CMakeFiles/a89_913_Gabor_Ioana.dir/main.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/domain/Event.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/MemoryRepository.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/controller/EventsController.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/ui/ConsoleUI.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/validators/Validators.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/domain/AppExceptions.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/app_tests/TestEvent.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/app_tests/TestRepository.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/app_tests/TestAll.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/app_tests/TestController.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/AbstractFileRepository.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/CSVEventList.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/HTMLEventList.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/TextFileRepository.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/AbstractUserEventList.cpp.o CMakeFiles/a89_913_Gabor_Ioana.dir/repository/DataBaseEventsRepository.cpp.o -o a89_913_Gabor_Ioana -l sqlite3 #")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        PrintSupport
        REQUIRED)
add_executable(a89-913-Gabor-Ioana
        main.cpp domain/Event.h domain/Event.cpp
        repository/MemoryRepository.h repository/MemoryRepository.cpp
        controller/EventsController.h controller/EventsController.cpp
        ui/ConsoleUI.h ui/ConsoleUI.cpp
        validators/Validators.h validators/Validators.cpp
        domain/AppExceptions.h domain/AppExceptions.cpp
        app_tests/TestEvent.cpp app_tests/TestRepository.cpp
        app_tests/TestAll.h app_tests/TestAll.cpp
        app_tests/TestController.h app_tests/TestController.cpp
        repository/AbstractRepository.h repository/AbstractFileRepository.h
        repository/AbstractFileRepository.cpp repository/CSVEventList.h repository/CSVEventList.cpp
        repository/HTMLEventList.h repository/HTMLEventList.cpp
        repository/TextFileRepository.h repository/TextFileRepository.cpp
        repository/AbstractUserEventList.h repository/AbstractUserEventList.cpp
        repository/DataBaseEventsRepository.h ui/GUI.cpp ui/GUI.h ui/GUI.ui ui/UserUI.cpp ui/UserUI.h ui/UserUI.ui ui/AdminUI.cpp ui/AdminUI.h ui/AdminUI.ui repository/FakeRepository.cpp repository/FakeRepository.h repository/FakeUserEventList.cpp repository/FakeUserEventList.h
        qcustomplot-source/qcustomplot.h qcustomplot-source/qcustomplot.cpp ui/statisticsUI.cpp ui/statisticsUI.h ui/statisticsUI.ui ui/statisticsUI.cpp)
target_link_libraries(a89-913-Gabor-Ioana
        Qt6::Core
        Qt6::Widgets
        Qt6::PrintSupport
        )

