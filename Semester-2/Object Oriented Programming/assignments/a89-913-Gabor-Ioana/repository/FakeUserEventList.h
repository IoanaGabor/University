//
// Created by ioana on 19.05.2023.
//

#ifndef A89_913_GABOR_IOANA_FAKEUSEREVENTLIST_H
#define A89_913_GABOR_IOANA_FAKEUSEREVENTLIST_H


#include "AbstractUserEventList.h"

class FakeUserEventList : public AbstractUserEventList{
private:
public:
    FakeUserEventList(const std::string &fileName, bool fakeReturnValueForFind);

    void setFakeReturnValueForFind(bool fakeReturnValueForFind);

private:
    bool fakeReturnValueForFind;
public:
    bool isPresent(const std::string &elementId) override;
    void load() override;

    void save() override;

    void displayEventList() override;
};


#endif //A89_913_GABOR_IOANA_FAKEUSEREVENTLIST_H
