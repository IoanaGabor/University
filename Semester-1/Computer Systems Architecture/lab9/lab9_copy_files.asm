bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    input_file db "input.txt", 0
    acces_input db "r", 0
    input_file_descriptor dd -1
    output_file db "output.txt", 0
    acces_output db "w", 0
    output_file_descriptor dd -1
    format db "%c", 0
    status resb 4
    buff db 1
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword acces_input     
        push dword input_file
        call [fopen]
        add esp, 4*2                ; clean-up the stack
;call getlasterror
        mov [input_file_descriptor], eax  ; store the file descriptor returned by fopen
        
        cmp eax, 0
        je final

        push dword acces_output     
        push dword output_file
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [output_file_descriptor], eax  ; store the file descriptor returned by fopen
        
        cmp eax, 0
        je final
        
        loop_label:
            
            push dword [input_file_descriptor]         
            push dword 1
            push dword 1
            push dword buff
            call [fread]  ;read a character
            add esp, 4 * 4
            cmp eax, 0
            je close_files
            mov eax, 0
            mov al, [buff]
            push eax
            push dword format
            push dword [output_file_descriptor]
            call [fprintf]
            add esp, 4*3
        jmp loop_label
        
        close_files:
        push dword [input_file_descriptor]
        call [fclose]
        add esp, 4
        push dword [output_file_descriptor]
        call [fclose]
        add esp, 4
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
