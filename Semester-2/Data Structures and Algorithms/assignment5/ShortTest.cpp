#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testKeySet() {
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());
    smm.add(1, 2);
    smm.add(1, 3);
    smm.add(3, 3);
    smm.add(-3, -3);
    smm.add(5, 3);
    smm.add(-5, -3);
    vector<int> expected = {-5, -3, 1, 3, 5};
    assert(smm.keySet() == expected);
    smm.remove(5, 3);
    expected = {-5, -3, 1, 3};
    assert(smm.keySet() == expected);

    SortedMultiMap smm2 = SortedMultiMap(relation1);
    vector<int> expected2;
    for (int i = 1; i <= 100; i++) {
        smm2.add(-i, i);
        smm2.add(i, i);
    }
    for (int i = -100; i <= 100; i++) {
        if (i != 0) {
            expected2.push_back(i);
        }
    }
    assert(smm2.keySet() == expected2);

    SortedMultiMap smm3 = SortedMultiMap(relation1);
    vector<int> expected3;
    set<int> expectedKeySet3;
    for (int i = 1; i <= 100; i++) {
        int nb = rand() % 1000;
        smm3.add(nb, nb);
        expectedKeySet3.insert(nb);
    }
    for (auto key: expectedKeySet3) {
        expected3.push_back(key);
    }
    sort(expected3.begin(), expected3.end());
    assert(smm3.keySet() == expected3);

    std::cout << "Test key set done\n";
}

void testAll() {
    testKeySet();
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());
    smm.add(1, 2);
    smm.add(1, 3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v = smm.search(1);
    assert(v.size() == 2);
    v = smm.search(3);
    assert(v.size() == 0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}
