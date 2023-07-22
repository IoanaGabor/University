//
// Created by ioana on 30.03.2023.
//

#include <cassert>
#include "TestDynamicVector.h"
#include "../domain/DynamicVector.h"

void TestDynamicVector::testAdd() {
    DynamicVector<int> dynamicVector = DynamicVector<int>();
    dynamicVector.add(1);
    dynamicVector.add(2);
    dynamicVector.add(3);
    dynamicVector.add(4);
    dynamicVector.add(5);
    assert(dynamicVector.getSize() == 5);
}

void TestDynamicVector::testPopBack() {
    DynamicVector<int> dynamicVector = DynamicVector<int>();
    dynamicVector.add(1);
    dynamicVector.add(2);
    dynamicVector.add(3);
    dynamicVector.add(4);
    dynamicVector.pop_back();
    assert(dynamicVector.getSize() == 3);
    dynamicVector.pop_back();
    assert(dynamicVector.getSize() == 2);
}

void TestDynamicVector::testIndexing(){
    DynamicVector<int> dynamicVector = DynamicVector<int>();
    dynamicVector.add(1);
    dynamicVector.add(2);
    dynamicVector.add(3);
    dynamicVector.add(4);
    assert(dynamicVector[1]==2);
    assert(dynamicVector[3] == 4);
    try{
        dynamicVector[432];
        assert(false);
    }catch (DynamicVectorException &dynamicVectorException){
        assert(true);
    }
}

void TestDynamicVector::testAllDynamicVector() {
    TestDynamicVector::testAdd();
    TestDynamicVector::testPopBack();
    TestDynamicVector::testIndexing();
    TestDynamicVector::testCopyConstructor();
}

void TestDynamicVector::testCopyConstructor() {
    DynamicVector<int> dynamicVector = DynamicVector<int>();
    dynamicVector.add(1);
    dynamicVector.add(2);
    dynamicVector.add(3);
    dynamicVector.add(4);
    DynamicVector<int> copyOfDynamicVector = DynamicVector<int>(dynamicVector);
    assert(dynamicVector.getSize() == copyOfDynamicVector.getSize());
    assert(dynamicVector[0] == copyOfDynamicVector[0]);
    assert(dynamicVector[1] == copyOfDynamicVector[1]);
    assert(dynamicVector[2] == copyOfDynamicVector[2]);
    assert(dynamicVector[3] == copyOfDynamicVector[3]);
}
