#include "encodings.h"

Register Encodings[] = {
    {"x0",  0b00000}, {"x1",  0b00001}, {"x2",  0b00010}, {"x3",  0b00011},
    {"x4",  0b00100}, {"x5",  0b00101}, {"x6",  0b00110}, {"x7",  0b00111},
    {"x8",  0b01000}, {"x9",  0b01001}, {"x10", 0b01010}, {"x11", 0b01011},
    {"x12", 0b01100}, {"x13", 0b01101}, {"x14", 0b01110}, {"x15", 0b01111},
    {"x16", 0b10000}, {"x17", 0b10001}, {"x18", 0b10010}, {"x19", 0b10011},
    {"x20", 0b10100}, {"x21", 0b10101}, {"x22", 0b10110}, {"x23", 0b10111},
    {"x24", 0b11000}, {"x25", 0b11001}, {"x26", 0b11010}, {"x27", 0b11011},
    {"x28", 0b11100}, {"x29", 0b11101}, {"x30", 0b11110}, {"x31", 0b11111},
};

Register ABI_names[] = {
    {"zero", 0b00000},  // Hard-wired zero
    {"ra", 0b00001},    // Return address
    {"sp", 0b00010},    // Stack pointer
    {"gp", 0b00011},    // Global pointer
    {"tp", 0b00100},    // Thread pointer
    {"t0", 0b00101},    // Temporary register
    {"t1", 0b00110},    // Temporary register
    {"t2", 0b00111},    // Temporary register
    {"s0", 0b01000},    // Saved register / frame pointer
    {"fp", 0b01000},    // Frame pointer (alias of s0)
    {"s1", 0b01001},    // Saved register
    {"a0", 0b01010},    // Function argument / return value
    {"a1", 0b01011},    // Function argument / return value
    {"a2", 0b01100},    // Function argument
    {"a3", 0b01101},    // Function argument
    {"a4", 0b01110},    // Function argument
    {"a5", 0b01111},    // Function argument
    {"a6", 0b10000},    // Function argument
    {"a7", 0b10001},    // Function argument
    {"s2", 0b10010},    // Saved register
    {"s3", 0b10011},    // Saved register
    {"s4", 0b10100},    // Saved register
    {"s5", 0b10101},    // Saved register
    {"s6", 0b10110},    // Saved register
    {"s7", 0b10111},    // Saved register
    {"s8", 0b11000},    // Saved register
    {"s9", 0b11001},    // Saved register
    {"s10",0b11010},    // Saved register
    {"s11",0b11011},    // Saved register
    {"t3", 0b11100},    // Temporary register
    {"t4", 0b11101},    // Temporary register
    {"t5", 0b11110},    // Temporary register
    {"t6", 0b11111}     // Temporary register
};

Instruction Instructions[] = {

    // Defined all R-Type instructions.
    {"add", "R", 0b0000000, 0b000, 0b0110011},
    {"sub", "R", 0b0100000, 0b000, 0b0110011},
    {"slt", "R", 0b0000000, 0b010, 0b0110011},
    {"srl", "R", 0b0000000, 0b101, 0b0110011},
    {"or" , "R", 0b0000000, 0b110, 0b0110011},
    {"and", "R", 0b0000000, 0b111, 0b0110011},

    // Defined all I-Type instructions and set their funct7 as -1 (NONE).
    {"lw"  , "I", NONE, 0b010, 0b0000011},
    {"addi", "I", NONE, 0b000, 0b0010011},
    {"jalr", "I", NONE, 0b000, 0b1100111},

    // Defined all S-Type instructions.
    {"sw", "S", NONE, 0b010, 0b0100011},

    // Defined all B-Type instructions.
    {"beq", "B", NONE, 0b000, 0b1100011},
    {"bne", "B", NONE, 0b001, 0b1100011},
    {"blt", "B", NONE, 0b100, 0b1100011},

    // Defined all J-Type instructions and set funct3 as NONE.
    {"jal", "J", NONE, NONE, 0b1101111},

    // TODO: impliment bonus part.  
};

const int register_encoding(const char* name){
    for (int i = 0; i < 32; i++){
        if (strcmp(Encodings[i].name, name)==0){ return Encodings[i].address; }
        if (strcmp(ABI_names[i].name, name)==0){ return ABI_names[i].address; }
    }
    return NONE;
}

Instruction instruction_encoding(const char* name){
    for (int i = 0; i < sizeof(Instructions)/sizeof(Instruction); i++){
        if (strcmp(Instructions[i].name, name) == 0){ return Instructions[i]; }
    }
    return (Instruction){"NONE", "N", NONE, NONE, NONE};
}

bool is_valid_register(const char* _reg){
    if (register_encoding(_reg) == NONE){ return false; }
    return true;
}

bool is_valid_instruction(const char* _ins){
    if (strcmp(instruction_encoding(_ins).name, "NONE") == 0){ return false; }
    return true;
}