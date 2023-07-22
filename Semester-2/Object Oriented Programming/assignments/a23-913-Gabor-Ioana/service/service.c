#include "service.h"
#include "domain/product.h"
#include "repository/repository.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils/utils.h"
#include "repository/undo_redo_repository.h"
#include "ui/ui.h"


Service *createService(Repository *product_repository, UndoRedoRepository *undoRedoRepository) {
    Service *service = (Service *) malloc(sizeof(Service));
    if (service == NULL) {
        return NULL;
    }
    service->product_repository = product_repository;
    service->undoRedoRepository = undoRedoRepository;
    addState(service->undoRedoRepository, service->product_repository->all_products);
    return service;
}

void destroyService(Service *service) {
    if (service != NULL) {
        if (service->undoRedoRepository != NULL) {
            destroyUndoRedoRepository(service->undoRedoRepository);
            service->undoRedoRepository = NULL;
        }
        if (service->product_repository != NULL) {
            destroyRepository(service->product_repository);
            service->product_repository = NULL;
        }

        free(service);
    }
}


int addProduct(Service *service, char *name, char *category, int quantity, int expiration_year, int expiration_month,
               int expirationDay) {
    if (validateCategory(category) == -1) {
        return -2;
    }
    int return_code_for_add;
    Product *product = createProduct(name, category, quantity, expiration_year,
                                     expiration_month, expirationDay);
    return_code_for_add = addProductToRepository(service->product_repository,
                                                 product);
    if (return_code_for_add == -1) {
        Product *updated_product = getProductGivenByNameAndCategory(service->product_repository,
                                                                    name, category);
        if (getExpirationDay(updated_product) != expirationDay ||
            getExpirationMonth(updated_product) != expiration_month ||
            getExpirationYear(updated_product) != expiration_year) {
            return -3;
        }
        Product *updatedProduct = createProduct(name, category, quantity + updated_product->quantity,
                                                expiration_year,
                                                expiration_month, expirationDay);
        updateProductGivenByNameAndCategory(service->product_repository, name, category,
                                            updatedProduct);
    }
    addState(service->undoRedoRepository, service->product_repository->all_products);
    return return_code_for_add;
}

int performUndoOperation(Service *service) {
    if (canPerformUndo(service->undoRedoRepository)) {
        destroyVectorData(service->product_repository->all_products);
        service->product_repository->all_products = make_copy_of_vector(undo_repository(service->undoRedoRepository),
                                                                        (void *(*)(void *)) &createCopyOfProduct);
        return 0;
    } else {
        return -1;
    }

}


int performRedoOperation(Service *service) {
    if (canPerformRedo(service->undoRedoRepository)) {
        destroyVectorData(service->product_repository->all_products);
        service->product_repository->all_products = make_copy_of_vector(redo_repository(service->undoRedoRepository),
                                                                        (void *(*)(void *)) &createCopyOfProduct);
        return 0;
    } else {
        return -1;
    }

}


int updateQuantityOfProductGivenByNameAndCategory(Service *service, char *name, char *category, int new_quantity) {
    if (validateCategory(category) == -1) {
        return -2;
    }
    Product *updated_product = getProductGivenByNameAndCategory(service->product_repository, name, category);
    if (updated_product == NULL) {
        return -1;
    }
    int returnCodeForUpdate = updateProductGivenByNameAndCategory(service->product_repository, name, category,
                                                                  createProduct(name, category, new_quantity,
                                                                                updated_product->expiration_year,
                                                                                updated_product->expiration_month,
                                                                                updated_product->expiration_day));
    if (returnCodeForUpdate == 0) {
        addState(service->undoRedoRepository, service->product_repository->all_products);
    }
    return returnCodeForUpdate;
}

int deleteProductGivenByNameAndCategory(Service *service, char *name, char *category) {
    int returnCodeForDelete = deleteProductByNameAndCategory(service->product_repository, name, category);
    if (returnCodeForDelete == 0) {
        addState(service->undoRedoRepository, service->product_repository->all_products);
    }
    return returnCodeForDelete;
}

Vector *getAllProductsWhoseNameContainAGivenString(Service *service, char *searched_string) {
    Vector *all_products = getAllProductsFromRepository(service->product_repository);
    Vector *filtered_products = createVector(1, sizeof(Product), &destroyProductFields);;
    int number_of_products = getLength(all_products);
    for (int i = 0; i < number_of_products; i++) {
        Product *current_product = (Product *) get_element_at_position(all_products, i);
        if (strstr(current_product->name, searched_string) != NULL) {
            add(filtered_products, current_product);
        }
    }
    return filtered_products;
}

Vector *getAllProductsWhoseCategoryContainAGivenString(Service *service, char *searched_string) {
    Vector *all_products = getAllProductsFromRepository(service->product_repository);
    Vector *filtered_products = createVector(1, sizeof(Product), &destroyProductFields);;
    int number_of_products = getLength(all_products);
    for (int i = 0; i < number_of_products; i++) {
        Product *current_product = (Product *) get_element_at_position(all_products, i);
        if (strstr(current_product->category, searched_string) != NULL) {
            add(filtered_products, current_product);
        }
    }
    return filtered_products;
}

void sortByQuantity(Vector *products, bool ascending) {
    int length = getLength(products);
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            Product *first_product = (Product *) get_element_at_position(products, i);
            Product *second_product = (Product *) get_element_at_position(products, j);
            if ((ascending && first_product->quantity > second_product->quantity) ||
                (!ascending && first_product->quantity < second_product->quantity)) {
                swapProducts(first_product, second_product);
            }
        }
    }
}

Vector *getAllProductsWhoseNameContainAGivenStringSortedByQuantity(Service *service,
                                                                   char *searched_string, bool ascending) {
    Vector *filtered_products = getAllProductsWhoseNameContainAGivenString(service, searched_string);

    sortByQuantity(filtered_products, ascending);
    return filtered_products;
}

Vector *getProductsWhichExpireSoon(Service *service,
                                   char *category,
                                   int howManyDaysTillExpiry) {
    Vector *filtered_products = getAllProductsWhoseCategoryContainAGivenString(service, category);
    int number_of_products = getLength(filtered_products);
    int howManyDaysSinceToday;
    Vector *soonToExpireProducts = createVector(1, sizeof(Product), destroyProductFields);
    for (int i = 0; i < number_of_products; i++) {
        Product *current_product = (Product *) get_element_at_position(filtered_products, i);
        howManyDaysSinceToday = getNumberOfDaysBetweenCurrentDateAndThis(current_product->expiration_year,
                                                                         current_product->expiration_month,
                                                                         current_product->expiration_day);
        if (howManyDaysSinceToday > 0 && howManyDaysSinceToday < howManyDaysTillExpiry) {
            add(soonToExpireProducts, createCopyOfProduct(current_product));
        }
    }
    destroy(filtered_products);
    return soonToExpireProducts;
}

Vector *getProductsWithQuantityLessThan(Service *service,
                                        int requiredQuantity) {
    Vector *filtered_products = getAllProductsWhoseCategoryContainAGivenString(service, "");
    int number_of_products = getLength(filtered_products);
    Vector *productsWithQuantityLessThan = createVector(1, sizeof(Product), destroyProductFields);
    for (int i = 0; i < number_of_products; i++) {
        Product *current_product = (Product *) get_element_at_position(filtered_products, i);
        int current_quantity = getQuantity(current_product);
        if (current_quantity < requiredQuantity) {
            add(productsWithQuantityLessThan, createCopyOfProduct(current_product));
        }
    }
    destroy(filtered_products);
    return productsWithQuantityLessThan;
}