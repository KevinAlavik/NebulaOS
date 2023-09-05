#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h" 
#include "utils.h"

void handleWriteMemory(Memory *mem, const char *address_str, const char *data_str) {
    uint16_t address = strtol(address_str, NULL, 16);
    uint8_t data = strtol(data_str, NULL, 16);
    writeByte(mem, address, data);
    printf("Wrote 0x%02X to address 0x%04X\n", data, address);
}

void handleHelp(Shell *shell) {
    printf("Available commands:\n");
    printf("help - Display this help message\n");
    printf("echo [message] - Print a message to the console\n");
    printf("exit - Exit the shell\n");
    printf("wm [address] [data] - Write data to a memory address\n");
    printf("sm [address] - Read and print data from a memory address\n");
    printf("dm [startAddress] [endAddress]- Read and print data from a start address to end address\n");
    printf("fm [value] - Search for exact value in memory\n");
}

void handleEcho(Shell *shell, const char *message) {
    printf("%s\n", message);
}

void handleReadMemory(Memory *mem, const char *address_str) {
    uint16_t address = strtol(address_str, NULL, 16);
    uint8_t data = readByte(mem, address);
    printf("Read 0x%02X from address 0x%04X\n", data, address);
}

void handleDumpMemory(Memory *mem, const char *start_address_str, const char *end_address_str) {
    uint16_t start_address = strtol(start_address_str, NULL, 16);
    uint16_t end_address = strtol(end_address_str, NULL, 16);

    if (start_address <= end_address) {
        for (uint16_t address = start_address; address <= end_address; address++) {
            uint8_t data = readByte(mem, address);
            printf("Address 0x%04X: 0x%02X\n", address, data);
        }
    } else {
        printf("Invalid address range: start address must be less than or equal to end address.\n");
    }
}

void handleFindMemory(Memory *mem, const char *value_str) {
    uint8_t search_value = strtol(value_str, NULL, 16);
    uint16_t total_addresses = MAX_MEMORY_SIZE;
    uint16_t count = 0;

    for (uint16_t address = 0; address < total_addresses; address++) {
        uint8_t data = readByte(mem, address);
        if (data == search_value) {
            count++;
        }
    }

    printf("Searched for 0x%02X:\n", search_value);
    printf("Addresses with 0x%02X: %u\n", search_value, count);
    printf("Addresses with other: %u\n", total_addresses - count);
}


void handleCommand(Shell *shell, Memory *mem, const char *command) {
    char commandCopy[256];
    strcpy(commandCopy, command);

    char *token = strtok(commandCopy, " ");

    if (token != NULL) {
        if (strcmp(token, "help") == 0) {
            handleHelp(shell);
        } else if (strcmp(token, "clear") == 0) {
            clear_screen();
        } else if (strcmp(token, "dm") == 0) {
            char *start_address = strtok(NULL, " ");
            char *end_address = strtok(NULL, " ");
            if (start_address != NULL && end_address != NULL) {
                handleDumpMemory(mem, start_address, end_address);
            } else {
                printf("Usage: dm [start_address] [end_address]\n");
            }
        } else if (strcmp(token, "echo") == 0) {
            char *message = strtok(NULL, "");
            if (message != NULL) {
                handleEcho(shell, message);
            } else {
                printf("Usage: echo [message]\n");
            }
        } else if (strcmp(token, "wm") == 0) {
            char *address_str = strtok(NULL, " ");
            char *data_str = strtok(NULL, " ");
            if (address_str != NULL && data_str != NULL) {
                handleWriteMemory(mem, address_str, data_str);
            } else {
                printf("Usage: wm [address] [data]\n");
            }
        } else if (strcmp(token, "sm") == 0) { 
            char *address_str = strtok(NULL, " ");
            if (address_str != NULL) {
                handleReadMemory(mem, address_str);
            } else {
                printf("Usage: sm [address]\n");
            }
        }  else if (strcmp(token, "fm") == 0) { 
            char *search_value_str = strtok(NULL, " ");
            if (search_value_str != NULL) {
                handleFindMemory(mem, search_value_str);
            } else {
                printf("Usage: fm [value]\n");
            }
        } else if (strcmp(token, "exit") == 0) {
            printf("Exiting shell.\n");
            exit(0);
        } else {
            printf("Unknown command: %s\n", token);
        }
    }
}
