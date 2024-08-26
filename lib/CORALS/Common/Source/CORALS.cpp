/**
 ********************************************************************************
 * @file    CORALS.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS Software Core
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS.hpp"

#include <StateManager.hpp>

#include "CORALS_Configuration.hpp"
#include "CORALS_DataStore.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;

} // end namespace

void initialize() {
#ifdef GIGA_R1_M7
    DEBUG_OUT.begin(115200);
    DEBUG_OUT.println("CORALS Initializing...");
#endif // GIGA_R1_M7

    Initialize_DataStore();

#ifdef GIGA_R1_M7
    DEBUG_OUT.println("CORALS Initialized.");
#endif // GIGA_R1_M7
}

void run() {
    CORALS_OS.Run();
}

} // end namespace CORALS