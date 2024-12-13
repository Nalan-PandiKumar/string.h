#include <stdio.h>
#include "asm_string.h"  // Include your custom header file with strchr

// Custom strchr function
char* custom_strchr(const char* str, int c) {
    // Ensure that c is within the valid range of 0 to 255 (unsigned char range)
    if (c < 0 || c > 255) {
        return NULL; // Invalid character, return NULL
    }

    while (*str != '\0') {
        if (*str == (char)c) {
            return (char*)str; // Found the character, return pointer
        }
        str++;
    }
    if (*str == (char)c) return str;
    // If character is not found, return NULL
    return NULL;
}

// Struct to hold test case information for strchr
typedef struct {
    const char* test_case_name;
    const char* str;    // String to search in
    int c;              // Character to search for
    const char* expected_result;  // Expected result (pointer as a string representation)
} TestCase;

// Variables to count passed and failed test cases
int pass = 0, fail = 0;

// Function to run a single test case for strchr
void run_test_case(TestCase test_case) {
    // Compute expected result using custom_strchr
    char* expected_result = custom_strchr(test_case.str,test_case.c);

    // Compute actual result using the standard strchr function
    char* actual_result = strchr(test_case.str, test_case.c);

    printf("result := (%p)\texpected := (%p)\n", actual_result, expected_result);

    // Compare results
    printf("Test Case: %s\n", test_case.test_case_name);
    if ((expected_result == actual_result) ||
        (expected_result != NULL && actual_result != NULL && *expected_result == *actual_result)) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        if (expected_result == NULL) {
            printf("Expected: NULL\n");
        }
        else {
            printf("Expected: %s\n", expected_result);
        }
        if (actual_result == NULL) {
            printf("Actual:   NULL\n");
        }
        else {
            printf("Actual:   %s\n", actual_result);
        }
        fail++;
    }
}

// Main function to run all test cases for strchr
int main() {
    // Test case array for strchr
    TestCase test_cases[] = {
        // Basic cases
        {"Character found in middle of string", "hello", 'l', "llo"},
        {"Character found at beginning", "hello", 'h', "hello"},
        {"Character found at end", "hello", 'o', "o"},
        {"Character not found", "hello", 'x', NULL},

        // Edge cases
        {"Empty string, search for character", "", 'a', NULL},
        {"Search for null character in string", "hello", '\0', NULL},
        {"Search for invalid character (out of range)", "hello", 300, NULL},
        {"Search for negative character (out of range)", "hello", -1, NULL},

        // Special character cases
        {"String with space", "hello world", ' ', " world"},
        {"String with special character", "!@#$", '#', "#$"},
        {"String with digits", "12345", '3', "345"},

        // Search for characters at different positions
        {"Search for character at the first position", "hello", 'h', "hello"},
        {"Search for character at the last position", "hello", 'o', "o"},
        {"Search for character not in string", "hello", 'z', NULL},

        // Large string cases
        {"Search for character in large string", "aaaaaaaaaaa", 'a', "aaaaaaaaaaaaa"},
        {"Search for character in large string, not found", "aaaaaaaaaaaaaa", 'z', NULL},

        // Search for uppercase characters
        {"Search for uppercase character", "Hello", 'H', "Hello"},
        {"Search for lowercase character in uppercase string", "HELLO", 'h', NULL},

        // Strings with digits
        {"String with digits, character found", "12345", '3', "345"},
        {"String with digits, character not found", "12345", '6', NULL},

        // Searching for first and last characters
        {"Search for first character in string", "hello", 'h', "hello"},
        {"Search for last character in string", "hello", 'o', "o"},
        {"Search for second character in string", "hello", 'e', "ello"},

        // Special characters
        {"String with special characters", "#$%&", '$', "$%&"},
        {"String with special characters, not found", "#$%&", '@', NULL},

        // Searching for non-printable characters
        {"String with non-printable character", "hello\x01", '\x01', "\x01"},
        {"String without non-printable character", "hello\x01", '\x02', NULL},

        // Strings with escape characters
        {"String with escape character", "hello\nworld", '\n', "\nworld"},
        {"String with escape character not found", "hello\nworld", '\t', NULL},

        // Searching for characters in mixed case strings
        {"Case sensitive search, character found", "HelloWorld", 'W', "World"},
        {"Case sensitive search, character not found", "HelloWorld", 'w', NULL},

        // Strings with multiple occurrences of a character
        {"Multiple occurrences of character, first found", "aabbcc", 'b', "bbcc"},
        {"Multiple occurrences of character, last found", "aabbcc", 'b', "bbcc"},

        // Searching for character in string with only one character
        {"Single character string, found", "x", 'x', "x"},
        {"Single character string, not found", "x", 'y', NULL},

        // Large number of occurrences of the same character
        {"Many occurrences of character", "aaaaa", 'a', "aaaaa"},
        {"Many occurrences of character not found", "aaaaa", 'b', NULL},

        // Searching for NULL character explicitly
        {"Search for null character at the end", "hello", '\0', NULL},
        {"Search for null character in string", "hello\x00world", '\0', NULL},

        // Searching for characters in a string with digits and special chars
        {"Search for special character in string", "abc$123", '$', "$123"},
        {"Search for digit in string", "abc123", '1', "123"},

        // Case where string is a single character
        {"String of one character, found", "x", 'x', "x"},
        {"String of one character, not found", "x", 'y', NULL},

        // Test searching for characters in a string of special characters
        {"String of special characters, match", "!@#$%^&*", '$', "$%^&*"},
        {"String of special characters, no match", "!@#$%^&*", '+', NULL},

        // Edge case for searching invalid values
        {"Search for character larger than 255", "hello", 300, NULL},
        {"Search for character less than 0", "hello", -1, NULL},

        // Search for a character in an empty string
        {"Search for character in empty string", "", 'a', NULL},
    };

    // Number of test cases
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    // Run all test cases for strchr
    for (int i = 0; i < num_test_cases; i++) {
        run_test_case(test_cases[i]);
    }

    // Report results
    printf("Total pass score: (%d/%d)\n", pass, num_test_cases);
    return 0;
}
