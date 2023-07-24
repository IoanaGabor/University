bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    S db 1, 6, 3, 1
    l equ $ - S
    D times l-1 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov EAX, 0
        mov ECX, l
        FOR_INDEX:
            mov al, [S+ ecx -2]
            mov ah, 0
            mov bl, [S + ecx - 1]
            div bl
            mov [D + ecx - 2], al
        Loop FOR_INDEX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
