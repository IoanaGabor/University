//
// Created by ioana on 08.06.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StatisticsUI.h" resolved

#include "statisticsUI.h"
#include "ui_statisticsUI.h"
#include "qcustomplot-source/qcustomplot.h"


StatisticsUI::StatisticsUI(EventsController& eventsController,QWidget *parent) : eventsController(eventsController),
        QWidget(parent), ui(new Ui::StatisticsUI) {
    ui->setupUi(this);
    this->setWindowTitle("Distribution of the Number of Attendants");
    customPlot = new QCustomPlot(this);
    barPlot = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    loadPlot();
}

void StatisticsUI::loadPlot() const {
    QVector<double> keyData;
    QVector<double> valueData;
    std::vector<Event> allEvents = eventsController.listEventsAdministrator();
    std::map<double, double> distributionOfNumberOfAttendants;
    for(auto event:allEvents){
        distributionOfNumberOfAttendants[event.getNumberOfAttendants()] ++;
    }
    for(auto bar:distributionOfNumberOfAttendants){
        keyData.push_back(bar.first);
        valueData.push_back(bar.second);
    }
    barPlot->setData(keyData, valueData);
    barPlot->rescaleAxes();
    customPlot->resize(width(), height());
    customPlot->replot();
}

StatisticsUI::~StatisticsUI() {
    delete ui;
}

void StatisticsUI::handleExitPressed() {
    this->hide();
    emit this->exitClicked();
}
