#include <stdio.h>
#include "asm_string.h"
#include <math.h>


int custom_strncmp(const char* s1, const char* s2, size_t n) {
    // If n is 0, no characters are compared, return 0
    if (n == 0 || s1 == NULL || s2 == NULL) {
        return 0;
    }

    // Compare characters up to n or until a null character is encountered
    while (n-- > 0) {
        // If the characters differ or we reach the end of a string
        if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0') {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        // Move to the next character in both strings
        s1++;
        s2++;
    }

    // If all characters matched up to n, return 0
    return 0;
}


// Struct to hold test case information
typedef struct {
    const char* test_case_name;
    const char* str1; // First string to compare
    const char* str2; // Second string to compare
    size_t n;         // Number of characters to compare
} TestCase;

// Variables to count passed and failed test cases
int pass = 0, fail = 0;

// Function to run a single test case
void run_test_case(TestCase test_case) {
    // Compute expected result using custom_strncmp
    int expected_result = custom_strncmp(test_case.str1, test_case.str2, test_case.n);

    // Compute actual result using your strncmp implementation
    int actual_result = strncmp(test_case.str1, test_case.str2, test_case.n);


    // Compare results
    printf("Test Case: %s\n", test_case.test_case_name);
    if (expected_result == actual_result) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected: %d\n", expected_result);
        printf("Actual:   %d\n\n", actual_result);
        fail++;
    }
}

// Main function to run all test cases
int main() {

    // Test case array
    TestCase test_cases[] = {
        // Basic cases
        {"Identical strings, full comparison", "abc", "abc", 3},
        {"Identical strings, partial comparison", "abc", "abc", 2},
        {"Different strings, first character differs", "abc", "xbc", 1},
        {"Different strings, last character differs", "abc", "abd", 3},
        {"Different lengths, equal up to n", "abc", "abcd", 3},

        // Edge cases
        {"Empty strings, n = 0", "", "", 0},
        {"Empty strings, n > 0", "", "", 5},
        {"First string empty", "", "abc", 3},
        {"Second string empty", "abc", "", 3},
        {"One character strings, match", "a", "a", 1},
        {"One character strings, mismatch", "a", "b", 1},

        // Cases where n = 0
        {"n = 0, identical strings", "abc", "abc", 0},
        {"n = 0, different strings", "abc", "xyz", 0},
        {"n = 0, one empty string", "abc", "", 0},

        // Special character cases
        {"Strings with spaces, match", "abc def", "abc def", 7},
        {"Strings with spaces, mismatch", "abc def", "abc xyz", 7},
        {"Strings with special characters", "!@#$", "!@#$", 4},
        {"Strings with special characters, mismatch", "!@#$", "!@#%", 4},
        {"Strings with numbers", "1234", "1234", 4},
        {"Strings with numbers, mismatch", "1234", "1235", 4},

        // Case sensitivity
        {"Case sensitive match", "abc", "abc", 3},
        {"Case sensitive mismatch", "abc", "ABC", 3},

        // Long strings
        {"Long strings, first mismatch", "abcdefg", "abcdxyz", 7},
        {"Long strings, partial match", "abcdefg", "abcdxyz", 4},
        {"Long strings, full mismatch", "abcdefg", "xyzabcd", 7},

  
        // Mixed cases
        {"Partial match, different lengths", "abc", "abcdef", 3},
        {"Mismatch after n", "abcdef", "abcxyz", 6},
        {"Match, n larger than strings", "abc", "abc", 100},
        {"Mismatch, n larger than strings", "abc", "abd", 100},

        // Null character
        {"Null character in string 1", "abc\0xyz", "abc\0123", 7},
        {"Null character in string 2", "abc\0xyz", "abc\0xyz", 7},
        {"Null character mismatch", "abc\0xyz", "abc\0123", 7},

        // Edge comparisons
        {"First string shorter, match up to n", "abc", "abcd", 3},
        {"Second string shorter, match up to n", "abcd", "abc", 3},
        {"First string shorter, mismatch", "abc", "abcd", 4},
        {"Second string shorter, mismatch", "abcd", "abc", 4},

        // Large n with empty strings
        {"Large n, both empty", "", "", 100},
        {"Large n, first empty", "", "abcdef", 100},
        {"Large n, second empty", "abcdef", "", 100},

        // Mixed character types
        {"Mixed letters and numbers, match", "abc123", "abc123", 6},
        {"Mixed letters and numbers, mismatch", "abc123", "abc124", 6},
        {"Mixed letters and symbols, match", "abc!@#", "abc!@#", 6},
        {"Mixed letters and symbols, mismatch", "abc!@#", "abc!@%", 6}
    };


    // Number of test cases
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    // Run all test cases
    for (int i = 0; i < num_test_cases; i++) {
        run_test_case(test_cases[i]);
    }

    // Report results
    pass = abs(pass - fail);
    printf("Total pass score: (%d/%d)\n", pass, num_test_cases);
    return 0;
}
