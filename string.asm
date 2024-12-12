; ============================================
; FILE: string.asm
; DESCRIPTION:
;   This file contains the assembly implementation 
;   of all functions typically found in the C standard 
;   library's `<string.h>`. The goal of this project 
;   is to replicate and understand the functionality 
;   of these functions at the lowest level, utilizing 
;   the x86-32 instruction set.
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

extern malloc : PROC
; ====================================================================================================================
.code

; Function : (strlen) ->Get the length of a null-terminated string.
; unsigned int strlen(const char *str)
strlen PROC
    ;Prologue
    PUSH EBP                      ; Save EBP
    MOV  EBP, ESP                 ; Establish stack frame
    PUSH ESI                      ; Save ESI
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
    POP ESI                 ; restore ESI
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
    PUSH ESI                            ; Save ESI
    PUSH EDI                            ; Save EDI
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
    POP EDI                 ; Restore EDI
    POP ESI                 ; Restore ESI
    POP EAX                 ; Restore EAX
    LEAVE                   ; Clean up stack frame
    RET                     ; Return to caller
strcpy  ENDP

strncpy PROC
    ; Prologue
    PUSH EBP                     ; Save EBP
    MOV  EBP, ESP                ; Establish stack frame
    PUSH EAX                     ; Save EAX
    PUSH ECX                     ; Save ECX
    PUSH ESI                     ; Save ESI
    PUSH EDI                     ; Save EDI

    MOV  EDI, DWORD PTR [EBP + 8]   ; Load the destination address into EDI
    MOV  ESI, DWORD PTR [EBP + 12]  ; Load the source address into ESI
    MOV  ECX, DWORD PTR [EBP + 16]  ; Load the size (n) into ECX

    

    ; Check if n == 0 (Nothing to copy)
    TEST ECX, ECX                 ; Is ECX == 0?
    JZ strncpy_return             ; If yes, just return

    ; Adding 1 to ECX for null byte
    INC ECX

strncpy_loop:
    MOV AL,BYTE PTR[ESI]            ; Read the character from source string
    CMP AL,0                        ; Check the charcater is null byte 
    JZ  strncpy_pad                 ; If null byte encountered then start padding remaining bytes
    MOV BYTE PTR[EDI],AL            ; Write the character to destination
    INC EDI                         ; Increment the destination pointer
    INC ESI                         ; Increment the source pointer
    DEC ECX                         ; Decrement the character count need to be copied
    CMP ECX,1                       ; Check ECX = 1 
    JNE  strncpy_loop               ; If not repeat the loop
    

strncpy_pad:
    MOV BYTE PTR[EDI],0             ; Padd the remaining bytes with null
    DEC ECX                         ; Decrement the character count
    INC EDI                         ; Increment the destination pointer
    CMP ECX,0                       ; Check ECX = 0
    JNE strncpy_pad                 ; If not repeat the padding
    


strncpy_return:
    ; Epilogue
    POP EDI                       ; Restore EDI
    POP ESI                       ; Restore ESI
    POP ECX                       ; Restore ECX
    POP EAX                       ; Restore EAX
    LEAVE                         ; Clean up stack frame
    RET                           ; Return to caller

strncpy ENDP


; Function : (strcat) ->Concatenate two null-terminated strings.
; char* strcat(char* dest, const char* src)
strcat  PROC
        ;Prologue
        PUSH EBP                        ; Save EBP
        MOV  EBP,ESP                    ; Establish stack frame
        PUSH ESI                        ; Save ESI
        PUSH EDI                        ; Save EDI
        MOV  EDI, DWORD PTR[EBP + 8]    ; Load the destination address into EDI
        MOV  ESI, DWORD PTR[EBP + 12]   ; Load the source address into ESI
        
        PUSH EDI                        ; passing destination string as argument strlen
        CALL strlen                     ; calling strlen
        ADD  ESP,4                      ; cleaning function arguments

        MOV  ECX,EAX                    ; ECX = length of destination string
        
        PUSH ESI                        ; passing source string as argument strlen
        CALL strlen                     ; calling strlen
        ADD  ESP,4                      ; cleaning function arguments

        ADD  ECX,EAX                    ; ECX = length of destination string and source string
        INC  ECX                        ; ECX = ECX + 1 for null character

        PUSH ECX                        ; passing total length of concat string to malloc
        CALL malloc                     ; calling malloc
        ADD  ESP,4                      ; cleaning function arguments

        MOV ECX,EAX                     ; ECX = heap_ptr

strcat_destination:
        MOV DL,BYTE PTR[EDI]            ; read charcater from destination string
        CMP DL,0                        ; check dl == 0 null byte
        JZ  strcat_source               ; destination string is over 
        MOV BYTE PTR[ECX],DL            ; write destination str to the heap location allocated malloc
        INC EDI                         ; increment destination pointer
        INC ECX                         ; increment heap pointer
        JMP strcat_destination          ; repeat the loop

strcat_source:
        MOV DL,BYTE PTR[ESI]            ; read charcater from source string
        CMP DL,0                        ; check dl == 0 null byte
        JZ  strcat_return               ; source string is over 
        MOV BYTE PTR[ECX],DL            ; write destination str to the heap location allocated malloc
        INC ESI                         ; increment source pointer
        INC ECX                         ; increment heap pointer
        JMP strcat_source               ; repeat the loop
        
strcat_return:
        MOV BYTE PTR[ECX],0             ; append null byte to concated string
        ;Epilogue
        POP EDI                         ; Restore EDI
        POP ESI                         ; Restore ESI
        LEAVE                           ; clean up stack frame
        RET                             ; return

        
strcat  ENDP

END