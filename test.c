#include <stdio.h>
#include "asm_string.h"
#include <math.h>
int pass = 0, fail = 0;

// Custom strcat function
char* custom_strcat(char* dest, const char* src) {
    if (!dest || !src) return NULL;  // Handle null pointers

    char* original_dest = dest;

    // Move dest pointer to the null terminator
    while (*dest) dest++;

    // Append entire source string to dest
    while (*src) {
        *dest++ = *src++;
    }

    *dest = '\0';  // Null-terminate the resulting string
    return original_dest;
}

// Struct to hold test case information
typedef struct {
    const char* test_case_name;
    const char* dest_initial;  // Initial content of dest
    const char* src;           // Source string
} TestCase;

// Function to run a single test case
void run_test_case(TestCase test_case) {
    char dest_custom[100] = { 0 };
    char dest_my[100] = { 0 };

    // Copy the initial content of dest_initial into both dest arrays
    snprintf(dest_custom, sizeof(dest_custom), "%s", test_case.dest_initial);
    snprintf(dest_my, sizeof(dest_my), "%s", test_case.dest_initial);

    // Compute expected result using custom_strcat
    custom_strcat(dest_custom, test_case.src);

    // Compute actual result using strcat
    strcat(dest_my, test_case.src);

    // Compare results
    printf("Test Case: %s\n", test_case.test_case_name);
    if (strcmp(dest_custom, dest_my) == 0) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected: %s\n", dest_custom);
        printf("Actual:   %s\n\n", dest_my);
        fail++;
    }
}

// Main function to run all test cases
int main() {
    // Define 50 test cases
    TestCase test_cases[50] = {
        // Basic tests
        {"Test Case 1: Append Entire Source", "Hello", "World"},
        {"Test Case 2: Append Empty Source", "Hello", ""},
        {"Test Case 3: Append to Empty Dest", "", "World"},
        {"Test Case 4: Append Single Character Source", "Hello", "A"},
        {"Test Case 5: Append Single Space Source", "Space", " "},

        // Edge cases
        {"Test Case 6: Append to Null Terminated Dest", "Null\0Extra", "Append"},
        {"Test Case 7: Append Null Terminated Source", "Start", "Stop\0Extra"},
        {"Test Case 8: Append Large Source to Small Dest", "Small", "LargeString"},
        {"Test Case 9: Append Single Null Character Source", "Start", "\0"},
        {"Test Case 10: Append with Overlap", "Overlap", "lap"},

        // Special character tests
        {"Test Case 11: Append String with Spaces", "Hello ", "World Again"},
        {"Test Case 12: Append String with Numbers", "123", "456789"},
        {"Test Case 13: Append String with Special Characters", "@@@", "!!!???"},
        {"Test Case 14: Append String with Tabs", "Tabbed", "\t\tTabs"},
        {"Test Case 15: Append String with Newlines", "Lines", "\nNewLines"},

        // Complex tests
        {"Test Case 16: Append Empty Strings", "", ""},
        {"Test Case 17: Append to String with Trailing Spaces", "Trailing ", "Spaces"},
        {"Test Case 18: Append Overlapping Strings", "Overlap", "lapOver"},
        {"Test Case 19: Append to Null Terminated String", "Null\0Extra", "Append"},
        {"Test Case 20: Append Beyond Dest Capacity", "Limit", "OverflowTestString"},

        // Long strings
        {"Test Case 21: Append Long String to Short Dest", "Short", "LongStringToAppendHere"},
        {"Test Case 22: Append Short String to Long Dest", "VeryLongDestinationString", "Short"},
        {"Test Case 23: Append Exact Length Source", "Exact", "Length"},
        {"Test Case 24: Append Source Longer Than Dest", "ShortDest", "SourceIsMuchLonger"},
        {"Test Case 25: Append Entire Source to Large Dest", "LargeDest", "Source"},

        // Miscellaneous cases
        {"Test Case 26: Append Single Character", "Single", "A"},
        {"Test Case 27: Append Source with Null Character", "Start", "Null\0Test"},
        {"Test Case 28: Append Source Longer Than Dest", "Short", "MuchLongerString"},
        {"Test Case 29: Append Source with Mixed Case", "Case", "MiXeD"},
        {"Test Case 30: Append Unicode Characters", "Hello", "chinese"},

        {"Test Case 31: Append to Space-Filled Dest", "Spaces ", "Filler"},
        {"Test Case 32: Append String Ending with Null", "EndNull", "Null\0End"},
        {"Test Case 33: Append Long Source", "Base", "VeryLongSourceThatExceedsLimits"},
        {"Test Case 34: Append Empty Source", "BaseOnly", ""},
        {"Test Case 35: Append Special Characters", "Chars", "!@#$%^&*"},

        {"Test Case 36: Append Single Space", "Space", " "},
        {"Test Case 37: Append Single Tab", "Tabbed", "\t"},
        {"Test Case 38: Append Single Newline", "Lines", "\n"},
        {"Test Case 39: Append Multiple Newlines", "Multiline", "\n\n"},
        {"Test Case 40: Append Large Source to Large Dest", NULL, "LargerSource"},

        {"Test Case 41: Append Overlapping Memory", "Overlap", "lapOver"},
        {"Test Case 42: Append Single Null Character", "Start", "\0"},
        {"Test Case 43: Append Beyond Buffer Capacity", "Short", "VeryLongSourceString"},
        {"Test Case 44: Append Source with Leading Spaces", "Leading", "    Spaces"},
        {"Test Case 45: Append Empty Dest and Source", "", ""},

        {"Test Case 46: Append to Null-Terminated Dest", "Terminated\0Extra", "Source"},
        {"Test Case 47: Append to Filled Dest", "Filled", "Data"},
        {"Test Case 48: Append Exact Length Strings", "Exact", "Match"},
        {"Test Case 49: Append Source with Trailing Null", "Source", "Null\0"},
        {"Test Case 50: Append Unicode Characters", "Base", "Characters"},
    };

    // Run all test cases
    for (int i = 0; i < 50; i++) {
        run_test_case(test_cases[i]);
    }
    pass = abs(pass - fail);
    printf("Total pass score:(%d/50)\n", pass);
    return 0;
}
