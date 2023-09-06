#include "shell.h"
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "cpu.h"
#include "memory.h"
#include "fs.h"

#define PROMPT "nsh> "

void initializeShell(Shell *shell) {

}

void runShell(Shell *shell, CPU* cpu, FileSystem* fs, Memory* memory) {
    char input[256];
    
    handleCommand(&shell, &memory, &fs, "hello", &cpu);
    while (1) {
        printf(PROMPT);
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            
            if (strcmp(input, "exit") == 0) {
                printf("Exiting shell.\n");
                break;
            }
            
            handleCommand(&shell, &memory, &fs, input, &cpu);
        }
    }
}
