#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "lib/cpu.h"
#include "lib/memory.h"
#include "lib/utils.h"
#include "lib/assembler.h"
#include "lib/compiler.h" // Include the compiler header

int main() {
    CPU cpu;
    Memory mem;

    initializeCPU(&cpu, &mem);
    initializeMemory(&mem);

    clear_screen();

    printf("*** Nebula Boot Manager (NBM) ***\n");

    // Specify the path to the assembly file
    const char* bootAssembly = "src/roms/boot.s";

    uint8_t machineCode[] = {
        0x03, 0x00, 0x01, 
        0x03, 0x01, 0x01, 
        0x01, 0x00, 0x01, 
        0x05             
    };

    printf("Loading program into ROM (%d bytes)\n", sizeof(machineCode));
    loadROM(&cpu, machineCode, sizeof(machineCode));
    printf("done.\n\nRunning program...\n");
    runProgram(&cpu, &mem, sizeof(machineCode));
    printf("done.\n\n");

    // Calculate and print free and used bytes of ROM
    uint16_t freeBytes = MAX_ROM_SIZE - cpu.PC;
    uint16_t usedBytes = cpu.PC;

    printf("Free bytes of ROM: %d\n", freeBytes);
    printf("Used bytes of ROM: %d\n", usedBytes);

    return 0;
}
