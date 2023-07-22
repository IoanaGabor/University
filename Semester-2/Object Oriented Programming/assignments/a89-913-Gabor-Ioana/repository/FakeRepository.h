//
// Created by ioana on 19.05.2023.
//

#ifndef A89_913_GABOR_IOANA_FAKEREPOSITORY_H
#define A89_913_GABOR_IOANA_FAKEREPOSITORY_H


#include "MemoryRepository.h"

template<class T>
class FakeRepository : public MemoryRepository<T> {
private:
    bool fakeReturnValueForFind;
public:
    explicit FakeRepository(bool fakeReturnValueForFind);

    bool isPresent(const std::string &elementId) override;

    void setFakeReturnValueForFind(bool fakeReturnValueForFind);

};

template<class T>
bool FakeRepository<T>::isPresent(const std::string &elementId) {
    return fakeReturnValueForFind;
}

template<class T>
FakeRepository<T>::FakeRepository(bool fakeReturnValueForFind):fakeReturnValueForFind(fakeReturnValueForFind) {}

template<class T>
void FakeRepository<T>::setFakeReturnValueForFind(bool returnValueToBeSet) {
    fakeReturnValueForFind = returnValueToBeSet;
}

#endif //A89_913_GABOR_IOANA_FAKEREPOSITORY_H
