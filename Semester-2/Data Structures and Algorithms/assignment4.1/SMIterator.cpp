#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <random>

using namespace std;

SMIterator::SMIterator(const SortedMap &m) : map(m) {
    ///total, best:O(nlogn), average: O(nlogn), worst: O(n^2)
    this->array = new TElem[m.numberOfElements + 1];
    SortedMap::TNode *current_node;
    int current = 0;
    for (int i = 0; i < m.sizeOfHashTable; i++) {
        current_node = m.hashtable[i];
        while (current_node != nullptr) {
            array[current++] = current_node->elem;
            current_node = current_node->next;
        }
    }
    quickSort(array, 0, m.numberOfElements - 1);
    currentElement = 0;
}

int SMIterator::partition(TElem arrayToBeSorted[], int low, int high) {
    ///theta(high-low) - linear
    int randomInt = random() % (high-low+1);
    swap(arrayToBeSorted[randomInt+low], arrayToBeSorted[high]);
    TElem pivot = arrayToBeSorted[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (map.relation(arrayToBeSorted[j].first, pivot.first)) {
            i++;
            swap(arrayToBeSorted[i], arrayToBeSorted[j]);
        }
    }
    swap(arrayToBeSorted[i + 1], arrayToBeSorted[high]);
    return i + 1;
}

void SMIterator::quickSort(TElem arrayToBeSorted[], int low, int high) {
    ///total, best:O(nlogn), average: O(nlogn), worst: O(n^2)
    if (low < high) {
        int pi = partition(arrayToBeSorted, low, high);
        quickSort(arrayToBeSorted, low, pi - 1);
        quickSort(arrayToBeSorted, pi + 1, high);
    }
}

void SMIterator::first() {
    ///theta(1)
    currentElement = 0;
}

void SMIterator::last() {
    ///theta(1)
    currentElement = map.numberOfElements-1;
}


void SMIterator::next() {
    ///theta(1)
    if (!valid()) {
        throw std::exception();
    }
    currentElement++;
}

void SMIterator::previous() {
    ///theta(1)
    if (!valid()) {
        throw std::exception();
    }
    currentElement--;
}

bool SMIterator::valid() const {
    ///theta(1)
    return 0<= currentElement && currentElement < map.numberOfElements;
}

TElem SMIterator::getCurrent() const {
    ///theta(1)
    if (!valid()) {
        throw std::exception();
    }
    return array[currentElement];
}

SMIterator::~SMIterator() {
    delete[] array;
}