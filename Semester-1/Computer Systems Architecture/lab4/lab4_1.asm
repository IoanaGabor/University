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
    a dw 1000000110011110b
    b dw 1000000111111111b
    c resd 1

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, [a]
        shr ax, 10
        mov dword[c], 0
        or [c], ax ;a
        or dword[c], 0000111111100000b ;b
        
        mov ax, [b]
        and ax, 0000111100000000b
        shr ax, 3
        or [c], ax ;c
        
        mov ax, [a]
        shr eax, 15
        or [c], eax        ;d
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
