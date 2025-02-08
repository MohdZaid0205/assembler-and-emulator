section .text
    global mergeREncoding

mergeREncoding:
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
ret                 ; return the encoded instruction from EAX



section .note.GNU-stack