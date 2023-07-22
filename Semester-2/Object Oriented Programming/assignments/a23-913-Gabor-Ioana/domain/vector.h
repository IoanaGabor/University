#pragma once

#include "domain/product.h"

typedef Product TElement;

typedef struct {
    void *elements;
    int length;
    int capacity;
    int elementSize;

    void (*freeElementData)(void *pointerToElem);
} Vector;

Vector *createVector(int capacity, int elementSize, void (*free_element_data)());

void destroy(Vector *vector);

void add(Vector *vector, const void *element);

void *get_element_at_position(Vector *vector, int position);

void set_element_at_position(Vector *vector, int position, void *element);

Vector *make_copy_of_vector(Vector *original_vector, void *(*createCopyOfElem)(void *oldElem));

void delete_last_element(Vector *vector);

int getLength(Vector *vector);

int getCapacity(Vector *vector);

void destroyVectorData(Vector *vector);

void
vectorOfProductsToString(Vector *vector, void (*element_to_string)(TElement element, char *resulting_element_string),
                         char *resulting_vector_string);
