#include <stdio.h>
#include <stdlib.h>  // For dynamic memory allocation
#include "asm_string.h"

// Custom strncpy function (handling NULL and buffer size limit)
char* custom_strncpy(char* dest, const char* src, size_t n) {
    if (src == NULL || dest == NULL) {
        return NULL;  // Return NULL if either pointer is invalid
    }

    char* original_dest = dest;  // Save the start of the destination
    while (n-- && (*dest++ = *src++));  // Copy characters until 'n' or the end of the string

    if (n > 0) {
        *dest = '\0';  // Ensure null-termination if there's space left
    }

    return original_dest;
}

int pass = 0, fail = 0;

// Struct to hold test case information
typedef struct {
    const char* test_case_name;
    const char* src_str;
    size_t n;  // The number of characters to copy
} TestCase;

void run_test_case(TestCase test_case) {
    // Allocate memory for destination strings
    char dest_custom[100];
    char dest_my[100];

    // Ensure that both destination arrays are properly initialized
    memset(dest_custom, 0, sizeof(dest_custom));
    memset(dest_my, 0, sizeof(dest_my));

    // Check if the source string is NULL, to avoid copying NULL values
    
        // Run custom_strncpy for expected result
        custom_strncpy(dest_custom, test_case.src_str, test_case.n);

        // Run your standard strncpy for actual result
        strncpy(dest_my, test_case.src_str, test_case.n);

        // Compare the results and print the output
        printf("Test Case: %s\n", test_case.test_case_name);
        printf("result:%s,expected:%s\n", dest_my, dest_custom);
        if (strcmp(dest_custom, dest_my) == 0) {
            printf("Test Passed\n\n");
            pass++;
        }
        else {
            printf("Test Failed\n\n");
            printf("Expected: %s\n", dest_custom);
            printf("Actual: %s\n\n", dest_my);
            fail++;
        }
 }



int main() {
    // Define test cases with source strings and size limits for strncpy
    TestCase test_cases[50] = {
        {"Test Case 1: Copy Empty String", "", 10},
        {"Test Case 2: Copy Short String", "apple", 2},
        {"Test Case 3: Copy Long String", "banana1234", 5},
        {"Test Case 4: Copy String with Special Characters", "grape!@#", 10},
        {"Test Case 5: Copy String with Numbers", "12345", 10},
        {"Test Case 6: Copy String with Spaces", "hello world", 10},
        {"Test Case 7: Copy Single Character", "a", 10},
        {"Test Case 8: Copy String with Leading Spaces", "  space", 1},
        {"Test Case 9: Copy String with Trailing Spaces", "space  ", 10},
        {"Test Case 10: Copy a Large String", "aVeryLongStringToTestTheFunctionalityOfMyStrncpy", 20},
        {"Test Case 11: Copy Empty String", "", 10},
        {"Test Case 12: Copy Alpha Numeric", "Test123", 10},
        {"Test Case 13: Copy String with Special Characters", "@#$%^&*()", 10},
        {"Test Case 14: Copy Mixed Case", "HeLlO", 10},
        {"Test Case 15: Copy Space Only", "     ", 10},
        {"Test Case 16: Copy String with Backslashes", "C:\\Program Files", 10},
        {"Test Case 17: Copy Single Digit", "5", 10},
        {"Test Case 18: Copy String with Periods", "Hello.World", 10},
        {"Test Case 19: Copy String with Dashes", "Hello-World", 10},
        {"Test Case 20: Copy String with Underscores", "Hello_World", 10},
        {"Test Case 21: Copy Mixed Case and Numbers", "Test456", 10},
        {"Test Case 22: Copy NULL String", NULL, 10},
        {"Test Case 23: Copy String with Chinese Characters", "chinese", 10},
        {"Test Case 24: Copy Long String", "Lorem ipsum dolor sit amet, consectetur adipiscing elit.", 40},
        {"Test Case 25: Copy String with Tabs", "Hello\tWorld", 10},
        {"Test Case 26: Copy Single Word", "word", 10},
        {"Test Case 27: Copy String with Punctuation", "Hello! How are you?", 10},
        {"Test Case 28: Copy String with Newline", "Hello\nWorld", 10},
        {"Test Case 29: Copy String with Multiple Newlines", "Hello\n\nWorld", 10},
        {"Test Case 30: Copy String with Multiple Spaces", "Hello      World", 10},
        {"Test Case 31: Copy String with Multiple Dashes", "----", 10},
        {"Test Case 32: Copy Empty String", "", 10},
        {"Test Case 33: Copy Alphabet String", "abcdefghijklmnopqrstuvwxyz", 10},
        {"Test Case 34: Copy String with Only Zeros", "0000000", 10},
        {"Test Case 35: Copy String with Repeated Characters", "aaaaaaaaaa", 10},
        {"Test Case 36: Copy String with Mixed Numbers and Special Characters", "1234!@#$", 10},
        {"Test Case 37: Copy String with One Space", " ", 10},
        {"Test Case 38: Copy String with Asterisks", "*&*^&*", 10},
        {"Test Case 39: Copy Empty String", "", 10},
        {"Test Case 40: Copy Random String", "r&*8%fgt", 10},
        {"Test Case 41: Copy Large String", "ThisIsAVeryLargeStringThatWillTestTheCapacityOfMyStrncpyFunctionAndCheckHowItHandlesLongInputs", 40},
        {"Test Case 42: Copy String with Mixed Case and Numbers", "TeST123", 10},
        {"Test Case 43: Copy String with Slashes", "C/Windows/System32", 10},
        {"Test Case 44: Copy String with Mixed Characters", "Hello$%#", 10},
        {"Test Case 45: Copy String with Dots and Commas", "Test...Case", 10},
        {"Test Case 46: Copy String with Uppercase", "HELLO", 10},
        {"Test Case 47: Copy Short String", "xyz", 10},
        {"Test Case 48: Copy String with Double Quotes", "\"Hello\"", 10},
        {"Test Case 49: Copy String with Different Case", "tEsT", 10},
        {"Test Case 50: Copy String with Long Numerical Input", "1234567890123456789012345678901234567890", 40}
    };

    // Run all test cases
    for (int i = 0; i < 50; i++) {
        run_test_case(test_cases[i]);
    }

    // Output results
    printf("Pass score: %d/50\n", pass);
    printf("Fail score: %d\n", fail);

    return 0;
}
