/********************************************************************************
** Form generated from reading UI file 'UserUI.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERUI_H
#define UI_USERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserUI
{
public:

    void setupUi(QWidget *UserUI)
    {
        if (UserUI->objectName().isEmpty())
            UserUI->setObjectName("UserUI");
        UserUI->resize(400, 300);

        retranslateUi(UserUI);

        QMetaObject::connectSlotsByName(UserUI);
    } // setupUi

    void retranslateUi(QWidget *UserUI)
    {
        UserUI->setWindowTitle(QCoreApplication::translate("UserUI", "UserUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserUI: public Ui_UserUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERUI_H
