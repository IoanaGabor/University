//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_DOCTORWINDOW_H
#define E913_913_GABOR_IOANA_DOCTORWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QTextEdit>
#include <QPushButton>
#include "Doctor.h"
#include "AbstractObserver.h"
#include "Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DoctorWindow; }
QT_END_NAMESPACE

class DoctorWindow : public QWidget, public AbstractObserver {
Q_OBJECT

    void update() override;

public:
    explicit DoctorWindow(Doctor doctor,Controller *controller,QWidget *parent = nullptr);

    ~DoctorWindow() override;

private:
    Ui::DoctorWindow *ui;
    Doctor doctor;
    QHBoxLayout *mainLayout;
    QTableWidget *patientsTable;
    Controller *controller;
    QCheckBox *checkBox;
    QFormLayout *addPatientForm;
    QTextEdit *patientNameTextEdit;
    QTextEdit *patientDiagnosisTextEdit;
    QTextEdit *patientSpecialisationTextEdit;
    QTextEdit *patientCurrentDoctorTextEdit;
    QTextEdit *patientDateTextEdit;
    QPushButton *addButton;
    QFormLayout *updatePatientForm;
    QTextEdit *patientUpdateDiagnosisTextEdit;
    QTextEdit *patientUpdateSpecialisationTextEdit;
    QPushButton *updateButton;

    void handleAddPatient();
    void handleUpdatePatient();
};


#endif //E913_913_GABOR_IOANA_DOCTORWINDOW_H
