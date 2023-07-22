#include "repository/repository.h"
#include "test_repository.h"


#include "test_domain.h"
#include "domain/product.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_create_repository_destroy_repository() {
    Product *product = createProduct("asdfsa", "sweets", 3, 2023, 8, 3);
    Repository *repository = createRepository();
    addProductToRepository(repository, product);
    Vector *all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products) == 1);
    destroyRepository(repository);
}

void test_delete_repository() {
    Product *product = createProduct("asdfsa", "sweets", 3, 2023, 8, 3);
    Repository *repository = createRepository();
    addProductToRepository(repository, product);
    deleteProductByNameAndCategory(repository, "asdfsa", "sweets");
    Vector *all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products) == 0);
    destroyRepository(repository);
}

void test_update_repository() {
    Product *product = createProduct("asdfsa", "sweets", 3, 2023, 8, 3);
    Repository *repository = createRepository();
    addProductToRepository(repository, product);
    updateProductGivenByNameAndCategory(repository, "asdfsa", "sweets",createProduct("asdfsa", "sweets", 57, 2023, 8, 3));
    Vector *all_products = getAllProductsFromRepository(repository);
    assert(getLength(all_products)== 1);
    destroyRepository(repository);
}

void run_tests_repository() {
    test_create_repository_destroy_repository();
    test_delete_repository();
    test_update_repository();
}