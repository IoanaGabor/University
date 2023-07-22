#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Vector *createVector(int capacity, int elementSize, void (*freeElementData)()) {
    Vector *vector = (Vector *) malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->capacity = capacity;
    vector->length = 0;
    vector->elementSize = elementSize;
    vector->elements = malloc(capacity * elementSize);
    if (vector->elements == NULL)
        return NULL;
    vector->freeElementData = freeElementData;
    return vector;
}

void destroy(Vector *vector) {
    if (vector == NULL)
        return;
    for (int i = 0; i < vector->length; i++) {
        vector->freeElementData(get_element_at_position(vector, i));
    }
    if (vector->elements != NULL) {
        free(vector->elements);
        vector->elements = NULL;
    }
    free(vector);
    vector = NULL;
}

void destroyVectorData(Vector *vector) {
    if (vector == NULL)
        return;
    for (int i = 0; i < vector->length; i++) {
        vector->freeElementData(get_element_at_position(vector, i));
    }
    if (vector->elements != NULL) {
        free(vector->elements);
        vector->elements = NULL;
    }
}


void resize(Vector *vector) {
    if (vector == NULL)
        return;

    vector->capacity *= 2;
    void *pointerToNewElements = malloc(vector->elementSize * vector->capacity);
    if (pointerToNewElements == NULL) {
        return;
    }
    memcpy(pointerToNewElements, vector->elements, vector->elementSize * vector->length);
    free(vector->elements);
    vector->elements = pointerToNewElements;
}

void add(Vector *vector, const void *element) {
    if (vector == NULL)
        return;
    if (vector->elements == NULL)
        return;
    if (vector->length == vector->capacity)
        resize(vector);
    memcpy(vector->elements + vector->length * vector->elementSize, element, vector->elementSize);
    vector->length++;
}

void *get_element_at_position(Vector *vector, int position) {
    if (position >= vector->length) {
        return NULL;
    }
    return (vector->elements + position * vector->elementSize);
}

void set_element_at_position(Vector *vector, int position, void *element) {
    if (position >= vector->length) {
        return;
    }
    memcpy(vector->elements + position * vector->elementSize, element, vector->elementSize);
}

void delete_last_element(Vector *vector) {
    if (vector == NULL)
        return;
    if (vector->elements == NULL)
        return;
    if (vector->length == 0) {
        return;
    }
    destroyProductFields(get_element_at_position(vector, vector->length - 1));
    vector->length--;
}

Vector *make_copy_of_vector(Vector *original_vector, void *(*createCopyOfElem)(void *oldElem)) {

    Vector *vector = (Vector *) malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->capacity = original_vector->capacity;
    vector->length = original_vector->length;
    vector->elementSize = original_vector->elementSize;
    vector->elements = malloc(original_vector->capacity * original_vector->elementSize);
    if (vector->elements == NULL)
        return NULL;
    vector->freeElementData = original_vector->freeElementData;
    for (int i = 0; i < original_vector->length; i++) {
        memcpy(vector->elements + i * vector->elementSize,
               createCopyOfElem(get_element_at_position(original_vector, i)), vector->elementSize);
    }
    return vector;
}

int getLength(Vector *vector) {
    if (vector == NULL)
        return 0;
    return vector->length;
}

int getCapacity(Vector *vector) {
    if (vector == NULL)
        return 0;
    return vector->capacity;
}

