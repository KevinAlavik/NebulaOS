#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "lib/cpu.h"
#include "lib/memory.h"
#include "lib/utils.h"
#include "lib/assembler.h"

int createDirectory(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        if (mkdir(path, 0755) != 0) {
            printf("Failed to create directory: %s\n", path);
            return 1;
        }
    }
    return 0;
}

int writeBinaryFile(const char* fileName, const void* data, size_t size) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", fileName);
        return 1;
    }

    if (fwrite(data, 1, size, file) != size) {
        printf("Failed to write to file: %s\n", fileName);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int compileAndLoadAssembly(const char* assemblyCode, CPU* cpu, Memory* mem) {
    if (assemblyCode == NULL || cpu == NULL || mem == NULL) {
        return 1;
    }

    uint8_t machineCode[MAX_ROM_SIZE];
    size_t machineCodeSize = sizeof(machineCode);
    int result = assemble(assemblyCode, machineCode, &machineCodeSize);

    if (result != 0) {
        printf("Assembly failed with error code %d\n", result);
        return 1;
    }

    char outputDirectory[256];
    snprintf(outputDirectory, sizeof(outputDirectory), "src/roms");
    if (createDirectory(outputDirectory) != 0) {
        return 1;
    }

    char outputFileName[256];
    snprintf(outputFileName, sizeof(outputFileName), "%s/boot.nbb", outputDirectory);

    if (writeBinaryFile(outputFileName, machineCode, machineCodeSize) != 0) {
        return 1;
    }

    printf("Loading program into ROM (%s bytes)", machineCodeSize);
    loadROM(cpu, machineCode, machineCodeSize);
    printf("done.\n");

    return 0;
}

int main() {
    CPU cpu;
    Memory mem;

    initializeCPU(&cpu, &mem);
    initializeMemory(&mem);

    clear_screen();

    printf("*** Nebula Boot Manager (NBM) ***\n");

    // Define your assembly code as a single line
    const char* assemblyCode = "MOV R0, 0x01; ADD R0, R0, 0x01; HLT";

    if (compileAndLoadAssembly(assemblyCode, &cpu, &mem) != 0) {
        return 1;
    }

    printf("Program Content in ROM:\n");
    for (size_t i = 0; i < MAX_ROM_SIZE; i++) {
        printf("%02X ", cpu.ROM[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    runCPULoop(&cpu, &mem);

    printf("Result Address: 0x%X\n", cpu.R[2]);
    printf("Result Value: %d\n", cpu.R[2]);

    return 0;
}
