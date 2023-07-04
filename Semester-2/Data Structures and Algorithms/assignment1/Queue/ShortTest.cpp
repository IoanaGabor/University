#include "ShortTest.h"
#include "Queue.h"
#include <assert.h>
#include <iostream>


void testMiddle(){
    Queue q;
    assert(q.isEmpty() == true);
    try {
        q.popMiddle();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    // odd number of elements
    q.push(5);
    q.push(1);
    q.push(10);
    assert(q.isEmpty() == false);
    assert(q.popMiddle() == 1);
    assert(q.pop() == 5);
    assert(q.pop() == 10);
    assert(q.isEmpty() == true);
    // even number of elements + full capacity
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);
    q.push(8);
    assert(q.isEmpty() == false);
    assert(q.popMiddle() == 5);
    assert(q.pop() == 1);
    assert(q.pop() == 2);
    assert(q.pop() == 3);
    assert(q.pop() == 4);
    assert(q.popMiddle()==7);
    assert(q.pop() == 6);
    assert(q.pop() == 8);
    ///even number of elements
    q.push(5);
    q.push(1);
    q.pop();
    q.push(23);
    q.push(10);
    assert(q.isEmpty() == false);
    assert(q.popMiddle() == 23);
    assert(q.pop() == 1);
    assert(q.pop() == 10);
    assert(q.isEmpty() == true);

    for(int i=0;i<100;i++){
        q.push(i);
    }
    assert(q.popMiddle()==50);
    for(int i=0;i<99;i++){
        q.pop();
    }

    for(int i=0;i<100;i++){
        q.push(i);
    }
    q.pop();
    q.pop();
    q.pop();
    assert(q.popMiddle()==51);
    for(int i=0;i<96;i++){
        q.pop();
    }
    assert(q.isEmpty());

    cout<<"Middle is ok"<<'\n';
}

void testAll() { 
	Queue q;
	assert(q.isEmpty() == true);
	q.push(5);
	q.push(1);
	q.push(10);
	assert(q.isEmpty() == false);
	assert(q.top() == 5);
	assert(q.pop() == 5);
	assert(q.top() == 1);
	assert(q.pop() == 1);
	assert(q.top() == 10);
	assert(q.pop() == 10);
	assert(q.isEmpty() == true);
    testMiddle();
}
