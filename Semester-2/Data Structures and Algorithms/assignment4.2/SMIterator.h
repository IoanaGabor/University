#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
public:
    virtual ~SMIterator();

private:
    SMIterator(const SortedMap& mapionar);

	//TODO - Representation
    TElem *array;
    int currentElement;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;

    TElem *heap;
    SortedMap::TNode **currentPositions;
    int heap_length;

    void addToHeap(TElem elem);

    TElem popFromHeap();

    void bubbleDown(int position);

    void bubbleUp(int position);
};

