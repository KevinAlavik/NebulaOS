#ifndef COMMANDS_H
#define COMMANDS_H

#include "shell.h"
#include "memory.h"
#include "fs.h"

// Function to handle user commands
void handleCommand(Shell *shell, Memory *mem, FileSystem* fs, const char *command);
void handleLaunch(Memory *mem);

#endif /* COMMANDS_H */
