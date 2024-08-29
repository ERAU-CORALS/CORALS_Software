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


#include "CORALS_Configuration.hpp"
#include "CORALS_Blinky.hpp"
#include "DataStore.hpp"
#include "StateManager.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;
// ::DataStore::DataStore CORALS_DataStore;

} // end namespace

void initialize() {
    CORALS_OUT_PRINTLN("CORALS Initializing...");

    CORALS_OS.Register("Blinky", Blinky, 1000, ::StateManager::SM_Priority::PRIORITY_HIGHEST);
    
    // Initialize_DataStore();
    // CORALS_OS.Register("DataStore", Run_DataStore, 500, ::StateManager::SM_Priority::PRIORITY_MEDIUM);

    CORALS_OUT_PRINTLN("CORALS Initialized.");
}

void run() {
    CORALS_DEBUG_PRINTLN("CORALS Loop.");

    CORALS_OS.Run();

    if (digitalRead(PC_13) == HIGH) {
        delay(1000);
    }

#ifdef GIGA_R1_M7
    while (SerialRPC.available()) Serial.write(SerialRPC.read());
#endif
}

} // end namespace CORALS