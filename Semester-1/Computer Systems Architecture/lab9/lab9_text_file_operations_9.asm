bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


extern exit               
extern fopen
extern fread
extern fclose
extern isalnum
extern printf
import exit msvcrt.dll    
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import isalnum msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    file_name db "input.txt", 0
    acces_mode db "r", 0
    file_descriptor resd 1
    buffer_size equ 100
    buffer resb 100
    frequency TIMES 256 dd 0
    maxim resb 1
    maxim_frequency dd 0
    print_format db "The maximum frequency is %d and the character is %c", 0

segment code use32 class=code
    start:
        push dword acces_mode
        push dword file_name
        call [fopen]     ; open the file
        add esp, 4*2
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax
        read_loop:
            push dword [file_descriptor]         
            push dword buffer_size
            push dword 1
            push dword buffer
            call [fread]  ;read maximum 100 characters
            add esp, 4*4
                        
            cmp eax, 0
            je end_read_loop
            
            mov ecx, eax
            current_buffer_loop:  
                push ecx
                push dword [buffer+ecx-1]
                call [isalnum] ;call isalnum on every character from the current buffer
                add esp, 4*1
                pop ecx
                cmp eax, 0                
                jne NotSpecialCharacterMaximumCandidate ;if a character is alphanum, then it is not ok
                mov ebx, 0
                mov bl, [buffer+ecx-1]
                inc dword [frequency + 4*ebx]  ;increase the frequency of the current special character
                
                mov edx, [frequency + 4*ebx]
                cmp [maxim_frequency], edx
                ja NotSpecialCharacterMaximumCandidate ;if the current frequency lower than the maximum, then it is not ok
                mov [maxim_frequency], edx  ;if the current frequency is >= maximum, we update the maxim and its frequency
                mov [maxim], bl                
                NotSpecialCharacterMaximumCandidate:
            loop current_buffer_loop
        jmp read_loop
        end_read_loop:
        mov eax, 0
        mov al, [maxim]
        push eax
        mov edx, [maxim_frequency]
        push edx
        push dword print_format
        call[printf]   ;printf the result
        add esp, 4*3
        
        push dword file_descriptor  
        call [fclose] ;close the file
        add esp, 4
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
