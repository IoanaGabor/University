#include <stdlib.h>
#include "repository.h"
#include <string.h>
#include "domain/product.h"

Repository *createRepository() {
    Repository *repository = (Repository *) malloc(sizeof(Repository));
    if (repository == NULL) {
        return NULL;
    }
    repository->all_products = createVector(1, sizeof(Product), &destroyProductFields);
    return repository;
}

void destroyRepository(Repository *repository) {
    if (repository != NULL) {
        destroy(repository->all_products);
        free(repository);
        repository = NULL;
    }
}

void updateProductGivenByItsPosition(Repository *repository, int position, Product *new_product) {
    set_element_at_position(repository->all_products, position, new_product);
}


int findIndexOfProductGivenByNameAndCategory(Repository *repository, char name[], char category[]) {
    for (int i = 0; i < repository->all_products->length; i++) {
        Product *current_product = (Product *) get_element_at_position(repository->all_products, i);
        if (strcmp(getName(current_product), name) == 0 && strcmp(getCategory(current_product), category) == 0) {
            return i;
        }
    }
    return -1;
}

Product *getProductGivenByNameAndCategory(Repository *repository, char name[], char category[]) {
    for (int i = 0; i < getLength(repository->all_products); i++) {
        Product *current_product = (Product *) get_element_at_position(repository->all_products, i);
        if (strcmp(getName(current_product), name) == 0 && strcmp(getCategory(current_product), category) == 0) {
            return current_product;
        }
    }
    return NULL;
}

int addProductToRepository(Repository *repository, Product *product) {
    int position_in_vector = findIndexOfProductGivenByNameAndCategory(repository, getName(product),
                                                                      getCategory(product));
    if (position_in_vector == -1) {
        add(repository->all_products, product);
        return 0;
    } else {
        return -1;
    }
}

int updateProductGivenByNameAndCategory(Repository *repository, char name[], char category[], Product *new_product) {
    int position_in_vector = findIndexOfProductGivenByNameAndCategory(repository, name, category);
    if (position_in_vector == -1) {
        return -1;
    } else {
        updateProductGivenByItsPosition(repository, position_in_vector, new_product);
        return 0;
    }
}

int deleteProductByNameAndCategory(Repository *repository, char name[], char category[]) {
    int index_of_product = findIndexOfProductGivenByNameAndCategory(repository, name, category);
    if (index_of_product == -1) {
        return -1;
    } else {
        swapProducts((Product *) get_element_at_position(repository->all_products, index_of_product),
                     (Product *) get_element_at_position(repository->all_products,
                                                         repository->all_products->length - 1));
        delete_last_element(repository->all_products);
        return 0;
    }
}

Vector *getAllProductsFromRepository(Repository *repository) {
    return make_copy_of_vector(repository->all_products, (void *(*)(void *)) &createCopyOfProduct);
}
