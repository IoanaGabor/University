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
    a db 2
    b dw 2
    c db 5
    d dd 12
    x dq 8
    r resq 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ebx, 7
        mov al, [a]
        mov ah, 0
        mul WORD[b]
        push DX
        push AX
        pop EAX
        sub ebx, eax
        mov eax, 0
        mov al, [c]
        add ebx, eax ; ebx = (7-a*b+c)
        mov eax, ebx ;eax = (7-a*b+c)
        mov ebx, 0
        mov bl, [a]
        div bx ; ax = (7-a*b+c)/a
        mov ebx, 0
        mov bx, ax ; ebx = (7-a*b+c)/a
        mov eax, [d]
        sub eax, ebx
        sub eax, 6 ;eax = d-(7-a*b+c)/a-6
        mov [r], eax ;r = d-(7-a*b+c)/a-6
        mov eax, dword[x+0]
        mov edx, dword[x+4]
        mov ebx, 2
        div ebx
        add [r], eax ; r = d-(7-a*b+c)/a-6+x/2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
