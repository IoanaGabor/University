#include "product.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Product *
createProduct(const char name[], const char category[], int quantity, int expiration_year, int expiration_month,
              int expiration_day) {
    Product *new_product = (Product *) malloc(sizeof(Product));
    if (new_product == NULL) {
        return NULL;
    }
    new_product->quantity = quantity;
    new_product->expiration_year = expiration_year;
    new_product->expiration_month = expiration_month;
    new_product->expiration_day = expiration_day;
    new_product->name = (char *) malloc(sizeof(char) * strlen(name) + 1);
    strcpy(new_product->name, name);
    new_product->category = (char *) malloc(sizeof(char) * strlen(category) + 1);
    strcpy(new_product->category, category);
    return new_product;
}

void *createCopyOfProduct(const void *oldProduct) {
    Product *newProduct = createProduct(((Product *) oldProduct)->name, ((Product *) oldProduct)->category,
                                        ((Product *) oldProduct)->quantity,
                                        ((Product *) oldProduct)->expiration_year,
                                        ((Product *) oldProduct)->expiration_month,
                                        ((Product *) oldProduct)->expiration_day);
    return newProduct;
}

char *getName(Product *product) {
    return product->name;
}

char *getCategory(Product *product) {
    return product->category;
}

int getQuantity(Product *product) {
    return product->quantity;
}

int getExpirationDay(Product *product) {
    return product->expiration_day;
}

int getExpirationMonth(Product *product) {
    return product->expiration_month;
}


int getExpirationYear(Product *product) {
    return product->expiration_year;
}


void swapProducts(Product *first_product, Product *second_product) {
    Product auxiliary_product = *(first_product);
    *(first_product) = *(second_product);
    *(second_product) = auxiliary_product;
}

void productToString(Product product, char *string_representation) {
    string_representation[0] = 0;
    strcat(string_representation, "Name: ");
    strcat(string_representation, product.name);
    strcat(string_representation, " Category: ");
    strcat(string_representation, product.category);
    strcat(string_representation, " Quantity: ");
    char integer_as_string[10];
    integer_as_string[0] = 0;
    sprintf(integer_as_string, "%d", product.quantity);
    strcat(string_representation, integer_as_string);
    strcat(string_representation, " Expiration Date: ");
    integer_as_string[0] = 0;
    sprintf(integer_as_string, "%d/", product.expiration_year);
    strcat(string_representation, integer_as_string);
    integer_as_string[0] = 0;
    sprintf(integer_as_string, "%d/", product.expiration_month);
    strcat(string_representation, integer_as_string);
    integer_as_string[0] = 0;
    sprintf(integer_as_string, "%d", product.expiration_day);
    strcat(string_representation, integer_as_string);
    strcat(string_representation, "\n");
}

void destroyProductFields(Product *product) {
    if (product != NULL) {
        if (product->category != NULL) {
            free(product->category);
            product->category = NULL;
        }
        if (product->name != NULL) {
            free(product->name);
            product->name = NULL;
        }
    }
}

void destroyProduct(Product *product) {
    if (product != NULL) {
        if (product->category != NULL) {
            free(product->category);
            product->category = NULL;
        }
        if (product->name != NULL) {
            free(product->name);
            product->name = NULL;
        }
        free(product);
        product = NULL;
    }
}