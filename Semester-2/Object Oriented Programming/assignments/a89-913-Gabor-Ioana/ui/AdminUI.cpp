//
// Created by ioana on 18.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AdminUI.h" resolved

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "AdminUI.h"
#include "ui_AdminUI.h"


AdminUI::AdminUI(EventsController& eventsController, QWidget *parent) :
        eventsController(eventsController), QWidget(parent), ui(new Ui::AdminUI) {
    ui->setupUi(this);
    this->setWindowTitle("Admin Mode");
    mainLayout = new QHBoxLayout(this);
    commandsLayout = new QVBoxLayout();
    errorMessageBox = new QMessageBox();
    errorMessageBox->setWindowTitle("Error!");
    createAddEventForm();
    createRemoveEventForm();
    this->exitButton = new QPushButton("exit admin mode");
    commandsLayout->addWidget(this->exitButton);
    tableLayout = new QVBoxLayout();
    mainLayout->addLayout(commandsLayout);
    mainLayout->addLayout(tableLayout);
    eventsTable = new QTableWidget();
    eventsTable->setColumnCount(5);
    tableLayout->addWidget(eventsTable);

    QObject::connect(exitButton, &QPushButton::clicked, this, &AdminUI::handleExitPressed);
    QObject::connect(addEventButton, &QPushButton::clicked, this, &AdminUI::addEventPressed);
    QObject::connect(updateEventButton, &QPushButton::clicked, this, &AdminUI::updateEventPressed);
    QObject::connect(removeEventButton, &QPushButton::clicked, this, &AdminUI::removeEventPressed);
    this->reloadEventsList();
}

void AdminUI::createRemoveEventForm() {
    removeEventFormLayout = new QFormLayout{};
    removeEventFormLayout->addWidget(new QLabel{"Remove an event"});
    labelRemoveTitle = new QLabel{"&Title" };
    textBoxRemoveTitle = new QLineEdit{};
    labelRemoveTitle->setBuddy(textBoxTitle);
    removeEventFormLayout->addRow(labelRemoveTitle, textBoxRemoveTitle);

    labelRemoveDateAndTime = new QLabel{"&Date and time"};
    textBoxRemoveDateAndTime = new QLineEdit{};
    labelRemoveDateAndTime->setBuddy(textBoxDateAndTime);
    removeEventFormLayout->addRow(labelRemoveDateAndTime, textBoxRemoveDateAndTime);
    removeEventButton = new QPushButton("remove event");
    removeEventFormLayout->addWidget(removeEventButton);
    commandsLayout->addLayout(removeEventFormLayout);
}

void AdminUI::addEventPressed() {
    std::string title = textBoxTitle->text().toStdString();
    std::string description = textBoxDescription->text().toStdString();
    std::string dateAndTime = textBoxDateAndTime->text().toStdString();
    std::string link = textBoxLink->text().toStdString();
    int numberOfAttendants = textBoxAttendants->text().toInt();
    try {
        this->eventsController.addEventAdministrator(
                title,
                description,
                dateAndTime,
                numberOfAttendants,
                link
        );
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
    reloadEventsList();
}

void AdminUI::updateEventPressed() {
    std::string title = textBoxTitle->text().toStdString();
    std::string description = textBoxDescription->text().toStdString();
    std::string dateAndTime = textBoxDateAndTime->text().toStdString();
    std::string link = textBoxLink->text().toStdString();
    int numberOfAttendants = textBoxAttendants->text().toInt();
    try {
        this->eventsController.updateEventAdministrator(
                title,
                description,
                dateAndTime,
                numberOfAttendants,
                link
        );
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
    reloadEventsList();
}

void AdminUI::removeEventPressed() {
    std::string title = textBoxRemoveTitle->text().toStdString();
    std::string dateAndTime = textBoxRemoveDateAndTime->text().toStdString();
    try {
        this->eventsController.removeEventAdministrator(
                title,
                dateAndTime
        );
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
    reloadEventsList();
}


void AdminUI::createAddEventForm() {
    eventFormLayout = new QFormLayout{};
    eventFormLayout->addWidget(new QLabel{"Add an event"});
    labelTitle = new QLabel{"&Title" };
    textBoxTitle = new QLineEdit{};
    labelTitle->setBuddy(textBoxTitle);
    eventFormLayout->addRow(labelTitle, textBoxTitle);

    labelDescription = new QLabel{"&Description" };
    textBoxDescription = new QLineEdit{};
    labelDescription->setBuddy(textBoxDescription);
    eventFormLayout->addRow(labelDescription, textBoxDescription);

    labelDateAndTime = new QLabel{"&Date and time"};
    textBoxDateAndTime = new QLineEdit{};
    labelDateAndTime->setBuddy(textBoxDateAndTime);
    eventFormLayout->addRow(labelDateAndTime, textBoxDateAndTime);

    labelAttendants = new QLabel{"&Nb. of attendants"};
    textBoxAttendants = new QLineEdit{};
    labelAttendants->setBuddy(textBoxAttendants);
    eventFormLayout->addRow(labelAttendants, textBoxAttendants);

    labelLink = new QLabel{"&Link" };
    textBoxLink = new QLineEdit{};
    labelLink->setBuddy(textBoxLink);
    eventFormLayout->addRow(labelLink, textBoxLink);
    addEventButton = new QPushButton("add event");
    updateEventButton = new QPushButton("update event");
    eventFormLayout->addWidget(addEventButton);
    eventFormLayout->addWidget(updateEventButton);
    commandsLayout->addLayout(eventFormLayout);
}

void AdminUI:: handleExitPressed(){
    this->hide();
    emit this->exitClicked();
}

void AdminUI::reloadEventsList(){
    this->eventsTable->clear();
    std::vector<Event> allEvents = this->eventsController.listEventsAdministrator();
    eventsTable->setRowCount(allEvents.size());
    int rowIndex = 0;
    for(auto &event:allEvents){
        this->eventsTable->setItem(rowIndex, 0, new QTableWidgetItem(tr(event.getTitle().c_str())));
        this->eventsTable->setItem(rowIndex, 1, new QTableWidgetItem(tr(event.getDescription().c_str())));
        this->eventsTable->setItem(rowIndex, 2, new QTableWidgetItem(tr(event.getDateAndTime().c_str())));
        this->eventsTable->setItem(rowIndex, 3, new QTableWidgetItem(tr(std::to_string(event.getNumberOfAttendants()).c_str())));
        this->eventsTable->setItem(rowIndex, 4, new QTableWidgetItem(tr(event.getLink().c_str())));
        rowIndex++;
    }
    eventsTable->setHorizontalHeaderLabels({"Title", "Description", "Date and time", "Attendants","Link"});
    eventsTable->resizeColumnsToContents();
}

AdminUI::~AdminUI() {
    delete ui;
}
