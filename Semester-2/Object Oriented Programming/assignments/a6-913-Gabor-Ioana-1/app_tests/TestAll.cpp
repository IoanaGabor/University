//
// Created by ioana on 31.03.2023.
//

#include "TestAll.h"
#include "TestEvent.h"
#include "TestRepository.h"
#include "TestController.h"

void TestAll::runAllTests() {
    TestEvent::testAllEvent();
    TestRepository::testAllRepository();
    TestController::testAllController();
}
