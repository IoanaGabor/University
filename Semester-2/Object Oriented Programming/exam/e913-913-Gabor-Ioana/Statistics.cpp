//
// Created by ioana on 16.06.2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Statistics.h" resolved

#include "Statistics.h"
#include "ui_Statistics.h"
#include "qcustomplot-source/qcustomplot.h"


Statistics::Statistics(Controller *controller,QWidget *parent) :
        controller(controller),QWidget(parent), ui(new Ui::Statistics) {
    ui->setupUi(this);
    this->setWindowTitle("Stats");
    mainLayout = new QHBoxLayout(this);
    customPlot = new QCustomPlot();
    mainLayout->addWidget(customPlot);
    update();
}

Statistics::~Statistics() {
    delete ui;
}

void Statistics::update() {
    auto mp = this->controller->getStatisticsMap();
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QVector<double> keyData;
    QVector<double> valueData;
    int cnt = 0;
    for(auto a:mp){
        keyData.push_back(cnt);
        valueData.push_back(a.second);
        cnt++;
    }
    bars->setData(keyData, valueData);
    customPlot->rescaleAxes();
    customPlot->replot();
}
