//
// Created by juliu on 09-10-2023.
//

#ifndef RISCVSIM_TYPES_H
#define RISCVSIM_TYPES_H

typedef long word;
typedef int hWord;
typedef char byte;
typedef unsigned long uWord;
typedef unsigned int uHWord;
typedef unsigned char uByte;

#define BIT_PR_BYTE 8
#define MAIN_MEM_SIZE 1000000

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(...)    /* Don't do anything in release builds */
#endif


#endif //RISCVSIM_TYPES_H
