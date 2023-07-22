//
// Created by ioana on 18.05.2023.
//

#ifndef A89_913_GABOR_IOANA_USERUI_H
#define A89_913_GABOR_IOANA_USERUI_H

#include <QWidget>
#include <QtWidgets>
#include "controller/EventsController.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserUI; }
QT_END_NAMESPACE

class UserUI : public QWidget {
Q_OBJECT

public:
    explicit UserUI(EventsController& eventsController,QWidget *parent = nullptr);

    ~UserUI() override;
signals:
    void exitClicked();
private:
    Ui::UserUI *ui;
    EventsController& eventsController;
    QPushButton *exit;
    QVBoxLayout* mainLayout;
    QFormLayout* searchLayout;
    QVBoxLayout* commandsLayout;
    QLabel* labelSearchBar;
    QLineEdit* textSearchBar;
    QPushButton *searchButton;
    QPushButton *openEventListButton;
    QPushButton *addEventButton;
    QPushButton *nextEventButton;
    QPushButton *removeEventButton;
    QFormLayout* eventFormLayout;
    QLabel* labelTitle;
    QLineEdit* textBoxTitle;
    QLabel* labelDescription;
    QLineEdit* textBoxDescription;
    QLabel* labelDateAndTime;
    QLineEdit* textBoxDateAndTime;
    QLineEdit* textBoxAttendants;
    QLabel* labelAttendants;
    QLabel* labelLink;
    QLineEdit* textBoxLink;

    QFormLayout* removeEventFormLayout;
    QLabel* labelRemoveTitle;
    QLineEdit* textBoxRemoveTitle;
    QLabel* labelRemoveDateAndTime;
    QLineEdit* textBoxRemoveDateAndTime;
    QMessageBox *errorMessageBox;

    std::vector<Event> lastSearchedEvents;
    int currentDisplayedEvent;
    void handleExitPressed();

    void createEventForm();

    void createSearchLayout();

    void handleOpenListPressed();

    void handleSearchEventsPressed();

    void handleNextEventPressed();
    void handleAddEventPressed();

    void removeEventPressed();

    void createRemoveEventForm();
};


#endif //A89_913_GABOR_IOANA_USERUI_H
