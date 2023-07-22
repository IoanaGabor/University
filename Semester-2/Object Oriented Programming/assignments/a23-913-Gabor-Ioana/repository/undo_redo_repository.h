#pragma once

#include "../domain/vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct {
    Vector *savedStates;
    int undoLimit;
    int undoCurrent;
} UndoRedoRepository;


UndoRedoRepository *createUndoRedoRepository();

void destroyUndoRedoRepository(UndoRedoRepository *undoRedo);

void addState(UndoRedoRepository *undoRedo, Vector *state);

void clearRedoNew(UndoRedoRepository *undoRedo);

Vector *undo_repository(UndoRedoRepository *undoRedo);

Vector *redo_repository(UndoRedoRepository *undoRedo);

bool canPerformUndo(UndoRedoRepository *undoRedoRepository);

bool canPerformRedo(const UndoRedoRepository *undoRedoRepository);