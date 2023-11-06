//
// Created by Jonas on 24-10-2023.
//
#include <time.h>
#include "utils.h"
#include "types.h"
#include "processor.h"
#include "unitTestFramework.h"

/*
Add a unit test by creating a function, and then adding an entry in one of test suites below with create test.
*/

int Mem_word_uTest() {
    word w = RandW();
    DEBUG_PRINT("w: %ld\n", w);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setWord(w, address);
    word result = getWord(address);
    DEBUG_PRINT("return w: %ld\n", result);
    return Assert_Equal(w, result);
}

int Mem_hWord_uTest() {
    hWord hW = RandHW();
    DEBUG_PRINT("hW: %d\n", hW);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setHWord(hW, address);
    hWord result = getHWord(address);
    DEBUG_PRINT("return w: %d\n", result);
    return Assert_Equal(hW, result);
}

int Mem_byte_uTest() {
    byte b = RandB();
    DEBUG_PRINT("b: %d\n", b);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setByte(b, address);
    byte result = getByte(address);
    DEBUG_PRINT("return w: %d\n", result);
    return Assert_Equal(b, result);
}

int Mem_uWord_uTest() {
    uWord uw = RandUW();
    DEBUG_PRINT("uw: %ld\n", uw);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setUWord(uw, address);
    uWord result = getUWord(address);
    return Assert_Equal(uw, result);
}

int Mem_uHWord_uTest() {
    uHWord uhw = RandUHW();
    DEBUG_PRINT("uhw: %d\n", uhw);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setUHWord(uhw, address);
    uHWord result = getUHWord(address);
    return Assert_Equal(uhw, result);
}

int Mem_uByte_uTest() {
    uByte ub = RandUB();
    DEBUG_PRINT("ub: %d\n", ub);
    word address = RandUW();
    DEBUG_PRINT("address: %ld\n", address);
    setUByte(ub, address);
    uByte result = getUByte(address);
    return Assert_Equal(ub, result);
}

int ADD_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000011100110000001010110011; //add t0, t1, t2
    word int1 = RandW();
    DEBUG_PRINT("int1: %ld\n", int1);
    word int2 = RandW();
    DEBUG_PRINT("int2: %ld\n", int2);
    word sum = (int1 + int2);
    DEBUG_PRINT("sum: %ld\n", sum);
    ipm.registers[t1] = int1;
    ipm.registers[t2] = int2;
    ADD(&ipm);
    DEBUG_PRINT("t0: %ld\n", ipm.registers[t0]);
    return Assert_Equal(sum, ipm.registers[t0]);
}

int SUB_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b01000000011100110000001010110011; //sub t0, t1, t2
    word int1 = RandW();
    DEBUG_PRINT("int1: %ld\n", int1);
    word int2 = RandW();
    DEBUG_PRINT("int2: %ld\n", int2);
    word result = (int1 - int2);
    DEBUG_PRINT("result: %ld\n", result);
    ipm.registers[t1] = int1;
    ipm.registers[t2] = int2;
    SUB(&ipm);
    DEBUG_PRINT("t0: %ld\n", ipm.registers[t0]);
    return Assert_Equal(result, ipm.registers[t0]);
}

int ADDI_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00001000100100110000001010010011; //addi t0, t1, 137
    word int1 = RandW();
    DEBUG_PRINT("int1: %ld\n", int1);
    word sum = (int1 + 137);
    DEBUG_PRINT("sum: %ld\n", sum);
    ipm.registers[t1] = int1;
    ADDI(&ipm);
    DEBUG_PRINT("t0: %ld\n", ipm.registers[t0]);
    return Assert_Equal(sum, ipm.registers[t0]);
}

int LUI_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000010001001001010110111; //lui t0, 137
    LUI(&ipm);
    DEBUG_PRINT("t0: %ld\n", ipm.registers[t0]);
    return Assert_Equal(137, ipm.registers[t0]);
}

int SLL_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a2] = RandW();
    ipm.registers[a3] = (rand()%31)+1;
    ipm.instruction = 0b00000000110101100001010110110011;  //sll  a1 , a2 , a3
    SLL(&ipm);
    DEBUG_PRINT("a1 = a2 << a3   a2: %ld  a3: %ld\n",ipm.registers[a2],ipm.registers[a3]);
    DEBUG_PRINT("a1: %ld\n", ipm.registers[a1]);
    word temp = ipm.registers[a2] << ipm.registers[a3];
    return Assert_Equal(temp, ipm.registers[a1]);

}

void MemoryTestSuite() {
    Test tests[] = {
    CreateTest(&Mem_word_uTest, "Mem word test"),
    CreateTest(&Mem_hWord_uTest, "Mem hWord test"),
    CreateTest(&Mem_byte_uTest, "Mem byte test"),
    CreateTest(&Mem_uWord_uTest, "Mem uWord test"),
    CreateTest(&Mem_uHWord_uTest, "Mem uHWord test"),
    CreateTest(&Mem_uByte_uTest, "Mem uByte test")
    };

    for (int i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++) {
        ExecuteTest(tests[i]);
    }
}

void InstructionSetTestSuite() {
    Test tests[] = {
    CreateTest(&ADD_uTest, "ADD test"),
    CreateTest(&SUB_uTest, "SUB test"),
    CreateTest(&ADDI_uTest, "ADDI test"),
    CreateTest(&LUI_uTest, "LUI test"),
    CreateTest(&SLL_uTest, "SLL test")
    };

    for (int i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++) {
        ExecuteTest(tests[i]);
    }
}

void ExecuteAllTests() {
    MemoryTestSuite();
    InstructionSetTestSuite();
}