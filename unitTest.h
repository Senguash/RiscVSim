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
    DEBUG_PRINT("w: %d\n", w);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setWord(w, address);
    word result = getWord(address);
    DEBUG_PRINT("return w: %d\n", result);
    return Assert_Equal(w, result);
}

int Mem_hWord_uTest() {
    hWord hW = RandHW();
    DEBUG_PRINT("hW: %d\n", hW);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setHWord(hW, address);
    hWord result = getHWord(address);
    DEBUG_PRINT("return w: %d\n", result);
    return Assert_Equal(hW, result);
}

int Mem_byte_uTest() {
    byte b = RandB();
    DEBUG_PRINT("b: %d\n", b);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setByte(b, address);
    byte result = getByte(address);
    DEBUG_PRINT("return w: %d\n", result);
    return Assert_Equal(b, result);
}

int Mem_uWord_uTest() {
    uWord uw = RandUW();
    DEBUG_PRINT("uw: %d\n", uw);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setUWord(uw, address);
    uWord result = getUWord(address);
    return Assert_Equal(uw, result);
}

int Mem_uHWord_uTest() {
    uHWord uhw = RandUHW();
    DEBUG_PRINT("uhw: %d\n", uhw);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setUHWord(uhw, address);
    uHWord result = getUHWord(address);
    return Assert_Equal(uhw, result);
}

int Mem_uByte_uTest() {
    uByte ub = RandUB();
    DEBUG_PRINT("ub: %d\n", ub);
    word address = RandUW();
    DEBUG_PRINT("address: %d\n", address);
    setUByte(ub, address);
    uByte result = getUByte(address);
    return Assert_Equal(ub, result);
}

int ADD_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000011100110000001010110011; //add t0, t1, t2
    word int1 = RandW();
    DEBUG_PRINT("int1: %d\n", int1);
    word int2 = RandW();
    DEBUG_PRINT("int2: %d\n", int2);
    word sum = (int1 + int2);
    DEBUG_PRINT("sum: %d\n", sum);
    ipm.registers[t1] = int1;
    ipm.registers[t2] = int2;
    ADD(&ipm);
    DEBUG_PRINT("t0: %d\n", ipm.registers[t0]);
    return Assert_Equal(sum, ipm.registers[t0]);
}

int SUB_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b01000000011100110000001010110011; //sub t0, t1, t2
    word int1 = RandW();
    DEBUG_PRINT("int1: %d\n", int1);
    word int2 = RandW();
    DEBUG_PRINT("int2: %d\n", int2);
    word result = (int1 - int2);
    DEBUG_PRINT("result: %d\n", result);
    ipm.registers[t1] = int1;
    ipm.registers[t2] = int2;
    SUB(&ipm);
    DEBUG_PRINT("t0: %d\n", ipm.registers[t0]);
    return Assert_Equal(result, ipm.registers[t0]);
}

int ADDI_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00001000100100110000001010010011; //addi t0, t1, 137
    word int1 = RandW();
    DEBUG_PRINT("int1: %d\n", int1);
    word sum = (int1 + 137);
    DEBUG_PRINT("sum: %d\n", sum);
    ipm.registers[t1] = int1;
    ADDI(&ipm);
    DEBUG_PRINT("t0: %d\n", ipm.registers[t0]);
    return Assert_Equal(sum, ipm.registers[t0]);
}

int LUI_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000010001001001010110111; //lui t0, 137
    LUI(&ipm);
    DEBUG_PRINT("t0: %d\n", ipm.registers[t0]);
    return Assert_Equal((137 << 12), ipm.registers[t0]);
}

int SLL_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a2] = RandW();
    ipm.registers[a3] = (rand()%31)+1;
    ipm.instruction = 0b00000000110101100001010110110011;  //sll  a1 , a2 , a3
    word temp = ipm.registers[a2] << ipm.registers[a3];
    SLL(&ipm);
    DEBUG_PRINT("a1 = a2 << a3   a2: %d  a3: %d\n",ipm.registers[a2],ipm.registers[a3]);
    DEBUG_PRINT("a1: %d\n", ipm.registers[a1]);
    return Assert_Equal(temp, ipm.registers[a1]);

}

