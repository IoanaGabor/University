//
// Created by ioana on 16.06.2023.
//
#include <QApplication>
#include "PatientRepository.h"
#include "DoctorRepository.h"
#include "DoctorWindow.h"
#include "Statistics.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PatientRepository patientRepository = PatientRepository("/home/ioana/second_semester/oop/e913-913-Gabor-Ioana/patients.txt");
    DoctorRepository doctorRepo = DoctorRepository("/home/ioana/second_semester/oop/e913-913-Gabor-Ioana/doctors.txt");
    Controller controller = Controller(&patientRepository);
    DoctorWindow *doctorWindow;
    for(auto doctor: doctorRepo.getAllDoctors()){
        doctorWindow = new DoctorWindow(doctor, &controller);
        doctorWindow->show();
        controller.addObserver(doctorWindow);
    }
    Statistics *statistics = new Statistics(&controller);
    controller.addObserver(statistics);
    statistics->show();
    return QApplication::exec();
}
