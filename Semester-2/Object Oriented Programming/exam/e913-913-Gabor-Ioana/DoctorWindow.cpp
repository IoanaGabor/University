//
// Created by ioana on 16.06.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DoctorWindow.h" resolved

#include <QMessageBox>
#include "DoctorWindow.h"
#include "ui_DoctorWindow.h"
#include "Patient.h"
#include "GenericException.h"


DoctorWindow::DoctorWindow(Doctor doctor,Controller *controller,QWidget *parent) :
        doctor(doctor),controller(controller),QWidget(parent), ui(new Ui::DoctorWindow) {
    ui->setupUi(this);
    this->setWindowTitle(doctor.getName().c_str());
    mainLayout = new QHBoxLayout(this);
    patientsTable = new QTableWidget();
    mainLayout->addWidget(patientsTable);
    checkBox = new QCheckBox();
    mainLayout->addWidget(checkBox);
    update();

    addPatientForm = new QFormLayout();
    patientNameTextEdit = new QTextEdit();
    patientDiagnosisTextEdit = new QTextEdit();
    patientSpecialisationTextEdit = new QTextEdit();
    patientCurrentDoctorTextEdit = new QTextEdit();
    patientDateTextEdit = new QTextEdit();
    addButton = new QPushButton("add");
    addPatientForm->addRow("Name",patientNameTextEdit );
    addPatientForm->addRow("Diagn",patientDiagnosisTextEdit );
    addPatientForm->addRow("Spec",patientSpecialisationTextEdit);
    addPatientForm->addRow("Doc",patientCurrentDoctorTextEdit);
    addPatientForm->addRow("Date",patientDateTextEdit);
    addPatientForm->addWidget(addButton);
    mainLayout->addLayout(addPatientForm);


    updatePatientForm = new QFormLayout();
    patientUpdateDiagnosisTextEdit = new QTextEdit();
    patientUpdateSpecialisationTextEdit = new QTextEdit();
    updateButton = new QPushButton("update");
    updatePatientForm->addRow("Diagn",patientUpdateDiagnosisTextEdit );
    updatePatientForm->addRow("spec",patientUpdateSpecialisationTextEdit);
    updatePatientForm->addWidget(updateButton);
    mainLayout->addLayout(updatePatientForm);
    QObject::connect(checkBox,&QCheckBox::stateChanged,this,  &DoctorWindow::update);
    QObject::connect(addButton,&QCheckBox::clicked,this,  &DoctorWindow::handleAddPatient);
    QObject::connect(updateButton,&QCheckBox::clicked,this,  &DoctorWindow::handleUpdatePatient);
}

DoctorWindow::~DoctorWindow() {
    delete ui;
}

void DoctorWindow::handleUpdatePatient(){
    int currentRow = patientsTable->currentRow();
    if(currentRow == -1){
        QMessageBox *messageBox = new QMessageBox();
        messageBox->setText("no selection");
        messageBox->show();
    }else{
        std::string name = patientsTable->item(currentRow, 0)->data(Qt::DisplayRole).toString().toStdString();
        std::string diagnosis= patientUpdateDiagnosisTextEdit->toPlainText().toStdString();
        std::string specialisation= patientUpdateSpecialisationTextEdit->toPlainText().toStdString();
        try{
            controller->updatePatient(name, diagnosis, specialisation, doctor);
            controller->notify();
        }catch (GenericException &ex){
            QMessageBox *messageBox = new QMessageBox();
            messageBox->setText(ex.getMessage().c_str());
            messageBox->show();
        }
    }
}

void DoctorWindow::handleAddPatient(){
    std::string name = patientNameTextEdit->toPlainText().toStdString();
    std::string diagnosis= patientDiagnosisTextEdit->toPlainText().toStdString();
    std::string specialisation= patientSpecialisationTextEdit->toPlainText().toStdString();
    std::string current_doctor= patientCurrentDoctorTextEdit->toPlainText().toStdString();
    int admission_date= patientDateTextEdit->toPlainText().toInt();
    try{
        controller->addPatient(name, diagnosis, specialisation, current_doctor, admission_date);
        controller->notify();
    }catch (GenericException &ex){
        QMessageBox *messageBox = new QMessageBox();
        messageBox->setText(ex.getMessage().c_str());
        messageBox->show();
    }
}

void DoctorWindow::update() {
    std::vector<Patient> patients;
    if(!checkBox->isChecked()){
        patients = controller->getPatientsWithSpecialisationOrUndiagnosed(doctor.getSpecialisation());
    }else{
        patients = controller->getPatientsWithCurrentDoctor(doctor.getName());
    }
    patientsTable->clear();
    patientsTable->setColumnCount(5);
    patientsTable->setRowCount((int)patients.size());
    for(int i=0;i<patients.size();i++){
        QTableWidgetItem *item1 = new QTableWidgetItem(patients[i].getName().c_str());

        patientsTable->setItem(i, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem(patients[i].getDiagnosis().c_str());
        patientsTable->setItem(i, 1, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(patients[i].getSpecialisation().c_str());
        patientsTable->setItem(i, 2, item3);
        QTableWidgetItem *item4 = new QTableWidgetItem(patients[i].getCurrentDoctor().c_str());
        patientsTable->setItem(i, 3, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem(std::to_string(patients[i].getAdmissionDate()).c_str());
        patientsTable->setItem(i, 4, item5);
        if(patients[i].getCurrentDoctor() == doctor.getName()){
            item1->setBackground(QBrush(Qt::GlobalColor::green));
            item2->setBackground(QBrush(Qt::GlobalColor::green));
            item3->setBackground(QBrush(Qt::GlobalColor::green));
            item4->setBackground(QBrush(Qt::GlobalColor::green));
            item5->setBackground(QBrush(Qt::GlobalColor::green));
        }
    }

}
