//
// Created by ioana on 26.05.2023.
//
#include <QApplication>
#include <QPushButton>
#include "Repository.h"
#include "Controller.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repository = Repository("../equations.txt");
    Controller controller = Controller(repository);
    GUI gui = GUI(controller);
    gui.show();
    return QApplication::exec();
}