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
    a db 1
    b dw 2
    c dd 3
    d dq 5
    r resq 1
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, 0
        mov edx, 0
        mov al, [a]; edx:eax = a
        
        mov ebx, dword[d+0]
        mov ecx, dword[d+4]
        add eax, ebx
        adc edx, ecx; edx: eax = a + d
        
        add eax, ebx
        adc edx, ecx; edx:eax = a + d + d
        
        mov ebx, dword[c]
        mov ecx, 0
        
        sub eax, ebx
        sbb edx, ecx; edx:eax = (a + d + d) - c       
        
        mov dword[r+0], eax
        mov dword[r+4], edx ; r = (a + d + d) - c       
        
        mov eax, 0
        mov ax, [b]
        mov edx, 0
        add ax, [b] ; edx: eax = (b + b)
        
        add dword[r+0], eax
        adc dword[r+4], edx; r = (a + d + d) - c + (b + b)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
