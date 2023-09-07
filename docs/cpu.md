## Overview
nerdy shit about the cpu 
## Registers

### General-Purpose Registers
- R0 to R7: Used for general data manipulation and arithmetic operations.
- R8 to R15: These 16-bit registers offer more storage capacity for data processing tasks.

### Special-Purpose Registers
- Program Counter (PC): Keeps track of the address of the next instruction to execute.
- Stack Pointer (SP): Points to the top of the stack, crucial for function calls and local variable storage.
- Flags Register (FLAGS): Contains status flags indicating the result of arithmetic operations (e.g., zero, carry, overflow).
- Instruction Pointer (IR): Holds the current instruction being executed.
- Memory Management Unit (MMU) Registers: Used for memory address translation and access permissions.

### Floating-Point Registers (FPRs)
- F0 to F7: These registers are dedicated to floating-point arithmetic, allowing efficient processing of real numbers.

### Vector Registers (SIMD)
- V0 to V7: These registers support Single Instruction, Multiple Data (SIMD) operations, useful for parallel data processing tasks.

### Debug Registers
- Breakpoint Register(s): Used to set breakpoints in code for debugging.
- Watchpoint Register(s): Monitors specific memory locations or conditions for debugging purposes.
- Trace Register(s): Helps trace the execution of code for debugging and analysis.

## Memory

## Memory

### ROM (Read-Only Memory)
- Address Range: [0xE000 - 0xFFFF]
- Size: 16K (16384 bytes)
- Purpose: Store machine code and firmware.

### RAM (Random Access Memory)
- Address Range: [0x0000 - 0xDFFF]
- Size: 64K (65536 bytes) 
- Purpose: Used for data storage and manipulation during program execution.


## Features

It’s very simple
## Notes and Comments

N65536 is a very bad and simple CPU wouldn’t use in a real life situation.

## Developers
some info for developers
## Struct
```c
typedef struct {
    uint16_t R[16];
    uint16_t PC;
    uint16_t SP;
    uint16_t FLAGS;
    uint16_t IR;
    uint16_t MMU[4];
    float F[8];
    __m128i V[8];
    uint16_t BP[4];
    uint16_t WP[4];
    uint16_t TR[4];
    uint8_t ROM[0x2000];
    uint8_t RAM[0xDE00];
} N65536;
```
