#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "configs.h"
#include "pch.h"

/**
 * @brief Translates an R-type instruction to its binary representation.
 *
 * R-type instructions typically include three registers and an operation code.
 * This function takes the instruction name and associated registers, then encodes
 * them into a bytecode representation.
 *
 * @param instruction The symbolic name of the instruction (e.g., "ADD", "SUB").
 * @param rs1 The name of the first source register.
 * @param rs2 The name of the second source register.
 * @param rd The name of the destination register.
 * @return BYTECODE The binary-encoded bytecode of the R-type instruction.
 */
BYTECODE translateRType(const char* instruction, const char* rs1, const char* rs2, const char* rd );

/**
 * @brief Translates an I-type instruction to its binary representation.
 *
 * I-type instructions often use a single source register and an immediate value.
 * This function encodes the instruction along with the register and immediate value.
 *
 * @param instruction The symbolic name of the instruction (e.g., "ADDI", "LW").
 * @param rs1 The name of the source register.
 * @param imm The immediate value as a string.
 * @param rd The name of the destination register.
 * @return BYTECODE The binary-encoded bytecode of the I-type instruction.
 */
BYTECODE translateIType(const char* instruction, const char* rs1, const char* imm, const char* rd );

/**
 * @brief Translates an S-type instruction to its binary representation.
 *
 * S-type instructions are typically used for memory storage operations.
 * This function encodes the given instruction, registers, and immediate value.
 *
 * @param instruction The symbolic name of the instruction (e.g., "SW").
 * @param rs1 The name of the base address register.
 * @param rs2 The name of the source register to store.
 * @param imm The immediate value as a string.
 * @return BYTECODE The binary-encoded bytecode of the S-type instruction.
 */
BYTECODE translateSType(const char* instruction, const char* rs1, const char* rs2, const char* imm);

/**
 * @brief Translates a B-type instruction to its binary representation.
 *
 * B-type instructions are typically used for conditional branching.
 * This function encodes the given instruction, registers, and branch offset.
 *
 * @param instruction The symbolic name of the instruction (e.g., "BEQ", "BNE").
 * @param rs1 The name of the first register to compare.
 * @param rs2 The name of the second register to compare.
 * @param imm The immediate branch offset as a string.
 * @return BYTECODE The binary-encoded bytecode of the B-type instruction.
 */
BYTECODE translateBType(const char* instruction, const char* rs1, const char* rs2, int imm);

/**
 * @brief Translates a J-type instruction to its binary representation.
 *
 * J-type instructions are typically used for unconditional jumps.
 * This function encodes the instruction, destination register, and jump offset.
 *
 * @param instruction The symbolic name of the instruction (e.g., "JAL").
 * @param imm The immediate jump offset as a string.
 * @param rd The name of the destination register.
 * @return BYTECODE The binary-encoded bytecode of the J-type instruction.
 */
BYTECODE translateJType(const char* instruction, int imm, const char* rd );


#endif