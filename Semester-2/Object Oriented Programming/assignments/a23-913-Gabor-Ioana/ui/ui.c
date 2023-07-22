#include "ui.h"
#include "service/service.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils/utils.h"

UI *createUI(Service *service) {
    UI *ui = (UI *) malloc(sizeof(UI));
    if (ui == NULL) {
        return NULL;
    }
    ui->product_service = service;
    return ui;
}


void destroyUI(UI *ui) {
    if (ui != NULL) {
        destroyService(ui->product_service);
        free(ui);
    }
}


void printConsoleMenu() {
    printf("add <name> <category> <quantity> <expiration day>\n");
    printf("delete <name> <category>\n");
    printf("update <name> <category> <quantity>\n");
    printf("search <asc/desc> <optional string>\n");
    printf("filter <maximum quantity>\n");
    printf("expire <number of days> <optional string>\n");
    printf("undo\n");
    printf("redo\n");
    printf("exit\n");
}

void printAVectorOfProducts(Vector *products) {
    char printed_string[10000];
    vectorOfProductsToString(products, &productToString, printed_string);
    printf("%s", printed_string);
}

void handleAddCommand(UI *ui, char **arguments) {
    int quantity = getPositiveIntegerFromString(arguments[3]);
    int year, month, day;
    getYearMonthDayFromDateString(arguments[4], &year, &month, &day);
    if (quantity < 1) {
        printf("quantity should be positive integers\n");
        return;
    }
    if (year < 1 || month < 1 || day < 1) {
        printf("invalid date\n");
    }
    int returnCodeForAdd = addProduct(ui->product_service, arguments[1], arguments[2], quantity, year, month, day);
    if (returnCodeForAdd == -2) {
        printf("The category should be one of dairy, sweets, meat or fruit\n");
    } else if (returnCodeForAdd == -3) {
        printf("This product already exists, but the quantity could not be updated, since there is a different expiry day.\n");
    } else if (returnCodeForAdd == -1) {
        printf("Product already exists, quantity was updated\n");
    } else {
        printf("Successfully added\n");
    }
}

void handleUpdateCommand(UI *ui, char **arguments) {
    int quantity = getPositiveIntegerFromString(arguments[3]);
    if (quantity == -1) {
        printf("quantity should be a positive integer");
        return;
    }
    int return_code_for_update = updateQuantityOfProductGivenByNameAndCategory(ui->product_service, arguments[1],
                                                                               arguments[2], quantity);
    if (return_code_for_update == -2) {
        printf("The category should be one of dairy, sweets, meat or fruit");
    } else if (return_code_for_update == -1) {
        printf("Product was not found\n");
    } else {
        printf("Successfully updated\n");
    }
}

void handleDeleteCommand(UI *ui, char **arguments) {
    int return_code_for_delete = deleteProductGivenByNameAndCategory(ui->product_service, arguments[1], arguments[2]);
    if (return_code_for_delete == -1) {
        printf("Product was not found\n");
    } else {
        printf("Successfully deleted\n");
    }
}

void handleSearchCommand(UI *ui, char **arguments, int arguments_length) {
    Vector *filtered_products;
    bool isAscending;
    if (strcmp(arguments[1], "asc") == 0) {
        isAscending = true;
    } else if (strcmp(arguments[1], "desc") == 0) {
        isAscending = false;
    } else {
        printf("invalid format\n");
        return;
    }
    if (arguments_length == 2) {
        filtered_products = getAllProductsWhoseNameContainAGivenStringSortedByQuantity(ui->product_service,
                                                                                       "", isAscending);
    } else {
        filtered_products = getAllProductsWhoseNameContainAGivenStringSortedByQuantity(
                ui->product_service, arguments[2], isAscending);
    }
    printAVectorOfProducts(filtered_products);
    destroy(filtered_products);
}

void handleFilterCommand(UI *ui, char **arguments, int arguments_length) {
    Vector *filtered_products;
    int whatQuantity = getPositiveIntegerFromString(arguments[1]);
    if (whatQuantity < 0) {
        printf("quantity should be a positive number\n");
        return;
    }
    filtered_products = getProductsWithQuantityLessThan(ui->product_service, whatQuantity);
    printAVectorOfProducts(filtered_products);
    destroy(filtered_products);
}


void handleExpireCommand(UI *ui, char **arguments, int arguments_length) {
    Vector *filtered_products;
    int howManyDays = getPositiveIntegerFromString(arguments[1]);
    if (howManyDays == -1) {
        printf("the number of days should be a positive integer");
        return;
    }
    if (arguments_length == 2) {
        filtered_products = getProductsWhichExpireSoon(ui->product_service, "", howManyDays);
    } else {
        filtered_products = getProductsWhichExpireSoon(ui->product_service, arguments[2], howManyDays);
    }
    printAVectorOfProducts(filtered_products);
    destroy(filtered_products);
}

void handleUndoCommand(UI *ui) {
    int return_code = performUndoOperation(ui->product_service);
    if (return_code == 0) {
        printf("successful undo\n");
    } else {
        printf("can't undo, no more undos\n");
    }
}


void handleRedoCommand(UI *ui) {
    int return_code = performRedoOperation(ui->product_service);
    if (return_code == 0) {
        printf("successful redo\n");
    } else {
        printf("can't redo, no more redos\n");
    }
}


void processLine(UI *ui, char *line) {
    if (strlen(line) == 0) {
        return;
    }
    char *argument = strtok(line, " ");
    char **arguments = (char **) malloc(sizeof(char *) * 6);
    int arguments_length = 0;
    while (argument != NULL && arguments_length < 6) {
        arguments[arguments_length] = (char *) malloc(sizeof(char) * 100);
        strcpy(arguments[arguments_length], argument);
        arguments_length++;
        argument = strtok(NULL, " ");
    }
    if (strcmp(arguments[0], "add") == 0 && arguments_length == 5) {
        handleAddCommand(ui, arguments);
    } else if (strcmp(arguments[0], "update") == 0 && arguments_length == 4) {
        handleUpdateCommand(ui, arguments);
    } else if (strcmp(arguments[0], "delete") == 0 && arguments_length == 3) {
        handleDeleteCommand(ui, arguments);
    } else if (strcmp(arguments[0], "search") == 0 && arguments_length <= 3 && arguments_length >= 2) {
        handleSearchCommand(ui, arguments, arguments_length);
    } else if (strcmp(arguments[0], "filter") == 0 && arguments_length == 2) {
        handleFilterCommand(ui, arguments, arguments_length);
    } else if (strcmp(arguments[0], "expire") == 0 && arguments_length <= 3 && arguments_length >= 2) {
        handleExpireCommand(ui, arguments, arguments_length);
    } else if (strcmp(arguments[0], "undo") == 0 && arguments_length <= 1) {
        handleUndoCommand(ui);
    } else if (strcmp(arguments[0], "redo") == 0 && arguments_length <= 1) {
        handleRedoCommand(ui);
    } else {
        printf("invalid command\n");
    }
    for (int i = 0; i < arguments_length; i++) {
        free(arguments[i]);
    }
    free(arguments);
    free(argument);
}

void runConsoleMenu(UI *ui) {
    char line[200];
    line[0] = 0;
    while (1) {
        printConsoleMenu();
        gets(line);
        if (strcmp(line, "exit") == 0) {
            break;
        }
        processLine(ui, line);
    }
}