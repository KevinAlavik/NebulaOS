#include "assembler.h"
#include <string.h>
#include <stdio.h>

static const struct {
    const char* name;
    uint8_t opcode;
} instructionTable[] = {
    {"ADD", 0x01},
    {"SUB", 0x02},
    {"MOV", 0x03},
    {"JMP", 0x04},
    {"HLT", 0x05},
};

static uint8_t findOpcode(const char* instruction) {
    for (size_t i = 0; i < sizeof(instructionTable) / sizeof(instructionTable[0]); i++) {
        if (strcmp(instruction, instructionTable[i].name) == 0) {
            return instructionTable[i].opcode;
        }
    }
    return 0xFF;
}

int assemble(const char* assemblyCode, uint8_t* machineCode, size_t* machineCodeSize) {
    if (assemblyCode == NULL || machineCode == NULL || machineCodeSize == NULL) {
        return -1;
    }

    size_t machineCodeLen = 0;
    size_t machineCodeCapacity = *machineCodeSize;

    const char* delimiters = " \t,";
    char* token = strtok((char*)assemblyCode, "\n");

    while (token != NULL) {
        char* parts[4];
        int numParts = 0;
        char* part = strtok(token, delimiters);

        while (part != NULL && numParts < 4) {
            parts[numParts++] = part;
            part = strtok(NULL, delimiters);
        }

        if (numParts != 4 || parts[0] == NULL || parts[1] == NULL || parts[2] == NULL || parts[3] == NULL) {
            return -2; // Invalid instruction format
        }

        uint8_t opcode = findOpcode(parts[0]);
        if (opcode == 0xFF) {
            return -3; // Unknown opcode
        }

        uint8_t operand1 = atoi(parts[1] + 1);
        uint8_t operand2 = atoi(parts[2] + 1);
        uint8_t operand3 = atoi(parts[3] + 1);

        if (operand1 > 15 || operand2 > 15 || operand3 > 15) {
            return -4; // Invalid operands
        }

        if (machineCodeLen + 4 > machineCodeCapacity) {
            return -5; // Insufficient buffer size
        }

        machineCode[machineCodeLen++] = opcode;
        machineCode[machineCodeLen++] = (operand1 << 4) | operand2;
        machineCode[machineCodeLen++] = operand3;

        token = strtok(NULL, "\n");
    }

    *machineCodeSize = machineCodeLen;

    return 0; // Successful assembly
}
