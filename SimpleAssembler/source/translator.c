#include "translator.h"
#include "encodings.h"

#ifdef _WIN32
    // impliment here
#else
    extern BYTECODE mergeREncoding(BYTE f7, BYTE rs2, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);
    extern BYTECODE mergeIEncoding(int immidiate, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);
    extern BYTECODE mergeSEncoding(int immidiate, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode);
    extern BYTECODE mergeBEncoding(int immidiate, BYTE rs2, BYTE rs1, BYTE f3, BYTE opcode);
    extern BYTECODE mergeJEncoding(int immidiate, BYTE rd, BYTE opcode);
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