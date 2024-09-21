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

#include "DataStore.tpp"
namespace CORALS {

CORALS_DataStore DataStore;

void DS_Init() {
    CORALS_DEBUG_PRINTLN("Initializing CORALS DataStore...");

    // Initialize DataStore
    // GainMatrix *__Gain_Matrix = new GainMatrix();
    // TargetList *__Target_List = new TargetList();
    // Quaternion *__Quaternion = new Quaternion();

    DataStore.Add_SDO<GainMatrix*>(GAIN_MATRIX);
    DataStore.Add_SDO<TargetList*>(TARGET_LIST);
    DataStore.Add_SDO<Quaternion*>(ATTITUDE_QUATERNION);

    const double default_double = 0.0;
    
    DataStore.Add_SDO<double>(PRIMARY_VOLTAGE, &default_double);
    DataStore.Add_SDO<double>(SECONDARY_VOLTAGE, &default_double);
    DataStore.Add_SDO<double>(SINGULARITY_PARAMETER, &default_double);

    CORALS_DEBUG_PRINTLN("CORALS DataStore Initialized.");
}

} // end namespace CORALS