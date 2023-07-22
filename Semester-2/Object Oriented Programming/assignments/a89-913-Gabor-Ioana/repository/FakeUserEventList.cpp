//
// Created by ioana on 19.05.2023.
//

#include "FakeUserEventList.h"

void FakeUserEventList::load() {

}

void FakeUserEventList::save() {

}

void FakeUserEventList::displayEventList() {

}

bool FakeUserEventList::isPresent(const std::string &elementId) {
    return fakeReturnValueForFind;
}

void FakeUserEventList::setFakeReturnValueForFind(bool fakeReturnValueForFind) {
    FakeUserEventList::fakeReturnValueForFind = fakeReturnValueForFind;
}

FakeUserEventList::FakeUserEventList(const std::string &fileName, bool fakeReturnValueForFind) : AbstractUserEventList(
        fileName), fakeReturnValueForFind(fakeReturnValueForFind) {}
