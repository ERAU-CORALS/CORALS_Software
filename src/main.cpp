#include <Arduino.h>
#include <RPC.h>
#include <stdio.h>

#include <CORALS.hpp>

void setup() {
    CORALS::initialize();
#ifdef GIGA_R1_M7
    if (RPC.cpu_id() == CM4_CPUID) {
        error("This sketch is not compatible with the M4 core.");
    }
    RPC.begin();
#elif defined(GIGA_R1_M4)
    if (RPC.cpu_id() == CM7_CPUID) {
        error("This sketch is not compatible with the M7 core.");
    }
#else
    #error "No core defined."
#endif // CPU_TYPE
}

void loop() {
    CORALS::run();
}