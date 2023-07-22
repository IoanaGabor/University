
#include "test_domain.h"
#include "domain/product.h"
#include "domain/vector.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_product() {
    Product *product = createProduct("asdfsa", "sweets", 3, 2023, 8, 3);
    assert(strcmp(product->name, "asdfsa") == 0);
    assert(strcmp(product->category, "sweets") == 0);
    assert(getQuantity(product) == 3);
    assert(getExpirationYear(product) == 2023);
    assert(getExpirationMonth(product) == 8);
    assert(getExpirationDay(product) == 3);
    destroyProductFields(product);
    free(product);
}

void test_vector() {
    Product *product = createProduct("asdfsa", "sweets", 3, 2023, 8, 3);
    Vector *vector = createVector(1,sizeof(Product), &destroyProductFields);
    add(vector, createCopyOfProduct(product));
    add(vector, createCopyOfProduct(product));
    add(vector, createCopyOfProduct(product));
    assert(getLength(vector) == 3);
    assert(getCapacity(vector) == 4);
    delete_last_element(vector);
    assert(getLength(vector) == 2);
    destroyVectorData(vector);
}


void run_tests_domain() {
    test_product();
    test_vector();
}