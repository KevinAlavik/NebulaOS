#include "cpu.h"

void initializeCPU(CPU *cpu, Memory *mem) {
    // Initialize CPU registers and memory
    cpu->A = 0;
    cpu->PC = 0;
    cpu->memory = mem;

    initializeMemory(mem);  // Initialize Memory
}

void executeInstruction(CPU *cpu, Memory *mem, const char *instruction) {
    // Implement CPU instruction execution logic here
    // For example, you can fetch instructions and data from Memory
    // and execute them based on the instruction set.
}
