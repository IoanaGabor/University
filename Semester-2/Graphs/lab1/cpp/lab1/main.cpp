#include <iostream>
#include "UI.h"
#include <fstream>
using namespace std;

int main() {
    UI* ui = new UI();
    ui->runConsoleMenu();
    return 0;
}
