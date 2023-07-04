#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
#include <iostream>

using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testPrevious() {
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1, 2);
    sm.add(2, 3);
    sm.add(6, 3);
    sm.add(4, 3);
    SMIterator it = sm.iterator();
    it.first();
    it.previous();
    try {
        it.getCurrent();
        assert(false);
    } catch (std::exception &exception) {
        assert(true);
    }
    it.first();
    it.next();
    it.previous();
    assert(it.getCurrent() == make_pair(1, 2));
    it.next();
    it.next();
    it.next();
    it.previous();
    assert(it.getCurrent() == make_pair(4, 3));
    it.previous();
    assert(it.getCurrent() == make_pair(2, 3));

    SortedMap sm2(relatie1);
    assert(sm2.size() == 0);
    assert(sm2.isEmpty());
    for(int i=0;i<1000;i++){
        sm.add(i,i);
    }
    SMIterator it2 = sm2.iterator();
    it2.last();
    int current = 999;
    while(it2.valid()){
        assert(it.getCurrent() == make_pair(current,current));
        current--;
        it2.previous();
    }

    cout<<"test previous";
}


void testAll() {
    testPrevious();
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1, 2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1) != NULL_TVALUE);
    TValue v = sm.add(1, 3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        assert(e.second != NULL_TVALUE);
        it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());
}
