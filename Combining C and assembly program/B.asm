section .bss
    character RESB 8

section .text
    global B
    extern C
    
B:
    mov [character], rdi
    mov rax, 1
    mov rdi, 1
    mov r9 , rsi
    mov rsi, character
    mov rdx, 8
    syscall
    pop rax
    lea rdx,[C]
    push r9
    push rdx
    ret
