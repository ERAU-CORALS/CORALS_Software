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
#include "CORALS_DataStore.hpp"
#include "CORALS_Telecommunicator.hpp"
#include "StateManager.hpp"

namespace CORALS {

namespace {

::StateManager::StateManager CORALS_OS;
// ::DataStore::DataStore CORALS_DataStore;

} // end namespace

void initialize() {
    CORALS_OUT_PRINTLN("CORALS Initializing...");

    DS_Init();
    TC_Init();

    CORALS_OS.Register("Blinky", Blinky, 1000, ::StateManager::SM_Priority::PRIORITY_HIGHEST);
    
    CORALS_OS.Register("Telecommunicator", TC_Run, 100, ::StateManager::SM_Priority::PRIORITY_MEDIUM);

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
    Serial.flush();
#endif
}

} // end namespace CORALS