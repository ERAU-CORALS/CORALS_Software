#include <Arduino.h>

#include <Matrix.tpp>

#include <CORALS.hpp>

void setup() {
    CORALS::initialize();
}

void loop() {
    CORALS::run();
}