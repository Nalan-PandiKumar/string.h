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

extern printf : PROC
extern exit   : PROC
; ====================================================================================================================
.data 
    ERROR_NULL_PTR BYTE "NULL POINTER DEREFERENCE",10,0

.code

; Function : (strlen) ->Get the length of a null-terminated string.
; unsigned int strlen(const char *str)
strlen PROC
    ;Prologue
    PUSH EBP                      ; Save EBP
    MOV  EBP, ESP                 ; Establish stack frame
    PUSH ESI                      ; Save ESI
    MOV  ESI, DWORD PTR [EBP + 8] ; Load the string address into ESI

    ;Check for source string is NULL
    TEST ESI,ESI                  ; Check ESI is not null
    JZ   strlen_failure           ; EXIT the program

    XOR  EAX, EAX                 ; Initialize EAX (length) to 0

strlen_loop:
    CMP  BYTE PTR [ESI], 0  ; Check if current character is null
    JE   strlen_return      ; If null, exit the loop
    INC  EAX                ; Increment length
    INC  ESI                ; Move to the next character
    JMP  strlen_loop        ; Repeat the loop

strlen_failure:
    MOV  EAX,1                   ; Indicate the error occured
    PUSH OFFSET ERROR_NULL_PTR   ; Passing error message
    CALL printf                  ; Display the error message
    ADD  ESP,4                   ; Clean up arguments
    CALL exit                    ; exit the program with failure code

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

    ; Check for NULL pointers
    TEST EDI,EDI                        ; Check EDI (dest) is NULL
    JZ   strcpy_failure                 ; If NULL, jump to failure
    TEST ESI,ESI                        ; Check ESI (src) is NULL
    JZ   strcpy_failure                 ; If NULL, jump to failure

strcpy_loop:
    MOV AL, BYTE PTR [ESI]              ; Load the byte from the source into AL
    MOV BYTE PTR [EDI], AL              ; Write the byte from AL into the destination
    CMP AL,0                            ; Check if null byte(\0) is copied
    JE  strcpy_return                   ; If null byte(\0) is found then exit
    INC ESI                             ; Increment src
    INC EDI                             ; Increment dest
    JMP strcpy_loop                     ; Repeat the loop

strcpy_failure:
    MOV  EAX,1                   ; Indicate the error occured
    PUSH OFFSET ERROR_NULL_PTR   ; Passing error message
    CALL printf                  ; Display the error message
    ADD  ESP,4                   ; Clean up arguments
    CALL exit                    ; exit the program with failure code

strcpy_return:
    ;Epilogue
    POP EDI                 ; Restore EDI
    POP ESI                 ; Restore ESI
    POP EAX                 ; Restore EAX
    LEAVE                   ; Clean up stack frame
    RET                     ; Return to caller
strcpy  ENDP

; Function : (strncpy) ->Copy a fixed number of characters from one string to another.
; void  strncpy(char* dest, char* src, size_t n);

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

    ; Check for NULL pointers
    TEST EDI,EDI                         ; Check EDI (dest) is NULL
    JZ   strncpy_failure                 ; If NULL, jump to failure
    TEST ESI,ESI                         ; Check ESI (src) is NULL
    JZ   strncpy_failure                 ; If NULL, jump to failure
    
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

strncpy_failure:
    MOV  EAX,1                   ; Indicate the error occured
    PUSH OFFSET ERROR_NULL_PTR   ; Passing error message
    CALL printf                  ; Display the error message
    ADD  ESP,4                   ; Clean up arguments
    CALL exit                    ; exit the program with failure code


strncpy ENDP

; Function : (strcat) -> Concatenate two null-terminated strings.
; char* strcat(char* dest, const char* src)
strcat PROC
       ; Prologue
       PUSH EBP                             ; Save EBP
       MOV  EBP,ESP                         ; Establish stack frame
       PUSH EDX                             ; Save EDX
       PUSH ESI                             ; Save ESI
       PUSH EDI                             ; Save EDI
       MOV  EDI,DWORD PTR[EBP + 8]          ; Load destination string into EDI
       MOV  ESI,DWORD PTR[EBP + 12]         ; Load source string into ESI

       ; Check for NULL pointers
       TEST EDI,EDI                 ; Check EDI (dest) is NULL
       JZ   strcat_failure          ; If NULL, jump to failure
       TEST ESI,ESI                 ; Check ESI (src) is NULL
       JZ   strcat_failure          ; If NULL, jump to failure

       MOV  EAX,EDI                 ; Store destination pointer for return

loop_to_destination_end:
       MOV  DL,BYTE PTR[EDI]        ; Read character from destination string
       TEST DL,DL                   ; Check if character is 0 (NULL terminator)
       JZ   append_source_string    ; If NULL, start appending source
       INC  EDI                     ; Increment destination pointer
       JMP  loop_to_destination_end ; Repeat the loop

append_source_string:
       MOV  DL,BYTE PTR[ESI]        ; Read character from source string
       TEST DL,DL                   ; Check if character is 0
       JZ   strcat_success          ; If NULL, append NULL terminator and return
       MOV  BYTE PTR[EDI],DL        ; Copy source character to destination
       INC  EDI                     ; Increment destination pointer
       INC  ESI                     ; Increment source pointer
       JMP  append_source_string    ; Repeat the loop

