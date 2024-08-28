#include <Arduino.h>
#include <stdlib.h>

#include <RPC.h>
#include <SerialRPC.h>

#include "CORALS.hpp"

void setup() {
    CORALS::initialize();
#ifdef GIGA_R1_M7

    Serial.begin(115200);

    // RPC Initialization
    unsigned long RPC_Start = millis();
    while (!RPC.begin() && millis() - RPC_Start < 10000) continue;
    if (!RPC.begin()) {
        Serial.println("Failed to initialize RPC.");
        abort();
    }

    if (RPC.cpu_id() == CM4_CPUID) {
        Serial.println("This sketch is not compatible with the M4 core.");
        abort();
    }

#elif defined(GIGA_R1_M4)

    SerialRPC.begin();

    // RPC Initialization
    unsigned long RPC_Start = millis();
    while (!RPC.begin() && millis() - RPC_Start < 10000) continue;
    if (!RPC.begin()) {
        SerialRPC.println("Failed to initialize RPC.");
        abort();
    }

    if (RPC.cpu_id() == CM7_CPUID) {
        SerialRPC.println("This sketch is not compatible with the M7 core.");
        abort();
    }

#else
    #error "No core defined."
#endif // CPU_TYPE
}

void loop() {
    CORALS::run();
}