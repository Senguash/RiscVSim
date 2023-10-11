//
// Created by juliu on 09-10-2023.
//



#ifndef RISCVSIM_MENMAN_H
#define RISCVSIM_MENMAN_H


#include "types.h"

void initMem();

word getInitPC();


void setWord(word value, word address);
word getWord(word address);

void setUWord(uWord value, word address);
uWord getUWord(word address);


void setHWord(hWord value, word address);
hWord getHWord(word address);

void setUHWord(uHWord value, word address);
uHWord getUHWord(word address);


void setByte(byte value, word address);
byte getByte(word address);

void setUByte(uByte value, word address);
uByte getUByte(word address);


#endif //RISCVSIM_MENMAN_H
