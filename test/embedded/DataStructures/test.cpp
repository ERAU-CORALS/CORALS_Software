/**
 ********************************************************************************
 * @file    matrix.inc
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests of DataStructures
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "vector.hpp"
#include "matrix.hpp"

void setup() {
    Serial.begin(115200);
    delay(3000);
    assert(Serial);

    UNITY_BEGIN();

    Vector_Test();
    Matrix_Test();

    UNITY_END();
}

void loop() {
    while (true) continue;
}