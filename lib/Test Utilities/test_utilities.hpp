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

#include <stdint.h>

#define MAX_LINE_LENGTH 80
typedef enum __verification_type {
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
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

// Verification Functions
void __Verify(const char *file, 
              int line, 
              const char *valueName, 
              bool expected, 
              bool actual, 
              test_results_t *results, 
              verification_type_t type);
void __Verify_Int(const char *file, 
                  int line, 
                  const char *valueName, 
                  int expected, 
                  int actual, 
                  test_results_t *results, 
                  verification_type_t type,
                  int delta);
void __Verify_Long(const char *file, 
                   int line, 
                   const char *valueName, 
                   long expected, 
                   long actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   long delta);
void __Verify_LongLong(const char *file, 
                       int line, 
                       const char *valueName, 
                       long long expected, 
                       long long actual, 
                       test_results_t *results, 
                       verification_type_t type,
                       long long delta);
void __Verify_Int8(const char *file, 
                   int line, 
                   const char *valueName, 
                   int8_t expected, 
                   int8_t actual, 
                   test_results_t *results, 
                   verification_type_t type,
                   int8_t delta);
void __Verify_Int16(const char *file, 
                    int line, 
                    const char *valueName, 
                    int16_t expected, 
                    int16_t actual, 
                    test_results_t *results, 
                    verification_type_t type,
                    int16_t delta);
void __Verify_Int32(const char *file,
                    int line,
                    const char *valueName,
                    int32_t expected,
                    int32_t actual,
                    test_results_t *results,
                    verification_type_t type,
                    int32_t delta);
void __Verify_Int64(const char *file,
                    int line,
                    const char *valueName,
                    int64_t expected,
                    int64_t actual,
                    test_results_t *results,
                    verification_type_t type,
                    int64_t delta);
void __Verify_UInt(const char *file,
                   int line,
                   const char *valueName,
                   unsigned int expected,
                   unsigned int actual,
                   test_results_t *results,
                   verification_type_t type,
                   unsigned int delta);
void __Verify_ULong(const char *file,
                    int line,
                    const char *valueName,
                    unsigned long expected,
                    unsigned long actual,
                    test_results_t *results,
                    verification_type_t type,
                    unsigned long delta);
void __Verify_ULongLong(const char *file,
                        int line,
                        const char *valueName,
                        unsigned long long expected,
                        unsigned long long actual,
                        test_results_t *results,
                        verification_type_t type,
                        unsigned long long delta);
void __Verify_UInt8(const char *file,
                    int line,
                    const char *valueName,
                    uint8_t expected,
                    uint8_t actual,
                    test_results_t *results,
                    verification_type_t type,
                    uint8_t delta);
void __Verify_UInt16(const char *file,
                     int line,
                     const char *valueName,
                     uint16_t expected,
                     uint16_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     uint16_t delta);
void __Verify_UInt32(const char *file,
                     int line,
                     const char *valueName,
                     uint32_t expected,
                     uint32_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     uint32_t delta);
void __Verify_UInt64(const char *file,
                     int line,
                     const char *valueName,
                     uint64_t expected,
                     uint64_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     uint64_t delta);
void __Verify_Size_t(const char *file,
                     int line,
                     const char *valueName,
                     size_t expected,
                     size_t actual,
                     test_results_t *results,
                     verification_type_t type,
                     size_t delta);

void __Verify_Char(const char *file,
                   int line,
                   const char *valueName,
                   char expected,
                   char actual,
                   test_results_t *results,
                   verification_type_t type);
void __Verify_Ptr(const char *file,
                  int line,
                  const char *valueName,
                  void *expected,
                  void *actual,
                  test_results_t *results,
                  verification_type_t type);
void __Verify_String(const char *file,
                     int line,
                     const char *valueName,
                     const char *expected,
                     const char *actual,
                     test_results_t *results,
                     verification_type_t type);

void __Verify_Float(const char *file,
                    int line,
                    const char *valueName,
                    float expected,
                    float actual,
                    test_results_t *results,
                    verification_type_t type,
                    float delta);
void __Verify_Double(const char *file,
                     int line,
                     const char *valueName,
                     double expected,
                     double actual,
                     test_results_t *results,
                     verification_type_t type,
                     double delta);

void __Verify_Memory(const char *file,
                     int line,
                     const char *valueName,
                     const void *expected,
                     const void *actual,
                     size_t size,
                     test_results_t *results);

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

#define Verify(valueName, expected, actual, type) __Verify (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type)
#define Verify_Int(valueName, expected, actual, type) __Verify_Int (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Long(valueName, expected, actual, type) __Verify_Long (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_LongLong(valueName, expected, actual, type) __Verify_LongLong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Int8(valueName, expected, actual, type) __Verify_Int8 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Int16(valueName, expected, actual, type) __Verify_Int16 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Int32(valueName, expected, actual, type) __Verify_Int32 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Int64(valueName, expected, actual, type) __Verify_Int64 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_UInt(valueName, expected, actual, type) __Verify_UInt (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_ULong(valueName, expected, actual, type) __Verify_ULong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_ULongLong(valueName, expected, actual, type) __Verify_ULongLong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_UInt8(valueName, expected, actual, type) __Verify_UInt8 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_UInt16(valueName, expected, actual, type) __Verify_UInt16 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_UInt32(valueName, expected, actual, type) __Verify_UInt32 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_UInt64(valueName, expected, actual, type) __Verify_UInt64 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Size_t(valueName, expected, actual, type) __Verify_Size_t (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Char(valueName, expected, actual, type) __Verify_Char (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type)
#define Verify_Ptr(valueName, expected, actual, type) __Verify_Ptr (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type)
#define Verify_String(valueName, expected, actual, type) __Verify_String (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type)
#define Verify_Float(valueName, expected, actual, type) __Verify_Float (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)
#define Verify_Double(valueName, expected, actual, type) __Verify_Double (__FILE__, __LINE__, valueName, expected, actual, &__test_results, type, 0)

#define Verify_Int_Within(valueName, expected, actual, delta) __Verify_Int (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Long_Within(valueName, expected, actual, delta) __Verify_Long (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_LongLong_Within(valueName, expected, actual, delta) __Verify_LongLong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Int8_Within(valueName, expected, actual, delta) __Verify_Int8 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Int16_Within(valueName, expected, actual, delta) __Verify_Int16 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Int32_Within(valueName, expected, actual, delta) __Verify_Int32 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Int64_Within(valueName, expected, actual, delta) __Verify_Int64 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_UInt_Within(valueName, expected, actual, delta) __Verify_UInt (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_ULong_Within(valueName, expected, actual, delta) __Verify_ULong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_ULongLong_Within(valueName, expected, actual, delta) __Verify_ULongLong (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_UInt8_Within(valueName, expected, actual, delta) __Verify_UInt8 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_UInt16_Within(valueName, expected, actual, delta) __Verify_UInt16 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_UInt32_Within(valueName, expected, actual, delta) __Verify_UInt32 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_UInt64_Within(valueName, expected, actual, delta) __Verify_UInt64 (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Size_t_Within(valueName, expected, actual, delta) __Verify_Size_t (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Float_Within(valueName, expected, actual, delta) __Verify_Float (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)
#define Verify_Double_Within(valueName, expected, actual, delta) __Verify_Double (__FILE__, __LINE__, valueName, expected, actual, &__test_results, WITHIN_MARGIN, delta)

#define Verify_Memory(valueName, expected, actual, size) __Verify_Memory (__FILE__, __LINE__, valueName, expected, actual, size, &__test_results)

#endif // __TEST_UTILITIES_HPP__