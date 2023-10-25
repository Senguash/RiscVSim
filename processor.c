//
// Created by jonas on 15-10-2023.
//
#include "processor.h"


void Compute(InternalProcessorMemory *ipm) {
	ZeroOutRegisters(ipm);
	ipm->exitInvoked = 0;
	while (ipm->exitInvoked == 0) {
		ipm->instruction = getWord((word)ipm->pc);
		ExecuteInstruction(ipm);
		ipm->pc += 4;
	}
}
/**
Executes the current instruction in ipm
 */
void ExecuteInstruction(InternalProcessorMemory *ipm) {
	byte opcode = ipm->instruction & 0b01111111;
    DEBUG_PRINT("\nInst="BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((byte)(ipm->instruction >> 8*3)));
    DEBUG_PRINT(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((byte)(ipm->instruction >> 8*2)));
    DEBUG_PRINT(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((byte)(ipm->instruction >> 8)));
    DEBUG_PRINT(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY((byte)(ipm->instruction)));
	DEBUG_PRINT("\nOpcode="BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(opcode));
	DEBUG_PRINT("\nFunct3="BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(GetFunct3(ipm->instruction)));
	DEBUG_PRINT("\nFunct7="BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(GetFunct7(ipm->instruction)));
	switch (opcode) {
		case (0b0110011):
			LogicalArithmetic(ipm);
			break;
		case (0b0010011):
			LogicalArithmeticImmediate(ipm);
			break;
		case (0b0000011):
			Load(ipm);
			break;
		case (0b0100011):
			Store(ipm);
			break;
		case (0b1100011):
			Branch(ipm);
			break;
		case (0b0110111):
			DEBUG_PRINT("\nLUI");
			LUI(ipm);
			break;
		case (0b0010111):
			DEBUG_PRINT("\nAUIPC");
			AUIPC(ipm);
			break;
		case (0b1101111):
			DEBUG_PRINT("\nJAL");
			JAL(ipm);
			break;
		case (0b1100111):
			DEBUG_PRINT("\nJALR");
			JALR(ipm);
			break;
		case (0b0000111):
			DEBUG_PRINT("\nPAUSE");
			PAUSE(ipm);
			break;
		case (0b1110011):
			DEBUG_PRINT("\nECALL");
			ECALL(ipm);
			break;
		default:
			DEBUG_PRINT("Invalid Instruction Reached\n");
			ipm->exitInvoked = 1;
	}
}
void PrintWordInAllFormats(word w) {
	printf("dec:%-10ld hex:0x%-10x bin:"WORD_TO_BINARY_PATTERN"\n", w, w, WORD_TO_BINARY(w));
}
void PrintRegisters(InternalProcessorMemory* ipm) {
	for (int i = 0; i < 32; i++) {
		printf("Reg:%2d ", i);
		PrintWordInAllFormats(ipm->registers[i]);
	}
}
void ZeroOutRegisters(InternalProcessorMemory* ipm) {
	for (int i = 0; i < 32; i++) {
		ipm->registers[i] = 0;
	}
}
/**
Gets the 3-bit function code (additional opcode) of an instruction
 */
byte GetFunct3(word instruction) {
	return (byte)(instruction >> 12) & 0b0000111;
}
/**
Gets the 7-bit function code (additional opcode) of an instruction
 */
byte GetFunct7(word instruction) {
	return (byte)(instruction >> 25) & 0b1111111;
}
/**
Gets the index of the destination register
 */
byte GetRD(InternalProcessorMemory *ipm) {
	return (byte)(ipm->instruction >> 7) & 0b00011111;
}
/**
Gets the index of first source register
 */
byte GetRS1(InternalProcessorMemory *ipm) {
	return (byte)(ipm->instruction >> 15) & 0b00011111;
}
/**
Gets the index of second source register
 */
byte GetRS2(InternalProcessorMemory *ipm) {
	return (byte)(ipm->instruction >> 20) & 0b00011111;
}
/**
Gets the value of a register by index
 */
word GetRegisterValue(byte index, InternalProcessorMemory *ipm) {
	return ipm->registers[index];
}
/**
Sets the value of a register by index
 */
void SetRegisterValue(byte index, word input, InternalProcessorMemory *ipm) {
	ipm->registers[index] = input;
}