int SLT_uTest(){
    InternalProcessorMemory ipm;
    word rand1 = RandW();
    word rand2 = RandW();
    ipm.registers[t1] = rand1;
    ipm.registers[t2] = rand2;
    ipm.instruction = 0b00000000011100110010010100110011;//    slt a0,t1,t2
    SLT(&ipm);
    word result = rand1 < rand2;
    DEBUG_PRINT("int1: %d\nint2: %d\nres: %d\nA0:%d\n",rand1,rand2,result,ipm.registers[a0]);
    return Assert_Equal(result,ipm.registers[a0]);
}

int SRA_uTest() {
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    ipm.registers[a2] = (rand() % 31) + 1;
    word ins = 0b01000000110001011101010100110011;
    ipm.instruction = ins; //sra  a0 , a1 , a2
    word temp = ipm.registers[a1] >> ipm.registers[a2];
    SRA(&ipm);
    DEBUG_PRINT("a0 = a1 >> a2   a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SRAI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b01000000001101011101010100010011;
    ipm.instruction = ins; //srai  a0 , a1 , 3
    word temp = ipm.registers[a1] >> 3;
    SRAI(&ipm);
    DEBUG_PRINT("a0 = a1 >> 3   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SLTI_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000011001000111010001100010011; //slti t1, t2, 50
    word randWord = RandUW();
    DEBUG_PRINT("randWord: ");
    DebugPrintWord(randWord);
    word result = (randWord < 50);
    DEBUG_PRINT("result: %d\n", result);
    ipm.registers[t2] = randWord;
    SLTI(&ipm);
    DEBUG_PRINT("t1: %d\n", ipm.registers[t1]);
    return Assert_Equal(result, ipm.registers[t1]);
}

int SLTU_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000011100110011010100110011;  //    sltu a0,t1,t2
    uWord temp1 = RandUW();
    uWord temp2 = RandUW();
    ipm.registers[t1] = temp1;
    ipm.registers[t2] = temp2;
    SLTU(&ipm);
    uWord res = temp1 < temp2;
    DEBUG_PRINT("temp1: %u \t temp2: %u \t res:%u\n",temp1,temp2,res);
    DEBUG_PRINT("a0: %d\t t1: %d \t t2:%d\n", ipm.registers[a0],ipm.registers[t1],ipm.registers[t2]);
    return Assert_Equal(res, ipm.registers[a0]);
}

int LB_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000110000001010000011; //lb t0, 0(t1)
    byte temp1 = RandB();
    DEBUG_PRINT("temp1: %d \n", temp1);
    word address = 0x100;
    setHWord(temp1, address);
    ipm.registers[t1] = address;
    LB(&ipm);
    word comp = (temp1 & 0xFF) | ((temp1 & 0x80) ? 0xFFFFFF00 : 0);
    DEBUG_PRINT("comp: %d \n", comp);
    return Assert_Equal(comp, ipm.registers[t0]);
}

int LH_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000110001001010000011; // lh t0, 0(t1)
    hWord temp1 = RandHW();
    DEBUG_PRINT("temp1: %d \n", temp1);
    word address = 0x100;
    setHWord(temp1, address);
    ipm.registers[t1] = address;
    LH(&ipm);
    word comp = (temp1 & 0xFFFF) | ((temp1 & 0x8000) ? 0xFFFF0000 : 0);
    DEBUG_PRINT("comp: %d \n", comp);
    return Assert_Equal(comp, ipm.registers[t0]);
}

int LW_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000110010001010000011; //lw t0, 0(t1)
    word temp1 = RandW();
    DEBUG_PRINT("temp1: %d \n", temp1);
    word address = 0x100;
    setWord(temp1, address);
    ipm.registers[t1] = address;
    LW(&ipm);
    DEBUG_PRINT("t0: %d \n", ipm.registers[t0]);
    return Assert_Equal(temp1, ipm.registers[t0]);
}

