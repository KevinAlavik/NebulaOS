#include#include "cpu.h"
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

void executeInstruction(CPU *cpu, Memory *mem, const char *instruction) {
    int i;
    for (i = 0; i < sizeof(instructionTable) / sizeof(instructionTable[0]); i++) {
        if (strcmp(instruction, instructionTable[i].name) == 0) {
            switch (instructionTable[i].opcode) {
                case OPCODE_ADD:
                    {
                        uint8_t reg1 = mem->read(cpu->PC + 1);
                        uint8_t reg2 = mem->read(cpu->PC + 2);
                        cpu->R[reg1] += cpu->R[reg2];
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_SUB:
                    {
                        uint8_t reg1 = mem->read(cpu->PC + 1);
                        uint8_t reg2 = mem->read(cpu->PC + 2);
                        cpu->R[reg1] -= cpu->R[reg2];
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_MOV:
                    {
                        uint8_t reg = mem->read(cpu->PC + 1);
                        uint8_t value = mem->read(cpu->PC + 2);
                        cpu->R[reg] = value;
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_JMP:
                    {
                        uint16_t targetAddress = mem->read16(cpu->PC + 1);
                        cpu->PC = targetAddress;
                    }
                    break;
                case OPCODE_HLT:
                    return;
                default:
                    printf("Unsupported instruction: %s\n", instruction);
                    return;
            }
            return;
        }
    }
    printf("Unsupported instruction: %s\n", instruction);
}

void loadROM(CPU *cpu, const uint8_t* program, uint16_t programSize) {
    if (programSize > sizeof(cpu->ROM)) {
        printf("Program size exceeds ROM capacity.\n");
        return;
    }

    memcpy(cpu->ROM, program, programSize);
}

void runCPULoop(CPU *cpu, Memory *mem) {
    while (1) {
        uint8_t instruction = mem->read(cpu->PC);
        executeInstruction(cpu, mem, instruction);
        if (instruction == OPCODE_HLT) {
            break;
        }
    }
}