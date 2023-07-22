#pragma once

#include "repository/repository.h"
#include "domain/product.h"
#include "repository/undo_redo_repository.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    Repository *product_repository;
    UndoRedoRepository *undoRedoRepository;
} Service;

Service *createService(Repository *product_repository, UndoRedoRepository *undoRedoRepository);

int addProduct(Service *service, char *name, char *category, int quantity, int expiration_year, int expiration_month,
               int expirationDay);

int updateQuantityOfProductGivenByNameAndCategory(Service *service, char *name, char *category, int new_quantity);

int deleteProductGivenByNameAndCategory(Service *service, char *name, char *category);

Vector *
getAllProductsWhoseNameContainAGivenStringSortedByQuantity(Service *service, char *searched_string, bool isAscending);

Vector *getAllProductsWhoseNameContainAGivenString(Service *service, char *searched_string);

void destroyService(Service *service);

int performUndoOperation(Service *service);

Vector *getProductsWhichExpireSoon(Service *service, char *category, int howManyDaysTillExpiry);

Vector *getAllProductsWhoseCategoryContainAGivenString(Service *service, char *searched_string);

int performRedoOperation(Service *service);

Vector *getProductsWithQuantityLessThan(Service *service, int requiredQuantity);