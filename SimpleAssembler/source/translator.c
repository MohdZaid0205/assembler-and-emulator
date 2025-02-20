#include "translator.h"
#include "encodings.h"

#ifdef _WIN32
    // Function to merge R-Type encoding
    BYTECODE mergeREncoding(BYTE f7, BYTE rs2, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode) {
        return ((f7 & 0x7F) << 25) |
            ((rs2 & 0x1F) << 20) |
            ((rs1 & 0x1F) << 15) |
            ((f3 & 0x07) << 12) |
            ((rd & 0x1F) << 7) |
            (opcode & 0x7F);
    }

    // Function to merge I-Type encoding
    BYTECODE mergeIEncoding(int imm, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode) {
        return ((imm & 0xFFF) << 20) |
            ((rs1 & 0x1F) << 15) |
            ((f3 & 0x07) << 12) |
            ((rd & 0x1F) << 7) |
            (opcode & 0x7F);
    }

    // Function to merge S-Type encoding
    BYTECODE mergeSEncoding(int imm, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode) {
        BYTE imm_upper = (imm >> 5) & 0x7F;
        BYTE imm_lower = imm & 0x1F;

        return ((imm_upper & 0x7F) << 25) |
            ((rs2 & 0x1F) << 20) |
            ((rs1 & 0x1F) << 15) |
            ((f3 & 0x07) << 12) |
            ((imm_lower & 0x1F) << 7) |
            (opcode & 0x7F);
    }

    // Function to merge B-Type encoding
    BYTECODE mergeBEncoding(int imm, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode) {
        BYTE imm_12 = (imm >> 12) & 0x1;
        BYTE imm_10_5 = (imm >> 5) & 0x3F;
        BYTE imm_4_1 = (imm >> 1) & 0xF;
        BYTE imm_11 = (imm >> 11) & 0x1;

        return ((imm_12 & 0x1) << 31) |
            ((imm_10_5 & 0x3F) << 25) |
            ((rs2 & 0x1F) << 20) |
            ((rs1 & 0x1F) << 15) |
            ((f3 & 0x07) << 12) |
            ((imm_4_1 & 0xF) << 8) |
            ((imm_11 & 0x1) << 7) |
            (opcode & 0x7F);
    }

    // Function to merge J-Type encoding
    BYTECODE mergeJEncoding(int imm, BYTE rd, BYTE opcode) {
        BYTE imm_20 = (imm >> 20) & 0x1;
        BYTE imm_10_1 = (imm >> 1) & 0x3FF;
        BYTE imm_11 = (imm >> 11) & 0x1;
        BYTE imm_19_12 = (imm >> 12) & 0xFF;

        return ((imm_20 & 0x1) << 31) |
            ((imm_10_1 & 0x3FF) << 21) |
            ((imm_11 & 0x1) << 20) |
            ((imm_19_12 & 0xFF) << 12) |
            ((rd & 0x1F) << 7) |
            (opcode & 0x7F);
    }
#else
    extern BYTECODE asm_mergeREncoding(BYTE f7, BYTE rs2, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);
    extern BYTECODE asm_mergeIEncoding(int immidiate, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);
    extern BYTECODE asm_mergeSEncoding(int immidiate, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode);
    extern BYTECODE asm_mergeBEncoding(int immidiate, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode);
    extern BYTECODE asm_mergeJEncoding(int immidiate, BYTE rd, BYTE opcode);

    #define mergeREncoding asm_mergeREncoding
    #define mergeIEncoding asm_mergeIEncoding
    #define mergeSEncoding asm_mergeSEncoding
    #define mergeBEncoding asm_mergeBEncoding
    #define mergeJEncoding asm_mergeJEncoding
#endif // _WIN32


BYTECODE translateRType(const char* instruction, const char* rs1, const char* rs2, const char* rd ){
    Instruction encodedINS = instruction_encoding(instruction);
    BYTE encodedRS1 = register_encoding(rs1);
    BYTE encodedRS2 = register_encoding(rs2);
    BYTE encodedRD_ = register_encoding(rd );
    return mergeREncoding(encodedINS.funct7, encodedRS2, encodedRS1, encodedINS.funct3, encodedRD_, encodedINS.opcode);
}

BYTECODE translateIType(const char* instruction, const char* rs1, const char* imm, const char* rd ){
    Instruction encodingINS = instruction_encoding(instruction);
    BYTE encodedRS1 = register_encoding(rs1);
    BYTE encodedRD_ = register_encoding(rd );
    int encodedIMM = immediate_encoding(imm);
    return mergeIEncoding(encodedIMM, encodedRS1, encodingINS.funct3, encodedRD_, encodingINS.opcode);
}

BYTECODE translateSType(const char* instruction, const char* rs1, const char* rs2, const char* imm){
    Instruction encodedINS = instruction_encoding(instruction);
    BYTE encodedRS1 = register_encoding(rs1);
    BYTE encodedRS2 = register_encoding(rs2);
    int encodedIMM = immediate_encoding(imm);
    return mergeSEncoding(encodedIMM, encodedRS2, encodedRS1, encodedINS.funct3, encodedINS.opcode);
}

BYTECODE translateBType(const char* instruction, const char* rs1, const char* rs2, const char* imm){
    Instruction encodedINS = instruction_encoding(instruction);
    BYTE encodedRS1 = register_encoding(rs1);
    BYTE encodedRS2 = register_encoding(rs2);
    int encodedIMM = immediate_encoding(imm);
    return mergeBEncoding(encodedIMM, encodedRS2, encodedRS1, encodedINS.funct3, encodedINS.opcode);
}

BYTECODE translateJType(const char* instruction, const char* imm, const char* rd ){
    Instruction encodedINS = instruction_encoding(instruction);
    BYTE encodedRD_ = register_encoding(rd );
    int encodedIMM = immediate_encoding(imm);
    return mergeJEncoding(encodedIMM, encodedRD_, encodedINS.opcode);
}