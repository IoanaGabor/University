//
// Created by ioana on 08.06.2023.
//

#ifndef A89_913_GABOR_IOANA_STATISTICSUI_H
#define A89_913_GABOR_IOANA_STATISTICSUI_H

#include <QWidget>
#include "controller/EventsController.h"
#include "qcustomplot-source/qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StatisticsUI; }
QT_END_NAMESPACE

class StatisticsUI : public QWidget {
Q_OBJECT

public:
    explicit StatisticsUI(EventsController& eventsController,QWidget *parent = nullptr);

    ~StatisticsUI() override;
signals:
    void exitClicked();
private:
    Ui::StatisticsUI *ui;
    EventsController& eventsController;
    void handleExitPressed();
    QCustomPlot *customPlot;
    QCPBars *barPlot;
public:
    void loadPlot() const;
};


#endif //A89_913_GABOR_IOANA_STATISTICSUI_H
