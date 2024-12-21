#include <stdio.h>
#include <math.h>
#include "asm_string.h"

// Custom implementation of strstr
char* custom_strstr(const char* haystack, const char* needle) {
    if (!haystack || !needle) return NULL; // Null check
    if (*needle == '\0') return (char*)haystack; // Empty needle

    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;

        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') return (char*)haystack; // Match found
        haystack++;
    }

    return NULL; // No match found
}

// Test case structure
typedef struct {
    const char* test_case_name;
    const char* haystack;
    const char* needle;
    const char* expected_result;
} TestCase;

int pass = 0, fail = 0;

// Run a single test case
void run_test_case(TestCase test_case) {
    char* actual_result = custom_strstr(test_case.haystack, test_case.needle);
    const char* expected_result = strstr(test_case.haystack, test_case.needle);

    printf("Test Case: %s\n", test_case.test_case_name);
    if (actual_result == expected_result ||
        (actual_result && expected_result && strcmp(actual_result, expected_result) == 0)) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected: %s\n", expected_result ? expected_result : "NULL");
        printf("Actual:   %s\n\n", actual_result ? actual_result : "NULL");
        fail++;
    }
}

int main() {
    // Define test cases
    TestCase test_cases[] = {
        // Basic test cases
        {"Basic match in the middle", "hello world", "world", "world"},
        {"Basic match at start", "hello world", "hello", "hello world"},
        {"Basic match at end", "hello world", "d", "d"},
        {"No match", "hello world", "test", NULL},
        {"Empty needle", "hello world", "", "hello world"},

        // Edge cases
        {"Empty haystack and needle", "", "", ""},
        {"Empty haystack", "", "test", NULL},
        {"Long needle", "short", "longneedle", NULL},

        // Case sensitivity
        {"Case-sensitive match", "Hello World", "World", "World"},
        {"Case-sensitive no match", "Hello World", "world", NULL},

        // Substring of a word
        {"Substring in middle of word", "abcdef", "cde", "cdef"},
        {"Substring at start", "abcdef", "abc", "abcdef"},
        {"Substring at end", "abcdef", "def", "def"},

        // Multiple occurrences
        {"Multiple matches", "abababab", "aba", "ababab"},
        {"Overlapping matches", "aaaaa", "aaa", "aaaa"},

        // Special characters
        {"Special character match", "abc$%^&*", "$%", "$%^&*"},
        {"Special character no match", "abc$%^&*", "@", NULL},

        // Numbers
        {"Numeric substring", "1234567890", "456", "4567890"},
        {"No numeric match", "1234567890", "987", NULL},

        // Non-printable characters
        {"Non-printable character match", "hello\x01world", "\x01", "\x01world"},
        {"Non-printable character no match", "hello\x01world", "\x02", NULL},

        // Escape sequences
        {"Escape character match", "hello\nworld", "\n", "\nworld"},
        {"Escape character no match", "hello\nworld", "\t", NULL},

        // Single-character needles
        {"Single character match", "abcdef", "c", "cdef"},
        {"Single character no match", "abcdef", "z", NULL},

        // Large strings
        {"Match in large string", "aaaaaaaaaaaaaaaaaaaab", "b", "b"},
        {"No match in large string", "aaaaaaaaaaaaaaaaaaaa", "b", NULL},

        // Long needles and haystacks
        {"Match long needle in long haystack", "thisisaverylongstringwithmanycharacters", "string", "stringwithmanycharacters"},
        {"No match long needle in long haystack", "thisisaverylongstringwithmanycharacters", "none", NULL},

        // Unicode characters
        {"Unicode match", "helloworld", "", "world"},
        {"Unicode no match", "helloworld", "", NULL},

        // Repeated patterns
        {"Repeated pattern match", "abababababab", "abab", "ababababab"},
        {"Repeated pattern no match", "abababababab", "abc", NULL},

        // Null haystack or needle
        {"Null haystack", "NULL", "test", NULL},
        {"Null needle", "hello world", "NULL", NULL},

        // Mixed cases
        {"Mixed case match", "HelloWorld", "World", "World"},
        {"Mixed case no match", "HelloWorld", "world", NULL},

        // Overlapping partial matches
        {"Overlapping partial match", "aaabaaa", "aaa", "aaabaaa"},
        {"Overlapping partial no match", "aaabaaa", "aaaa", NULL},

        // Strings with digits and characters
        {"Digits and characters match", "abc123", "123", "123"},
        {"Digits and characters no match", "abc123", "456", NULL},

        // Escaped sequences
        {"Escaped sequence match", "hello\\nworld", "\\n", "\\nworld"},
        {"Escaped sequence no match", "hello\\nworld", "\\t", NULL},

        // Searching entire string
        {"Match entire string", "abcdef", "abcdef", "abcdef"},
        {"No match with extra character", "abcdef", "abcdefg", NULL},

        // Partial matches
        {"Partial match start mismatch", "abcdef", "abz", NULL},
        {"Partial match end mismatch", "abcdef", "abcz", NULL},

        // Repeating single character
        {"Repeating character match", "aaaaaa", "aaa", "aaaaaa"},
        {"Repeating character no match", "aaaaaa", "aab", NULL},

        // Large haystack and needle
        {"Large haystack", "aaaaaaaaaaaaaaab", "ab", "ab"},
        {"Large needle not in haystack", "aaaaaaaaaaaaaaaa", "ba", NULL},
    };

    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    // Run test cases
    system("color a");
    for (int i = 0; i < num_test_cases; i++) {
        run_test_case(test_cases[i]);
        system("python d:/sleep.py");
    }

    // Print summary
    printf("Total Pass Score: (%d/51)\n", abs(pass - fail));

    return 0;
}
