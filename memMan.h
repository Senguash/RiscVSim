//
// Created by juliu on 09-10-2023.
//



#ifndef RISCVSIM_MENMAN_H
#define RISCVSIM_MENMAN_H


#include "types.h"

void initMem();
word getInitCP();
void setWord(word value, word address);
word getWord(word address);
void setHWord(hWord value, word address);
hWord getHWord(word address);
void setByte(byte value, word address);
byte getByte(word address);


#endif //RISCVSIM_MENMAN_H
