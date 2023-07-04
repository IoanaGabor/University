#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
    this->heap = new TElem [m.sizeOfHashTable+1];
    this->currentPositions = new SortedMap::TNode * [m.sizeOfHashTable];
    this->heap_length = 0;
    for(int i=0;i<m.sizeOfHashTable;i++){
        currentPositions[i] = m.hashtable[i];
        if(currentPositions[i]!= nullptr){
            addToHeap(currentPositions[i]->elem);
        }
    }
}

void SMIterator::addToHeap(TElem elem){
    this->heap[heap_length+1] = elem;
    heap_length++;
    bubbleUp(heap_length);
}

TElem SMIterator::popFromHeap(){
    TElem removed = heap[1];
    swap(heap[1], heap[heap_length]);
    heap_length--;
    bubbleDown(1);
    return removed;
}

void SMIterator::bubbleUp(int position){
    int pos = position;
    TElem elem = heap[pos];
    int parent = pos/2;
    while(pos>1 and map.relation(elem.first, heap[parent].first)){
        heap[pos] = heap[parent];
        pos = parent;
        parent = pos/2;
    }
    heap[pos] = elem;
}

void SMIterator::bubbleDown(int position){
    int pos = position;
    TElem elem = heap[pos];
    int maxChld;
    while(pos<heap_length){
        maxChld = -1;
        if(pos*2 <= heap_length){
            maxChld = pos*2;
        }
        if(pos*2+1 <= heap_length and map.relation(heap[pos*2+1].first, heap[pos*2].first)){
            maxChld =pos*2+1;
        }
        if(maxChld!=-1 && map.relation(heap[maxChld].first, heap[pos].first)){
            swap(heap[maxChld], heap[pos]);
            pos = maxChld;
        }else{
            break;
        }
    }
}

void SMIterator::first(){
    this->heap_length = 0;
    for(int i=0;i<map.sizeOfHashTable;i++){
        currentPositions[i] = map.hashtable[i];
        if(currentPositions[i]!= nullptr){
            addToHeap(currentPositions[i]->elem);
        }
    }
}

void SMIterator::next(){
    if(!valid()){
        throw std::exception();
    }
    TElem removed = popFromHeap();
    int where = map.hashFunction(removed.first, map.sizeOfHashTable);
    currentPositions[where]=currentPositions[where]->next;
    if(currentPositions[where]!= nullptr){
        addToHeap(currentPositions[where]->elem);
    }
}

bool SMIterator::valid() const{
	return heap_length!=0;
}

TElem SMIterator::getCurrent() const{
    if(!valid()){
        throw std::exception();
    }
	return heap[1];
}

SMIterator::~SMIterator() {
    delete[] heap;
    delete[] currentPositions;
}


