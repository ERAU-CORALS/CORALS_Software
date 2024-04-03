#include <Arduino.h>

#include <Tensor.tpp>

#include <CORALS.hpp>

void setup() {
    CORALS::initialize();
}

void loop() {
    CORALS::run();
}