; ============================================
; FILE: string.asm
; DESCRIPTION:
;   This file contains the assembly implementation 
;   of all functions typically found in the C standard 
;   library's `<string.h>`. The goal of this project 
;   is to replicate and understand the functionality 
;   of these functions at the lowest level, utilizing 
;   the x86-64 instruction set.
;
; FUNCTIONS IMPLEMENTED:
;   - strlen: Get the length of a null-terminated string.
;   - strcpy: Copy a null-terminated string to another location.
;   - strncpy: Copy a fixed number of characters from one string to another.
;   - strcat: Concatenate two null-terminated strings.
;   - strncat: Concatenate a fixed number of characters from one string to another.
;   - strcmp: Compare two null-terminated strings.
;   - strncmp: Compare a fixed number of characters of two strings.
;   - strchr: Locate the first occurrence of a character in a string.
;   - strrchr: Locate the last occurrence of a character in a string.
;   - strstr: Locate a substring within a string.
;   - strtok: Tokenize a string using a delimiter.
;   - memcpy: Copy a block of memory from one location to another.
;   - memmove: Safely copy overlapping blocks of memory.
;   - memset: Fill a block of memory with a specific value.
;   - memcmp: Compare two blocks of memory.
;   - strdup: Create a duplicate of a string (non-standard, but widely used).
;   - strerror: Return a string describing an error code.
;   - strspn: Get the length of the initial substring matching a set of characters.
;   - strcspn: Get the length of the initial substring not matching a set of characters.
;   - strpbrk: Locate the first occurrence of any character from a set in a string.
;   - strcoll: Compare two strings using locale settings.
;   - strxfrm: Transform a string for locale-sensitive comparison.
;
; PURPOSE:
;   Writing these functions in assembly provides a deeper understanding of:
;   - String manipulation and memory operations.
;   - The inner workings of the C standard library.
;   - Optimization of low-level routines for better performance.
;
; COMPATIBILITY:
;   - Assembled using MASM (Microsoft Macro Assembler).
;   - Targeted for x86-32 architecture.
;
; AUTHOR:
;   Nalan
; ============================================

.386
.model flat,c

; ====================================================================================================================
.code

; Function : (strlen) ->Get the length of a null-terminated string.
; unsigned int strlen(const char *str)
strlen PROC
    ;Prologue
    PUSH EBP                      ; Save EBP
    MOV  EBP, ESP                 ; Establish stack frame
    MOV  ESI, DWORD PTR [EBP + 8] ; Load the string address into ESI
    XOR  EAX, EAX                 ; Initialize EAX (length) to 0

strlen_loop:
    CMP  BYTE PTR [ESI], 0  ; Check if current character is null
    JE   strlen_return      ; If null, exit the loop
    INC  EAX                ; Increment length
    INC  ESI                ; Move to the next character
    JMP  strlen_loop        ; Repeat the loop

strlen_return:
    ;Epilogue
    LEAVE                   ; Clean up stack frame
    RET                     ; Return to caller
strlen ENDP

; Function : (strcpy) ->Copy a null-terminated string to another location.
; void strcpy(char* dest, const char* src)
strcpy  PROC
    ;Prologue
    PUSH EBP                            ; Save EBP
    MOV  EBP,ESP                        ; Establish stack frame
    PUSH EAX                            ; Save EAX
    MOV  EDI,DWORD PTR[EBP + 8]         ; Load the destination address into EDI
    MOV  ESI,DWORD PTR[EBP + 12]        ; Load the source address into ESI

strcpy_loop:
    MOV AL, BYTE PTR [ESI]              ; Load the byte from the source into AL
    MOV BYTE PTR [EDI], AL              ; Write the byte from AL into the destination
    CMP AL,0                            ; Check if null byte(\0) is copied
    JE  strcpy_return                   ; If null byte(\0) is found then exit
    INC ESI                             ; Increment src
    INC EDI                             ; Increment dest
    JMP strcpy_loop                     ; Repeat the loop

strcpy_return:
    ;Epilogue
    POP EAX                 ; Restore EAX
    LEAVE                   ; Clean up stack frame
    RET                     ; Return to caller
strcpy  ENDP

; Function : (strncpy) -> Copy a fixed number of characters from one string to another.
; void strncpy(char* dest, const char* src, size_t n)
strncpy PROC
    ; Prologue
    PUSH EBP                     ; Save EBP
    MOV  EBP, ESP                ; Establish stack frame
    PUSH EAX                     ; Save EAX
    PUSH ECX                     ; Save ECX

    MOV  EDI, DWORD PTR [EBP + 8]   ; Load the destination address into EDI
    MOV  ESI, DWORD PTR [EBP + 12]  ; Load the source address into ESI
    MOV  ECX, DWORD PTR [EBP + 16]  ; Load the size (n) into ECX

strncpy_loop:
    TEST ECX, ECX                 ; Check if ECX is 0
    JZ   strncpy_pad              ; If ECX == 0, move to padding

    MOV AL, BYTE PTR [ESI]        ; Load a byte from the source into AL
    MOV BYTE PTR [EDI], AL        ; Store the byte in the destination
    INC ESI                       ; Increment the source pointer
    INC EDI                       ; Increment the destination pointer
    DEC ECX                       ; Decrement the counter

    CMP AL, 0                     ; Check if the byte is null
    JNZ strncpy_loop              ; If not null, continue copying
    JMP strncpy_pad               ; If null, go to padding

strncpy_pad:
    TEST ECX, ECX                 ; Check if padding is required
    JZ   strncpy_return           ; If ECX == 0, no padding needed

    MOV BYTE PTR [EDI], 0         ; Fill the destination with null bytes
    INC EDI                       ; Increment the destination pointer
    DEC ECX                       ; Decrement the counter
    JMP strncpy_pad               ; Repeat until ECX == 0

strncpy_return:
    ; Epilogue
    POP ECX                       ; Restore ECX
    POP EAX                       ; Restore EAX
    LEAVE                         ; Clean up stack frame
    RET                           ; Return to caller

strncpy ENDP

; Function : (strcat) ->Concatenate two null-terminated strings.
; void strcat(char* dest, const char* src)


END