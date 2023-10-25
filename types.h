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

#define zero 0 //Zero Register
#define ra 1 //Return Address
#define sp 2 //Stack Pointer
#define gp 3 //Global Pointer
#define tp 4 //Thread Pointer
#define t0 5 //Temporary Register 0
#define t1 6 //Temporary Register 1
#define t2 7 //Temporary Register 2
#define s0 8 //Saved Register/Frame Pointer 0
#define s1 9 //Saved Register 1
#define a0 10 //Function Argument/Return Value 0
#define a1 11 //Function Argument 1
#define a2 12 //Function Argument 2
#define a3 13 //Function Argument 3
#define a4 14 //Function Argument 4
#define a5 15 //Function Argument 5
#define a6 16 //Function Argument 6
#define a7 17 //Function Argument 7
#define s2 18 //Saved Register 2
#define s3 19 //Saved Register 3
#define s4 20 //Saved Register 4
#define s5 21 //Saved Register 5
#define s6 22 //Saved Register 6
#define s7 23 //Saved Register 7
#define s8 24 //Saved Register 8
#define s9 25 //Saved Register 9
#define s10 26 //Saved Register 10
#define s11 27 //Saved Register 11
#define t3 28 //Temporary Register 3
#define t4 29 //Temporary Register 4
#define t5 30 //Temporary Register 5
#define t6 31 //Temporary Register 6

#endif //RISCVSIM_TYPES_H
