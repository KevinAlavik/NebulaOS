#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>
#include <stdio.h>

int assemble(const char* assemblyCode, uint8_t* machineCode, size_t* machineCodeSize);

#endif
