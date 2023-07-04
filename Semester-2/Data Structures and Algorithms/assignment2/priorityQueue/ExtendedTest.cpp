#include <assert.h>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include <vector>
#include <exception>
#include <iostream>

using namespace std;

bool rel2(TPriority p1, TPriority p2) {
    if (p1 <= p2) {
        return true;
    } else {
        return false;
    }
}

bool rel3(TPriority p1, TPriority p2) {
    if (p1 / 11 <= p2 / 11) {
        return true;
    } else {
        return false;
    }
}

bool rel4(TPriority p1, TPriority p2) {
    int pp1 = p1;
    if (p1 < 0) {
        pp1 = -1 * p1;
    }
    int pp2 = p2;
    if (p2 < 0) {
        pp2 = -1 * p2;
    }
    if (pp1 >= pp2) {
        return true;
    } else {
        return false;
    }
}


void testCreate() {
    cout << "Test create" << endl;
    PriorityQueue pq(rel2);
    assert(pq.isEmpty() == true);
    try {
        pq.top(); //if it is empty it should throw an exception
        assert(false); //if it did not throw an exception the assert will fail
    }
    catch (exception &) {
        assert(true);
    }
    try {
        pq.pop(); //if it is empty it should throw an exception
        assert(false); //if it did not throw an exception the assert will fail
    }
    catch (exception &) {
        assert(true);
    }
}

void testAdd() {
    cout << "Test add" << endl;
    PriorityQueue pq(rel2);
    for (int i = 0; i < 10; i++) {
        pq.push(i, i);
    }
    assert(pq.isEmpty() == false);
    for (int i = -10; i < 20; i++) {
        pq.push(i, i);
    }
    assert(pq.isEmpty() == false);
    for (int i = -100; i < 100; i++) {
        pq.push(i, i);
    }
    assert(pq.isEmpty() == false);

    for (int i = -1000; i <= 1000; i++) {
        pq.push(i, i);
    }
    assert(pq.isEmpty() == false);
    assert(pq.top().second != 1000);
    assert(pq.top().second == -1000);

    assert(pq.pop().second == -1000);
    assert(pq.top().second == -999);
}

void testMix(Relation rel) {
    cout << "Test mix" << endl;
    PriorityQueue pq(rel);
    for (int i = -100; i < 100; i++) {
        pq.push(i, i);
    }
    TPriority tp = pq.pop().second;
    for (int i = 0; i < 50; i++) {
        TPriority tp2 = pq.pop().second;
        assert(rel(tp, tp2));
        tp = tp2;
    }
    for (int i = -300; i < 300; i = i + 7) {
        pq.push(i, i);
    }
    tp = pq.pop().second;
    for (int i = 0; i < 200; i++) {
        TPriority tp2 = pq.pop().second;
        assert(rel(tp, tp2));
        tp = tp2;
    }

    for (int i = -1000; i < 1000; i = i + 11) {
        pq.push(i, i);
        pq.push(-2 * i, -2 * i);
        pq.push(2 * i, 2 * i);
        TPriority pp1 = pq.pop().second;
        TPriority pp2 = pq.pop().second;
        assert(rel(pp1, pp2));
    }
    tp = pq.pop().second;
    while (!pq.isEmpty()) {
        TPriority tp2 = pq.pop().second;
        assert(rel(tp, tp2));
        tp = tp2;
    }
}

void testRemove() {
    cout << "Test remove" << endl;
    PriorityQueue pq(rel2);
    for (int i = 0; i < 10; i++) {
        pq.push(i, i);
    }
    assert(pq.top().second == 0);
    assert(pq.isEmpty() == false);
    for (int i = -10; i < 20; i++) {
        pq.push(i, i);
    }
    assert(pq.top().second == -10);
    for (int i = 100; i > 50; i--) {
        pq.push(i, i);
    }
    assert(pq.top().second == -10);

    //the elements are given in the order of their priority
    for (int i = -10; i < 0; i++) {
        assert(pq.pop().second == i);
    }
    for (int i = 0; i < 10; i++) {
        assert(pq.pop().second == i);
        assert(pq.pop().second == i);
    }
    for (int i = 10; i < 20; i++) {
        assert(pq.pop().second == i);
    }
    for (int i = 51; i <= 100; i++) {
        assert(pq.pop().second == i);
    }


    assert(pq.isEmpty() == true);
}

void testQuantity() {//add a lot of elements 
    cout << "Test quantity" << endl;
    PriorityQueue pq(rel2);
    for (int i = 1; i <= 10; i++) {
        for (int j = 300; j >= -300; j--) {
            pq.push(j, j);
        }
    }

    for (int i = -300; i <= 300; i++) {
        for (int j = 1; j <= 10; j++) {
            assert(pq.pop().second == i);
        }
    }
}

void testIncreasePriority() {
    PriorityQueue pq = PriorityQueue(rel2);
    pq.push(1, 20);
    pq.push(2, 18);
    pq.push(3, 30);
    pq.push(4, 25);
    pq.push(5, 10);
    pq.push(6, 15);
    assert(pq.increasePriority(2, 17)==18);
    assert(pq.top().second == 10);
    assert(pq.increasePriority(3,-20)==30);
    assert(pq.top().second == -20);
    assert(pq.increasePriority(2, -23)==17);
    assert(pq.increasePriority(254, -23)==-1);
    assert(pq.top().second == -23);
    pq.pop();
    pq.pop();
    assert(pq.increasePriority(6, -50)==15);
    assert(pq.top().second == -50);
    assert(pq.increasePriority(5, 9)==10);
    pq.pop();
    assert(pq.top().second == 9);
    PriorityQueue pq2 = PriorityQueue(rel2);
    pq2.push(1, 2);
    pq2.push(2, 4);
    pq2.push(3, 6);
    pq2.push(4, 8);
    pq2.push(5, 10);
    pq2.push(6, 12);
    assert(pq2.increasePriority(3, 0)==6);
    pq2.pop();
    pq2.pop();
    assert(pq2.top().second==4);
    assert(pq2.increasePriority(10,0)==-1);
    try{
        pq2.increasePriority(6,30);
        assert(false);
    }catch (exception &){
        assert(true);
    }
    pq2.pop();
    pq2.pop();
    pq2.pop();
    pq2.pop();
    for (int i=0;i<100;i++){
        pq2.push(i, i);
    }
    pq2.increasePriority(94, -2);
    assert(pq2.top().second==-2);
    pq2.increasePriority(94, -5);
    assert(pq2.top().second==-5);
    pq2.increasePriority(0, -50);
    assert(pq2.top().second==-50);
}

void testAllExtended() {
    testIncreasePriority();
    testCreate();
    testAdd();
    testRemove();
    testMix(rel2);
    testMix(rel3);
    testMix(rel4);
    testQuantity();
}