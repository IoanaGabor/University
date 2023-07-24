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
    a db 01110110b
    b dw 0110010011100110b
    c resb 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, [a]
        shr al, 2
        and al, 15
        mov [c], al ; move the bits 2-5 from a to bits 0-3 at c
        mov ax, [b]
        shr ax, 6
        and ax, 15
        shl ax, 4
        or [c], al ; move the bits 6-9 from b to bits 4-7 at c
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
