bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


extern exit               
extern scanf
extern printf

import exit msvcrt.dll                              
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resd 1
    b resd 1
    result resd 1
    read_format db "%d %d", 0
    print_format db "%d", 0
    
segment code use32 class=code
    start:
        push dword b
        push dword a
        push dword read_format
        call [scanf]
        add esp, 4*3
        mov eax, [a]
        cdq
        mov ebx, eax
        mov ecx, edx
        mov eax, [b]
        cdq
        add eax, ebx
        adc edx, ecx
        mov ebx, [a]
        sub ebx, [b]
        idiv ebx
        mov [result], eax
        push dword [result]
        push dword print_format
        call[printf]
        add esp, 4*2
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
