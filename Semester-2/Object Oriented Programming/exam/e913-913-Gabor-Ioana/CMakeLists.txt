cmake_minimum_required(VERSION 3.24)
project(e913-913-Gabor-Ioana)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/ioana/Qt/6.5.0/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        PrintSupport
        REQUIRED)

add_executable(e913-913-Gabor-Ioana main.cpp DoctorRepository.h GenericException.h Doctor.h PatientRepository.h GenericException.cpp Doctor.cpp Patient.h Patient.cpp AbstractObserver.h AbstractObserver.cpp AbstractSubject.cpp AbstractSubject.h PatientRepository.cpp DoctorRepository.cpp Controller.cpp Controller.h DoctorWindow.h DoctorWindow.cpp Statistics.h Statistics.cpp qcustomplot-source/qcustomplot.cpp qcustomplot-source/qcustomplot.h)
target_link_libraries(e913-913-Gabor-Ioana
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::PrintSupport
        )
