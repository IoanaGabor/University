#pragma once

typedef struct {
    char *name;
    char *category;
    int quantity;
    int expiration_year;
    int expiration_month;
    int expiration_day;
} Product;

Product *
createProduct(const char name[], const char category[], int quantity, int expiration_year, int expiration_month,
              int expiration_day);

char *getName(Product *product);

char *getCategory(Product *product);

int getQuantity(Product *product);

int getExpirationDay(Product *product);

int getExpirationMonth(Product *product);

int getExpirationYear(Product *product);

int setQuantity(Product *product, int quantity);

void swapProducts(Product *first_product, Product *second_product);

void productToString(Product product, char *string_representation);

void destroyProductFields(Product *product);

void destroyProduct(Product *product);

void *createCopyOfProduct(const void *oldProduct);