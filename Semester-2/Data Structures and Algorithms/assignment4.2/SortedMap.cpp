#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <cmath>
using namespace std;

SortedMap::SortedMap(Relation r) {
	//TODO - Implementation
    relation = r;
    sizeOfHashTable = 5;
    numberOfElements = 0;
    A = 0.234;
    hashtable = new TNode*[sizeOfHashTable];
    for(int i=0;i<sizeOfHashTable;i++){
        hashtable[i] = nullptr;
    }
}

void SortedMap::resize(){
    TNode *current_node, *next;
    TNode** newHashTable = new TNode*[2*sizeOfHashTable];
    TNode** lastPosition = new TNode*[2*sizeOfHashTable];
    for(int i=0;i<2*sizeOfHashTable;i++){
        lastPosition[i] = nullptr;
        newHashTable[i] = nullptr;
    }
    TElem current_element;
    auto smIterator = SMIterator(*this);
    smIterator.first();
    while(smIterator.valid()){
        current_element = smIterator.getCurrent();
        int where = this->hashFunction(current_element.first, 2*sizeOfHashTable);
        TNode* newNode= new TNode();
        newNode->elem = current_element;
        newNode->next = nullptr;
        if(lastPosition[where]== nullptr){
            newHashTable[where] = newNode;
            lastPosition[where] = newHashTable[where];
        }else{
            lastPosition[where]->next = newNode;
            lastPosition[where] = lastPosition[where]->next;
        }
        smIterator.next();
    }
    delete []lastPosition;

    for(int i=0;i<sizeOfHashTable;i++){
        current_node = hashtable[i];
        while(current_node != nullptr){
            next = current_node->next;
            delete current_node;
            current_node = next;
        }
    }
    delete[] hashtable;
    sizeOfHashTable*=2;
    this->hashtable = newHashTable;
}

TValue SortedMap::add(TKey k, TValue v) {
    if(needsResizing()){
        this->resize();
    }
    int where = this->hashFunction(k, sizeOfHashTable);
    TNode *current_node, *previous= nullptr;
    TElem current_element;
    current_node = this->hashtable[where];
    int oldValue = NULL_TVALUE;
    while(current_node != nullptr){
        current_element = current_node->elem;
        if(current_element.first == k){
            oldValue = current_element.second;
            current_node->elem.second = v;
            break;
        }else if(relation(k,current_element.first)){
            break;
        }
        previous = current_node;
        current_node = current_node->next;
    }
    if(oldValue==NULL_TVALUE){
        TNode* newNode= new TNode();
        newNode->elem = {k,v};
        if(previous== nullptr){
            newNode->next = hashtable[where];
            hashtable[where] = newNode;
        }else{
            newNode->next = previous->next;
            previous->next = newNode;
        }
        numberOfElements++;
    }
	return oldValue;
}

bool SortedMap::needsResizing() const { return numberOfElements > 0.7 * sizeOfHashTable; }

TValue SortedMap::search(TKey k) const {
	//TODO - Implementation
    int where = this->hashFunction(k, sizeOfHashTable);
    TNode *current_node;
    TElem current_element;
    current_node = this->hashtable[where];
    while(current_node != nullptr){
        current_element = current_node->elem;
        if(current_element.first == k){
            return current_element.second;
        }else if(relation(k,current_element.first)){
            break;
        }
        current_node = current_node->next;
    }
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	//TODO - Implementation
    int where = this->hashFunction(k, sizeOfHashTable);
    TNode *current_node;
    TElem current_element;
    current_node = this->hashtable[where];
    int oldValue = NULL_TVALUE;
    TNode *next;
    TNode *prev = nullptr;
    while(current_node != nullptr){
        current_element = current_node->elem;
        if(current_element.first == k){
            oldValue = current_element.second;
            numberOfElements--;
            if(current_node==this->hashtable[where]){
                this->hashtable[where] = this->hashtable[where]->next;
                delete current_node;
                break;
            }else{
                prev->next = current_node->next;
                delete current_node;
                break;
            }
        }else if(relation(k,current_element.first)){
            break;
        }
        prev = current_node;
        current_node = current_node->next;
    }
	return oldValue;
}

int SortedMap::size() const {
	//TODO - Implementation
	return numberOfElements;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	return numberOfElements==0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    TNode*current_node, *next;
    for(int i=0;i<sizeOfHashTable;i++){
        current_node = hashtable[i];
        while(current_node != nullptr){
            next = current_node->next;
            delete current_node;
            current_node = next;
        }
    }
    delete[] hashtable;
}

int SortedMap::hashFunction(int key, int size) const {
    double whole;
    if(key<0){
        key = -key;
    }
    return floor(size * std::modf(key * A, &whole));
}
