//
// Created by Jonas on 24-10-2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#ifndef UNITTESTFRAMEWORK_H
#define UNITTESTFRAMEWORK_H

typedef struct Test Test;
struct Test {
    int (*test_funct_ptr)();
    char* name;
};

typedef int (*TestFunction)();

void TestPassed(char* message) {
    DEBUG_PRINT("PASSED TEST: %s\n",message);
};

void ThrowException(char* message) {
    printf("ERROR: FAILED TEST: %s\n",message);
    exit(-1);
};

void ExecuteTest(Test test) {
    int testResult = test.test_funct_ptr();
    if (testResult == 1) {
        TestPassed(test.name);
    }
    else {
        ThrowException(test.name);
    }
}
/**
Creates a test based on the address of a function and test name
 */
Test CreateTest(int (*funct_ptr)(), char* testName) {
    Test test;
    test.test_funct_ptr = funct_ptr;
    test.name = testName;
    return test;
}

/**
Gets a randomized word
 */
word RandW() {
    return (word) rand() % 65536 - 32768;
}
/**
Gets a randomized hWord
 */
hWord RandHW() {
    return (hWord) rand() % 65536-32768;
}
/**
Gets a randomized byte
 */
byte RandB() {
    return (byte) rand() % 65536-32768;
}
/**
Gets a randomized uWord
 */
uWord RandUW() {
    return (uWord) rand() % 65536;
}
/**
Gets a randomized uHWord
 */
uHWord RandUHW() {
    return (uHWord) rand() % 65536;
}
/**
Gets a randomized uByte
 */
uByte RandUB() {
    return (uByte) rand() % 65536;
}

#define Assert_Equal(a,b) (a == b)

#endif