word GetImmediate11to0(InternalProcessorMemory* ipm) {
	return (word)(ipm->instruction >> 20) & 0b00000000000000000000111111111111;
}

word GetUpperImmediate(InternalProcessorMemory* ipm) {
	return (ipm->instruction >> 12) & 0b11111111111111111111;
}

void LogicalArithmetic(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		{
			switch (GetFunct7(ipm->instruction)) {
			case (0b0000000):
				DEBUG_PRINT("\nADD");
				ADD(ipm);
				break;
			case (0b0100000):
				DEBUG_PRINT("\nSUB");
				SUB(ipm);
				break;
			}
		}
		break;
	case (0b001):
		DEBUG_PRINT("\nSLL");
		SLL(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("\nSLT");
		SLT(ipm);
		break;
	case (0b011):
		DEBUG_PRINT("\nSLTU");
		SLTU(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("\nXOR");
		XOR(ipm);
		break;
	case (0b101):
	{
		switch (GetFunct7(ipm->instruction)) {
		case (0b0000000):
			DEBUG_PRINT("\nSRL");
			SRL(ipm);
			break;
		case (0b0100000):
			DEBUG_PRINT("\nSRA");
			SRA(ipm);
			break;
		}
	}
		break;
	case (0b110):
		DEBUG_PRINT("\nOR");
		OR(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("\nAND");
		AND(ipm);
		break;
	}
}

void LogicalArithmeticImmediate(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("\nADDI");
		ADDI(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("\nSLLI");
		SLLI(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("\nSLTI");
		SLTI(ipm);
		break;
	case (0b011):
		DEBUG_PRINT("\nSLTIU");
		SLTIU(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("\nXORI");
		XORI(ipm);
		break;
	case (0b101):
	{
		switch (GetFunct7(ipm->instruction)) {
		case (0b0000000):
			DEBUG_PRINT("\nSRLI");
			SRLI(ipm);
			break;
		case (0b0100000):
			DEBUG_PRINT("\nSRAI");
			SRAI(ipm);
			break;
		}
	}
	break;
	case (0b110):
		DEBUG_PRINT("\nORI");
		ORI(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("\nANDI");
		ANDI(ipm);
		break;
	}
}

void Load(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("\nLB");
		LB(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("\nLH");
		LH(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("\nLW");
		LW(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("\nLBU");
		LBU(ipm);
		break;
	case (0b101):
		DEBUG_PRINT("\nLHU");
		LHU(ipm);
		break;
	}
}

void Store(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("\nSB");
		SB(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("\nSH");
		SH(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("\nSW");
		SW(ipm);
		break;
	}
}

void Branch(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("\nBEQ");
		BEQ(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("\nBNE");
		BNE(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("\nBLT");
		BLT(ipm);
		break;
	case (0b101):
		DEBUG_PRINT("\nBGE");
		BGE(ipm);
		break;
	case (0b110):
		DEBUG_PRINT("\nBLTU");
		BLTU(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("\nBGEU");
		BGEU(ipm);
		break;
	}
}

void ADD(InternalProcessorMemory *ipm) {
	//DEBUG_PRINT("RS1 "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(GetRS1(ipm)));
	//DEBUG_PRINT("RS1 Content: %ld\n", ipm->registers[GetRS1(ipm)]);
	//DEBUG_PRINT("RS2 "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(GetRS2(ipm)));
	//DEBUG_PRINT("RS2 Content: %ld\n", ipm->registers[GetRS2(ipm)]);
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] + ipm->registers[GetRS2(ipm)];
}

void SUB(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] - ipm->registers[GetRS2(ipm)];
}

void SLL(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SLT(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SLTU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void XOR(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SRL(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SRA(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void OR(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void AND(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void ADDI(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm);
}

void SLLI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SLTI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SLTIU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void XORI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SRLI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SRAI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void ORI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void ANDI(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LB(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LH(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LW(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LBU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LHU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SB(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SH(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void SW(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BEQ(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BNE(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BLT(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BGE(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BLTU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void BGEU(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void LUI(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = GetUpperImmediate(ipm);
}

void AUIPC(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void JAL(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void JALR(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void PAUSE(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}

void ECALL(InternalProcessorMemory *ipm) {
	DEBUG_PRINT("\nNot Implemented");
}