/********************************************************************************
** Form generated from reading UI file 'AdminUI.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINUI_H
#define UI_ADMINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminUI
{
public:

    void setupUi(QWidget *AdminUI)
    {
        if (AdminUI->objectName().isEmpty())
            AdminUI->setObjectName("AdminUI");
        AdminUI->resize(400, 300);

        retranslateUi(AdminUI);

        QMetaObject::connectSlotsByName(AdminUI);
    } // setupUi

    void retranslateUi(QWidget *AdminUI)
    {
        AdminUI->setWindowTitle(QCoreApplication::translate("AdminUI", "AdminUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminUI: public Ui_AdminUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINUI_H
