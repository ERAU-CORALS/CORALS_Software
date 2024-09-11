/**
 ********************************************************************************
 * @file    CORALS_Telecommunicator.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Telecommunication Manager
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_Telecommunicator.hpp"
#include "CORALS_Configuration.hpp"

#include "Telecommunicator.hpp"

namespace CORALS {

namespace {

::Telecommunication::Telecommunicator CORALS_Telecommunicator;

} // end namespace

void initialize() {
    CORALS_DEBUG_PRINTLN("Initializing CORALS Telecommunicator...");

    // Register Message Handlers

    CORALS_DEBUG_PRINTLN("CORALS Telecommunicator Initialized.");
}

void run() {
    CORALS_Telecommunicator.run();
}

} // end namespace CORALS