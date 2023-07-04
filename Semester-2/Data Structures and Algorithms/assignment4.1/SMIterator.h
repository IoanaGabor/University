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

    void quickSort(TElem *arrayToBeSorted, int low, int high);

    int partition(TElem *arrayToBeSorted, int low, int high);

    void previous();

    void last();
};

