#include "translator.h"
#include "encodings.h"

extern BYTECODE mergeREncoding(BYTE f7, BYTE rs2, BYTE rs1, BYTE f3, BYTE rd, BYTE opcode);

BYTECODE translateRType(const char* instruction, const char* rs1, const char* rs2, const char* rd ){
    Instruction encodedINS = instruction_encoding(instruction);
    BYTE encodedRS1 = register_encoding(rs1);
    BYTE encodedRS2 = register_encoding(rs2);
    BYTE encodedRD_ = register_encoding(rd );
    return mergeREncoding(encodedINS.funct7, encodedRS2, encodedRS1, encodedINS.funct3, encodedRD_, encodedINS.opcode);
}
