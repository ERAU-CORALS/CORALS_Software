/**
 ********************************************************************************
 * @file    main.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Main
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <Arduino.h>
#include <SerialRPC.h>

#include "Configuration.hpp"

#include "CORALS.hpp"

void setup_error(String message = "");

void setup() {
    // Serial Initialization
    Serial.begin(115200);
    const unsigned long serial_timer = millis();
    while (!Serial && (millis() - serial_timer < 10000)) continue;
    if (!Serial && DEBUG) {
        setup_error();
    }

    SERIAL_OUT_PRINTLN("Serial initialized for " + CORE_NAME + ".");

    // RPC Initialization
    if (!SerialRPC.begin()) {
        SERIAL_OUT_PRINTLN("Failed to initialize RPC on " + CORE_NAME + ".");
    }

    SERIAL_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");

    // BEGIN CORALS CODE

    CORALS::initialize();

    // END CORALS CODE
}

void loop() {
    // BEGIN CORALS CODE

    CORALS::run();

    // END CORALS CODE
}

void setup_error(String message) {
    if (message.length() > 0) SERIAL_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");
(message);

#ifdef GIGA_R1_M7
    if (digitalRead(PC_13) == LOW) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#elif defined(GIGA_R1_M4)
    if (digitalRead(LEDR) == HIGH) {
        while (true) {
            digitalWrite(LEDR, LOW);
            delay(500);
            digitalWrite(LEDR, HIGH);
            delay(500);
        }
    }
#endif // CPU_TYPE
}