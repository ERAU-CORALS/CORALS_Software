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
#include "CORALS_Blinky.hpp"
#include "DataStore.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;

} // end namespace

void initialize() {
    DEBUG_PRINTLN("CORALS Initializing...");

    CORALS_OS.Register("Blinky", Blinky, 1000, ::StateManager::SM_Priority::PRIORITY_HIGHEST);
    
    Initialize_DataStore();
    CORALS_OS.Register("DataStore", Run_DataStore, 500, ::StateManager::SM_Priority::PRIORITY_MEDIUM);

    DEBUG_PRINTLN("CORALS Initialized.");
}

void run() {
    DEBUG_PRINTLN("CORALS Loop.");

    CORALS_OS.Run();
}

} // end namespace CORALS