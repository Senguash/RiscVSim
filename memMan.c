//
// Created by juliu on 09-10-2023.
//

#include "memMan.h"

byte mainMem[MAIN_MEM_SIZE];

/**
 * Inits mainMem to all 0x00
 */
void initMem() {
    for (long i = 0; i < MAIN_MEM_SIZE; i++) {
        mainMem[i] = 0;
    }
}

/**
 * gets PC
 * @return word PC
 */
word getInitPC(){
//    DEBUG_PRINT("Getting initial PC is not implemented, for now it is just 0\n");
    return 0;
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setWord(word value, word address) {
    mainMem[address+3] = value>>BIT_PR_BYTE*3;
    mainMem[address+2] = (value<<BIT_PR_BYTE)>>BIT_PR_BYTE*3;
    mainMem[address+1] = (value<<BIT_PR_BYTE*2)>>BIT_PR_BYTE*3;
    mainMem[address] = (value<<BIT_PR_BYTE*3)>>BIT_PR_BYTE*3;
}

/**
 * gets the word at address
 * @param address got get word
 * @return word at address
 */
word getWord(word address){
    word temp = 0;
    temp = temp | ((((uWord)mainMem[address+3])<<(BIT_PR_BYTE*3)) & 0xff000000);
    temp = temp | ((((uWord)mainMem[address+2])<<(BIT_PR_BYTE*2)) & 0x00ff0000);
    temp = temp | ((((uWord)mainMem[address+1])<<(BIT_PR_BYTE*1)) & 0x0000ff00);
    temp = temp | (mainMem[address] & 0x000000ff);
    return temp;
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setUWord(uWord value, word address){
    mainMem[address+3] = value>>BIT_PR_BYTE*3;
    mainMem[address+2] = (value<<BIT_PR_BYTE)>>BIT_PR_BYTE*3;
    mainMem[address+1] = (value<<BIT_PR_BYTE*2)>>BIT_PR_BYTE*3;
    mainMem[address] = (value<<BIT_PR_BYTE*3)>>BIT_PR_BYTE*3;
}

/**
 * gets the uWord at address
 * @param address got get uWord
 * @return uWord at address
 */
uWord getUWord(word address){
    uWord temp = 0;
    temp = temp | mainMem[address] & 0x000000ff;
    temp = temp | ((((long)mainMem[address+1])<<BIT_PR_BYTE) & 0x0000ff00);
    temp = temp | ((((long)mainMem[address+2])<<BIT_PR_BYTE*2) & 0x00ff0000);
    temp = temp | ((((long)mainMem[address+3])<<BIT_PR_BYTE*3) & 0xff000000);
    return temp;
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setHWord(hWord value, word address){
    mainMem[address+1] = value>>BIT_PR_BYTE;
    mainMem[address] = (value<<BIT_PR_BYTE)>>BIT_PR_BYTE;
}

/**
 * gets the hWord at address
 * @param address got get hWord
 * @return hWord at address
 */
hWord getHWord(word address){
    hWord temp = 0;
    temp = temp | mainMem[address] & 0x00ff;
    temp = temp | ((((long)mainMem[address+1])<<BIT_PR_BYTE) & 0xff00);
    return temp;
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setUHWord(uHWord value, word address){
    mainMem[address+1] = value>>BIT_PR_BYTE;
    mainMem[address] = (value<<BIT_PR_BYTE)>>BIT_PR_BYTE;
}

/**
 * gets the uHWord at address
 * @param address got get uHWord
 * @return uHWord at address
 */
uHWord getUHWord(word address){
    uHWord temp = 0;
    temp = temp | mainMem[address] & 0x00ff;
    temp = temp | ((((long)mainMem[address+1])<<BIT_PR_BYTE) & 0xff00);
    return temp;
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setByte(byte value, word address){
    mainMem[address] = value;
}

/**
 * gets the byte at address
 * @param address got get byte
 * @return byte at address
 */
byte getByte(word address){
    return mainMem[address];
}

/**
 * sets the value at the address.
 * @param value to store in mem
 * @param address addres to store value in mem
 */
void setUByte(uByte value, word address){
    mainMem[address] = value;
}

/**
 * gets the uByte at address
 * @param address got get uByte
 * @return uByte at address
 */
uByte getUByte(word address){
    return mainMem[address];
}
