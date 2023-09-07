#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
                        uint8_t reg1 = readByte(mem, cpu->PC + 1);
                        uint8_t reg2 = readByte(mem, cpu->PC + 2);
                        cpu->R[reg1] += cpu->R[reg2];
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_SUB:
                    {
                        uint8_t reg1 = readByte(mem, cpu->PC + 1);
                        uint8_t reg2 = readByte(mem, cpu->PC + 2);
                        cpu->R[reg1] -= cpu->R[reg2];
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_MOV:
                    {
                        uint8_t reg = readByte(mem, cpu->PC + 1);
                        uint8_t value = readByte(mem, cpu->PC + 2);
                        cpu->R[reg] = value;
                        cpu->PC += 3;
                    }
                    break;
                case OPCODE_JMP:
                    {
                        uint16_t targetAddress = readWord(mem, cpu->PC + 1); // Use readWord for a 16-bit address
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
    if (programSize > (MAX_ROM_SIZE - cpu->PC)) { // Check against updated ROM size
        printf("Program size exceeds ROM capacity.\n");
        return;
    }

    memcpy(cpu->ROM + cpu->PC, program, programSize);
    cpu->PC += programSize;
}

void runCPULoop(CPU *cpu, Memory *mem) {
    while (cpu->PC < sizeof(cpu->ROM)) {
        uint16_t instructionAddress = cpu->PC;
        uint8_t instruction = readByte(mem, instructionAddress);
        executeInstruction(cpu, mem, instruction);

        if (instruction == OPCODE_HLT) {
            break;
        }

        if (instructionAddress == cpu->PC) {
            printf("Invalid instruction at address 0x%04X\n", instructionAddress);
            break;
        }
    }

    if (cpu->PC >= sizeof(cpu->ROM)) {
        printf("Program counter exceeded ROM size.\n");
    }
}



void printCPUState(const CPU *cpu) {
    printf("General-Purpose Registers:\n");
    for (int i = 0; i < 16; i++) {
        printf("R%d: 0x%04X\n", i, cpu->R[i]);
    }

    printf("Program Counter (PC): 0x%04X\n", cpu->PC);
    printf("Stack Pointer (SP): 0x%04X\n", cpu->SP);
    printf("Flags Register (FLAGS): 0x%04X\n", cpu->FLAGS);
    printf("Instruction Pointer (IR): 0x%04X\n", cpu->IR);

    printf("Memory Management Unit (MMU) Registers:\n");
    for (int i = 0; i < 4; i++) {
        printf("MMU%d: 0x%04X\n", i, cpu->MMU[i]);
    }

    printf("Floating-Point Registers (FPRs):\n");
    for (int i = 0; i < 8; i++) {
        printf("F%d: %f\n", i, cpu->F[i]);
    }

    printf("Vector Registers (SIMD):\n");
    for (int i = 0; i < 8; i++) {
        // You can customize the print format based on the data type stored in V[i]
        // For example, if V[i] stores integers, use %d; if it's floats, use %f, etc.
        printf("V%d: %d\n", i, &cpu->V[i]);
    }

    printf("Debug Registers:\n");
    for (int i = 0; i < 4; i++) {
        printf("BP%d: 0x%04X\n", i, cpu->BP[i]);
        printf("WP%d: 0x%04X\n", i, cpu->WP[i]);
        printf("TR%d: 0x%04X\n", i, cpu->TR[i]);
    }

    // printf("ROM:\n");
    // for (int i = 0; i < 0x2000; i++) {
    //     printf("ROM[%04X]: 0x%02X\n", i, cpu->ROM[i]);
    // }

    // printf("RAM:\n");
    // for (int i = 0; i < 0xDE00; i++) {
    //     printf("RAM[%04X]: 0x%02X\n", i, cpu->RAM[i]);
    // }
}


void initializeCPU(CPU *cpu, Memory *mem) {
    for (int i = 0; i < 16; i++) {
        cpu->R[i] = 0;
    }
    cpu->PC = 0;
    cpu->SP = 0;
    cpu->FLAGS = 0;
    cpu->IR = 0;
    for (int i = 0; i < 4; i++) {
        cpu->MMU[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        cpu->F[i] = 0.0f;
    }
    for (int i = 0; i < 8; i++) {
        cpu->V[i] = _mm_setzero_si128();
    }
    for (int i = 0; i < 4; i++) {
        cpu->BP[i] = 0;
        cpu->WP[i] = 0;
        cpu->TR[i] = 0;
    }
    for (int i = 0; i < 0x2000; i++) {
        cpu->ROM[i] = 0;
    }
    for (int i = 0; i < 0xDE00; i++) {
        cpu->RAM[i] = 0;
    }
}
