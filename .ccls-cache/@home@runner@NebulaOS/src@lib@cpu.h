#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <immintrin.h>

#include "memory.h"

typedef struct {
    uint16_t R[16];
    uint16_t PC;
    uint16_t SP;
    uint16_t FLAGS;
    uint16_t IR;
    uint16_t MMU[4];
    float F[8];
    __m128i V[8];
    uint16_t BP[4];
    uint16_t WP[4];
    uint16_t TR[4];
    uint8_t ROM[0x2000];
    uint8_t RAM[0xDE00];
} CPU;

void initializeCPU(CPU *cpu, Memory *mem);
void executeInstruction(CPU *cpu, Memory *mem, const char *instruction);
void loadROM(CPU *cpu, const uint8_t* program, uint16_t programSize);
void runCPULoop(CPU *cpu, Memory *mem);

#endif /* CPU_H */
