/**
 ********************************************************************************
 * @file    test_utilities.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Test Utility Functions
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "test_utilities.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void PrintLine();
void BlockPrint(const char *content);
inline void PrintPass(int testNumber);
inline void PrintFail(int testNumber, int lineNumber, const char *fileName);

void Banner(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char temp[1];
    unsigned const int contentLength = vsnprintf(temp, 0, fmt, args) + 1;
    char content[contentLength + 1];
    vsnprintf(content, contentLength, fmt, args);
    va_end(args);
    
    PrintLine();

    if (strlen(content) <= MAX_LINE_LENGTH) {
        char line_buffer[MAX_LINE_LENGTH + 1];
        const uint8_t left_padding = (MAX_LINE_LENGTH - strlen(content)) / 2;
        for (uint8_t i = 0; i < left_padding; i++) {
            line_buffer[i] = (left_padding > 2) && (i < left_padding - 2) ? '-' : ' ';
        }
        for (uint8_t i = strlen(line_buffer) + 2; i < MAX_LINE_LENGTH; i++) {
            line_buffer[i] = '-';
        }
        strcpy(line_buffer + left_padding, content);
        verify_output(line_buffer);
    }
    else {
        verify_output('\n');
        BlockPrint(content);
        verify_output('\n');
    }

    PrintLine();
}

void Print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char temp[1];
    unsigned const int contentLength = vsnprintf(temp, 0, fmt, args) + 1;
    char content[contentLength + 1];
    vsnprintf(content, contentLength, fmt, args);
    va_end(args);

    if (strlen(content) <= MAX_LINE_LENGTH) {
        verify_output(content);
        verify_output('\n');
    }
    else {
        BlockPrint(content);
    }
}

void __TestPreamble(const char *testName, 
                    const char *testFile, 
                    const char *testDescription,
                    string_array_t testForLoopSets, 
                    string_array_t testPreconditionsList,
                    string_array_t testResultsList) {
    PrintLine();
    verify_output("\n");

    Print("\tTest Name: %s", testName);
    Print("\tFile: %s", testFile);
    verify_output("\n");
    
    verify_output("\tFUNCTIONAL DESCRIPTION:\n");
    Print("%s", testDescription);
    verify_output("\n");

    verify_output("\tCONDITIONS:\n");
    if (testForLoopSets.array != NULL) {
        verify_output("\tFOR:\n");
        for (size_t i = 0; i < testForLoopSets.size; i++) {
            Print("\t\t- %s", testForLoopSets.array[i]);
        }
        verify_output("\n");
    }
    if (testPreconditionsList.array != NULL) {
        verify_output("\tWITH:\n");
        for (size_t i = 0; i < testPreconditionsList.size; i++) {
            Print("\t\t- %s", testPreconditionsList.array[i]);
        }
        verify_output("\n");
    }
    if (testResultsList.array != NULL) {
        verify_output("\tExpected Results:\n");
        for (size_t i = 0; i < testResultsList.size; i++) {
            Print("\t\t- %s", testResultsList.array[i]);
        }
        verify_output("\n");
    }

    PrintLine();
}

void __TestPostamble(const char *testName, 
                     test_results_t results) {
    PrintLine();
    verify_output("\n");

    Print("Test Results for %s:", testName);
    Print("\t%d Test Points\n", results.total);

    Print("\t%d Passed\n", results.passed);
    Print("\t%d Failed\n", results.failed);

    PrintLine();
}

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              int expected,
              int actual,
              test_results_t *results,
              verification_type_t type,
              double percent,
              int margin) {
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %d...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %d...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %d...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %d...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case LESS_THAN:
            Print("Verifying %s is less than %d...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %d...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%d has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%d has not been verified.", expected);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case WITHIN_PERCENT:
            Print("Verifying %s is within %.2lf%% of %d...\n", valueName, percent * 100, expected);
            if (actual >= expected * (1 - percent) && actual <= expected * (1 + percent)) {
                Print("The expected value of %d +/- %.2lf has been verified.", expected, percent * 100);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %d +/- %.2lf has not been verified.", expected, percent * 100);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %d of %d...\n", valueName, margin, expected);
            if (actual >= expected - margin && actual <= expected + margin) {
                Print("The expected value of %d +/- %d has been verified.", expected, margin);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %d +/- %d has not been verified.", expected, margin);
                Print("The actual value was %d.", actual);
                results->failed++;
            }
            break;
        default:
            Print("Invalid verification type.");
            results->failed++;
            break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, lineNumber, testFile);

    verify_output("\n");
}

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              unsigned long expected,
              unsigned long actual,
              test_results_t *results,
              verification_type_t type,
              double percent,
              unsigned long margin) {
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %lu...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %lu...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %lu...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %lu...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case LESS_THAN:
            Print("Verifying %s is less than %lu...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %lu...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%lu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%lu has not been verified.", expected);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case WITHIN_PERCENT:
            Print("Verifying %s is within %.2lf%% of %lu...\n", valueName, percent * 100, expected);
            if (actual >= expected * (1 - percent) && actual <= expected * (1 + percent)) {
                Print("The expected value of %lu +/- %.2lf has been verified.", expected, percent * 100);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %lu +/- %.2lf has not been verified.", expected, percent * 100);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %lu of %lu...\n", valueName, margin, expected);
            if (actual >= expected - margin && actual <= expected + margin) {
                Print("The expected value of %lu +/- %lu has been verified.", expected, margin);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %lu +/- %lu has not been verified.", expected, margin);
                Print("The actual value was %lu.", actual);
                results->failed++;
            }
            break;
        default:
            Print("Invalid verification type.");
            results->failed++;
            break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, lineNumber, testFile);

    verify_output("\n");
}

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              double expected,
              double actual,
              test_results_t *results,
              verification_type_t type,
              double percent,
              double margin) {
    results->total++;
    bool passed = false;
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %.2lf...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of ==%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %.2lf...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of !=%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %.2lf...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of >%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %.2lf...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of >=%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case LESS_THAN:
            Print("Verifying %s is less than %.2lf...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of <%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %.2lf...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%.2lf has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of <=%.2lf has not been verified.", expected);
                Print("The actual value was %.2lf.", actual);
            }
            break;
        case WITHIN_PERCENT:
            Print("Verifying %s is within %.2lf%% of %.2lf...\n", valueName, percent * 100, expected);
            if (actual >= expected * (1 - percent) && actual <= expected * (1 + percent)) {
                Print("The expected value of %.2lf +/- %.2lf has been verified.", expected, percent * 100);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %.2lf +/- %.2lf has not been verified.", expected, percent * 100);
                Print("The actual value was %.2lf.", actual);
                results->failed++;
            }
            break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %.2lf of %.2lf...\n", valueName, margin, expected);
            if (actual >= expected - margin && actual <= expected + margin) {
                Print("The expected value of %.2lf +/- %.2lf has been verified.", expected, margin);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %.2lf +/- %.2lf has not been verified.", expected, margin);
                Print("The actual value was %.2lf.", actual);
                results->failed++;
            }
            break;
        default:
            Print("Invalid verification type.");
            break;
    }

    if (passed) {
        PrintPass(results->total);
        results->passed++;
    }
    else {
        PrintFail(results->total, lineNumber, testFile);
        results->failed++;
    }

    verify_output("\n");
}

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              const char *expected,
              const char *actual,
              test_results_t *results,
              verification_type_t type) {
    results->total++;
    bool passed = false;
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to \"%s\"...\n", valueName, expected);
            if (strcmp(expected, actual) == 0) {
                Print("The expected value of ==\"%s\" has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of ==\"%s\" has not been verified.", expected);
                Print("The actual value was %s.", actual);
            }
            break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to \"%s\"...\n", valueName, expected);
            if (strcmp(expected, actual) != 0) {
                Print("The expected value of !=%s has been verified.", expected);
                passed = true;
            }
            else {
                Print("The expected value of !=%s has not been verified.", expected);
                Print("The actual value was %s.", actual);
            }
            break;
        default:
            Print("Invalid verification type.");
            break;
    }

    if (passed) {
        PrintPass(results->total);
        results->passed++;
    }
    else {
        PrintFail(results->total, lineNumber, testFile);
        results->failed++;
    }

    verify_output("\n");
}

void PrintLine() {
    for (uint8_t i = 0; i < MAX_LINE_LENGTH; i++) {
        verify_output('-');
    }
    verify_output('\n');
}

void BlockPrint(const char *content) {
    char line_buffer[MAX_LINE_LENGTH + 2];
    char *line_buffer_ptr = line_buffer;
    char *content_ptr = (char *)content;
    uint8_t line_length = 0;

    while (strlen(content_ptr) > MAX_LINE_LENGTH) {

        // Copy a line of test from the content to the line buffer
        strncpy(line_buffer_ptr, content_ptr, MAX_LINE_LENGTH);
        line_buffer_ptr[MAX_LINE_LENGTH + 1] = '\0';
        
        // Redact Line to last whitespace
        line_length = strlen(line_buffer_ptr);
        int itermax = (MAX_LINE_LENGTH < line_length) ? MAX_LINE_LENGTH : line_length;
        for (int i = itermax; i >= 0 && !isspace(line_buffer_ptr[i]); i--) continue;
        line_length = strlen(line_buffer_ptr);

        // Print the line buffer
        verify_output(line_buffer_ptr);
        verify_output('\n');

        // Move the content pointer to the next line
        content_ptr += line_length;
    }

    // Print the last line
    verify_output(content_ptr);
}


inline void PrintPass(int testNumber) {
    Print("\t(X) Pass\t( ) Fail\t[%d]", testNumber);
}

inline void PrintFail(int testNumber, int lineNumber, const char *fileName) {
    Print("\t( ) Pass\t(X) Fail\t[%d] [line %d in %s]", testNumber, lineNumber, fileName);
}