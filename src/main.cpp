#include <Arduino.h>

#include <RPC.h>
#include <SerialRPC.h>

#include "CORALS.hpp"
#include "CORALS_Configuration"

#if ((defined(GIGA_R1_M7) && defined(GIGA_R1_M4)) || \
     (!defined(GIGA_R1_M7) && !defined(GIGA_R1_M4)))
    #error "Environment variables incorrect."
#elif ((defined(GIGA_R1_M7) && defined(CORE_CM4)) || \
       (defined(GIGA_R1_M4) && defined(CORE_CM7)))
    #error "Environment variables mismatch Arduino core."
#endif // CPU_TYPE

void setup_error(String message = "");

void setup() {
    // Serial Initialization
    Serial.begin(115200);
    const unsigned long serial_timer = millis();
    while (!Serial && (millis() - serial_timer < 10000)) continue;
    if (!Serial) {
        setup_error();
    }

    DEBUG_OUT_PRINTLN("Serial initialized for " + CORE_NAME + ".");

    // RPC Initialization
    if (!SerialRPC.begin()) {
        setup_error("Failed to initialize RPC on " + CORE_NAME + ".");
    }

    DEBUG_OUT_PRINTLN("RPC initialized on " + CORE_NAME + ".");

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
    if (message.length() > 0) DEBUG_OUT_PRINTLN(message);

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