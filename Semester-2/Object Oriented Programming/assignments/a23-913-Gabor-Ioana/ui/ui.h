#pragma once

#include "service/service.h"

typedef struct {
    Service *product_service;
} UI;

UI *createUI(Service *service);

void runConsoleMenu(UI *ui);

void destroyUI(UI *ui);

void printAVectorOfProducts(Vector *products);
