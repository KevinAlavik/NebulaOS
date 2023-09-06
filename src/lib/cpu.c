#include "cpu.h"
#include <stdio.h>

void executeInstruction(CPU *cpu, Memory *mem, const char *instruction) {
    if (strcmp(instruction, "ADD") == 0) {
        uint8_t reg1 = mem->read(cpu->PC + 1);
        uint8_t reg2 = mem->read(cpu->PC + 2);
        cpu->R[reg1] += cpu->R[reg2];
        cpu->PC += 3;
    } else if (strcmp(instruction, "JMP") == 0) {
        uint16_t targetAddress = mem->read16(cpu->PC + 1);
        cpu->PC = targetAddress;
    } else {
        printf("Unsupported instruction: %s\n", instruction);
    }
}

void initializeCPU(CPU *cpu, Memory *mem) {
    memset(cpu, 0, sizeof(CPU));
    cpu->PC = 0x0000;
}
