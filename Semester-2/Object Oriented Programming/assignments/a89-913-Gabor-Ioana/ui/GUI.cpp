//
// Created by ioana on 18.05.2023.
//

#include <QPushButton>
#include <QHBoxLayout>
#include "GUI.h"
#include "ui_GUI.h"


GUI::GUI(EventsController& eventsController, QWidget *parent) : eventsController(eventsController),
        QWidget(parent), ui(new Ui::GUI) {
    ui->setupUi(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    this->setWindowTitle("Main menu");
    this->userButton = new QPushButton("User mode");
    mainLayout->addWidget(this->userButton);
    this->adminButton = new QPushButton("Admin mode");
    mainLayout->addWidget(this->adminButton);
    this->statisticsButton = new QPushButton("Statistics");
    mainLayout->addWidget(this->statisticsButton);
    QObject::connect(userButton,&QPushButton::clicked,this,&GUI::handleEnterUserMode);
    QObject::connect(adminButton,&QPushButton::clicked,this,&GUI::handleEnterAdminMode);
    QObject::connect(statisticsButton,&QPushButton::clicked,this,&GUI::handleEnterStatistics);
    this->adminUI = new AdminUI(eventsController);
    this->userUI = new UserUI(eventsController);
    this->statisticsUI = new StatisticsUI(eventsController);
    QObject::connect(this->adminUI,&AdminUI::exitClicked, this, &QWidget::show);
    QObject::connect(this->userUI,&UserUI::exitClicked, this, &QWidget::show);
    QObject::connect(this->statisticsUI,&StatisticsUI::exitClicked,this,&QWidget::show);
}

void GUI::handleEnterUserMode(){
    this->hide();
    this->userUI->show();
}

void GUI::handleEnterAdminMode(){
    this->hide();
    this->adminUI->showMaximized();
    this->adminUI->reloadEventsList();
}

void GUI::handleEnterStatistics(){
    this->hide();
    this->statisticsUI->show();
    this->statisticsUI->loadPlot();
}


GUI::~GUI() {
    delete ui;
}
