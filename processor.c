//
// Created by jonas on 15-10-2023.
//
#include "processor.h"

/**
 * execute the program in memory
 * @param ipm
 */
void Compute(InternalProcessorMemory *ipm) {
	ZeroOutRegisters(ipm);
	ipm->exitInvoked = 0;
	while (ipm->exitInvoked == 0) {
		ipm->instruction = getWord((word)ipm->pc);
		ExecuteInstruction(ipm);
        ipm->registers[0] = 0;
		ipm->pc += 4;
	}

}
/**
 * Executes the current instruction in ipm
 * @param ipm
 */
void ExecuteInstruction(InternalProcessorMemory *ipm) {
	byte opcode = ipm->instruction & 0b01111111;
    DEBUG_PRINT("Inst="WORD_TO_BINARY_PATTERN" ", WORD_TO_BINARY((ipm->instruction)));
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
			DEBUG_PRINT("LUI\n");
			LUI(ipm);
			break;
		case (0b0010111):
			DEBUG_PRINT("AUIPC\n");
			AUIPC(ipm);
			break;
		case (0b1101111):
			DEBUG_PRINT("JAL\n");
			JAL(ipm);
			break;
		case (0b1100111):
			DEBUG_PRINT("JALR\n");
			JALR(ipm);
			break;
		case (0b1110011):
			DEBUG_PRINT("ECALL\n");
			ECALL(ipm);
			break;
		default:
			DEBUG_PRINT("Invalid Instruction Reached\n");
			ipm->exitInvoked = 1;
	}
}
/**
 * prints word in dec, hex and bin
 * @param w word
 */
void PrintWordInAllFormats(word w) {
	printf("dec:%-10d hex:0x%-10x bin:"WORD_TO_BINARY_PATTERN"\n", w, w, WORD_TO_BINARY(w));
}
/**
 * prints word in dec, hex and bin
 * only when debug flag is set in utils.h
 * @param w word
 */
void DebugPrintWord(word w) {
	DEBUG_PRINT("dec:%-10d hex:0x%-10x bin:"WORD_TO_BINARY_PATTERN"\n", w, w, WORD_TO_BINARY(w));
}

/**
 * Prints all regs in ipm
 * @param ipm
 */
void PrintRegisters(InternalProcessorMemory* ipm) {
	for (int i = 0; i < 32; i++) {
		printf("Reg:%2d ", i);
		PrintWordInAllFormats(ipm->registers[i]);
	}
}

/**
 * creats a dump file at fileName with all regs from ipm in binary littel-endian
 * @param ipm
 * @param fileName
 */
void DumpRegisters(InternalProcessorMemory* ipm, char *fileName){
    char resFile[100];
    strcpy(resFile,fileName);
    strcat(resFile, ".res");
    FILE* file = fopen(resFile, "wb");
    for (int i = 0; i < 32; ++i) {
        fwrite(&ipm->registers[i], sizeof(word), 1, file);
    }
    fclose(file);
}

/**
 * zeros all regs in ipm
 * @param ipm
 */
void ZeroOutRegisters(InternalProcessorMemory* ipm) {
	for (int i = 0; i < 31; i++) {
		ipm->registers[i] = 0;
	}
}

/**
 * Gets the 3-bit function code (additional opcode) of an instruction
 */
byte GetFunct3(word instruction) {
	return (byte)(instruction >> 12) & 0b0000111;
}

/**
 * Gets the 7-bit function code (additional opcode) of an instruction
 */
byte GetFunct7(word instruction) {
	return (byte)(instruction >> 25) & 0b1111111;
}

/**
 * Gets the index of the destination register
 */
byte GetRD(InternalProcessorMemory *ipm) {
	return (byte)(ipm->instruction >> 7) & 0b00011111;
}

/**
 * Gets the index of first source register
 */
byte GetRS1(InternalProcessorMemory *ipm) {
	return ((byte)(ipm->instruction >> 15)) & 0b00011111;
}

/**
 * Gets the index of second source register
 */
byte GetRS2(InternalProcessorMemory *ipm) {
	return (byte)(ipm->instruction >> 20) & 0b00011111;
}

/**
 * Extract immediate value from a word(instruction) at bit [11:0]
 * @param ipm
 * @return uWord as a word with immediate value
 */
