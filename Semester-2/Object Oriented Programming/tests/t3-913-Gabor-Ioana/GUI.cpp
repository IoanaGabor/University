//
// Created by ioana on 26.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "GUI.h"
#include "ui_GUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>


GUI::GUI(Controller &controller,QWidget *parent) :
        controller(controller),QWidget(parent), ui(new Ui::GUI) {
    ui->setupUi(this);
    this->setWindowTitle("Equations");
    mainLayout = new QVBoxLayout(this);
    equationsList = new QListWidget();
    mainLayout->addWidget(equationsList);
    loadEquations();
    buildUpdateForm();
    mainLayout->addLayout(updateForm);
    computeSolutionsButton = new QPushButton("show solutions");
    solutionsLabel = new QLabel();
    mainLayout->addWidget(computeSolutionsButton);
    mainLayout->addWidget(solutionsLabel);
    QObject::connect(updateButton, &QPushButton::pressed, this,&GUI::updateEquation);
    QObject::connect(computeSolutionsButton, &QPushButton::pressed, this,&GUI::showSolutions);
}

void GUI::buildUpdateForm() {
    updateForm = new QFormLayout();
    aLabel = new QLabel("a");
    aLineEdit = new QLineEdit();
    aLabel->setBuddy(aLineEdit);
    bLabel = new QLabel("b");
    bLineEdit = new QLineEdit();
    bLabel->setBuddy(bLineEdit);
    cLabel = new QLabel("c");
    cLineEdit = new QLineEdit();
    cLabel->setBuddy(cLineEdit);
    updateForm->addRow(aLabel, aLineEdit);
    updateForm->addRow(bLabel, bLineEdit);
    updateForm->addRow(cLabel, cLineEdit);
    updateButton = new QPushButton("update");
    updateForm->addWidget(updateButton);
}

void GUI::loadEquations() {
    allEquations = controller.getAllSortedEquations();
    equationsList->clear();
    for(auto &equation :allEquations){
        equationsList->addItem(QString::fromStdString(equation.toString()));
    }
}

void GUI::updateEquation(){
    double a = aLineEdit->text().toDouble();
    double b = bLineEdit->text().toDouble();
    double c = cLineEdit->text().toDouble();
    int index = equationsList->currentRow();
    if(index!=-1){
        controller.updateEquationGivenByItsPosition(allEquations[index], a, b,c);
        loadEquations();
    }
}

void GUI::showSolutions(){
    int index = equationsList->currentRow();
    if(index!=-1){
        Equation equation= allEquations[index];
        solutionsLabel->setText(QString::fromStdString(equation.solutionsAsString()));
    }else{
        solutionsLabel->setText(QString::fromStdString("no selected"));
    }
}

GUI::~GUI() {
    delete ui;
}
