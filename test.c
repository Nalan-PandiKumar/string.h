#include <stdio.h>
#include <stddef.h>
#include "asm_string.h" // Include your custom memset implementation header

// Custom reference memset implementation (for testing purposes)
void* test_memset(void* str, int c, size_t n) {
    if (!str)
        return NULL;

    unsigned char* s = (unsigned char*)str;
    for (size_t i = 0; i < n; i++) {
        s[i] = (unsigned char)c;
    }
    return str;
}

// Test case structure
typedef struct {
    const char* test_case_name; // Description of the test case
    char input[100];            // Input buffer
    int fill_value;             // Value to set
    size_t size;                // Number of bytes to set
} TestCase;

int pass = 0, fail = 0;

// Run a single test case
void run_test_case(TestCase test_case) {
    printf("Test Case: %s\n", test_case.test_case_name);

    // Prepare input for memset
    char actual[100], expected[100];
    for (size_t i = 0; i < sizeof(test_case.input); i++) {
        actual[i] = test_case.input[i];
        expected[i] = test_case.input[i];
    }

    // Generate expected result using reference function
    test_memset(expected, test_case.fill_value, test_case.size);

    // Call your custom memset function
    memset(NULL, test_case.fill_value, test_case.size);

    // Compare results
    int is_passed = 1;
    for (size_t i = 0; i < sizeof(test_case.input); i++) {
        if (actual[i] != expected[i]) {
            is_passed = 0;
            break;
        }
    }

    if (is_passed) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected: ");
        for (size_t i = 0; i < sizeof(test_case.input); i++) {
            printf("%02X ", (unsigned char)expected[i]);
        }
        printf("\nActual:   ");
        for (size_t i = 0; i < sizeof(test_case.input); i++) {
            printf("%02X ", (unsigned char)actual[i]);
        }
        printf("\n\n");
        fail++;
    }
}

int main() {
    // Define 50 test cases
    TestCase test_cases[] = {
        {"Fill full buffer with 0", {0}, 0, 100},
        {"Fill full buffer with 0xFF", {0}, 0xFF, 100},
        {"Partial fill with 0xAA", {0}, 0xAA, 10},
        {"Fill up to size 0", {0}, 0x00, 0},
        {"Fill 1 byte", {0}, 0x55, 1},
        {"Fill 50 bytes with 0xAB", {0}, 0xAB, 50},
        {"Fill edge case (0 bytes)", {0}, 0x01, 0},
        {"Fill buffer with negative value (converted to unsigned)", {0}, -1, 20},
        {"Fill unaligned memory (3 bytes)", {1, 2, 3}, 0xEE, 3},
        {"Fill overlapping regions", "Overlap", 0x44, 4},
        {"Fill buffer with null terminator", "Hello\0World", 0x99, 12},
        {"Fill single-byte string", "H", 0x00, 1},
        {"Fill middle section of a string", "ABCDEFGHIJ", 0xFF, 5},
        {"Fill with zero size", "Test", 0xAA, 0},
        {"Fill full with alternate bits", {0}, 0b01010101, 100},
        {"Fill with edge values (0x00)", {0}, 0x00, 100},
        {"Fill with edge values (0xFF)", {0}, 0xFF, 100},
        {"Fill with a single character", {0}, 'A', 1},
        {"Fill half the buffer", {0}, 0x77, 50},
        {"Empty buffer with large size", {0}, 0x88, 0},
        {"Fill after non-zero initialization", {1, 2, 3, 4, 5}, 0x55, 5},
        {"Fill after special chars", {1, '\n', '\t', 0x7F}, 0xEE, 4},
        {"Fill buffer ending with null terminator", "Test\0\0\0", 0xAA, 6},
        {"Fill entire array with a pattern", {0}, 0x5A, 100},
        {"Fill full buffer with random ASCII", {0}, 0x42, 100},
        {"Overwrite non-ASCII values", {200, 210, 220}, 0x80, 3},
        {"Small size with aligned memory", {1, 2, 3}, 0xF0, 1},
        {"Fill repeating sections", "12345", 0xAA, 3},
        {"Alternate fill start/end", "Start and end", 0xBB, 15},
        {"Fill just before null terminator", "BufferTest", 0xFF, 10},
        {"Change previously filled buffer", {0x99}, 0x33, 50},
        {"Reset to zero after fill", {0x99}, 0x00, 50},
        {"String with spaces", "Hello World", 0x20, 11},
        {"Fill with capital letter", "Testing", 'X', 7},
        {"Partial overwrite in middle", "PartialOverwrite", 0xCC, 5},
        {"Fill empty buffer", "", 0x55, 10},
        {"Multiple fills in succession", {0}, 0x11, 30},
        {"Fill overlapping ASCII", "ABC\0XYZ", 0xAA, 7},
        {"Fill buffer starting at offset", "Offset Test", 0xCC, 6},
        {"Fill special escape sequences", "New\nLine", 0x00, 8},
        {"Partial overwrite after reset", {0xFF}, 0x77, 5},
        {"Fill non-printable chars", {0}, 0x1F, 100},
        {"Fill alternating sections", "123ABC", 0x88, 3},
        {"Null terminator at beginning", "\0Test", 0x55, 5},
        {"Fill buffer with mix of data", {1, 2, 3, 4, 5}, 0xEE, 5},
        {"Test all bytes zero", {0}, 0x00, 100},
        {"Test all bytes max", {0}, 0xFF, 100},
    };

    int total_tests = sizeof(test_cases) / sizeof(TestCase);

    // Run all test cases
    for (int i = 0; i < total_tests; i++) {
        run_test_case(test_cases[i]);
    }

    // Print summary
    printf("Total Tests: %d\n", total_tests);
    printf("Pass: %d\n", pass);
    printf("Fail: %d\n", fail);

    return 0;
}
