#include "assembler.h"
#include <stdio.h>
#include <string.h>

#define INSTRUCTION_ADD "ADD"
#define INSTRUCTION_SUB "SUB"
#define INSTRUCTION_MOV "MOV"
#define INSTRUCTION_JMP "JMP"
#define INSTRUCTION_HLT "HLT"

#define OPCODE_ADD 0x01
#define OPCODE_SUB 0x02
#define OPCODE_MOV 0x03
#define OPCODE_JMP 0x04
#define OPCODE_HLT 0x05

typedef struct {
    const char* name;
    uint8_t opcode;
} Instruction;

static const Instruction instructionTable[] = {
    {INSTRUCTION_ADD, OPCODE_ADD},
    {INSTRUCTION_SUB, OPCODE_SUB},
    {INSTRUCTION_MOV, OPCODE_MOV},
    {INSTRUCTION_JMP, OPCODE_JMP},
    {INSTRUCTION_HLT, OPCODE_HLT},
};

static uint8_t getOpcode(const char* instruction) {
    for (int i = 0; i < sizeof(instructionTable) / sizeof(instructionTable[0]); i++) {
        if (strcmp(instruction, instructionTable[i].name) == 0) {
            return instructionTable[i].opcode;
        }
    }
    return 0;
}

int assembleProgram(const char* assemblyCode, uint8_t* machineCode, int machineCodeSize) {
    int programSize = 0;

    char* token = strtok((char*)assemblyCode, "\n");
    while (token != NULL) {
        char instruction[4];
        char operand1[4];
        char operand2[4];

        int numTokens = sscanf(token, "%s %s %s", instruction, operand1, operand2);

        if (numTokens == 3) {
            uint8_t opcode = getOpcode(instruction);
            if (opcode == 0) {
                return -1;
            }

            int reg1 = atoi(operand1);
            int reg2 = atoi(operand2);

            if (reg1 < 0 || reg1 > 15 || reg2 < 0 || reg2 > 15) {
                return -1;
            }

            if (programSize + 3 <= machineCodeSize) {
                machineCode[programSize++] = opcode;
                machineCode[programSize++] = (uint8_t)reg1;
                machineCode[programSize++] = (uint8_t)reg2;
            } else {
                return -1;
            }
        } else {
            return -1;
        }

        token = strtok(NULL, "\n");
    }

    return programSize;
}
