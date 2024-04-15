/**
 ********************************************************************************
 * @file    test.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of Matrix Class
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <unity.h>

#include "vector.hpp"

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(Vector_Constructor);
    RUN_TEST(Vector_MultiVector_Operators);
    RUN_TEST(Vector_MultiVector_Assignment_Operators);
    RUN_TEST(Vector_Element_Operators);
    RUN_TEST(Vector_Element_Assignment_Operators);
    RUN_TEST(Vector_Operations);
    
    UNITY_END();

    return 0;
}