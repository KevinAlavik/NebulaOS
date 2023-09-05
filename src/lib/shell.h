#ifndef SHELL_H
#define SHELL_H
#include "cpu.h"
#include "memory.h"
typedef struct {
    
} Shell;

void initializeShell(Shell *shell);
void runShell(Shell *shell, CPU* cpu, Memory* memory);

#endif /* SHELL_H */
