section .text
    global example
    global addition

example:            ;; just a refernce example function to get compiler and linker working.
    mov eax, edi    ;; move first argument to eax 
    add eax, esi    ;; add second argument to eax
    dec eax         ;; decrease resultant by one
    ret             ;; return whatever is present in eax

addition:
    mov eax, edi
    add eax, esi
    ret

section .note.GNU-stack