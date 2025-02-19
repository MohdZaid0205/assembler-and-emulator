section .text
    global asm_mergeREncoding
    global asm_mergeIEncoding
    global asm_mergeSEncoding
    global asm_mergeBEncoding
    global asm_mergeJEncoding

asm_mergeREncoding:
    mov eax, r9d    ; Load the [opcode] parameter (r9d) into the EAX register

    mov ebx, r8d    ; Load [rd] (r8d) into EBX
    shl ebx, 0x07   ; shift it left by 7 bits
    add eax, ebx    ; and add to EAX

    mov ebx, ecx    ; Load [f3] (ecx) into EBX
    shl ebx, 0x0c   ; shift it left by 12 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edx    ; Load [rs1] (edx) into EBX
    shl ebx, 0x0f   ; shift it left by 15 bit
    add eax, ebx    ; and add to EAX

    mov ebx, esi    ; Load [rs2] (esi) into EBX
    shl ebx, 0x14   ; shift it left by 20 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edi    ; Load [f7] (edi) into EBX
    shl ebx, 0x19   ; shift it left by 25 bit
    add eax, ebx    ; and add to EAX
ret

asm_mergeIEncoding:
    mov eax, r8d    ; Load the [opcode] parameter (r8d) into the EAX register

    mov ebx, ecx    ; Load [rd] (ecx) into EBX
    shl ebx, 0x07   ; shift it left by 7 bits
    add eax, ebx    ; and add to EAX

    mov ebx, edx    ; Load [f3] (eedx) into EBX
    shl ebx, 0x0c   ; shift it left by 12 bit
    add eax, ebx    ; and add to EAX

    mov ebx, esi    ; Load [rs1] (esi) into EBX
    shl ebx, 0x0f   ; shift it left by 15 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edi    ; Load Imm[11:0] into edi
    shl ebx, 0x14   ; shift left by 20 bits
    add eax, ebx    ; add 12 bits imm to EAX
ret

asm_mergeSEncoding:
    mov eax, r8d    ; Load the [opcode] parameter (r8d) into the EAX register

    mov ebx, edi    ; Load imm[4:0] into EBX
    shl ebx, 0x1b   ; shift to truncate [11:5]
    shr ebx, 0x14   ; shift to insertion position
    shr edi, 0x05   ; truncate imm[4:0] from imm
    add eax, ebx    ; and add to EAX

    mov ebx, ecx    ; Load [f3] (ecx) into EBX
    shl ebx, 0x0c   ; shift it left by 12 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edx    ; Load [rs1] (edx) into EBX
    shl ebx, 0x0f   ; shift it left by 15 bit
    add eax, ebx    ; and add to EAX

    mov ebx, esi    ; Load [rs2] (esi) into EBX
    shl ebx, 0x14   ; shift it left by 20 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edi    ; Load imm[11:5] (edi) into EBX
    shl ebx, 0x19   ; shift it left by 25 bit
    add eax, ebx    ; and add to EAX
ret

asm_mergeBEncoding:
    sar edi, 0x01
    mov eax, r8d    ; Load the [opcode] parameter (r8d) into the EAX register

    mov ebx, edi    ; Load imm[3:0] into EBX
    shl ebx, 0x1c   ; shift to truncate excessive part
    shr ebx, 0x14   ; shift to truncate excessive part
    shr edi, 0x04   ; truncate imm[3:0] from imm
    add eax, ebx    ; and add to EAX

    mov ebx, ecx    ; Load [f3] (ecx) into EBX
    shl ebx, 0x0c   ; shift it left by 12 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edx    ; Load [rs1] (edx) into EBX
    shl ebx, 0x0f   ; shift it left by 15 bit
    add eax, ebx    ; and add to EAX

    mov ebx, esi    ; Load [rs2] (esi) into EBX
    shl ebx, 0x14   ; shift it left by 20 bit
    add eax, ebx    ; and add to EAX

    mov ebx, edi    ; Load imm[11:5] (edi) into EBX
    shl ebx, 0x1a   ; truncate imm[12:11]
    shr ebx, 0x01
    shr edi, 0x06   ; truncate imm[9:4] from imm
    add eax, ebx    ; and add to EAX

    mov ebx, edi    ; move imm[11:10] (edi) to ebx
    shl ebx, 0x1f   ; truncate imm[12]
    shr ebx, 0x18   ; position imm[11]
    shr edi, 0x01   ; truncate imm[11] (edi)
    add eax, ebx    ; and add to EAX

    mov ebx, edi    
    shl ebx, 0x1f
    add eax, ebx
ret

asm_mergeJEncoding:
    sar edi, 0x01
    mov eax, edx    ; Load opcode into [EAX]
    
    mov ebx, esi    ; Load rd to [RBX]
    shl ebx, 0x07   ; shift left by 0x07
    add eax, ebx    ; add rd at [11:7]

    mov ebx, edi    ; Load imm into [RBX]
    shl ebx, 0x16   ; truncate all except imm[10:1]
    shr ebx, 0x01   ; posion it to isa requirement
    shr edi, 0x0a   ; truncate imm[10:1]
    add eax, ebx    ; add to bytecode representation

    mov ebx, edi    ; pre-truncated part of edi
    shl ebx, 0x1f   ; remove all except imm[11]
    shr ebx, 0x0b   ; shift to its position
    shr edi, 0x01   ; truncate imm[11]
    add eax, ebx    ; add imm[11] to position

    mov ebx, edi    ; load pre-truncated part of edi
    shl ebx, 0x18   ; truncate imm[20]
    shr ebx, 0x0c   ; positon wrt isa
    shr edi, 0x08   ; truncate imm[19:12]
    add eax, ebx    ; add imm[19:12] to position

    mov ebx, edi    ; load imm[20]
    shl ebx, 0x1f   ; position wrt isa
    add eax, ebx
ret

section .note.GNU-stack