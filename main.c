#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint16_t memory[UINT16_MAX];

enum {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

uint16_t registers[R_COUNT];

//create the instruction set here

enum {
    OP_BR = 0,
    OP_ADD,
    OP_LD,
    OP_ST,
    OP_JSR,
    OP_AND,
    OP_LDR,
    OP_STR,
    OP_RTI,
    OP_NOT,
    OP_LDI,
    OP_STI,
    OP_JMP,
    OP_RES,
    OP_LEA,
    OP_TRAP
};

enum {
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
};

uint16_t sign_extend(uint16_t x, int bit_count) {
    if( x >> (bit_count - 1) & 1) {
        x |= (0xFFF << bit_count);
    }
    return x;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("lc3 [image-file] ...\n");
        exit(2);
    }

    for(int i = 1; i<argc; i++) {
        if(!read_image(argv[i])) {
            printf("Failed to load image %s\n", argv[i]);
            exit(1);
        }
    }

    enum { PC_START = 0x3000 };
    registers[R_PC] = PC_START;

    int running = 1;
    while(running) {
        uint16_t instr = mem_read(registers[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_ADD:
                printf("Addition\n");
                break;
            case OP_AND:
                printf("And\n");
                break;
            default:
                printf("\n");
                break;
        }
    }
    return 0;
}
