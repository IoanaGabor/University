#pragma once

#include "domain/vector.h"


typedef struct {
    Vector *all_products;
} Repository;

Repository *createRepository();

int addProductToRepository(Repository *repository, Product *product);

Vector *getAllProductsFromRepository(Repository *repository);

int deleteProductByNameAndCategory(Repository *repository, char name[], char category[]);

int updateProductGivenByNameAndCategory(Repository *repository, char name[], char category[], Product *new_product);

Product *getProductGivenByNameAndCategory(Repository *repository, char name[], char category[]);

void destroyRepository(Repository *repository);