#include "shell.h"
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "cpu.h"
#include "memory.h"

void initializeShell(Shell *shell) {

}

void runShell(Shell *shell, CPU* cpu, Memory* memory) {
    char input[256];
    
    while (1) {
        printf("nos> ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            
            if (strcmp(input, "exit") == 0) {
                printf("Exiting shell.\n");
                break;
            }
            
            handleCommand(&shell, &memory, input);
        }
    }
}
