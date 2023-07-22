cmake_minimum_required(VERSION 3.24)
project(t3-913-Gabor-Ioana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/ioana/Qt/6.5.0/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(t3-913-Gabor-Ioana main.cpp GUI.cpp GUI.h GUI.ui Equation.cpp Equation.h Repository.cpp Repository.h Controller.cpp Controller.h)
target_link_libraries(t3-913-Gabor-Ioana
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

