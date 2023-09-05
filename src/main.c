#include <stdio.h>
#include <stdlib.h>
#include "lib/cpu.h"
#include "lib/shell.h"
#include "lib/fs.h"
#include "lib/memory.h"
#include "lib/utils.h"

int main() {
    CPU cpu;
    Shell shell;
    FileSystem fs;
    Memory mem;

    initializeCPU(&cpu, &mem);
    initializeShell(&shell);
    initializeFileSystem(&fs);
    initializeMemory(&mem);

    clear_screen();

    printf("** Nebula OS Command Interface ***\n");
    printf("Booted into command interface\n");
    printf("Free ram %u\n", getFreeMemory(&mem));
    
    runShell(&shell, &cpu, &mem);

    return 0;
}
