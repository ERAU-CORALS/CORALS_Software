/**
 ********************************************************************************
 * @file    test_utilities.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Test Utility Functions
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __TEST_UTILITIES_HPP__
#define __TEST_UTILITIES_HPP__

#include <Arduino.h>

#define MAX_LINE_LENGTH 80
typedef enum __verification_type {
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    WITHIN_PERCENT,
    WITHIN_MARGIN
} verification_type_t;

typedef struct __test_results {
    unsigned int passed;
    unsigned int failed;
    unsigned int total;
} test_results_t;
static test_results_t __test_results __attribute__((unused)) = {0, 0, 0};

typedef struct __string_array {
    const char **array;
    size_t size;
} string_array_t;

typedef test_results_t (*test_function_t)(void);

#define verify_output(str) Serial.print(str)

void __TestPreamble(const char *testName, 
                    const char *testFile, 
                    const char *testDescription,
                    string_array_t testForLoopSets, 
                    string_array_t testPreconditionsList,
                    string_array_t testResultsList);
void __TestPostamble(const char *testName, 
                     test_results_t results);

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              int expected,
              int actual,
              test_results_t *results,
              verification_type_t type,
              double percent = 0,
              int margin = 0);
              
void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              unsigned long expected,
              unsigned long actual,
              test_results_t *results,
              verification_type_t type,
              double percent = 0,
              unsigned long margin = 0);

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              double expected,
              double actual,
              test_results_t *results,
              verification_type_t type,
              double percent = 0,
              double margin = 0);

void __Verify(const char *testFile,
              const int lineNumber,
              const char *valueName,
              const char *expected,
              const char *actual,
              test_results_t *results,
              verification_type_t type);

void Banner(const char* fmt, ...)
        __attribute__((format(printf, 1, 2)));
void Print(const char* fmt, ...)
        __attribute__((format(printf, 1, 2)));

void PrintLine();

#define TestPreamble(testDescription, testForLoopSets, testPreconditionsList, testResultsList) verify_output("\n"); \
                    string_array_t forLoopSets = {testForLoopSets, (testForLoopSets == NULL) ? 0 : sizeof(testForLoopSets) / sizeof(char*)}; \
                    string_array_t preconditionsList = {testPreconditionsList, (testPreconditionsList == NULL) ? 0 : sizeof(testPreconditionsList) / sizeof(char*)}; \
                    string_array_t resultsList = {testResultsList, (testResultsList == NULL) ? 0 : sizeof(testResultsList) / sizeof(char*)}; \
                    __TestPreamble(__func__, __FILE__, testDescription, forLoopSets, preconditionsList, resultsList); \
                    __test_results = {0, 0, 0};
#define TestPostamble() __TestPostamble(__func__, __test_results); \
                        verify_output("\n");
#define Verify(valueName, expected, actual, type) __Verify (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type);
#define Verify_Percent(valueName, expected, actual, percent_in) __Verify (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_PERCENT, percent_in);
#define Verify_Margin(valueName, expected, actual, margin_in) __Verify (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, 0.0,  margin_in);

#endif // __TEST_UTILITIES_HPP__