word GetImmediate11to0Unsigned(InternalProcessorMemory* ipm) {
	return (word)(ipm->instruction >> 20) & 0b00000000000000000000111111111111;
}

/**
 * Extract immediate value from a word(instruction) at bit [11:0]
 * @param ipm
 * @return word with immediate value
 */
word GetImmediate11to0(InternalProcessorMemory* ipm) {
    return (word)(ipm->instruction >> 20);
}

/**
 * Extract immediate value from a word(instruction) at bit [12][10:5]
 * @param ipm
 * @return word with immediate value
 */
word GetImmediate12and10to5(InternalProcessorMemory* ipm) {
    word toReturn = 0;
    toReturn = toReturn | ((ipm->instruction >> 31) << 12); // bit 12
    toReturn = toReturn | (((ipm->instruction >> 25) & 0b00000000000000000000000000111111) << 5);  // bit 10:5
    toReturn = toReturn | (((ipm->instruction >> 8)  & 0b00000000000000000000000000001111) << 1);  // bit 4:1
    toReturn = toReturn | (((ipm->instruction >> 7)  & 0b00000000000000000000000000000001) << 11); // bit 11
    return toReturn;
}

/**
 * Extract immediate value from a word(instruction) at bit [20][19:12][11][10:1]
 * @param ipm
 * @return word with immediate value
 */
word GetImmediate20and10to1and11and19to12(InternalProcessorMemory* ipm){
    word toReturn = 0;
    toReturn = toReturn | ((ipm->instruction >> 31) << 20); // bit 20
    toReturn = toReturn | (((ipm->instruction >> 21) & 0b00000000000000000000001111111111) << 1);  // bit 10:1
    toReturn = toReturn | (((ipm->instruction >> 20) & 0b00000000000000000000000000000001) << 11); // bit 11
    toReturn = toReturn | (((ipm->instruction >> 12) & 0b00000000000000000000000011111111) << 12); // bit 19:12
    return toReturn;
}

/**
 * Extract immediate value from a word(instruction) at bit [31:12]
 * @param ipm
 * @return word with immediate value
 */
word GetImmediate31to12(InternalProcessorMemory* ipm) {
	return (ipm->instruction >> 12);
}

/**
 * Extract immediate value from a word(instruction) at bit [11:5]
 * @param ipm
 * @return word with immediate value
 */
word GetImmediate11to5(InternalProcessorMemory* ipm){
	word temp1 = (ipm->instruction >> 25) << 5;
	word temp2 = (ipm->instruction >> 7 ) & 0x0000001f;
	return temp1 | temp2;
}

/**
 * Called by ExecuteInstruction for segmentation. Is a sub switch for execution of instruction.
 * @param ipm
 */
