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

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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
        strncpy(line_buffer + left_padding - 1, content, strlen(content));
        verify_output(line_buffer);
        verify_output('\n');
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


void __Verify(const char *file, 
              int line, 
              const char *valueName, 
              bool expected, 
              bool actual, 
              test_results_t *results, 
              verification_type_t type) 
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %s...\n", valueName, expected ? "true" : "false");
            if (expected == actual) {
                Print("The expected value of ==%s has been verified.", expected ? "true" : "false");
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%s has not been verified.", expected ? "true" : "false");
                Print("The actual value was %s.", actual ? "true" : "false");
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %s...\n", valueName, expected ? "true" : "false");
            if (expected != actual) {
                Print("The expected value of !=%s has been verified.", expected ? "true" : "false");
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%s has not been verified.", expected ? "true" : "false");
                Print("The actual value was %s.", actual ? "true" : "false");
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Int(const char *file, 
                  int line, 
                  const char *valueName, 
                  int expected, 
                  int actual, 
                  test_results_t *results, 
                  verification_type_t type,
                  int delta)
{
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
        case WITHIN_MARGIN:
            Print("Verifying %s is within %d of %d...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %d +/- %d has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %d +/- %d has not been verified.", expected, delta);
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
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Long(const char *file, 
                   int line, 
                   const char *valueName, 
                   long expected, 
                   long actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   long delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %ld...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %ld...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %ld...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %ld...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %ld...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %ld...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        default: 
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_LongLong(const char *file, 
                       int line, 
                       const char *valueName, 
                       long long expected, 
                       long long actual, 
                       test_results_t *results, 
                       verification_type_t type,
                       long long delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %lld...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %lld...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %lld...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %lld...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %lld...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %lld...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        default: 
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Int8(const char *file, 
                   int line, 
                   const char *valueName, 
                   int8_t expected, 
                   int8_t actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   int8_t delta)
{
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
        case WITHIN_MARGIN:
            Print("Verifying %s is within %d of %d...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %d +/- %d has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %d +/- %d has not been verified.", expected, delta);
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
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Int16(const char *file, 
                   int line, 
                   const char *valueName, 
                   int16_t expected, 
                   int16_t actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   int16_t delta)
{
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
        case WITHIN_MARGIN:
            Print("Verifying %s is within %d of %d...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %d +/- %d has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %d +/- %d has not been verified.", expected, delta);
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
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Int32(const char *file, 
                   int line, 
                   const char *valueName, 
                   int32_t expected, 
                   int32_t actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   int32_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %ld...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %ld...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %ld...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %ld...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %ld...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %ld...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%ld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%ld has not been verified.", expected);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %ld of %ld...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %ld +/- %ld has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %ld +/- %ld has not been verified.", expected, delta);
                Print("The actual value was %ld.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Int64(const char *file, 
                   int line, 
                   const char *valueName, 
                   int64_t expected, 
                   int64_t actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   int64_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %lld...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %lld...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %lld...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %lld...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %lld...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %lld...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%lld has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%lld has not been verified.", expected);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %lld of %lld...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %lld +/- %lld has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %lld +/- %lld has not been verified.", expected, delta);
                Print("The actual value was %lld.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_UInt(const char *file,
                   int line,
                   const char *valueName,
                   unsigned int expected,
                   unsigned int actual,
                   test_results_t *results,
                   verification_type_t type,
                   unsigned int delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %u...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %u...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %u...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %u...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %u...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %u...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %u of %u...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %u +/- %u has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %u +/- %u has not been verified.", expected, delta);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_ULong(const char *file,
                    int line,
                    const char *valueName,
                    unsigned long expected,
                    unsigned long actual,
                    test_results_t *results,
                    verification_type_t type,
                    unsigned long delta)
{
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
        case WITHIN_MARGIN:
            Print("Verifying %s is within %lu of %lu...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %lu +/- %lu has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %lu +/- %lu has not been verified.", expected, delta);
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
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_ULongLong(const char *file,
                        int line,
                        const char *valueName,
                        unsigned long long expected,
                        unsigned long long actual,
                        test_results_t *results,
                        verification_type_t type,
                        unsigned long long delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %llu...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %llu...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %llu...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %llu...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %llu...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %llu...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %llu of %llu...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %llu +/- %llu has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %llu +/- %llu has not been verified.", expected, delta);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_UInt8(const char *file,
                   int line,
                   const char *valueName,
                   uint8_t expected,
                   uint8_t actual,
                   test_results_t *results,
                   verification_type_t type,
                   uint8_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %u...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %u...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %u...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %u...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %u...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %u...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %u of %u...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %u +/- %u has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %u +/- %u has not been verified.", expected, delta);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_UInt16(const char *file,
                   int line,
                   const char *valueName,
                   uint16_t expected,
                   uint16_t actual,
                   test_results_t *results,
                   verification_type_t type,
                   uint16_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %u...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %u...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %u...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %u...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %u...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %u...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %u of %u...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %u +/- %u has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %u +/- %u has not been verified.", expected, delta);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_UInt32(const char *file,
                   int line,
                   const char *valueName,
                   uint32_t expected,
                   uint32_t actual,
                   test_results_t *results,
                   verification_type_t type,
                   uint32_t delta)
{
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
        case WITHIN_MARGIN:
            Print("Verifying %s is within %lu of %lu...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %lu +/- %lu has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %lu +/- %lu has not been verified.", expected, delta);
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
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_UInt64(const char *file,
                     int line,
                     const char *valueName,
                     uint64_t expected,
                     uint64_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     uint64_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %llu...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %llu...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %llu...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %llu...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %llu...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %llu...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%llu has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%llu has not been verified.", expected);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %llu of %llu...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %llu +/- %llu has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %llu +/- %llu has not been verified.", expected, delta);
                Print("The actual value was %llu.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Size_t(const char *file,
                     int line,
                     const char *valueName,
                     size_t expected,
                     size_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     size_t delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");
    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %u...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %u...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %u...\n", valueName, expected);
            if (actual > expected) {
                Print("The expected value of >%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %u...\n", valueName, expected);
            if (actual >= expected) {
                Print("The expected value of >=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %u...\n", valueName, expected);
            if (actual < expected) {
                Print("The expected value of <%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %u...\n", valueName, expected);
            if (actual <= expected) {
                Print("The expected value of <=%u has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%u has not been verified.", expected);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %u of %u...\n", valueName, delta, expected);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %u +/- %u has been verified.", expected, delta);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %u +/- %u has not been verified.", expected, delta);
                Print("The actual value was %u.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Char(const char *file,
                   int line,
                   const char *valueName,
                   char expected,
                   char actual,
                   test_results_t *results,
                   verification_type_t type)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %c...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%c has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%c has not been verified.", expected);
                Print("The actual value was %c.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %c...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%c has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%c has not been verified.", expected);
                Print("The actual value was %c.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Ptr(const char *file,
                  int line,
                  const char *valueName,
                  void *expected,
                  void *actual,
                  test_results_t *results,
                  verification_type_t type)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %p...\n", valueName, expected);
            if (expected == actual) {
                Print("The expected value of ==%p has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%p has not been verified.", expected);
                Print("The actual value was %p.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %p...\n", valueName, expected);
            if (expected != actual) {
                Print("The expected value of !=%p has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%p has not been verified.", expected);
                Print("The actual value was %p.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_String(const char *file,
                     int line,
                     const char *valueName,
                     const char *expected,
                     const char *actual,
                     test_results_t *results,
                     verification_type_t type)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %s...\n", valueName, expected);
            if (strcmp(expected, actual) == 0) {
                Print("The expected value of ==%s has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%s has not been verified.", expected);
                Print("The actual value was %s.", actual);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %s...\n", valueName, expected);
            if (strcmp(expected, actual) != 0) {
                Print("The expected value of !=%s has been verified.", expected);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%s has not been verified.", expected);
                Print("The actual value was %s.", actual);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Double(const char *file,
                     int line,
                     const char *valueName,
                     double expected,
                     double actual,
                     test_results_t *results,
                     verification_type_t type,
                     double delta)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    char expected_str[(int)ceil(log10(expected)) + 9];
    char actual_str[(int)ceil(log10(actual)) + 9];
    char delta_str[(int)ceil(log10(delta)) + 9];

    dtostrf(expected, 0, 6, expected_str);
    dtostrf(actual, 0, 6, actual_str);
    dtostrf(delta, 0, 6, delta_str);

    switch (type) {
        case EQUAL:
            Print("Verifying %s is equal to %s...\n", valueName, expected_str);
            if (expected == actual) {
                Print("The expected value of ==%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of ==%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case NOT_EQUAL:
            Print("Verifying %s is not equal to %s...\n", valueName, expected_str);
            if (expected != actual) {
                Print("The expected value of !=%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of !=%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case GREATER_THAN:
            Print("Verifying %s is greater than %s...\n", valueName, expected_str);
            if (actual > expected) {
                Print("The expected value of >%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case GREATER_THAN_OR_EQUAL:
            Print("Verifying %s is greater than or equal to %s...\n", valueName, expected_str);
            if (actual >= expected) {
                Print("The expected value of >=%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of >=%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case LESS_THAN:
            Print("Verifying %s is less than %s...\n", valueName, expected_str);
            if (actual < expected) {
                Print("The expected value of <%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case LESS_THAN_OR_EQUAL:
            Print("Verifying %s is less than or equal to %s...\n", valueName, expected_str);
            if (actual <= expected) {
                Print("The expected value of <=%s has been verified.", expected_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of <=%s has not been verified.", expected_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        case WITHIN_MARGIN:
            Print("Verifying %s is within %s of %s...\n", valueName, delta_str, expected_str);
            if (actual >= expected - delta && actual <= expected + delta) {
                Print("The expected value of %s +/- %s has been verified.", expected_str, delta_str);
                results->passed++;
                passed = true;
            }
            else {
                Print("The expected value of %s +/- %s has not been verified.", expected_str, delta_str);
                Print("The actual value was %s.", actual_str);
                results->failed++;
            }
        break;
        default:
            Print("Invalid verification type.");
            results->failed++;
        break;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

    verify_output("\n");
}

void __Verify_Memory(const char *file,
                     int line,
                     const char *valueName,
                     const void *expected,
                     const void *actual,
                     size_t size,
                     test_results_t *results)
{
    results->total++;
    bool passed = false;
    verify_output("\n");

    if (memcmp(expected, actual, size) == 0) {
        Print("The expected value of %s has been verified.", valueName);
        results->passed++;
        passed = true;
    }
    else {
        Print("The expected value of %s has not been verified.", valueName);
        results->failed++;
    }

    if (passed) PrintPass(results->total);
    else PrintFail(results->total, line, file);

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