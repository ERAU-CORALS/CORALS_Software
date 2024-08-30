/**
 ********************************************************************************
 * @file    CORALS_DataStore.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   CORALS DataStore Implementation
 * @version 1.0
 * @date    2024-03-24
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CORALS_DataStore.hpp"

#include "CORALS_Configuration.hpp"
namespace CORALS {

DataStore::DataStore () : ::DataStore::DataStore<DataStore_Keys>() {
    CORALS_DEBUG_PRINTLN("Initializing CORALS DataStore...");

    // Initialize DataStore
    Add_NDO<GainMatrix>(GAIN_MATRIX);
    Add_NDO<TargetList>(TARGET_LIST);
    Add_NDO<Quaternion>(ATTITUDE_QUATERNION);

    const double default_double = 0.0;
    
    Add_NDO<double>(PRIMARY_VOLTAGE, &default_double);
    Add_NDO<double>(SECONDARY_VOLTAGE, &default_double);
    Add_NDO<double>(SINGULARITY_PARAMETER, &default_double);

    CORALS_DEBUG_PRINTLN("CORALS DataStore Initialized.");
}

DataStore::~DataStore () {
    CORALS_DEBUG_PRINTLN("Deinitializing CORALS DataStore...");
    CORALS_DEBUG_PRINTLN("CORALS DataStore Deinitialized.");
}

} // end namespace CORALS