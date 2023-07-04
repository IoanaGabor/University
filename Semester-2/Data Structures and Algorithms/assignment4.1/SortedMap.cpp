#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <cmath>
using namespace std;

SortedMap::SortedMap(Relation r) {
    ///total, best, average: theta(sizeOfHashTable)
    relation = r;
    sizeOfHashTable = 4;
    numberOfElements = 0;
    A = 0.234;
    hashtable = new TNode*[sizeOfHashTable];
    for(int i=0;i<sizeOfHashTable;i++){
        hashtable[i] = nullptr;
    }
}

void SortedMap::resize(){
    ///total, best, average: theta(numberOfElements)
    sizeOfHashTable*=2;
    TNode** newHashTable = new TNode*[sizeOfHashTable];
    TNode *current_node, *next;
    for(int i=0;i<sizeOfHashTable;i++){
        newHashTable[i] = nullptr;
    }
    TElem current_element;
    for(int i=0;i<sizeOfHashTable/2;i++){
        current_node = hashtable[i];
        while(current_node != nullptr){
            current_element = current_node->elem;
            int where = this->hashFunction(current_element.first);
            next = current_node->next;
            current_node->next = newHashTable[where];
            newHashTable[where] = current_node;
            current_node = next;
        }
    }
    delete[] hashtable;
    this->hashtable = newHashTable;
}

TValue SortedMap::add(TKey k, TValue v) {
    ///best case: theta(1), worst case: theta(numberOfElements),
    if(needsResizing()){
        this->resize();
    }
    int where = this->hashFunction(k);
    TNode *current_node;
    TElem current_element;
    current_node = this->hashtable[where];
    int oldValue = NULL_TVALUE;
    while(current_node != nullptr){
        current_element = current_node->elem;
        if(current_element.first == k){
            oldValue = current_element.second;
            current_node->elem.second = v;
            break;
        }
        current_node = current_node->next;
    }
    if(oldValue==NULL_TVALUE){
        current_node = new TNode();
        current_node->elem = {k,v};
        current_node->next = hashtable[where];
        hashtable[where] = current_node;
        numberOfElements++;
    }
	return oldValue;
}

bool SortedMap::needsResizing() const { return numberOfElements > 0.7 * sizeOfHashTable; }

TValue SortedMap::search(TKey k) const {
    ///best case: theta(1), average case: theta(1+alpha), worst case: theta(numberOfElements), O(numberOfElements);
    int where = this->hashFunction(k);
    TNode *current_node;
    TElem current_element;
    current_node = this->hashtable[where];
    while(current_node != nullptr){
        current_element = current_node->elem;
        if(current_element.first == k){
            return current_element.second;
        }
        current_node = current_node->next;
    }
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    ///best case: theta(1), average case: theta(1+alpha), worst case: theta(numberOfElements), overall O(numberOfElements)
    int where = this->hashFunction(k);
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
        }
        prev = current_node;
        current_node = current_node->next;
    }
	return oldValue;
}

int SortedMap::size() const {
	return numberOfElements;
}

bool SortedMap::isEmpty() const {
	return numberOfElements==0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    ///total, best, average: theta(numberOfElements)
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

int SortedMap::hashFunction(int key) const {
    double whole;
    if(key<0){
        key = -key;
    }
    return floor(sizeOfHashTable*std::modf(key*A,&whole));
}
