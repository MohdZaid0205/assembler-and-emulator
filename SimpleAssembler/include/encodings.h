#ifndef REG_ENCODINGS
#define REG_ENCODINGS

#define byte char
#define null -1

/**
 * @struct Register
 * @brief Defines a structure to represent a processor register.
 *
 * This structure represents a processor register, which typically consists of:
 * - `name`: A constant character pointer holding the symbolic name of the register (e.g., "x0", "sp").
 * - `address`: A 5-bit binary integer that encodes the unique address of the register.
 */
typedef struct {
    const char* name;   // Symbolic name of the register (e.g., "x0")
    const byte address; // 5-bit binary address of the register
} Register;

/**
 * @struct Instruction
 * @brief Represents an instruction in a processor's instruction set architecture.
 *
 * This structure holds information necessary to define a complete instruction:
 * - `name`: The symbolic name of the instruction (e.g., "ADD", "SUB").
 * - `type`: The symbolic name of instruction type (e.g., "R", "I").
 * - `funct7`: A 7-bit function code used to specify additional operation details.
 * - `funct3`: A 3-bit function code used for operation differentiation.
 * - `opcode`: A unique operation code representing the instruction class.
 */
typedef struct {
    const char* name;    // Symbolic name of the instruction (e.g., "ADD")
    const char* type;    // Symbolic name of instruction type (e.g., "R", "I")
    const byte funct7;   // 7-bit function code for additional operation details
    const byte funct3;   // 3-bit function code for operation differentiation
    const byte opcode;   // Operation code representing the instruction class
} Instruction;


// An array of Register structs representing the 32 general-purpose registers.
// Defined in encodings.c
extern Register Encodings[];
extern Register ABI_names[];

// An array containing all possible instructions and their corresponding feilds.
extern Instruction Instructions[];

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
const int register_encoding(const char* name);

/**
 * @brief Encodes the given instruction name into its corresponding structure.
 *
 * This function looks up an instruction by its symbolic name and returns an
 * `Instruction` structure containing the funct7, funct3, opcode, and immediate values.
 *
 * @param name The symbolic name of the instruction, e.g., "ADD", "SUB".
 * @return An `Instruction` structure if the instruction is found; otherwise, a default-initialized structure.
 */
Instruction instruction_encoding(const char* name);

#endif