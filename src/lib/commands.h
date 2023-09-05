#ifndef COMMANDS_H
#define COMMANDS_H

#include "shell.h"
#include "memory.h"

// Function to handle user commands
void handleCommand(Shell *shell, Memory *mem, const char *command);

#endif /* COMMANDS_H */
