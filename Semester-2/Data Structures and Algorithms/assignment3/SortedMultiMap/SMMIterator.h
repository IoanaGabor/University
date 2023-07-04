#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
	//TODO - Representation
    SinglyLinkedListOnArrayIterator<pair<TKey, SinglyLinkedListOnArray<TValue>*>> iterator;
    TKey currentKey;
    SinglyLinkedListOnArrayIterator<int>* currentValues;
    bool invalid;
public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

