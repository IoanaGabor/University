/********************************************************************************
** Form generated from reading UI file 'statisticsUI.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICSUI_H
#define UI_STATISTICSUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticsUI
{
public:

    void setupUi(QWidget *StatisticsUI)
    {
        if (StatisticsUI->objectName().isEmpty())
            StatisticsUI->setObjectName("StatisticsUI");
        StatisticsUI->resize(400, 300);

        retranslateUi(StatisticsUI);

        QMetaObject::connectSlotsByName(StatisticsUI);
    } // setupUi

    void retranslateUi(QWidget *StatisticsUI)
    {
        StatisticsUI->setWindowTitle(QCoreApplication::translate("StatisticsUI", "StatisticsUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticsUI: public Ui_StatisticsUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICSUI_H
