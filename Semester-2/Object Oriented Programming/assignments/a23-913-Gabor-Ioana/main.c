#include <stdio.h>
#include "domain/product.h"
#include "repository/repository.h"
#include "ui/ui.h"
#include <time.h>
#include <tests/test_domain.h>
#include <tests/test_repository.h>
#include <tests/test_service.h>

void add_hardcoded_products_to_service(Service *service) {
    addProduct(service, "napolact", "dairy", 2, 2023, 4, 30);
    addProduct(service, "milka", "sweets", 3, 2023, 3, 30);
    addProduct(service, "salmon", "meat", 5, 2023, 3, 30);
    addProduct(service, "nuggets", "meat", 1, 2023, 5, 30);
    addProduct(service, "oreo", "sweets", 7, 2023, 3, 30);
    addProduct(service, "pomegranate", "fruit", 4, 2023, 3, 30);
    addProduct(service, "apple", "fruit", 6, 2023, 3, 30);
    addProduct(service, "lemon", "dairy", 2, 2023, 3, 30);
    addProduct(service, "bread", "dairy", 7, 2023, 3, 30);
    addProduct(service, "milk", "dairy", 10, 2023, 3, 30);
}

int main(int argc, char **argv) {
    run_tests_domain();
    run_tests_repository();
    run_tests_service();
    Repository *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository();
    Service *service = createService(repository, undoRedoRepository);
    add_hardcoded_products_to_service(service);
    UI *ui = createUI(service);
    if (repository == NULL || service == NULL || ui == NULL) {
        printf("application could not start\n");
    }
    runConsoleMenu(ui);
    destroyUI(ui);
}
