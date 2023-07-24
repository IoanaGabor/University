bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    S1 db 1,2,3,3,2,1,2,3,2
    l1 equ $ - S1
    S2 db 3,2
    l2 equ $ - S2
    Sol times l1 resb 1
    keepCount resb 4
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, l1
        jecxz endLoop
        mov esi, S1
        mov edx, 0
        mov eax, 0  ;eax is the index of the current element in S1
        For_index:
            mov [keepCount], ecx 
            mov edi, S2 ;load the addres of the first element in S2
            mov ecx, l2
            lea esi, [eax+S1] ;load the address of the current element from S1 to esi
            jecxz endLoop
            cauta:
                cmpsb
                jne NotOk  ;if the elements are not equal, jump to not ok
                cmp esi, S1 + l1 ;if the end of S1 is reached, the cauta loop is exited
            Loopne cauta
            cmp ecx, 0 ; if the cauta loop has been exited and not all the elements from S2 have been considered, jump to not ok
            jne NotOk
            mov [Sol + edx], al ; if there is a match, then add the corresponding index to the solution
            inc edx
            NotOk:
            inc eax
            mov ecx, [keepCount]
        Loop For_index
        endLoop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
