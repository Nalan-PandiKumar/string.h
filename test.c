#include <stdio.h>
#include "asm_string.h"

// Custom implementation of strtok
char* custom_strtok(char* str, const char* delim) {
    static char* saved_str = NULL;

    if (str == NULL) {
        str = saved_str;
    }

    // If no string to process, return NULL
    if (str == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*str && strchr(delim, *str)) {
        ++str;
    }

    // If end of string is reached, return NULL
    if (*str == '\0') {
        saved_str = NULL;
        return NULL;
    }

    // Start of the token
    char* token_start = str;

    // Find the end of the token
    while (*str && !strchr(delim, *str)) {
        ++str;
    }

    // Null-terminate the token if a delimiter is found
    if (*str) {
        *str = '\0';
        saved_str = str + 1;
    }
    else {
        saved_str = NULL;
    }

    return token_start;
}

// Test case structure
typedef struct {
    const char* test_case_name;
    char input[100];
    const char* delim;
    const char* expected_tokens[15]; // Expected tokens (up to 10 tokens per case)
} TestCase;

int pass = 0, fail = 0;

// Run a single test case
void run_test_case(TestCase test_case) {
    printf("Test Case: %s\n", test_case.test_case_name);

    char input_copy[100];
    strcpy(input_copy, test_case.input); // Preserve original input

    char* token = strtok(input_copy, test_case.delim);
    int token_index = 0;
    int is_pass = 1;

    while (token != NULL || test_case.expected_tokens[token_index] != NULL) {
        const char* expected = test_case.expected_tokens[token_index];

        if ((token == NULL && expected != NULL) || (token != NULL && expected == NULL) ||
            (token != NULL && strcmp(token, expected) != 0)) {
            is_pass = 0;
            break;
        }

        token = strtok(NULL, test_case.delim);
        token_index++;
    }

    if (is_pass) {
        printf("Test Passed\n\n");
        pass++;
    }
    else {
        printf("Test Failed\n");
        printf("Expected Tokens: ");
        for (int i = 0; test_case.expected_tokens[i] != NULL; i++) {
            printf("%s ", test_case.expected_tokens[i]);
        }
        printf("\nActual Tokens:   ");
        strcpy(input_copy, test_case.input);
        token = strtok(input_copy, test_case.delim);
        while (token != NULL) {
            printf("%s ", token);
            token = strtok(NULL, test_case.delim);
        }
        printf("\n\n");
        fail++;
    }
}

int main() {
    // Define test cases
    TestCase test_cases[] = {
        {"Basic tokenization", "hello,world", ",", {"hello", "world", NULL}},
        {"Single delimiter", "a,b,c", ",", {"a", "b", "c", NULL}},
        {"Multiple delimiters", "a,,b,,c", ",", {"a", "b", "c", NULL}},
        {"Leading delimiters", ",,a,b,c", ",", {"a", "b", "c", NULL}},
        {"Trailing delimiters", "a,b,c,,", ",", {"a", "b", "c", NULL}},
        {"Spaces as delimiters", "a b c", " ", {"a", "b", "c", NULL}},
        {"Mixed delimiters", "a,b c", ", ", {"a", "b", "c", NULL}},
        {"Only delimiters", ",,,,", ",", {NULL}},
        {"No delimiters", "abc", ",", {"abc", NULL}},
        {"Empty input", "", ",", {NULL}},
        {"Empty delimiter", "abc", "", {"abc", NULL}},
        {"Numbers and letters", "123abc456", "abc", {"123", "456", NULL}},
        {"Special characters", "!@#abc$%^", "abc", {"!@#", "$%^", NULL}},
        {"Mixed whitespace", " a b\tc\n", " \t\n", {"a", "b", "c", NULL}},
        {"Case-sensitive tokens", "Hello,world", ",", {"Hello", "world", NULL}},
        {"Repeating single character", "aaa", "a", {NULL}},
        {"Nested delimiters", "a,b,,c", ",", {"a", "b", "c", NULL}},
        {"Non-printable characters", "a\x01\x02", "\x01\x02", {"a", NULL}},
        {"Escape sequences", "a\\nb\\tc", "\\nt", {"a", "b", "c", NULL}},
        {"Long string", "a,b,c,d,e,f,g,h,i,j", ",", {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", NULL}},
        {"Delimiter at start and end", ",a,b,c,", ",", {"a", "b", "c", NULL}},
        {"Multiple space tokens", "  a   b  c ", " ", {"a", "b", "c", NULL}},
        {"Delimiter as part of token", "a,b,c,", ",", {"a", "b", "c", NULL}},
        {"Mixed alphanumeric", "123,abc,456", ",", {"123", "abc", "456", NULL}},
        {"Mixed symbols", "a@b#c", "@#", {"a", "b", "c", NULL}},
        {"Digits only", "123,456", ",", {"123", "456", NULL}},
        {"Tokens with spaces", "a b , c d", ", ", {"a", "b", "c", "d", NULL}},
        {"Delimiter overlap", "aaabaaa", "aaa", {"b", NULL}},
        {"Tab-separated", "a\tb\tc", "\t", {"a", "b", "c", NULL}},
        {"Newline-separated", "a\nb\nc", "\n", {"a", "b", "c", NULL}},
        {"Single-character string", "a", ",", {"a", NULL}},
        {"Delimiter-only string", ",", ",", {NULL}},
        {"Tokens with punctuation", "a.b,c!", ",.!?", {"a", "b", "c", NULL}},
        {"Token length variation", "a,abc,abcd", ",", {"a", "abc", "abcd", NULL}},
        {"Consecutive delimiters", "a,,b,c", ",", {"a", "b", "c", NULL}},
        {"Complex input", "a,b;c.d", ",;.", {"a", "b", "c", "d", NULL}},
        {"Numeric tokens", "123,456,789", ",", {"123", "456", "789", NULL}},
        {"Partial token overlap", "abcabcabc", "abc", {NULL}},
        {"Repeated delimiters", "a,,,b", ",", {"a", "b", NULL}},
        {"Delimiter with spaces", "a , b , c", ", ", {"a", "b", "c", NULL}},
        {"Mixed case tokens", "a,A,b,B", ",", {"a", "A", "b", "B", NULL}},
    };

    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; i++) {
        run_test_case(test_cases[i]);
    }

    printf("Total Passed: %d\n", pass);
    printf("Total Failed: %d\n", fail);

    return 0;
}
