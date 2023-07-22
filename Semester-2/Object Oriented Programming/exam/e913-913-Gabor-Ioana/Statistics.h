//
// Created by ioana on 16.06.2023.
//

#ifndef E913_913_GABOR_IOANA_STATISTICS_H
#define E913_913_GABOR_IOANA_STATISTICS_H

#include <QWidget>
#include <QHBoxLayout>
#include "AbstractObserver.h"
#include "Controller.h"
#include "qcustomplot-source/qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Statistics; }
QT_END_NAMESPACE

class Statistics : public QWidget , public AbstractObserver {
Q_OBJECT

public:
    explicit Statistics(Controller *controller,QWidget *parent = nullptr);

    void update() override;

    ~Statistics() override;

private:
    Ui::Statistics *ui;
    Controller *controller;
    QHBoxLayout *mainLayout;
    QCustomPlot *customPlot;
};


#endif //E913_913_GABOR_IOANA_STATISTICS_H
