#pragma once

#include "SortedMultiMap.h"


class SMMIterator {
    friend class SortedMultiMap;

private:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap &map;

    SMMIterator(const SortedMultiMap &map);

    void dfs(int node);

    //TODO - Representation
    TElem *elements;
    int current;
    int nrElements;
public:
    void first();

    void next();

    bool valid() const;

    TElem getCurrent() const;

    virtual ~SMMIterator();

};

