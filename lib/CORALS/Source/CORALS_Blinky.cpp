/**
 ********************************************************************************
 * @file    CORALS_Blinky.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Blinking LED for Activity Indication
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_Blinky.hpp"

#include <Arduino.h>

namespace CORALS {

void Blinky(void) {
#ifdef GIGA_R1_M7

    // Blink LED
    if (digitalRead(PC_13) == HIGH) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
    }

#else // GIGA_R1_M4

    // Blink LED
    if (digitalRead(PC_13) == LOW) {
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
    }

#endif // CPU_TYPE
}

} // end namespace CORALS