#include "undo_redo_repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

UndoRedoRepository *createUndoRedoRepository() {
    UndoRedoRepository *undoRedo = (UndoRedoRepository *) malloc(sizeof(UndoRedoRepository));
    if (undoRedo == NULL)
        return NULL;

    undoRedo->savedStates = createVector(1, sizeof(Vector), &destroyVectorData);
    undoRedo->undoLimit = 0;
    undoRedo->undoCurrent = 0;
    return undoRedo;
};


void destroyUndoRedoRepository(UndoRedoRepository *undoRedo) {
    if (undoRedo == NULL) {
        return;
    }

    for (int index = 0; index < undoRedo->undoLimit; index++) {
        if (get_element_at_position(undoRedo->savedStates, index) != NULL) {
            undoRedo->savedStates->freeElementData((Vector *) get_element_at_position(undoRedo->savedStates, index));
        }
    }
    if (undoRedo->savedStates->elements != NULL) {
        free(undoRedo->savedStates->elements);
        undoRedo->savedStates->elements = NULL;
    }
    if (undoRedo->savedStates != NULL) {
        free(undoRedo->savedStates);
        undoRedo->savedStates = NULL;
    }
    if (undoRedo != NULL) {
        free(undoRedo);
        undoRedo = NULL;
    }
};


void addState(UndoRedoRepository *undoRedo, Vector *state) {
    clearRedoNew(undoRedo);
    Vector *vector = make_copy_of_vector(state, (void *(*)(void *)) &createCopyOfProduct);
    add(undoRedo->savedStates, vector);
    undoRedo->undoLimit += 1;
    undoRedo->undoCurrent += 1;
};

void clearRedoNew(UndoRedoRepository *undoRedo) {
    for (int i = undoRedo->undoLimit - 1; i > undoRedo->undoCurrent; i--) {
        delete_last_element(undoRedo->savedStates);
    }
    undoRedo->undoLimit = undoRedo->undoCurrent;
}


Vector *undo_repository(UndoRedoRepository *undoRedo) {
    if (undoRedo->undoCurrent == 0) {
        return NULL;
    }

    if (undoRedo->undoCurrent == undoRedo->undoLimit) {
        undoRedo->undoCurrent--;
    }
    undoRedo->undoCurrent--;
    return (Vector *) get_element_at_position(undoRedo->savedStates, undoRedo->undoCurrent);
}

Vector *redo_repository(UndoRedoRepository *undoRedo) {
    if (undoRedo->undoCurrent == undoRedo->undoLimit)
        return NULL;
    undoRedo->undoCurrent++;
    return (Vector *) get_element_at_position(undoRedo->savedStates, undoRedo->undoCurrent);
}


bool canPerformUndo(UndoRedoRepository *undoRedoRepository) {
    return (undoRedoRepository->undoCurrent != 1 && getLength(undoRedoRepository->savedStates) == 1) ||
           (undoRedoRepository->undoCurrent != 0 && undoRedoRepository->savedStates->length > 1);
}

bool canPerformRedo(const UndoRedoRepository *undoRedoRepository) {
    return undoRedoRepository->undoCurrent + 1 < undoRedoRepository->undoLimit;
}