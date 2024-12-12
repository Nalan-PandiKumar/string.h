#include <stdio.h>
#include <stdlib.h>
#include "asm_string.h"



void free_memory(char* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

void test_strcat(const char* dest, const char* src) {
    // Dynamically allocate space for dest and src concatenation
    char* result = strcat(dest, src);

    if (result != NULL) {
        printf("Result of strcat: %s\n", result);
        free_memory(result);  // Free the dynamically allocated memory
    }
    else {
        printf("Memory allocation failed\n");
    }
}

int main() {
    // Array of 50 test cases for dest and src strings
    const char* test_cases[50][2] = {
        {"Hello", "World"},
        {"", "Test"},
        {"Test", ""},
        {"", ""},
        {"AB", "CD"},
        {"This", "is"},
        {"a", "test"},
        {"The", "quick brown fox"},
        {"jumps", "over"},
        {"lazy", "dog"},
        {"C", "Programming"},
        {"x", "y"},
        {"open", "ai"},
        {"hello", " there"},
        {"concatenate", "strings"},
        {"my", "name"},
        {"is", "Nalan"},
        {"this", "is a"},
        {"test case", "for strcat"},
        {"good", "luck"},
        {"happy", "coding"},
        {"make", "sure"},
        {"to", "join"},
        {"two", "strings"},
        {"and", "concatenate"},
        {"with", "dynamic"},
        {"memory", "allocation"},
        {"be", "careful"},
        {"about", "your memory"},
        {"test", "the"},
        {"edge", "cases"},
        {"with", "empty"},
        {"strings", "also"},
        {"concatenate", "long"},
        {"strings", "as well"},
        {"check", "for NULL"},
        {"values", "in strings"},
        {"handle", "all"},
        {"test", "cases"},
        {"effectively", "in"},
        {"the", "real world"},
        {"assert", "that"},
        {"memory", "is freed"},
        {"after", "each"},
        {"concatenation", "operation"},
        {"avoid", "memory"},
        {"leaks", "at"},
        {"all", "costs"}
    };

    // Loop through the test cases and perform strcat for each one
    for (int i = 0; i < 48; i++) {
        printf("\nTest Case %d:\n", i + 1);
        test_strcat(test_cases[i][0], test_cases[i][1]);
    }

    return 0;
}
