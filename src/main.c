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

    createFile(&fs, "root", "example.txt");
    writeFile(&fs, "root", "example.txt", "Hello, World!");

    initializeCPU(&cpu, &mem);
    initializeShell(&shell);
    initializeFileSystem(&fs);
    initializeMemory(&mem);

    clear_screen();
    
    runShell(&shell, &cpu, &fs, &mem);

    return 0;
}
