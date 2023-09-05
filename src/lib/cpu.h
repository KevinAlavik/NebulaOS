#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"  // Include Memory module

// Define CPU structure with registers
typedef struct {
    uint8_t A;
    uint8_t PC;
    Memory* memory;
} CPU;

void initializeCPU(CPU *cpu, Memory *mem);  // Pass Memory as a parameter
void executeInstruction(CPU *cpu, Memory *mem, const char *instruction);  // Pass Memory as a parameter

#endif /* CPU_H */
