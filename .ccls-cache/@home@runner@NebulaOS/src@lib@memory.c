#include "memory.h"

void initializeMemory(Memory *mem) {
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        mem->memory[i] = 0;  // Initialize all memory bytes to 0
    }
}

uint8_t readByte(Memory *mem, uint16_t address) {
    if (address < MAX_MEMORY_SIZE) {
        return mem->memory[address];
    } else {
        return 0;
    }
}

void writeByte(Memory *mem, uint16_t address, uint8_t data) {
    if (address < MAX_MEMORY_SIZE) {
        mem->memory[address] = data;
    }
}

uint16_t readWord(Memory *mem, uint16_t address) {
    uint16_t lowByte = readByte(mem, address);
    uint16_t highByte = readByte(mem, address + 1);
    return (highByte << 8) | lowByte;
}

void writeWord(Memory *mem, uint16_t address, uint16_t data) {
    writeByte(mem, address, data & 0xFF);
    writeByte(mem, address + 1, (data >> 8) & 0xFF);
}

uint16_t getFreeMemory(Memory *mem) {
    uint16_t freeBytes = 0;
    
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        if (mem->memory[i] == 0) {
            freeBytes++;
        }
    }
    
    return freeBytes;
}
