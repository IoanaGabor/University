//
// Created by ioana on 31.03.2023.
//

#include "TestAll.h"
#include "TestDynamicVector.h"
#include "TestEvent.h"
#include "TestRepository.h"
#include "TestController.h"

void TestAll::runAllTests() {
    TestDynamicVector::testAllDynamicVector();
    TestEvent::testAllEvent();
    TestRepository::testAllRepository();
    TestController::testAllController();
}
