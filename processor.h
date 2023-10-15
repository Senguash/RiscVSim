//
// Created by jonas on 15-10-2023.
//
#include <stdio.h>
#include "types.h"
#include "main.h"
#include "memMan.h"

#define zero = 0;
#define ra = 1; //Return Address
#define sp = 2; //Stack Pointer
#define gp = 3; //Global Pointer
#define tp = 4; //Thread Pointer

typedef struct InternalProcessorMemory InternalProcessorMemory;
struct InternalProcessorMemory {
	word registers[32]; //Register Array
	int pc; //Process Counter
	word instruction; //Current Instruction
};

void Compute(InternalProcessorMemory ipm);
void ExecuteInstruction(InternalProcessorMemory ipm);

byte GetFunct3(word instruction);
byte GetFunct7(word instruction);
byte GetRD(InternalProcessorMemory ipm);
byte GetRS1(InternalProcessorMemory ipm);
byte GetRS2(InternalProcessorMemory ipm);

void LogicalArithmetic(InternalProcessorMemory ipm);
void LogicalArithmeticImmediate(InternalProcessorMemory ipm);
void Load(InternalProcessorMemory ipm);
void Store(InternalProcessorMemory ipm);
void Branch(InternalProcessorMemory ipm);

void ADD(InternalProcessorMemory ipm);
void SUB(InternalProcessorMemory ipm);
void SLL(InternalProcessorMemory ipm);
void SLT(InternalProcessorMemory ipm);
void SLTU(InternalProcessorMemory ipm);
void XOR(InternalProcessorMemory ipm);
void SRL(InternalProcessorMemory ipm);
void SRA(InternalProcessorMemory ipm);
void OR(InternalProcessorMemory ipm);
void AND(InternalProcessorMemory ipm);
void ADDI(InternalProcessorMemory ipm);
void SLLI(InternalProcessorMemory ipm);
void SLTI(InternalProcessorMemory ipm);
void SLTIU(InternalProcessorMemory ipm);
void XORI(InternalProcessorMemory ipm);
void SRLI(InternalProcessorMemory ipm);
void SRAI(InternalProcessorMemory ipm);
void ORI(InternalProcessorMemory ipm);
void ANDI(InternalProcessorMemory ipm);
void LB(InternalProcessorMemory ipm);
void LH(InternalProcessorMemory ipm);
void LW(InternalProcessorMemory ipm);
void LBU(InternalProcessorMemory ipm);
void LHU(InternalProcessorMemory ipm);
void SB(InternalProcessorMemory ipm);
void SH(InternalProcessorMemory ipm);
void SW(InternalProcessorMemory ipm);
void BEQ(InternalProcessorMemory ipm);
void BNE(InternalProcessorMemory ipm);
void BLT(InternalProcessorMemory ipm);
void BGE(InternalProcessorMemory ipm);
void BLTU(InternalProcessorMemory ipm);
void BGEU(InternalProcessorMemory ipm);
void LUI(InternalProcessorMemory ipm);
void AUIPC(InternalProcessorMemory ipm);
void JAL(InternalProcessorMemory ipm);
void JALR(InternalProcessorMemory ipm);
void PAUSE(InternalProcessorMemory ipm);
void ECALL(InternalProcessorMemory ipm);