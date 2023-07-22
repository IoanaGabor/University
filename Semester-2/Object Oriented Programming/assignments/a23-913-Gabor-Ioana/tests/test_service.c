#include "service/service.h"
#include "test_service.h"
#include <assert.h>
#include <string.h>

void test_create_service_destroy_service() {
    Repository *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository();
    Service *service = createService(repository, undoRedoRepository);
    addProduct(service, "napolact", "dairy", 2, 2023, 4, 30);
    Vector *all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products) == 1);
    destroyService(service);
}

void test_undo_redo_service() {
    Repository *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository();
    Service *service = createService(repository, undoRedoRepository);
    addProduct(service, "napolact", "dairy", 2, 2023, 4, 30);
    addProduct(service, "sana", "dairy", 2, 2023, 4, 30);
    addProduct(service, "covalact", "dairy", 2, 2023, 4, 30);
    Vector *all_products;
    performUndoOperation(service);
    all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products) == 2);
    performRedoOperation(service);
    all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products) == 3);
    destroyService(service);
}

void test_search(){
    Repository *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository();
    Service *service = createService(repository, undoRedoRepository);
    addProduct(service, "napolact", "dairy", 2, 2023, 4, 30);
    addProduct(service, "sana", "dairy", 2, 2023, 4, 30);
    addProduct(service, "idkana", "dairy", 5, 2023, 4, 30);
    addProduct(service, "covalact", "dairy", 2, 2023, 4, 30);
    Vector *searched_products;
    searched_products = getAllProductsWhoseNameContainAGivenStringSortedByQuantity(service, "ana", true);
    assert(getLength(searched_products) == 2);
    assert(strcmp(getName(get_element_at_position(searched_products,0)), "sana")==0);
    assert(strcmp(getName(get_element_at_position(searched_products,1)), "idkana")==0);
    searched_products = getAllProductsWhoseNameContainAGivenStringSortedByQuantity(service, "ana", false);
    assert(getLength(searched_products) == 2);
    assert(strcmp(getName(get_element_at_position(searched_products,1)), "sana")==0);
    assert(strcmp(getName(get_element_at_position(searched_products,0)), "idkana")==0);

    destroyService(service);

}

void run_tests_service() {
    test_create_service_destroy_service();
    test_undo_redo_service();
    test_search();
}