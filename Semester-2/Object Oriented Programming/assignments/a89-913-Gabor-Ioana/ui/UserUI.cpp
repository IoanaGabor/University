//
// Created by ioana on 18.05.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserUI.h" resolved

#include <QLabel>
#include <QHBoxLayout>
#include "UserUI.h"
#include "ui_UserUI.h"


UserUI::UserUI(EventsController& eventsController,QWidget *parent) :
    eventsController(eventsController),QWidget(parent), ui(new Ui::UserUI) {
    ui->setupUi(this);
    this->setWindowTitle("User Mode");
    mainLayout = new QVBoxLayout(this);
    createSearchLayout();
    errorMessageBox = new QMessageBox();
    errorMessageBox->setWindowTitle("Error!");
    this->exit = new QPushButton("exit user mode");
    commandsLayout = new QVBoxLayout();
    QLabel *currentEventLabel = new QLabel{"Current Event"};
    commandsLayout->addWidget(currentEventLabel);
    lastSearchedEvents=std::vector<Event>();
    currentDisplayedEvent=0;
    QObject::connect(exit, &QPushButton::clicked, this, &UserUI::handleExitPressed);
    createEventForm();
    createRemoveEventForm();
    commandsLayout->addLayout(eventFormLayout);
    commandsLayout->addWidget(this->exit);
    mainLayout->addLayout(commandsLayout);
}

void UserUI::createSearchLayout() {
    auto horizontalSearchLayout = new QHBoxLayout();
    searchLayout = new QFormLayout{};
    labelSearchBar = new QLabel{"&Search" };
    textSearchBar = new QLineEdit{};
    searchButton = new QPushButton("search");
    labelSearchBar->setBuddy(textSearchBar);
    searchLayout->addRow(labelSearchBar, textSearchBar);
    horizontalSearchLayout->addLayout(searchLayout);
    horizontalSearchLayout->addWidget(searchButton);
    mainLayout->addLayout(horizontalSearchLayout);
    QObject::connect(searchButton, &QPushButton::clicked, this, &UserUI::handleSearchEventsPressed);
}

void UserUI::createEventForm() {
    eventFormLayout = new QFormLayout{};
    labelTitle = new QLabel{"&Title" };
    textBoxTitle = new QLineEdit{};
    labelTitle->setBuddy(textBoxTitle);
    textBoxTitle->setReadOnly(true);
    eventFormLayout->addRow(labelTitle, textBoxTitle);

    labelDescription = new QLabel{"&Description" };
    textBoxDescription = new QLineEdit{};
    labelDescription->setBuddy(textBoxDescription);
    textBoxDescription->setReadOnly(true);
    eventFormLayout->addRow(labelDescription, textBoxDescription);

    labelDateAndTime = new QLabel{"&Date and time"};
    textBoxDateAndTime = new QLineEdit{};
    labelDateAndTime->setBuddy(textBoxDateAndTime);
    textBoxDateAndTime->setReadOnly(true);
    eventFormLayout->addRow(labelDateAndTime, textBoxDateAndTime);

    labelAttendants = new QLabel{"&Nb. of attendants"};
    textBoxAttendants = new QLineEdit{};
    labelAttendants->setBuddy(textBoxAttendants);
    textBoxAttendants->setReadOnly(true);
    eventFormLayout->addRow(labelAttendants, textBoxAttendants);

    labelLink = new QLabel{"&Link" };
    textBoxLink = new QLineEdit{};
    labelLink->setBuddy(textBoxLink);
    eventFormLayout->addRow(labelLink, textBoxLink);
    addEventButton = new QPushButton("add event");
    nextEventButton = new QPushButton("next event");
    openEventListButton = new QPushButton("open list");
    textBoxLink->setReadOnly(true);
    eventFormLayout->addWidget(addEventButton);
    eventFormLayout->addWidget(nextEventButton);
    eventFormLayout->addWidget(openEventListButton);
    QObject::connect(openEventListButton, &QPushButton::clicked, this, &UserUI::handleOpenListPressed);
    QObject::connect(nextEventButton, &QPushButton::clicked, this, &UserUI::handleNextEventPressed);
    QObject::connect(addEventButton, &QPushButton::clicked, this, &UserUI::handleAddEventPressed);
}

void UserUI::createRemoveEventForm() {
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
    QObject::connect(removeEventButton, &QPushButton::clicked, this, &UserUI::removeEventPressed);
}


void UserUI:: handleExitPressed(){
    this->hide();
    emit this->exitClicked();
}

void UserUI:: handleOpenListPressed(){
    this->eventsController.openUserEventList();
}

void UserUI:: handleAddEventPressed(){
    if(lastSearchedEvents.size()==0){
        errorMessageBox->setText("no events");
        errorMessageBox->show();
        return;
    }
    try{
        this->eventsController.addEventUser(lastSearchedEvents[currentDisplayedEvent].getId());
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
}

void UserUI::removeEventPressed() {
    std::string title = textBoxRemoveTitle->text().toStdString();
    std::string dateAndTime = textBoxRemoveDateAndTime->text().toStdString();
    try {
        this->eventsController.removeEventUser(
                title,
                dateAndTime
        );
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
}


void UserUI:: handleSearchEventsPressed(){
    std::string searchedText = this->textSearchBar->text().toStdString();
    try{
        lastSearchedEvents = eventsController.selectAllEventsByMonth(searchedText);
        if(lastSearchedEvents.size()){
            currentDisplayedEvent=lastSearchedEvents.size()-1;
        }
        handleNextEventPressed();
    }catch (EventsControllerException &eventsControllerException){
        errorMessageBox->setText(eventsControllerException.get_message().c_str());
        errorMessageBox->show();
    }
}

void UserUI::handleNextEventPressed(){
    if(lastSearchedEvents.empty()){
        this->textBoxTitle->setText("");
        this->textBoxDescription->setText("");
        this->textBoxDateAndTime->setText("");
        this->textBoxLink->setText("");
        this->textBoxAttendants->setText("");
        return;
    }
    currentDisplayedEvent++;
    currentDisplayedEvent%=(int)lastSearchedEvents.size();
    this->textBoxTitle->setText(QString::fromStdString(lastSearchedEvents[currentDisplayedEvent].getTitle()));
    this->textBoxDescription->setText(QString::fromStdString(lastSearchedEvents[currentDisplayedEvent].getDescription()));
    this->textBoxDateAndTime->setText(QString::fromStdString(lastSearchedEvents[currentDisplayedEvent].getDateAndTime()));
    this->textBoxLink->setText(QString::fromStdString(lastSearchedEvents[currentDisplayedEvent].getLink()));
    this->textBoxAttendants->setText(QString::fromStdString(std::to_string(lastSearchedEvents[currentDisplayedEvent].getNumberOfAttendants())));
}

UserUI::~UserUI() {
    delete ui;
}
