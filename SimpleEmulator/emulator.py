from enum import Enum
from dataclasses import dataclass

PC:int = 0

class InstructionType(Enum):
    R = 0b00001
    I = 0b00010
    S = 0b00100
    B = 0b01000
    J = 0b10000

@dataclass
class Instruction:
    _type:InstructionType
    _name:str
    _opcode:int
    _func3:int
    _func7:int

@dataclass
class Register:
    _name:str
    _abi_name:str
    _address:int
    _value:int = 0

memoryList = [0 for _ in range(32)] 

instructionSet: list[Instruction] = [
    Instruction(InstructionType.R, "add", 0b0110011, 0b000, 0b0000000),
    Instruction(InstructionType.R, "sub", 0b0110011, 0b000, 0b0100000),
    Instruction(InstructionType.R, "slt", 0b0110011, 0b010, 0b0000000),
    Instruction(InstructionType.R, "srl", 0b0110011, 0b101, 0b0000000),
    Instruction(InstructionType.R, "or", 0b0110011, 0b110, 0b0000000),
    Instruction(InstructionType.R, "and", 0b0110011, 0b111, 0b0000000),
    
    Instruction(InstructionType.I, "lw", 0b0000011, 0b010, None),
    Instruction(InstructionType.I, "addi", 0b0010011, 0b000, None),
    Instruction(InstructionType.I, "jalr", 0b1100111, 0b000, None),
    
    Instruction(InstructionType.S, "sw", 0b0100011, 0b010, None),
    
    Instruction(InstructionType.B, "beq", 0b1100011, 0b000, None),
    Instruction(InstructionType.B, "bne", 0b1100011, 0b001, None),
    Instruction(InstructionType.B, "blt", 0b1100011, 0b100, None),
    
    Instruction(InstructionType.J, "jal", 0b1101111, None, None),
]

registerSets: list[Register] = [
    Register("x0" , "zero", 0b00000),
    Register("x1" , "ra", 0b00001),
    Register("x2" , "sp", 0b00010),
    Register("x3" , "gp", 0b00011),
    Register("x4" , "tp", 0b00100),
    Register("x5" , "t0", 0b00101),
    Register("x6" , "t1", 0b00110),
    Register("x7" , "t2", 0b00111),
    Register("x8" , "s0", 0b01000),
    Register("x9" , "s1", 0b01001),
    Register("x10", "a0", 0b01010),
    Register("x11", "a1", 0b01011),
    Register("x12", "a2", 0b01100),
    Register("x13", "a3", 0b01101),
    Register("x14", "a4", 0b01110),
    Register("x15", "a5", 0b01111),
    Register("x16", "a6", 0b10000),
    Register("x17", "a7", 0b10001),
    Register("x18", "s2", 0b10010),
    Register("x19", "s3", 0b10011),
    Register("x20", "s4", 0b10100),
    Register("x21", "s5", 0b10101),
    Register("x22", "s6", 0b10110),
    Register("x23", "s7", 0b10111),
    Register("x24", "s8", 0b11000),
    Register("x25", "s9", 0b11001),
    Register("x26", "s10", 0b11010),
    Register("x27", "s11", 0b11011),
    Register("x28", "t3", 0b11100),
    Register("x29", "t4", 0b11101),
    Register("x30", "t5", 0b11110),
    Register("x31", "t6", 0b11111),
]

