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
    S db '+22b86X8'
    l equ $ - S
    S2 db 'a45'
    l2 equ $ - S2
    D times l2 + l/2 resb 1
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l2
        mov edi, D
        forIndex:
            mov al,[S2+ecx - 1] 
            mov [edi], al
            inc edi
        Loop forIndex ;moved the elements of S2 in reverse order
        
        mov ecx, l
        mov esi, S
        mov edi, D + l2
        forIndex2:
            mov al,[esi] 
            mov [edi], al
            inc edi
            inc esi
            inc esi
            dec ecx
        Loop forIndex2 ;moved the elements of S2 in reverse order            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
