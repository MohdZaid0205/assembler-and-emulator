#ifndef REG_ENCODINGS
#define REG_ENCODINGS

/**
 * @struct Register
 * @brief Defines a structure to represent a processor register.
 *
 * This structure holds:
 * - A string `name`: The register's symbolic name (e.g., "x0", "sp").
 * - An integer `address`: The binary encoding of the register address.
 */
typedef struct {
    const char* name;   // Symbolic name of the register (e.g., "x0")
    const int address;  // 5-bit binary address of the register
} Register;

// An array of Register structs representing the 32 general-purpose registers.
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

/**
 * @brief Retrieves the binary address of a given register name.
 *
 * This function searches for the specified register name in both the
 * standard register encodings (`Encodings`) and ABI-defined register names (`ABI_names`).
 * If found, the corresponding 5-bit binary address is returned.
 *
 * @param name The name of the register to search for, e.g., "x0", "sp", "t1".
 * @return The 5-bit binary address of the register if found; otherwise, -1 to indicate an error.
 */
const int register_address(const char* name);

#endif