void LogicalArithmetic(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		{
			switch (GetFunct7(ipm->instruction)) {
			case (0b0000000):
				DEBUG_PRINT("ADD\n");
				ADD(ipm);
				break;
			case (0b0100000):
				DEBUG_PRINT("SUB\n");
				SUB(ipm);
				break;
			}
		}
		break;
	case (0b001):
		DEBUG_PRINT("SLL\n");
		SLL(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("SLT\n");
		SLT(ipm);
		break;
	case (0b011):
		DEBUG_PRINT("SLTU\n");
		SLTU(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("XOR\n");
		XOR(ipm);
		break;
	case (0b101):
	{
		switch (GetFunct7(ipm->instruction)) {
		case (0b0000000):
			DEBUG_PRINT("SRL\n");
			SRL(ipm);
			break;
		case (0b0100000):
			DEBUG_PRINT("SRA\n");
			SRA(ipm);
			break;
		}
	}
		break;
	case (0b110):
		DEBUG_PRINT("OR\n");
		OR(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("AND\n");
		AND(ipm);
		break;
	}
}

/**
 * Called by ExecuteInstruction for segmentation. Is a sub switch for execution of instruction.
 * @param ipm
 */
void LogicalArithmeticImmediate(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("ADDI\n");
		ADDI(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("SLLI\n");
		SLLI(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("SLTI\n");
		SLTI(ipm);
		break;
	case (0b011):
		DEBUG_PRINT("SLTIU\n");
		SLTIU(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("XORI\n");
		XORI(ipm);
		break;
	case (0b101):
	{
		switch (GetFunct7(ipm->instruction)) {
		case (0b0000000):
			DEBUG_PRINT("SRLI\n");
			SRLI(ipm);
			break;
		case (0b0100000):
			DEBUG_PRINT("SRAI\n");
			SRAI(ipm);
			break;
		}
	}
	break;
	case (0b110):
		DEBUG_PRINT("ORI\n");
		ORI(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("ANDI\n");
		ANDI(ipm);
		break;
	}
}

/**
 * Called by ExecuteInstruction for segmentation. Is a sub switch for execution of instruction.
 * @param ipm
 */
void Load(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("LB\n");
		LB(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("LH\n");
		LH(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("LW\n");
		LW(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("LBU\n");
		LBU(ipm);
		break;
	case (0b101):
		DEBUG_PRINT("LHU\n");
		LHU(ipm);
		break;
	}
}

/**
 * Called by ExecuteInstruction for segmentation. Is a sub switch for execution of instruction.
 * @param ipm
 */
void Store(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("SB\n");
		SB(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("SH\n");
		SH(ipm);
		break;
	case (0b010):
		DEBUG_PRINT("SW\n");
		SW(ipm);
		break;
	}
}
/**
 * Called by ExecuteInstruction for segmentation. Is a sub switch for execution of instruction.
 * @param ipm
 */
void Branch(InternalProcessorMemory *ipm) {
	switch (GetFunct3(ipm->instruction)) {
	case (0b000):
		DEBUG_PRINT("BEQ\n");
		BEQ(ipm);
		break;
	case (0b001):
		DEBUG_PRINT("BNE\n");
		BNE(ipm);
		break;
	case (0b100):
		DEBUG_PRINT("BLT\n");
		BLT(ipm);
		break;
	case (0b101):
		DEBUG_PRINT("BGE\n");
		BGE(ipm);
		break;
	case (0b110):
		DEBUG_PRINT("BLTU\n");
		BLTU(ipm);
		break;
	case (0b111):
		DEBUG_PRINT("BGEU\n");
		BGEU(ipm);
		break;
	}
}


/**
 * **********************************************
 *           single RISC-V instructions
 * **********************************************
 *
 * The following functions are not commented.
 * They are all our RISC-v instruction implementation
 */

void ADD(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] + ipm->registers[GetRS2(ipm)];
}

void SUB(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] - ipm->registers[GetRS2(ipm)];
}

void SLL(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] << ipm->registers[GetRS2(ipm)];
}

void SLT(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] < ipm->registers[GetRS2(ipm)];
}

void SLTU(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = (uWord) ipm->registers[GetRS1(ipm)] < (uWord) ipm->registers[GetRS2(ipm)]; 
}

void XOR(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] ^ ipm->registers[GetRS2(ipm)];
}

void SRL(InternalProcessorMemory *ipm) {
    uWord a1t = ipm->registers[GetRS1(ipm)];
    uWord a2t = ipm->registers[GetRS2(ipm)];
    word ret = (word)(a1t>>a2t);
    ipm->registers[GetRD(ipm)] = ret;
}

void SRA(InternalProcessorMemory *ipm) {
    word a1t = ipm->registers[GetRS1(ipm)];
    word a2t = ipm->registers[GetRS2(ipm)];
    word ret = (word)(a1t>>a2t);
	ipm->registers[GetRD(ipm)] = ret;
}

void OR(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] | ipm->registers[GetRS2(ipm)];
}

void AND(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] & ipm->registers[GetRS2(ipm)];
}

void ADDI(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm);
}

void SLLI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] << GetImmediate11to0(ipm);
}

void SLTI(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] < GetImmediate11to0(ipm);
}

void SLTIU(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ((uWord)ipm->registers[GetRS1(ipm)]) < (GetImmediate11to0Unsigned(ipm));
}

void XORI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] ^ GetImmediate11to0(ipm);
}

void SRLI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ((uWord)ipm->registers[GetRS1(ipm)]) >> ((uWord) GetImmediate11to0(ipm));
}

void SRAI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] >> (GetImmediate11to0(ipm) & 0b11111);
}

void ORI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] | GetImmediate11to0(ipm);
}