class Executable:
    _value:int
    _isValid:bool
    _immediate:int
    _instruction:Instruction
    _registers:list[Register]
    
    def __init__(self, value:int):
        self._value = value
        for inst in instructionSet:
            opc:bool = (0b1111111 & self._value) == inst._opcode
            if inst._func3 != None:
                fc3:bool = (0b111 << 12 & self._value) == inst._func3 << 12
            else:
                fc3:bool = True
            if inst._func7 != None:
                fc7:bool = (0b1111111 << 25 & self._value) == inst._func7 << 25
            else:
                fc7:bool = True
            if opc and fc3 and fc7:
                self._instruction = inst
                self._isValid = True
                break
        else:
            self._isValid = False
            return
        self._registers = [None, None, None]
        self._immediate = None
        self.setRegisters()
        self.setImmediate()

    def getRegisters(self, p1, p2, p3):
        rs1 = (self._value >> 15) & 0b11111
        rs2 = (self._value >> 20) & 0b11111
        rd = (self._value >> 7) & 0b11111
        
        for reg in registerSets:
            if reg._address == rs1 and p1:
                self._registers[0] = reg
            if reg._address == rs2 and p2:
                self._registers[1] = reg
            if reg._address == rd and p3:
                self._registers[2] = reg

    def setImmediate(self):
        if self._instruction._type == InstructionType.I:
            self._immediate = self._value >> 20
            if self._immediate & (1 << 11):
                self._immediate -= (1 << 12)

        elif self._instruction._type == InstructionType.S:
            self._immediate = (((self._value >> 25) << 5) + ((self._value >> 7) & 0b11111)) << 1
            if self._immediate & (1 << 11):
                self._immediate -= (1 << 12)

        elif self._instruction._type == InstructionType.B:
            self._immediate = (((self._value >> 31) << 12) + (((self._value >> 7) & 0b1) << 11) + (((self._value >> 25) & 0b111111) << 5) +         (((self._value >> 8) & 0b1111) << 1))

            if self._immediate & (1 << 12):  
                self._immediate -= (1 << 13)


        elif self._instruction._type == InstructionType.J:
            self._immediate = ((self._value >> 31) & 0b1) << 20
            self._immediate |= ((self._value << 1) >> 22) << 1
            self._immediate |= ((self._value >> 20) & 0b1) << 11
            self._immediate |= ((self._value >> 12) & 0b11111111) << 12

            if self._immediate & (1 << 20):
                self._immediate -= (1 << 21)  

    def setRegisters(self):
        if (self._instruction._type == InstructionType.R):
            self.getRegisters(True, True, True)

        elif (self._instruction._type == InstructionType.I):
            self.getRegisters(True, False, True)
        
        elif (self._instruction._type == InstructionType.S):
            self.getRegisters(True, True, False)
                
        elif (self._instruction._type == InstructionType.B):
            self.getRegisters(True, True, False)

        elif (self._instruction._type == InstructionType.J):
            self.getRegisters(False, False, True)

    def __str__(self):
        return f"{self._registers=} {self._instruction=} {self._immediate=} {self._isValid=} {self._value=}"

binaries: list[Executable] = []

def readFile(fileIn:str):
    with open(fileIn, "r") as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip()
            binaries.append(Executable(int(line, 2)))
            
        for i in binaries:
            if not i._isValid:
                print(f"Invalid instruction: {bin(i._value)}")
                break

def intTo2_sCompiment(n:int, bits:int=32) -> str:
    if n < 0:
        n = (1 << bits) + n
    return bin(n)[2:].zfill(bits)

def registerWrite(fileOut:str, bases:int):
    with open(fileOut, "a") as file:
        file.write(f"{PC}")
        for register in registerSets:
            if bases == 2:
                file.write(f" 0b{intTo2_sCompiment(register._value)}")
            elif bases == 10:
                file.write(f" {int(register._value)}")
        file.write(" \n")

def memoryWrite(fileOut:str, bases:int):
    memoryAdd:int = 0x10000
    with open(fileOut, "a") as file:
        for i in memoryList:
            if bases == 2:
                file.write(f"0x000{str((hex(memoryAdd))[-5:]).upper()}:0b{intTo2_sCompiment(i)}\n")
            elif bases == 10:
                file.write(f"0x000{str((hex(memoryAdd))[-5:]).upper()}:{i}\n")
            memoryAdd += 4