strcat_success:
       MOV BYTE PTR[EDI],0          ; Append NULL terminator at the end
       JMP strcat_return            ; Return

strcat_failure:
       XOR EAX,EAX                  ; Set EAX = 0 for failure return

strcat_return:
       ; Epilogue
       POP EDI                      ; Restore EDI
       POP ESI                      ; Restore ESI
       POP EDX                      ; Restore EDX
       LEAVE                        ; Clean up stack frame
       RET                          ; Return

strcat ENDP

; Function : (strncat)-> Concatenate a fixed number of characters from one string to another.
; char* strncat(char* dest, const char* src, size_t n);
strncat PROC
    ;Prologue
    PUSH EBP                        ; Save EBP
    MOV  EBP,ESP                    ; Establish a stack frame
    PUSH ECX                        ; Save ECX
    PUSH EDX                        ; Save EDX
    PUSH ESI                        ; Save ESI
    PUSH EDI                        ; Save EDI
    MOV  EDI,DWORD PTR[EBP + 8]      ; Load destination pointer into EDI
    MOV  ESI,DWORD PTR[EBP + 12]     ; Load source pointer into ESI
    MOV  ECX,DWORD PTR[EBP + 16]    ; Load the size(n) of character to append

    ;Check for NULL pointers
    TEST EDI,EDI                    ; Check EDI destination pointer is NULL
    JZ   strncat_failure            ; If NULL exit the program
    
    TEST ESI,ESI                    ; Check ESI source pointer is NULL
    JZ   strncat_failure            ; If NULL exit the program

    MOV  EAX,EDI                    ; Store destination pointer for return

loop_to_destination_end:
    MOV  DL,BYTE PTR[EDI]           ; Read character from destination string
    TEST DL,DL                      ; Check cheacter is NULL byte
    JZ   append_source_string       ; If NULL start appending the source
    INC  EDI                        ; Increment destination pointer
    JMP  loop_to_destination_end    ; Repeat the loop

append_source_string:
    MOV  DL,BYTE PTR[ESI]           ; Read character from source string
    TEST DL,DL                      ; Check the character is NULL byte
    JZ   strncat_success            ; Return
    CMP  ECX,0                      ; Check counter is zero
    JZ   strncat_success            ; If counter is zero then return
    MOV  BYTE PTR[EDI],DL           ; Write the character at the end of destination
    INC  ESI                        ; Increment source pointer
    INC  EDI                        ; Increment destination pointer
    DEC  ECX                        ; Decrement counter
    JMP  append_source_string       ; Repeat the loop

strncat_success:
    MOV BYTE PTR[EDI],0             ; Append the NULL character at the end
    JMP strncat_return              ; Return

strncat_failure:
    XOR EAX,EAX                     ; EAX = 0

strncat_return:

    ;Epilogue
    POP EDI                         ; Restore EDI
    POP ESI                         ; Restore ESI
    POP EDX                         ; Restore EDX
    POP ECX                         ; Restore ECX
    LEAVE                           ; Clean up stack frame
    RET                             ; Return

strncat ENDP

; Function : (strcmp)-> Concatenate a fixed number of characters from one string to another.
; int strcmp(const char *str1, const char *str2);
strcmp  PROC
    PUSH EBP                            ; Save EBP
    MOV  EBP,ESP                        ; Estabilsh stack frame
    PUSH EDX
    PUSH ESI                            ; Save ESI
    PUSH EDI                            ; Save EDI
    MOV  EDI, DWORD PTR[EBP + 8]        ; Load the string1 address into EDI 
    MOV  ESI, DWORD PTR[EBP + 12]       ; Load the string2 address into ESI

    ; Check for NULL pointers
    TEST EDI,EDI                 ; Check EDI (dest) is NULL
    JZ   strcmp_failure          ; If NULL, jump to failure
    TEST ESI,ESI                 ; Check ESI (src) is NULL
    JZ   strcmp_failure          ; If NULL, jump to failure

strcmp_loop:
    MOV  AL,BYTE PTR[EDI]               ; Read charcater from string1
    MOV  DL,BYTE PTR[ESI]               ; Read charcater from string1
    CMP  AL,0                           ; Check character from string1 is null byte
    JZ   strcmp_success                 ; if reached null return
    CMP  DL,0                           ; Check character from string2 is null byte
    JZ   strcmp_success                 ; if reached null return
    INC  EDI                            ; Increment string1 pointer
    INC  ESI                            ; Increment string2 pointer
    CMP  AL,DL                          ; Compare string1 chracter and string2 character
    JE   strcmp_loop                    ; If both the character are equal then continue the loop

strcmp_success:
    SUB   AL,DL                           ; Compute difference between two characters
    MOVSX EAX,AL                          ; Write the computed difference with sign in EAX
    JMP   strcmp_return                   ; Return

strcmp_failure:
    MOV  EAX,1                             ; EAX = 1 indicate failure
    PUSH OFFSET ERROR_NULL_PTR             ; Error indicates null pointer is passed to strcmp
    CALL printf                            ; call to printf
    ADD  ESP,4                             ; Function arguments clean up
    CALL exit                              ; Exit program with stacks code 1

strcmp_return:
    ;Epilogue
    POP   EDI                             ; Restore EDI
    POP   ESI                             ; Restore ESI
    POP   EDX                             ; Restore EDX
    LEAVE                                 ; Clean up stack frame
    RET                                   ; Return
strcmp  ENDP
END