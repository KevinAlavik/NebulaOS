#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MAX_MEMORY_SIZE 65536
#define MAX_ROM_SIZE 16384

typedef struct {
    uint8_t memory[MAX_MEMORY_SIZE];
} Memory;

void initializeMemory(Memory *mem);
uint8_t readByte(Memory *mem, uint16_t address);
void writeByte(Memory *mem, uint16_t address, uint8_t data);
uint16_t readWord(Memory *mem, uint16_t address);
void writeWord(Memory *mem, uint16_t address, uint16_t data);
uint16_t getFreeMemory(Memory *mem);

#endif /* MEMORY_H */
