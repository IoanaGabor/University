//
// Created by ioana on 26.05.2023.
//

#ifndef T3_913_GABOR_IOANA_GUI_H
#define T3_913_GABOR_IOANA_GUI_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include "Controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Controller &controller,QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    Controller &controller;
    QVBoxLayout *mainLayout;
    QListWidget *equationsList;
    QPushButton *computeSolutionsButton;
    QLabel *solutionsLabel;
    QFormLayout *updateForm;
    QLineEdit *aLineEdit;
    QLabel *aLabel;
    QLineEdit *bLineEdit;
    QLabel *bLabel;
    QLineEdit *cLineEdit;
    QLabel *cLabel;
    QPushButton *updateButton;
    std::vector<Equation> allEquations;
    void updateEquation();
    void showSolutions();
    void loadEquations();

    void buildUpdateForm();
};


#endif //T3_913_GABOR_IOANA_GUI_H
