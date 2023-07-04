#include <iostream>
#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	elements = new TElem [map.smmSize];
    nrElements=0;
    dfs(map.root);
    current=0;
}

void SMMIterator::dfs(int node){
    //theta(smmSizeL)
    if(node==-1){
        return;
    }
    dfs(map.nodes[node].left);
    for(int i=0;i<map.nodes[node].valuesSize;i++){
        elements[nrElements++] = {map.nodes[node].key,map.nodes[node].values[i]};
    }
    dfs(map.nodes[node].right);
}

void SMMIterator::first(){
    current=0;
}

void SMMIterator::next(){
    if(!valid()){
        throw std::exception();
    }
    current++;
}

bool SMMIterator::valid() const{
	return current<map.smmSize;
}

TElem SMMIterator::getCurrent() const{
    if(!valid()){
        throw std::exception();
    }
	return elements[current];
}

SMMIterator::~SMMIterator() {
    delete[] elements;
}


