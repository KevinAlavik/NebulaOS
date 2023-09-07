#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>

int compileAssemblyFile(const char* filename, uint8_t* machineCode, int machineCodeSize);

#endif // COMPILER_H
