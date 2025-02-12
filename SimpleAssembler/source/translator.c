#include "translator.h"
#include "encodings.h"

extern BYTECODE mergeREncoding(BYTE f7, BYTE rs2, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);
extern BYTECODE mergeIEncoding(BYTECODE immidiate, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);

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