def execute(fileOut:str, format=10):
    global PC
    PC = 0
    registerSets[2]._value = 380
    
    while True:
        registerSets[0]._value = 0
        in_process: Executable = binaries[PC//4]
        print(f"{PC} {in_process._instruction._name} {in_process._registers[2]._name if in_process._registers[2] != None else ''} {in_process._registers[0]._name if in_process._registers[0] != None else ''} {in_process._registers[1]._name if in_process._registers[1] != None else ''} {in_process._immediate if in_process._immediate != None else ''}" )
        # print(f"{bin(in_process._immediate if in_process._immediate != None else 0)}")
        if in_process._instruction._name == "beq" and in_process._registers[1]._abi_name == "zero" and in_process._registers[0]._abi_name == "zero" and in_process._immediate == 0:
            PC += 4
            registerWrite(fileOut, format)
            memoryWrite(fileOut, format)
            break
        if in_process._instruction._name == "add":
            in_process._registers[2]._value = in_process._registers[0]._value + in_process._registers[1]._value
        elif in_process._instruction._name == "sub":
            in_process._registers[2]._value = in_process._registers[0]._value - in_process._registers[1]._value
        elif in_process._instruction._name == "slt":
            in_process._registers[2]._value = int(in_process._registers[0]._value < in_process._registers[1]._value)
        elif in_process._instruction._name == "srl":
            in_process._registers[2]._value = int(in_process._registers[0]._value >> int(bin(in_process._registers[1]._value)[-5:], 2))
        elif in_process._instruction._name == "or":
            in_process._registers[2]._value = in_process._registers[0]._value | in_process._registers[1]._value & 0b11111
        elif in_process._instruction._name == "and":
            in_process._registers[2]._value = in_process._registers[0]._value & in_process._registers[1]._value & 0b11111
        elif in_process._instruction._name == "lw":
            print(in_process._immediate + in_process._registers[0]._value)
            in_process._registers[2]._value = memoryList[in_process._immediate + in_process._registers[0]._value]
        elif in_process._instruction._name == "addi":
            in_process._registers[2]._value = in_process._immediate + in_process._registers[0]._value
        elif in_process._instruction._name == "jalr":
            PC = in_process._registers[0]._value + in_process._immediate - 4
            in_process._registers[2]._value = PC + 4
        elif in_process._instruction._name == "sw":
            memoryList[in_process._immediate + in_process._registers[1]._value] = in_process._registers[0]._value  
        elif in_process._instruction._name == "beq":
            PC = PC + in_process._immediate - 4 if in_process._registers[0]._value == in_process._registers[1]._value else PC
        elif in_process._instruction._name == "bne":
            PC = PC + in_process._immediate - 4 if in_process._registers[0]._value != in_process._registers[1]._value else PC
        elif in_process._instruction._name == "jal":
            in_process._registers[2]._value = PC + 4
            if in_process._immediate %4 == 0:
                PC = PC + in_process._immediate - 4
            else:
                ...
        PC += 4
        registerSets[0]._value = 0
        registerWrite(fileOut, format)

if __name__ == "__main__":
    import os
    inputFolder = "C:\\Users\\mdzai\\Downloads\\final_valuation_framework_mar30_2025_students_v5\\automatedTesting\\tests\\bin\\simple"
    outputFolder = "C:\\Users\\mdzai\\Downloads\\final_valuation_framework_mar30_2025_students_v5\\automatedTesting\\tests\\user_traces\\simple"
    if not os.path.exists(outputFolder):
        os.makedirs(outputFolder)
    for file in os.listdir(inputFolder):
        if file.endswith(".txt"):
            inputFile = os.path.join(inputFolder, file)
            outputFile = os.path.join(outputFolder, file)
            with open(outputFile, "w") as f:
                f.write("")
            print(f"Reading {inputFile}")
            readFile(inputFile)
            execute(outputFile, format=10)
            # execute(outputFile, format=10)
            print(f"Output written to {outputFile}")
            for i in registerSets:
                i._value = 0
            for i in memoryList:
                i = 0
            binaries.clear()