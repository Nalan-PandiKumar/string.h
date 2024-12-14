/*
============================================
FILE: asm_string.h
DESCRIPTION:
    Header file for the assembly implementation
    of `<string.h>` functions. This file contains
    function declarations and external references
    to be used in projects integrating the custom
    string library.

USAGE:
    Include this file in any assembly or mixed
    C/assembly project to access the implemented
    string functions.

DECLARED FUNCTIONS:
    01) strlen: Get the length of a null-terminated string.
    02) strcpy: Copy a null-terminated string to another location.
    03) strncpy: Copy a fixed number of characters from one string to another.
    04) strcat: Concatenate two null-terminated strings.
    05) strncat: Concatenate a fixed number of characters from one string to another.
    06) strcmp: Compare two null-terminated strings.
    07) strncmp: Compare a fixed number of characters of two strings.
    08) strchr: Locate the first occurrence of a character in a string.
    09) strrchr: Locate the last occurrence of a character in a string.
    10) strstr: Locate a substring within a string.
    11) strtok: Tokenize a string using a delimiter.
    12) memcpy: Copy a block of memory from one location to another.
    13) memmove: Safely copy overlapping blocks of memory.
    14) memset: Fill a block of memory with a specific value.
    15) memcmp: Compare two blocks of memory.
    16) strdup: Create a duplicate of a string (non-standard, but widely used).
    17) strerror: Return a string describing an error code.
    18) strspn: Get the length of the initial substring matching a set of characters.
    19) strcspn: Get the length of the initial substring not matching a set of characters.
    20) strpbrk: Locate the first occurrence of any character from a set in a string.
    21) strcoll: Compare two strings using locale settings.
    22) strxfrm: Transform a string for locale-sensitive comparison.

NOTE:
    - Functions adhere to the x86-32 System V ABI or
      Microsoft x32 ABI based on the target OS.
    - Null-terminated strings are assumed where applicable.

AUTHOR:
    Nalan
============================================
*/

//  MACRO DEFINITIONS
typedef unsigned int X32_UMAX; //Unsigned maximum for X32-Bit architecture
typedef int X32_MAX; //Signed maximum for X32-Bit architecture

// FUNCTION DECLARATIONS
extern  X32_UMAX strlen(const char* str);
extern  void     strcpy(char* dest,  const char* src);
extern  void     strncpy(char* dest, const char* src, X32_UMAX n);
extern  char*    strcat(char* dest,  const char* src);
extern  char*    strncat(char* dest, const char* src, X32_UMAX n);
extern  X32_MAX  strcmp(const char* str1, const char* str2);
extern  X32_MAX  strncmp(const char* str1, const char* str2, X32_UMAX n);
extern  char*    strchr(const char* str, int c);
