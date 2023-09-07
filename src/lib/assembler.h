#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define MAX_PROGRAM_SIZE 256

int assembleProgram(const char* assemblyCode, uint8_t* machineCode, int machineCodeSize);

#endif // CPU_ASSEMBLER_H
