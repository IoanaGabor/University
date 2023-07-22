//
// Created by ioana on 18.05.2023.
//

#ifndef A89_913_GABOR_IOANA_GUI_H
#define A89_913_GABOR_IOANA_GUI_H

#include <QWidget>
#include <QtWidgets>
#include "controller/EventsController.h"
#include "AdminUI.h"
#include "UserUI.h"
#include "statisticsUI.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(EventsController& eventsController, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    EventsController& eventsController;
    QPushButton* userButton;
    QPushButton* adminButton;
    QPushButton* statisticsButton;
    UserUI* userUI;
    AdminUI* adminUI;
    StatisticsUI* statisticsUI;
    void handleEnterUserMode();

    void handleEnterAdminMode();

    void handleEnterStatistics();
};


#endif //A89_913_GABOR_IOANA_GUI_H