void ANDI(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->registers[GetRS1(ipm)] & GetImmediate11to0(ipm);
}

void LB(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = getByte(ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm));
	ipm->registers[GetRD(ipm)] = (ipm->registers[GetRD(ipm)] & 0xFF) | ((ipm->registers[GetRD(ipm)] & 0x80) ? 0xFFFFFF00 : 0);
}

void LH(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = getHWord(ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm));
	ipm->registers[GetRD(ipm)] = (ipm->registers[GetRD(ipm)] & 0xFFFF) | ((ipm->registers[GetRD(ipm)] & 0x8000) ? 0xFFFF0000 : 0);
}

void LW(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = getWord(ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm));
}

void LBU(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = getUByte(ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm));
}

void LHU(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = getUHWord(ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm));
}

void SB(InternalProcessorMemory *ipm) {
	setByte((byte)ipm->registers[GetRS2(ipm)],ipm->registers[GetRS1(ipm)]+GetImmediate11to5(ipm));	
}

void SH(InternalProcessorMemory *ipm) {
	setHWord((hWord)ipm->registers[GetRS2(ipm)],ipm->registers[GetRS1(ipm)]+GetImmediate11to5(ipm));
}

void SW(InternalProcessorMemory *ipm) {
	setWord(ipm->registers[GetRS2(ipm)],ipm->registers[GetRS1(ipm)]+GetImmediate11to5(ipm));
	
}

void BEQ(InternalProcessorMemory *ipm) {
	if(ipm->registers[GetRS1(ipm)] == ipm->registers[GetRS2(ipm)]){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void BNE(InternalProcessorMemory *ipm) {
    if(ipm->registers[GetRS1(ipm)] != ipm->registers[GetRS2(ipm)]){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void BLT(InternalProcessorMemory *ipm) {
    if(ipm->registers[GetRS1(ipm)] < ipm->registers[GetRS2(ipm)]){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void BGE(InternalProcessorMemory *ipm) {
    if(ipm->registers[GetRS1(ipm)] >= ipm->registers[GetRS2(ipm)]){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void BLTU(InternalProcessorMemory *ipm) {
    if(((uWord)ipm->registers[GetRS1(ipm)]) < ((uWord)ipm->registers[GetRS2(ipm)])){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void BGEU(InternalProcessorMemory *ipm) {
    if(((uWord)ipm->registers[GetRS1(ipm)]) >= ((uWord)ipm->registers[GetRS2(ipm)])){
        ipm->pc += GetImmediate12and10to5(ipm)-4;
    }
}

void LUI(InternalProcessorMemory *ipm) {
	ipm->registers[GetRD(ipm)] = GetImmediate31to12(ipm)  << 12;
}

void AUIPC(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->pc + (GetImmediate31to12(ipm)<<12);
}

void JAL(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->pc + 4;
    ipm->pc = ipm->pc + GetImmediate20and10to1and11and19to12(ipm)-4;
}

void JALR(InternalProcessorMemory *ipm) {
    ipm->registers[GetRD(ipm)] = ipm->pc + 4;
    ipm->pc = ((ipm->registers[GetRS1(ipm)] + GetImmediate11to0(ipm)) & (~0x00000001))-4;
}

void ECALL(InternalProcessorMemory *ipm) {
	switch (ipm->registers[a7]) {
		case 1: //PrintInt
		{
			printf("%" PRIi32"\n", ipm->registers[a0]);
		}
		break;
		case 2: //PrintFloat
		{
			float* ptr = &ipm->registers[a0];
			double d = (double)*ptr;
			printf("%f\n", d);
		}
		break;
		case 4: //PrintString
		{
			word address = ipm->registers[a0];
			byte c = getByte(address);
			while (c != 0) 
			{
				printf("%c", c);
				
				if (address % 4 == 3) {
					address-=7;
				}
				else {
					address++;
				}
				c = getByte(address);
			}
			printf("\n");
		}
		break;
		case 10: //Exit
		{
			ipm->exitInvoked = 1;
		}
		break;
		case 11: //PrintChar
		{
			printf("%c", ipm->registers[a0]);
		}
		break;
		case 17: //GetCWD
		{
            //not done cos not needed
		}
        //rest is not done con not needed
		break;
	}
}