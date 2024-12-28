#include <stdio.h>
#include <stddef.h>
#include "asm_string.h"



// Custom memcpy implementation
void* custom_memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

// Custom memcmp implementation
int custom_memcmp(const void* ptr1, const void* ptr2, size_t n) {
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return (p1[i] > p2[i]) - (p1[i] < p2[i]);
        }
    }
    return 0;
}

// Test case structure
typedef struct {
    const char* test_case_name;
    void* input;
    size_t size;
    void* expected;
} TestCase;

int pass = 0, fail = 0;

// Run a single test case
void run_test_case(TestCase test_case) {
    printf("Test Case: %s\n", test_case.test_case_name);

    unsigned char actual[100] = { 0 };

    memcpy(actual, test_case.input, test_case.size);

    if (memcmp(test_case.expected, actual, test_case.size) == 0) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected: ");
        for (size_t i = 0; i < test_case.size; i++) {
            printf("%02X ", ((unsigned char*)test_case.expected)[i]);
        }
        printf("\nActual:   ");
        for (size_t i = 0; i < test_case.size; i++) {
            printf("%02X ", actual[i]);
        }
        printf("\n\n");
        fail++;
    }
}

int main() {
    // Data definitions for test cases
    char str1[] = "Hello, World!";
    char str2[] = "Test";
    int int_array1[] = { 1, 2, 3, 4 };
    int int_array2[] = { -1, -2, -3, -4 };
    float float_array1[] = { 1.1f, 2.2f, 3.3f };
    float float_array2[] = { -1.1f, -2.2f, -3.3f };
    struct {
        int id;
        char name[10];
    } custom_struct = { 42, "StructTest" };
    unsigned char random_bytes[] = { 0xDE, 0xAD, 0xBE, 0xEF };

    // 50 test cases
    TestCase test_cases[] = {
        // String tests
        {"Copy Full String", str1, sizeof(str1), str1},
        {"Copy Partial String", str1, 5, "Hello"},
        {"Copy Empty String", "", 0, ""},
        {"Copy String with Null", "abc\0def", 7, "abc\0def"},
        {"Copy String Overlapping Memory", "OverlapTest", 8, "OverlapT"},

        // Integer array tests
        {"Copy Full Integer Array", int_array1, sizeof(int_array1), int_array1},
        {"Copy Partial Integer Array", int_array1, 2 * sizeof(int), (int[]) { 1, 2 }},
        {"Copy Empty Integer Array", int_array1, 0, ""},
        {"Copy Negative Integer Array", int_array2, sizeof(int_array2), int_array2},
        {"Copy Mixed Integer Array", (int[]) { 1, -1, 2, -2 }, 4 * sizeof(int), (int[]) { 1, -1, 2, -2 }},

        // Float array tests
        {"Copy Full Float Array", float_array1, sizeof(float_array1), float_array1},
        {"Copy Partial Float Array", float_array1, 2 * sizeof(float), (float[]) { 1.1f, 2.2f }},
        {"Copy Negative Float Array", float_array2, sizeof(float_array2), float_array2},
        {"Copy Mixed Float Array", (float[]) { 1.0f, -1.0f }, 2 * sizeof(float), (float[]) { 1.0f, -1.0f }},
        {"Copy Empty Float Array", float_array1, 0, ""},

        // Struct tests
        {"Copy Full Struct", &custom_struct, sizeof(custom_struct), &custom_struct},
        {"Copy Partial Struct", &custom_struct, 4, &(int){42}},
        {"Copy Struct Name Only", custom_struct.name, 10, "StructTest"},
        {"Copy Struct ID Only", &custom_struct.id, 4, &(int){42}},
        {"Copy Empty Struct", &custom_struct, 0, ""},

        // Random byte tests
        {"Copy Random Bytes", random_bytes, sizeof(random_bytes), random_bytes},
        {"Copy Partial Random Bytes", random_bytes, 2, (unsigned char[]) { 0xDE, 0xAD }},
        {"Copy Empty Random Bytes", random_bytes, 0, ""},
        {"Copy Single Byte", random_bytes, 1, (unsigned char[]) { 0xDE }},
        {"Copy Repeating Byte", (unsigned char[]) { 0xFF, 0xFF, 0xFF }, 3, (unsigned char[]) { 0xFF, 0xFF, 0xFF }},

        // Edge cases
        {"Copy 0 Bytes", str1, 0, ""},
        {"Copy 1 Byte", str1, 1, "H"},
        {"Copy Large Buffer", str1, 20, str1},
        //{"Copy Null Pointer", NULL, 0, NULL},
        {"Copy Data with Alignment", (int[]) { 0x12345678 }, sizeof(int), (int[]) { 0x12345678 }},

        // Boundary checks
        {"Copy Exact Memory Size", "BoundaryTest", 11, "BoundaryTes"},
        {"Copy Beyond Memory Size", "Test", 10, "Test"},
        {"Copy Data with Padding", "\x01\x02\x00\x00", 4, "\x01\x02\x00\x00"},
        {"Copy Misaligned Data", (unsigned char[]) { 0x01, 0x02 }, 2, (unsigned char[]) { 0x01, 0x02 }},
        {"Copy Unaligned Memory", (unsigned char[]) { 0x01 }, 1, (unsigned char[]) { 0x01 }},

        // Other data types
        {"Copy Double Array", (double[]) { 1.1, 2.2 }, 2 * sizeof(double), (double[]) { 1.1, 2.2 }},
        {"Copy Long Array", (long[]) { 1000, 2000 }, 2 * sizeof(long), (long[]) { 1000, 2000 }},
        {"Copy Mixed Data Types", (int[]) { 1, 0xFF, 0x1234 }, 3 * sizeof(int), (int[]) { 1, 0xFF, 0x1234 }},
        {"Copy Bytes of Float", &float_array1[0], 4, (float[]) { 1.1f }},
        {"Copy Bytes of Integer", &int_array1[0], 4, (int[]) { 1 }},

        // Filler tests for 50
        {"Copy ASCII Characters", "ASCII", 5, "ASCII"},
        {"Copy Trailing Spaces", "space    ", 9, "space    "},
        {"Copy Hex Values", "\xDE\xAD\xBE\xEF", 4, "\xDE\xAD\xBE\xEF"},
        {"Copy Aligned Struct", &custom_struct, sizeof(custom_struct), &custom_struct},
        {"Copy Struct Padding", &custom_struct, 6, (unsigned char[]) { 42, 0, 0, 0, 'S', 't' }}
    };

    int total_tests = sizeof(test_cases) / sizeof(TestCase);

    // Run all test cases
    for (int i = 0; i < total_tests; i++) {
        run_test_case(test_cases[i]);
    }

    // Print summary
    printf("Pass Score: %d\n", pass);
    printf("Fail Score: %d\n", fail);

    return 0;
}

