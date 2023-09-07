#include "compiler.h"
#include "assembler.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 8192

int compileAssemblyFile(const char* filename, uint8_t* machineCode, int machineCodeSize) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return -1;
    }

    char assemblyCode[MAX_FILE_SIZE];
    int bytesRead = fread(assemblyCode, 1, MAX_FILE_SIZE, file);
    fclose(file);

    if (bytesRead <= 0) {
        printf("Error: Unable to read file %s\n", filename);
        return -1;
    }

    int assembledSize = assembleProgram(assemblyCode, machineCode, machineCodeSize);

    if (assembledSize < 0) {
        printf("Error: Assembly failed for file %s\n", filename);
        return -1;
    }

    return assembledSize;
}
