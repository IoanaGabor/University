//
// Created by ioana on 18.05.2023.
//

#ifndef A89_913_GABOR_IOANA_ADMINUI_H
#define A89_913_GABOR_IOANA_ADMINUI_H

#include <QWidget>
#include <QtWidgets>
#include <QMessageBox>
#include "controller/EventsController.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AdminUI; }
QT_END_NAMESPACE

class AdminUI : public QWidget {
Q_OBJECT

    void addEventPressed();

public:
    explicit AdminUI(EventsController& eventsController, QWidget *parent = nullptr);

    ~AdminUI() override;
signals:
    void exitClicked();
private:
    Ui::AdminUI *ui;
    EventsController& eventsController;
    QHBoxLayout* mainLayout;
    QVBoxLayout* commandsLayout;
    QPushButton *exitButton;
    QPushButton *addEventButton;
    QPushButton *updateEventButton;
    QPushButton *removeEventButton;
    QFormLayout* eventFormLayout;
    QFormLayout* removeEventFormLayout;
    QLabel* labelRemoveTitle;
    QLineEdit* textBoxRemoveTitle;
    QLabel* labelRemoveDateAndTime;
    QLineEdit* textBoxRemoveDateAndTime;
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
    QVBoxLayout* tableLayout;
    QTableWidget *eventsTable;
    QMessageBox *errorMessageBox;
    void handleExitPressed();

    void createAddEventForm();

    void createRemoveEventForm();

    void updateEventPressed();

    void removeEventPressed();
public:
    void reloadEventsList();
};


#endif //A89_913_GABOR_IOANA_ADMINUI_H