int XOR_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    ipm.registers[a2] = RandW();
    word ins = 0b00000000110001011100010100110011;
    ipm.instruction = ins; //xor  a0 , a1 , a2
    word temp = ipm.registers[a1] ^ ipm.registers[a2];
    XOR(&ipm);
    DEBUG_PRINT("a0 = a1 XOR a2   a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int XORI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00011001101001011100010100010011;
    ipm.instruction = ins; //xori  a0 , a1 , 0b110011010
    word temp = ipm.registers[a1] ^ (word)0b110011010;
    XORI(&ipm);
    DEBUG_PRINT("a0 = a1 XORI 0b110011010   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int OR_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    ipm.registers[a2] = RandW();
    word ins = 0b00000000110001011110010100110011;
    ipm.instruction = ins; //or  a0 , a1 , a2
    word temp = ipm.registers[a1] | ipm.registers[a2];
    OR(&ipm);
    DEBUG_PRINT("a0 = a1 OR a2   a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}
int AND_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    ipm.registers[a2] = RandW();
    word ins = 0b00000000110001011111010100110011;
    ipm.instruction = ins; //and  a0 , a1 , a2
    word temp = ipm.registers[a1] & ipm.registers[a2];
    AND(&ipm);
    DEBUG_PRINT("a0 = a1 AND a2   a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SRL_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    ipm.registers[a2] = (rand() % 31) + 1;
    word ins = 0b00000000110001011101010100110011;
    ipm.instruction = ins; //srl  a0 , a1 , a2
    word temp = ((uWord)ipm.registers[a1]) >> ((uWord)ipm.registers[a2]);
    SRL(&ipm);
    DEBUG_PRINT("a0 = a1 >>(logi) a2   a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SLLI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00000000001101011001010100010011;
    ipm.instruction = ins; //slli  a0 , a1 , 3
    word temp = ipm.registers[a1] << 3;
    SLLI(&ipm);
    DEBUG_PRINT("a0 = a1 << 3   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SRLI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00000000001101011101010100010011;
    ipm.instruction = ins; //srli  a0 , a1 , 3
    word temp = ((uWord)ipm.registers[a1]) >> ((uWord)3);
    SRLI(&ipm);
    DEBUG_PRINT("a0 = a1 >> 3   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SLTIU_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00000000001101011011010100010011;
    ipm.instruction = ins; //sltiu  a0 , a1 , 3
    word temp = ((uWord)ipm.registers[a1]) < ((uWord)3);
    SLTIU(&ipm);
    DEBUG_PRINT("a0 = a1 < 3   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int ORI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00000000101001011110010100010011;
    ipm.instruction = ins; //ori  a0 , a1 , 0b1010
    word temp = ipm.registers[a1] | 0b1010;
    ORI(&ipm);
    DEBUG_PRINT("a0 = a1 | 0b1010   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int ANDI_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = RandW();
    word ins = 0b00000000101001011111010100010011;
    ipm.instruction = ins; //and  a0 , a1 , 0b1010
    word temp = ipm.registers[a1] & 0b1010;
    ANDI(&ipm);
    DEBUG_PRINT("a0 = a1 & 0b1010   a1: %d\n", ipm.registers[a1]);
    DEBUG_PRINT("a0: %d\n", ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SW_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000100001011010001110100011; //        sw s0, 7(a1)
    word val = RandW();
    word address = RandUW();
    word imm = 7;
    ipm.registers[s0] = val; 
    ipm.registers[a1] = address;
    SW(&ipm);
    word res = getWord(address+imm);
    DEBUG_PRINT("Address: %d \t val:%d \t res:%d\n",address,val,res);
    return Assert_Equal(res,val);
} 

int BEQ_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) rand()%2;
    ipm.registers[a2] = (word) rand()%2;
    ipm.pc = 0;
    word ins = 0b00000000101101100000010001100011;
    ipm.instruction = ins;// beq  a2 , a1 , 8
    int temp = -1;
    if(ipm.registers[a1] == ipm.registers[a2]) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BEQ(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int BLT_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) rand()%3;
    ipm.registers[a2] = (word) rand()%3;
    ipm.pc = 0;
    word ins = 0b00000000110001011100010001100011;
    ipm.instruction = ins;// blt  a1 , a2 , 8
    int temp = -1;
    if(ipm.registers[a1] < ipm.registers[a2]) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BLT(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int BGE_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) rand()%3;
    ipm.registers[a2] = (word) rand()%3;
    ipm.pc = 0;
    word ins = 0b00000000110001011101010001100011;
    ipm.instruction = ins;// bge  a1 , a2 , 8
    int temp = -1;
    if(ipm.registers[a1] >= ipm.registers[a2]) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BGE(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int BNE_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) rand()%3;
    ipm.registers[a2] = (word) rand()%3;
    ipm.pc = 0;
    word ins = 0b00000000110001011001010001100011;
    ipm.instruction = ins;// bne  a1 , a2 , 8
    int temp = -1;
    if(ipm.registers[a1] != ipm.registers[a2]) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BNE(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int BGEU_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) (rand()%3-1);
    ipm.registers[a2] = (word) (rand()%3-1);
    ipm.pc = 0;
    word ins = 0b00000000110001011111010001100011;
    ipm.instruction = ins;// bgeu  a1 , a2 , 8
    int temp = -1;
    if(((uWord)ipm.registers[a1]) >= ((uWord)ipm.registers[a2])) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BGEU(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int BLTU_uTest(){
    InternalProcessorMemory ipm;
    ipm.registers[a1] = (word) (rand()%3-1);
    ipm.registers[a2] = (word) (rand()%3-1);
    ipm.pc = 0;
    word ins = 0b00000000110001011110010001100011;
    ipm.instruction = ins;// bltu  a1 , a2 , 8
    int temp = -1;
    if(((uWord)ipm.registers[a1]) < ((uWord)ipm.registers[a2])) {
        temp = 4; //4 because pc is counted 4 up when executing
    } else {
        temp = 0;
    }
    BLTU(&ipm);
    DEBUG_PRINT("a1: %d  a2: %d\n", ipm.registers[a1], ipm.registers[a2]);
    DEBUG_PRINT("pc should be: %d  pc is: %d\n", temp, ipm.pc);
    return Assert_Equal(temp, ipm.pc);
}

int AUIPC_uTest(){
    InternalProcessorMemory ipm;
    ipm.pc = (rand()%10)*4;
    word ins = 0b00000000000001001001010100010111;
    ipm.instruction = ins;// auipc a0, 73
    int temp = ipm.pc + (73 << 12);
    AUIPC(&ipm);
    DEBUG_PRINT("pc is : %d\n", ipm.pc);
    DEBUG_PRINT("Should be: %d   is: %d\n", temp, ipm.registers[a0]);
    return Assert_Equal(temp, ipm.registers[a0]);
}

int SH_uTest(){
    InternalProcessorMemory ipm;
    word address = RandUW();
    hWord val = RandHW();
    word imm = 7;
    ipm.instruction = 0b00000000100001011001001110100011;  //        sh s0, 7(a1)
    ipm.registers[s0] = (word)val;
    ipm.registers[a1] = address;
    SH(&ipm);
    hWord res = getHWord(address+imm);
    DEBUG_PRINT("Address: %d \t val:%d \t res:%d\n",address,val,res);
    return Assert_Equal(res, val);
}

int SB_uTest(){
    InternalProcessorMemory ipm;
    word address = RandUW();
    byte val = RandB();
    word imm = 7;
    ipm.instruction = 0b00000000100001011000001110100011; //       sb s0, 7(a1)
    ipm.registers[s0] = (word)val;
    ipm.registers[a1] = address;
    SB(&ipm);
    byte res = getByte(address + imm);
    DEBUG_PRINT("Address: %d \t val:%d \t res:%d\n",address,val,res);
    return Assert_Equal(res,val);
}

int JAL_uTest(){
    InternalProcessorMemory ipm;
    ipm.pc = (rand()%3)*4;
    word ins = 0b11111111110111111111010101101111;
    ipm.instruction = ins;// jal a0, -4
    int newPC = ipm.pc - 4 - 4; //4 is subtracted because it is added in execution.
    word returnAaddress = ipm.pc + 4;
    DEBUG_PRINT("pc was: %d\n", ipm.pc);
    JAL(&ipm);
    DEBUG_PRINT("PC should be: %d   is: %d\n", newPC, ipm.pc);
    DEBUG_PRINT("return address should be: %d   is: %d\n", returnAaddress, ipm.registers[a0]);
    if(newPC == ipm.pc && returnAaddress == ipm.registers[a0]){
        return 1;
    } else {
        return 0;
    }
}

int JALR_uTest(){
    InternalProcessorMemory ipm;
    ipm.pc = (rand()%3)*4;
    ipm.registers[a1] = RandW();
    word ins = 0b11111111110001011000010101100111;
    ipm.instruction = ins;// jal a0, a1, -4
    int newPC = ((ipm.registers[a1] - 4) & (~0x00000001)) -4; //4 is subtracted because it is added in execution.
    word returnAddress = ipm.pc + 4;
    DEBUG_PRINT("pc was: %d\n", ipm.pc);
    JALR(&ipm);
    DEBUG_PRINT("PC should be: %d   is: %d\n", newPC, ipm.pc);
    DEBUG_PRINT("return address should be: %d   is: %d\n", returnAddress, ipm.registers[a0]);
    if(newPC == ipm.pc && returnAddress == ipm.registers[a0]){
        return 1;
    } else {
        return 0;
    }
}

int LBU_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000110100001010000011; //lbu t0, 0(t1)
    uByte temp1 = RandUB();
    DEBUG_PRINT("temp1: %d \n", temp1);
    word address = 0x100;
    setUByte(temp1, address);
    ipm.registers[t1] = address;
    LBU(&ipm);
    return Assert_Equal(temp1, ipm.registers[t0]);
}

int LHU_uTest(){
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000110101001010000011; //lhu t0, 0(t1)
    uHWord temp1 = RandUHW();
    DEBUG_PRINT("temp1: %d \n", temp1);
    word address = 0x100;
    setUHWord(temp1, address);
    ipm.registers[t1] = address;
    LHU(&ipm);
    return Assert_Equal(temp1, ipm.registers[t0]);
}

int ECALL_uTest() {
    InternalProcessorMemory ipm;
    ipm.instruction = 0b00000000000000000000000001110011; //ecall
    ipm.registers[a7] = 1;
    word randWord = RandW();
    DEBUG_PRINT("randWord: ");
    DebugPrintWord(randWord);
    DEBUG_PRINT("Ecall output: ");
    ipm.registers[a0] = randWord;
    ECALL(&ipm);

    ipm.registers[a7] = 2;
    ipm.registers[a0] = 0x40490FDB;
    DEBUG_PRINT("Approximation of pi: ");
    ECALL(&ipm);

    ipm.registers[a7] = 4;
    word address = 0x1000;
    ipm.registers[a0] = address;
    setByte(65, address);
    setByte(32, address + 1);
    setByte(115, address + 2);
    setByte(116, address + 3);
    setByte(114, address - 4);
    setByte(105, address - 4 + 1);
    setByte(110, address - 4 + 2);
    setByte(103, address - 4 + 3);
    setByte(0, address - 8);
    DEBUG_PRINT("Printing \"A string\": ");
    ECALL(&ipm);

    ipm.registers[a7] = 11;
    DEBUG_PRINT("Printing ASCII chars 33-126: ");
    for (word i = 33; i < 126; i++) {
        ipm.registers[a0] = i;
        ECALL(&ipm);
    }
    return Assert_Equal(1, 1);
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
    CreateTest(&SLL_uTest, "SLL test"),
    CreateTest(&SLT_uTest, "SLT test"),
    CreateTest(&SRA_uTest, "SRA test"),
    CreateTest(&SLTI_uTest, "SLTI test"),
    CreateTest(&ECALL_uTest, "ECALL test"),
    CreateTest(&SLTU_uTest, "SLTU test"),
    CreateTest(&XOR_uTest, "XOR test"),
    CreateTest(&OR_uTest, "OR test"),
    CreateTest(&AND_uTest, "AND test"),
    CreateTest(&SRL_uTest, "SRL test"),
    CreateTest(&SLLI_uTest, "SLLI test"),
    CreateTest(&SLTIU_uTest, "SLTIU test"),
    CreateTest(&XORI_uTest, "XORI test"),
    CreateTest(&SRLI_uTest, "SRLI test"),
    CreateTest(&SRAI_uTest, "SRAI test"),
    CreateTest(&ORI_uTest, "ORI test"),
    CreateTest(&ANDI_uTest, "ANDI test"),
    CreateTest(&SW_uTest,"SW test"),
    CreateTest(&BEQ_uTest,"BEQ test"),
    CreateTest(&LB_uTest, "LB test"),
    CreateTest(&LH_uTest, "LH test"),
    CreateTest(&LW_uTest, "LW test"),
    CreateTest(&BLT_uTest, "BLT test"),
    CreateTest(&BGE_uTest, "BGE test"),
    CreateTest(&BNE_uTest, "BNE test"),
    CreateTest(&BGEU_uTest, "BGEU test"),
    CreateTest(&BLTU_uTest, "BLTU test"),
    CreateTest(&AUIPC_uTest, "AUIPC test"),
    CreateTest(&SH_uTest, "SH test"),
    CreateTest(&SB_uTest, "SB test"),
    CreateTest(&AUIPC_uTest, "AUIPC test"),
    CreateTest(&JAL_uTest, "JAL test"),
    CreateTest(&JALR_uTest, "JALR test"),
    CreateTest(&LBU_uTest, "LBU test"),
    CreateTest(&LHU_uTest, "LHU test")
    };

    for (int i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++) {
        ExecuteTest(tests[i]);
    }
}

void ExecuteAllTests() {
    MemoryTestSuite();
    InstructionSetTestSuite();
}