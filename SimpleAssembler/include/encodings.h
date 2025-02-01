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
// Defined in encodings.c
extern Register Encodings[];
extern Register ABI_names[];

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